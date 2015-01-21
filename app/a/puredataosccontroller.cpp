#include "puredataosccontroller.h"

PureDataOSCController::PureDataOSCController()
{
}

void PureDataOSCController::sendOSC(QString route, float value){
    UdpTransmitSocket transmitSocket( IpEndpointName( ADDRESS, PORT ) );
    char buffer[OUTPUT_BUFFER_SIZE];
    osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );

    p << osc::BeginBundleImmediate
        << osc::BeginMessage( route.toUtf8().constData() )
            << value << osc::EndMessage
        << osc::EndBundle;

    transmitSocket.Send( p.Data(), p.Size() );

}
