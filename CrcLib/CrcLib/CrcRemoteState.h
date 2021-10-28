#ifndef CrcRemoteState_h
#define CrcRemoteState_h
#ifdef MAIN_TEST
#include <cstdint>

#include <stdio.h>
#define PRINT printf
#else
#include <Arduino.h>
#define PRINT Serial.print
#endif

namespace CrcUtility {
class RemoteState {
private:
    uint8_t serialize_button_bank1();
    uint8_t serialize_button_bank2();

public:
    uint8_t joystick1X;
    uint8_t joystick1Y;
    uint8_t joystick2X;
    uint8_t joystick2Y;

    uint8_t gachetteG;
    uint8_t gachetteD;

    bool arrowRight;
    bool arrowUp;
    bool arrowLeft;
    bool arrowDown;
    bool colorRight;
    bool colorUp;
    bool colorLeft;
    bool colorDown;
    bool L1;
    bool R1;
    bool select;
    bool start;
    bool logo; // PS button on PS3/4, XBox button on XBox One, etc.
    bool hatL; // hat = pression sur joystick
    bool hatR;

    uint8_t serialize_update(uint8_t* buf, bool keyframe, RemoteState& prev);
    void deserialize_update(uint8_t* buf);
    // Function that prints to the serial port the current state of the payload
    // For Debugging purposes only
    // Remove from your code for release
    void PrintPayload();
};
}

#endif // CrcRemoteState_h
