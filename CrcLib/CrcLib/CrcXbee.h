#ifndef CrcXbee_h
#define CrcXbee_h

#include "CrcRemoteState.h"
#include <Arduino.h>
#include <XBee.h>

namespace CrcUtility {
// Maps to each button
enum class BUTTON {
    SELECT,
    START,
    L1,
    R1,
    HATL,
    HATR,
    LOGO,
    ARROW_RIGHT,
    ARROW_UP,
    ARROW_LEFT,
    ARROW_DOWN,
    COLORS_RIGHT,
    COLORS_UP,
    COLORS_LEFT,
    COLORS_DOWN,
    NONE = 255,
};

// Channel mapping for use with readAnalogChannel(uint8_t channel)
enum class ANALOG {
    JOYSTICK1_X,
    JOYSTICK1_Y,
    JOYSTICK2_X,
    JOYSTICK2_Y,
    GACHETTE_L,
    GACHETTE_R,
    NONE = 255,
};

class CrcXbee {
public:
    CrcXbee()                   = default;
    ~CrcXbee()                  = default;
    CrcXbee(const CrcXbee& bee) = default;
    CrcXbee& operator=(const CrcXbee& bee) = default;

    // Reads the boolean value of a button on the remote
    bool ReadDigitalChannel(BUTTON channel) const;

    // Reads the analog (0 to 255) value of a joystick on the remote
    uint8_t ReadAnalogChannel(ANALOG channel) const;

    // Starts the serial channels
    void Initialize(HardwareSerial& stream);

    // Reads the data and saves it to the payload
    void UpdateData(uint8_t batStatus);

    // Return the remote control state (CRConnect)
    RemoteState State();

    // Sets the payload to the default values
    void ResetState();

    // Returns true if communication is currently updating
    bool IsCommValid() const;

private:
    typedef enum {
        BEGIN,
        WAITING,
        RECVONE,
        READY,
    } init_state_t;

    // xBee Object that manages data
    XBee _xbee = XBee();

    // Remote address
    XBeeAddress64 _addr;
    init_state_t _addrInitState;

    // Watchdog and communication timer
    unsigned long _lastUpdate = 0;

    // Send battery status
    unsigned long _lastBatStatus        = 0;
    const unsigned long _batStatusDelay = 5000; // 5s

    // Maximum allowed time to update the payload
    const unsigned long _maxNoUpdateDelay = 500;

    // Value that is true if payload was updated within the last acceptable time
    // frame
    bool _communicationValid = false;

    // Last state of the remote
    RemoteState _state;
};
}

#endif
