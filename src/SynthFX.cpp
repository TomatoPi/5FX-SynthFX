#include <5FX/jackwrap.hpp>

#include <jack/jack.h>
#include <jack/midiport.h>

#include <signal.h>

#include <thread>
#include <chrono>
#include <atomic>

sfx::jack::Client client;
jack_port_t* midi_in = nullptr;
jack_port_t* out_1 = nullptr;
jack_port_t* out_2 = nullptr;

std::atomic_flag run;

static int jack_callback(jack_nframes_t nframes, void* args) {

  return 0;
}

void sigkill(int) {
  run.clear();
}

int main(int argc, char const* argv[]) {

  signal(SIGTERM, sigkill);

  client.open(
    "5FX-SynthFX",
    {
      {&midi_in, "midi_in", JACK_DEFAULT_MIDI_TYPE, JackPortIsInput},
      {&out_1, "out_1", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput},
      {&out_2, "out_2", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput}
    },
    jack_callback);
  client.activate();

  run.test_and_set();
  do {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  } while (run.test_and_set());

  return 0;
}
