#ifndef CrcNeo_h
#define CrcNeo_h

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

namespace CrcUtility {
#define NO_PATTERN 255
#define PATTERN_TEST 0
#define PATTERN_FASTCHRISTMAS 1
#define PATTERN_BLINDINGDANGER 2
#define PATTERN_STARTUP 3
#define PATTERN_CONNECTED 4
#define PATTERN_DISCONNECTED 5
#define PATTERN_ERROR1 6
#define PATTERN_ERROR2 7
#define PATTERN_ERROR3 8
#define PATTERN_ERROR4 9

class CrcNeo {
public:
    CrcNeo(unsigned char pin)
        : _neoPin(pin)
        , _pixel(Adafruit_NeoPixel(1, pin, NEO_GRB + NEO_KHZ800))
    {
    }
    ~CrcNeo() = default;

    void Initialize();

    void SetColor(unsigned char r, unsigned char g, unsigned char b);

    void Update(unsigned int delta);

    void StartPattern(unsigned char pattern, bool repeat);

private:
    struct Color {
        unsigned char r;
        unsigned char g;
        unsigned char b;
    };

    struct ColorDuration {
        Color col;
        int dur;
    };

    void SetColor(Color col);

    struct ColorDuration* GetColorDuration(unsigned char pattern);

    long GetDurationMicros();

    unsigned char _currentPattern;
    int _currentIndex;

    bool _repeatPattern;

    long _currentCount;

    unsigned char _neoPin;

    Adafruit_NeoPixel _pixel;

    Color _noColor = { 0, 0, 0 };

    Color _red_high     = { 255, 0, 0 };
    Color _green_high   = { 0, 255, 0 };
    Color _blue_high    = { 0, 0, 255 };
    Color _yellow_high  = { 255, 255, 0 };
    Color _cyan_high    = { 0, 255, 255 };
    Color _magenta_high = { 255, 0, 255 };
    Color _white_high   = { 255, 255, 255 };

    Color _orange_high = { 255, 128, 0 };

    Color _red_low     = { 25, 0, 0 };
    Color _green_low   = { 0, 25, 0 };
    Color _blue_low    = { 0, 0, 25 };
    Color _yellow_low  = { 25, 25, 0 };
    Color _cyan_low    = { 0, 25, 25 };
    Color _magenta_low = { 25, 0, 25 };
    Color _white_low   = { 25, 25, 25 };

    // Sentinel for the end of arrays
    ColorDuration _sentinelColDur = { _noColor, -1 };

    // Pattern 0
    ColorDuration _lightPattern_TestBlink[19] = { { _red_low, 250 },
        { _noColor, 250 }, { _red_low, 250 }, { _noColor, 250 },
        { _red_low, 250 }, { _noColor, 500 }, { _green_low, 750 },
        { _noColor, 250 }, { _green_low, 750 }, { _noColor, 250 },
        { _green_low, 750 }, { _noColor, 500 }, { _blue_low, 250 },
        { _noColor, 250 }, { _blue_low, 250 }, { _noColor, 250 },
        { _blue_low, 250 }, { _noColor, 500 }, _sentinelColDur };

    // Pattern 1
    ColorDuration _lightPattern_FastChristmas[3]
        = { { _red_low, 100 }, { _green_low, 100 }, _sentinelColDur };

    // Pattern 2
    ColorDuration _lightPattern_BlindingDanger[7] = { { _yellow_high, 200 },
        { _noColor, 500 }, { _yellow_high, 100 }, { _noColor, 100 },
        { _yellow_high, 100 }, { _noColor, 500 }, _sentinelColDur };

    // Pattern 3
    ColorDuration _lightPattern_Startup[8]
        = { { _red_high, 500 }, { _green_high, 500 }, { _blue_high, 500 },
              { _yellow_high, 500 }, { _cyan_high, 500 },
              { _magenta_high, 500 }, { _white_high, 500 }, _sentinelColDur };

    // Pattern 4
    ColorDuration _lightPattern_Connected[7] = { { _cyan_high, 100 },
        { _noColor, 100 }, { _cyan_high, 100 }, { _noColor, 100 },
        { _cyan_high, 100 }, { _noColor, 500 }, _sentinelColDur };

    // Pattern 5
    ColorDuration _lightPattern_Disconnected[7] = { { _orange_high, 100 },
        { _noColor, 100 }, { _orange_high, 100 }, { _noColor, 100 },
        { _orange_high, 100 }, { _noColor, 500 }, _sentinelColDur };

    // Pattern 6
    ColorDuration _lightPattern_ErrorPattern1[7] = { { _red_low, 150 },
        { _noColor, 150 }, { _red_low, 150 }, { _noColor, 150 },
        { _yellow_low, 400 }, { _noColor, 2000 }, _sentinelColDur };

    // Pattern 7
    ColorDuration _lightPattern_ErrorPattern2[7] = { { _magenta_low, 150 },
        { _noColor, 150 }, { _cyan_low, 150 }, { _noColor, 150 },
        { _magenta_low, 150 }, { _noColor, 2000 }, _sentinelColDur };

    // Pattern 8
    ColorDuration _lightPattern_ErrorPattern3[5]
        = { { _cyan_low, 400 }, { _noColor, 150 }, { _red_low, 400 },
              { _noColor, 2000 }, _sentinelColDur };

    // Pattern 9
    ColorDuration _lightPattern_ErrorPattern4[5]
        = { { _yellow_low, 150 }, { _noColor, 150 }, { _magenta_low, 400 },
              { _noColor, 2000 }, _sentinelColDur };
};
}
#endif
