#ifndef PUREDATAOSCCONTROLLER_H
#define PUREDATAOSCCONTROLLER_H
#include <QString>
#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"
#define ADDRESS "127.0.0.1"
#define PORT 7000

#define OUTPUT_BUFFER_SIZE 1024

class PureDataOSCController
{
public:
    PureDataOSCController();
    void sendOSC(QString route, float value);
};

#endif // PUREDATAOSCCONTROLLER_H
