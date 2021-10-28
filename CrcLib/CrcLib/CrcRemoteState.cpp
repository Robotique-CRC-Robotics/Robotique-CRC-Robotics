#include "CrcRemoteState.h"

namespace CrcUtility {
uint8_t RemoteState::serialize_update(
    uint8_t* buf, bool keyframe, RemoteState& prev)
{
    uint8_t len = 1;
    if (prev.gachetteG != gachetteG || keyframe) {
        buf[0] |= 1;
        buf[len++] = gachetteG;
    }
    if (prev.gachetteD != gachetteD || keyframe) {
        buf[0] |= 2;
        buf[len++] = gachetteD;
    }
    if (prev.joystick1X != joystick1X || prev.joystick1Y != joystick1Y
        || keyframe) {
        buf[0] |= 4;
        buf[len++] = joystick1X;
        buf[len++] = joystick1Y;
    }
    if (prev.joystick2X != joystick2X || prev.joystick2Y != joystick2Y
        || keyframe) {
        buf[0] |= 8;
        buf[len++] = joystick2X;
        buf[len++] = joystick2Y;
    }
    uint8_t prev_but1 = prev.serialize_button_bank1();
    uint8_t but1      = serialize_button_bank1();
    if (prev_but1 != but1 || keyframe) {
        buf[0] |= 16;
        buf[len++] = but1;
    }
    uint8_t prev_but2 = prev.serialize_button_bank2();
    uint8_t but2      = serialize_button_bank2();
    if (prev_but2 != but2 || keyframe) {
        buf[0] |= 32;
        buf[len++] = but2;
    }
    return len;
}

uint8_t RemoteState::serialize_button_bank1()
{
    uint8_t val = 0;
    val |= arrowRight;
    val |= arrowUp << 1;
    val |= arrowLeft << 2;
    val |= arrowDown << 3;
    val |= colorRight << 4;
    val |= colorUp << 5;
    val |= colorLeft << 6;
    val |= colorDown << 7;
    return val;
}

uint8_t RemoteState::serialize_button_bank2()
{
    uint8_t val = 0;
    val |= L1;
    val |= R1 << 1;
    val |= select << 2;
    val |= start << 3;
    val |= logo << 4;
    val |= hatL << 5;
    val |= hatR << 6;
    return val;
}

void RemoteState::deserialize_update(uint8_t* payload)
{
    uint8_t len = 0;
    if (payload[0] & 1) {
        gachetteG = payload[++len];
    }
    if (payload[0] & 2) {
        gachetteD = payload[++len];
    }
    if (payload[0] & 4) {
        joystick1X = payload[++len];
        joystick1Y = payload[++len];
    }
    if (payload[0] & 8) {
        joystick2X = payload[++len];
        joystick2Y = payload[++len];
    }
    if (payload[0] & 16) {
        uint8_t b  = payload[++len];
        arrowRight = b & 1;
        arrowUp    = (b >> 1) & 1;
        arrowLeft  = (b >> 2) & 1;
        arrowDown  = (b >> 3) & 1;
        colorRight = (b >> 4) & 1;
        colorUp    = (b >> 5) & 1;
        colorLeft  = (b >> 6) & 1;
        colorDown  = (b >> 7) & 1;
    }
    if (payload[0] & 32) {
        uint8_t b = payload[++len];
        L1        = b & 1;
        R1        = (b >> 1) & 1;
        select    = (b >> 2) & 1;
        start     = (b >> 3) & 1;
        logo      = (b >> 4) & 1;
        hatL      = (b >> 5) & 1;
        hatR      = (b >> 6) & 1;
    }
}

void RemoteState::PrintPayload()
{
    PRINT("Arrows:");
    if (arrowUp) {
        PRINT(" UP");
    }
    if (arrowRight) {
        PRINT(" RIGHT");
    }
    if (arrowDown) {
        PRINT(" DOWN");
    }
    if (arrowLeft) {
        PRINT(" LEFT");
    }
    PRINT(", colors:");
    if (colorUp) {
        PRINT(" UP");
    }
    if (colorRight) {
        PRINT(" RIGHT");
    }
    if (colorDown) {
        PRINT(" DOWN");
    }
    if (colorLeft) {
        PRINT(" LEFT");
    }
    PRINT(", L1: ");
    PRINT(L1);
    PRINT(", R1: ");
    PRINT(R1);
    PRINT(", select: ");
    PRINT(select);
    PRINT(", start: ");
    PRINT(start);
    PRINT(", logo: ");
    PRINT(logo);
    PRINT(", hatL: ");
    PRINT(hatL);
    PRINT(", hatR: ");
    PRINT(hatR);
    PRINT(", left trigger: ");
    PRINT(gachetteG);
    PRINT(", right trigger: ");
    PRINT(gachetteD);
    PRINT(", left X: ");
    PRINT(joystick1X);
    PRINT(", left Y: ");
    PRINT(joystick1Y);
    PRINT(", right X: ");
    PRINT(joystick2X);
    PRINT(", right Y: ");
    PRINT(joystick2Y);
    PRINT("\n");
}
}
