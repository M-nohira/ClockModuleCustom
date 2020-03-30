#include "NTP.h"

NTP::NTP(IPAddress addr)
{
    _address = addr;
    udp = WiFiUDP();
    udp.begin(port);
}

NTP::~NTP()
{
    udp.stop();
}

void NTP::SendTimeReq()
{
    udp.beginPacket(address,port);
    udp.write();
    udp.endPacket();
}