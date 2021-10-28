#include "CrcNeo.h"

namespace CrcUtility {

void CrcNeo::Initialize()
{
    pinMode(_neoPin, OUTPUT);

    _pixel.begin();
    _pixel.show();

    _currentPattern = NO_PATTERN;

    StartPattern(PATTERN_STARTUP, false);
}

void CrcNeo::SetColor(unsigned char r, unsigned char g, unsigned char b)
{
    _pixel.setPixelColor(0, r, g, b);
    _pixel.show();
}

void CrcNeo::SetColor(Color col) { SetColor(col.r, col.g, col.b); }

void CrcNeo::StartPattern(unsigned char pattern, bool repeat)
{
    _currentPattern = pattern;
    _repeatPattern  = repeat;
    _currentCount   = 0;
    _currentIndex   = 0;
}

void CrcNeo::Update(unsigned int delta)
{
    if (_currentPattern == NO_PATTERN) {
        return;
    }

    _currentCount += delta;

    long dur = GetDurationMicros();

    if (_currentCount > dur) {
        _currentCount -= dur;
        _currentIndex++;

        // Check if we've reached the sentinel value
        if (GetColorDuration(_currentPattern)->dur < 0) {
            if (_repeatPattern) {
                _currentIndex = 0;
            } else {
                _currentPattern = NO_PATTERN;
                SetColor(_noColor);
                return;
            }
        }
    }

    SetColor(GetColorDuration(_currentPattern)->col);
}

struct CrcNeo::ColorDuration* CrcNeo::GetColorDuration(unsigned char pattern)
{
    if (pattern == PATTERN_TEST)
        return &(_lightPattern_TestBlink[_currentIndex]);
    else if (pattern == PATTERN_FASTCHRISTMAS)
        return &(_lightPattern_FastChristmas[_currentIndex]);
    else if (pattern == PATTERN_BLINDINGDANGER)
        return &(_lightPattern_BlindingDanger[_currentIndex]);
    else if (pattern == PATTERN_STARTUP)
        return &(_lightPattern_Startup[_currentIndex]);
    else if (pattern == PATTERN_CONNECTED)
        return &(_lightPattern_Connected[_currentIndex]);
    else if (pattern == PATTERN_DISCONNECTED)
        return &(_lightPattern_Disconnected[_currentIndex]);
    else if (pattern == PATTERN_ERROR1)
        return &(_lightPattern_ErrorPattern1[_currentIndex]);
    else if (pattern == PATTERN_ERROR2)
        return &(_lightPattern_ErrorPattern2[_currentIndex]);
    else if (pattern == PATTERN_ERROR3)
        return &(_lightPattern_ErrorPattern3[_currentIndex]);
    else if (pattern == PATTERN_ERROR4)
        return &(_lightPattern_ErrorPattern4[_currentIndex]);
    else
        return nullptr;
}

long CrcNeo::GetDurationMicros()
{
    return (static_cast<long>(GetColorDuration(_currentPattern)->dur)) * 1000;
}
}
