#include "CrcXbee.h"

namespace CrcUtility {

bool CrcXbee::ReadDigitalChannel(BUTTON channel) const
{
    switch (channel) {
    case BUTTON::ARROW_RIGHT: return _state.arrowRight;
    case BUTTON::ARROW_UP: return _state.arrowUp;
    case BUTTON::ARROW_LEFT: return _state.arrowLeft;
    case BUTTON::ARROW_DOWN: return _state.arrowDown;
    case BUTTON::COLORS_RIGHT: return _state.colorRight;
    case BUTTON::COLORS_UP: return _state.colorUp;
    case BUTTON::COLORS_LEFT: return _state.colorLeft;
    case BUTTON::COLORS_DOWN: return _state.colorDown;
    case BUTTON::L1: return _state.L1;
    case BUTTON::R1: return _state.R1;
    case BUTTON::SELECT: return _state.select;
    case BUTTON::START: return _state.start;
    case BUTTON::LOGO: return _state.logo;
    case BUTTON::HATL: return _state.hatL;
    case BUTTON::HATR: return _state.hatR;
    case BUTTON::NONE: return 0;
    }
}

uint8_t CrcXbee::ReadAnalogChannel(ANALOG channel) const
{
    switch (channel) {
    case ANALOG::JOYSTICK1_X: return _state.joystick1X;
    case ANALOG::JOYSTICK1_Y: return _state.joystick1Y;
    case ANALOG::JOYSTICK2_X: return _state.joystick2X;
    case ANALOG::JOYSTICK2_Y: return _state.joystick2Y;
    case ANALOG::GACHETTE_R: return _state.gachetteD;
    case ANALOG::GACHETTE_L: return _state.gachetteG;
    case ANALOG::NONE: return 0;
    }
}

void CrcXbee::Initialize(HardwareSerial& serial)
{
    serial.begin(9600);
    _xbee.setSerial(serial);
}

void CrcXbee::UpdateData(uint8_t batStatus)
{
    _xbee.readPacket();
    XBeeResponse resp = _xbee.getResponse();
    unsigned long now = millis();

    if (resp.isAvailable()) {
        // Serial.println("Packet available");
        if (resp.getApiId() == ZB_RX_RESPONSE) {
            ZBRxResponse rx = ZBRxResponse();
            resp.getZBRxResponse(rx);
            _state.deserialize_update(rx.getData());
            _lastUpdate         = millis();
            _communicationValid = true;
        } else if (resp.getApiId() == AtCommandResponse::API_ID) {
            AtCommandResponse rx;
            resp.getAtCommandResponse(rx);
            if (!rx.isOk())
                return;
            if (rx.getCommand()[0] != 'D' || rx.getValueLength() != 4)
                return;
            uint32_t val = ((uint32_t)rx.getValue()[0] << 24)
                | ((uint32_t)rx.getValue()[1] << 16)
                | ((uint32_t)rx.getValue()[2] << 8)
                | ((uint32_t)rx.getValue()[3]);
            if (rx.getCommand()[1] == 'H') {
                _addr.setMsb(val);
            } else if (rx.getCommand()[1] == 'L') {
                _addr.setLsb(val);
            } else {
                return;
            }
            if (_addrInitState == WAITING) {
                _addrInitState = RECVONE;
                // Send battery status right away after disconnect
                _lastBatStatus = now - _batStatusDelay - 1;
            } else {
                _addrInitState = READY;
            }
        }
    } else if (resp.isError()) {
        Serial.print("Error: ");
        Serial.println(resp.getErrorCode());
    } else if ((unsigned long)(now - _lastUpdate) > _maxNoUpdateDelay) {
        // rx.reset();
        ResetState();
        _communicationValid = false;
    }

    if (now - _lastBatStatus > _batStatusDelay) {
        _lastBatStatus = now;
        if (_addrInitState == READY /*&& _communicationValid*/) {
            ZBTxRequest req = ZBTxRequest(_addr, &batStatus, 1);
            _xbee.send(req);
        } else if (_addrInitState == BEGIN) {
            // Send address requests
            AtCommandRequest req = AtCommandRequest((uint8_t*)"DH");
            _xbee.send(req);
            req = AtCommandRequest((uint8_t*)"DL");
            _xbee.send(req);
            _addrInitState = WAITING;
        }
    }

    // Remove once running correctly
    // PrintPayload();
}

RemoteState CrcXbee::State() { return _state; }

void CrcXbee::ResetState()
{
    _state     = { };
    // Init to midpoint
    _state.joystick1X = 128;
    _state.joystick1Y = 128;
    _state.joystick2X = 128;
    _state.joystick2Y = 128;
}

bool CrcXbee::IsCommValid() const { return _communicationValid; }
}
