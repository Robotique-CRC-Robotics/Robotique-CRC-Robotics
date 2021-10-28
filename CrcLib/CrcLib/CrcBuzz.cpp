#include "CrcBuzz.h"

namespace CrcUtility {
void CrcBuzz::Initialize(unsigned char pin, bool start_tune)
{
    _buzzPin = pin;
    pinMode(_buzzPin, OUTPUT);

    if (start_tune) {
        StartTune(TUNE_METRO, false);
    }
}

void CrcBuzz::StartTune(unsigned char tune, bool repeat)
{
    _currentTune  = tune;
    _repeatTune   = repeat;
    _currentCount = 0;
    _currentIndex = 0;

    SetTone(GetNote(_currentIndex)->pitch);
}

void CrcBuzz::Update(unsigned int delta)
{
    if (_currentTune == NO_TUNE) {
        return;
    }

    _currentCount += delta;

    long dur = GetDurationMicros();

    if (_currentCount > dur) {
        _currentCount -= dur;
        _currentIndex++;

        // Check if we've reached the sentinel value
        if (GetNote(_currentTune)->dur < 0) {
            if (_repeatTune) {
                _currentIndex = 0;
            } else {
                _currentTune = NO_TUNE;
                SetTone(NOTE_SILENCE);
                return;
            }
        }

        SetTone(GetNote(_currentTune)->pitch);
    }
}

void CrcBuzz::SetTone(unsigned int pitch)
{
    noTone(_buzzPin);
    if (pitch != NOTE_SILENCE)
        tone(_buzzPin, pitch);
}

struct CrcBuzz::Note* CrcBuzz::GetNote(unsigned char tune)
{
    if (tune == TUNE_TEST)
        return &(_tune_test[_currentIndex]);
    else if (tune == TUNE_METRO)
        return &(_tune_metro[_currentIndex]);
    else if (tune == TUNE_CONNECTED)
        return &(_tune_connected[_currentIndex]);
    else if (tune == TUNE_DISCONNECTED)
        return &(_tune_disconnected[_currentIndex]);
    else if (tune == TUNE_PIN_ERROR)
        return &(_tune_pinError[_currentIndex]);
    else if (tune == TUNE_SPARE)
        return &(_tune_bindingError[_currentIndex]);
    else if (tune == TUNE_VALUE_ERROR)
        return &(_tune_valueError[_currentIndex]);
    else if (tune == TUNE_SERVO_ERROR)
        return &(_tune_servoError[_currentIndex]);
    else
        return nullptr;
}

long CrcBuzz::GetDurationMicros()
{
    return (static_cast<long>(GetNote(_currentTune)->dur)) * 1000;
}
}
