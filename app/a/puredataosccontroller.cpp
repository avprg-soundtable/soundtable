#include "puredataosccontroller.h"

PureDataOSCController::PureDataOSCController()
{
}

void PureDataOSCController::sendOSC(sting route, float value){
    UdpTransmitSocket transmitSocket( IpEndpointName( ADDRESS, PORT ) );
    char buffer[OUTPUT_BUFFER_SIZE];
    osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );

    p << osc::BeginBundleImmediate
        << osc::BeginMessage( "/test" )
            << value << osc::EndMessage
            << osc::BeginMessage( "/test/test2" )
                << value+100 << osc::EndMessage
                << osc::BeginMessage( "/test/test3" )
                    << value+1000 << osc::EndMessage
        << osc::EndBundle;

    transmitSocket.Send( p.Data(), p.Size() );

}
