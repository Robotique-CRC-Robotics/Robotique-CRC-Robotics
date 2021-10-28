#ifndef CrcBuzz_h
#define CrcBuzz_h

#include <Arduino.h>

namespace CrcUtility {
#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978

#define NO_TUNE 255
#define TUNE_TEST 0
#define TUNE_METRO 1
#define TUNE_CONNECTED 2
#define TUNE_DISCONNECTED 3
#define TUNE_PIN_ERROR 4
#define TUNE_SPARE 5
#define TUNE_VALUE_ERROR 6
#define TUNE_SERVO_ERROR 7

#define NOTE_SILENCE 0

class CrcBuzz {
public:
    CrcBuzz()  = default;
    ~CrcBuzz() = default;

    void Initialize(unsigned char pin, bool start_tune);

    void Update(unsigned int delta);

    void StartTune(unsigned char tune, bool repeat);

private:
    struct Note {
        unsigned int pitch;
        int dur;
    };

    Note* GetNote(unsigned char tune);

    void SetTone(unsigned int pitch);

    long GetDurationMicros();

    unsigned char _currentTune = NO_TUNE;

    int _currentIndex;

    bool _repeatTune;

    long _currentCount;

    unsigned char _buzzPin;

    Note _sentinelNote = { 0, -1 };

    // Tune 0
    Note _tune_test[8] = { { 110, 250 }, { 220, 250 }, { NOTE_SILENCE, 125 },
        { 392, 125 }, { NOTE_SILENCE, 125 }, { 294, 125 },
        { NOTE_SILENCE, 2000 }, _sentinelNote };

    // Tune 1
    Note _tune_metro[4] = { { NOTE_FS4, 500 }, { NOTE_B4, 500 },
        { NOTE_FS5, 800 }, _sentinelNote };

    // Tune 2
    Note _tune_connected[7]
        = { { NOTE_C4, 75 }, { NOTE_G4, 75 }, { NOTE_C5, 75 }, { NOTE_D4, 75 },
              { NOTE_A4, 75 }, { NOTE_D5, 75 }, _sentinelNote };

    // Tune 3
    Note _tune_disconnected[3]
        = { { NOTE_C3, 200 }, { NOTE_FS2, 200 }, _sentinelNote };

    // Tune 4
    Note _tune_pinError[6]
        = { { NOTE_D4, 150 }, { NOTE_D3, 150 }, { NOTE_D4, 150 },
              { NOTE_D3, 150 }, { NOTE_SILENCE, 2000 }, _sentinelNote };

    // Tune 5
    Note _tune_bindingError[9]
        = { { NOTE_D3, 100 }, { NOTE_SILENCE, 50 }, { NOTE_D3, 100 },
              { NOTE_SILENCE, 50 }, { NOTE_D3, 100 }, { NOTE_SILENCE, 50 },
              { NOTE_A3, 100 }, { NOTE_SILENCE, 2000 }, _sentinelNote };

    // Tune 6
    Note _tune_valueError[5] = { { NOTE_D3, 150 }, { NOTE_D4, 150 },
        { NOTE_A3, 150 }, { NOTE_SILENCE, 2000 }, _sentinelNote };

    // Tune 7
    Note _tune_servoError[7] = { { NOTE_D4, 100 }, { NOTE_SILENCE, 50 },
        { NOTE_D4, 150 }, { NOTE_D3, 150 }, { NOTE_A3, 150 },
        { NOTE_SILENCE, 2000 }, _sentinelNote };
};
}
#endif
