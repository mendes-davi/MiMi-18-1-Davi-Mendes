#ifndef MAX30100_BEATDETECTOR_H_
#define MAX30100_BEATDETECTOR_H_

#include <stdint.h>

#define BEATDETECTOR_INIT_HOLDOFF                2000    // in ms, how long to wait before counting
#define BEATDETECTOR_MASKING_HOLDOFF             200     // in ms, non-retriggerable window after beat detection
#define BEATDETECTOR_BPFILTER_ALPHA              0.6     // EMA factor for the beat period value
#define BEATDETECTOR_MIN_THRESHOLD               20      // minimum threshold (filtered) value
#define BEATDETECTOR_MAX_THRESHOLD               1200     // maximum threshold (filtered) value
#define BEATDETECTOR_STEP_RESILIENCY             30      // maximum negative jump that triggers the beat edge
#define BEATDETECTOR_THRESHOLD_FALLOFF_TARGET    0.3     // thr chasing factor of the max value when beat
#define BEATDETECTOR_THRESHOLD_DECAY_FACTOR      0.99    // thr chasing factor when no beat
#define BEATDETECTOR_INVALID_READOUT_DELAY       2000    // in ms, no-beat time to cause a reset
#define BEATDETECTOR_SAMPLES_PERIOD              10      // in ms, 1/Fs


typedef enum BeatDetectorState {
    BEATDETECTOR_STATE_INIT,
    BEATDETECTOR_STATE_WAITING,
    BEATDETECTOR_STATE_FOLLOWING_SLOPE,
    BEATDETECTOR_STATE_MAYBE_DETECTED,
    BEATDETECTOR_STATE_MASKING
} BeatDetectorState;

bool beatDetectorAddSample(float sample);
float beatDetectorGetRate();
float beatDetectorGetCurrentThreshold();
bool beatDetectorCheckForBeat(float value);
void beatDetectorDecreaseThreshold();

BeatDetectorState stateBeat = BEATDETECTOR_STATE_INIT;
float threshold = BEATDETECTOR_MIN_THRESHOLD;
float beatPeriod = 0;
float lastMaxValue = 0;
uint32_t tsLastBeat = 0;

#endif /* MAX30100_BEATDETECTOR_H_ */
