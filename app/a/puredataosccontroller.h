#ifndef PUREDATAOSCCONTROLLER_H
#define PUREDATAOSCCONTROLLER_H

#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"
#define ADDRESS "192.168.178.47"
#define PORT 7000

#define OUTPUT_BUFFER_SIZE 1024

class PureDataOSCController
{
public:
    PureDataOSCController();
    void sendOSC(sting route, float value);
};

#endif // PUREDATAOSCCONTROLLER_H
