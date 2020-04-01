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

void NTP::SendPacket(NtpPacket packet)
{
    udp.beginPacket(_address, port);
    udp.write(ntpPacket, sizeof(ntpPacket));
    udp.endPacket();
}

NtpPacket NtpPacket::ConvertFromBytes(byte *buffer)
{
    NtpPacket packet;
    packet.LI = (buffer[0] >> (8 - 2)) & 0b11;
    packet.VN = (buffer[0] >> (8 - 5)) & 0b111;
    packet.Mode = (buffer[0] >> (8 - 8)) & 0b111;
    packet.Stratum = buffer[1];
    packet.POll = buffer[2];
    packet.Precision = buffer[3];

    for (int cnt = 0; cnt <= 3; cnt++)
    {
        packet.RootDelay += buffer[4 + cnt] << (cnt + 1);
    }
    for (int cnt = 0; cnt <= 3; cnt++)
    {
        packet.RootDispersion += buffer[8 + cnt] << (cnt + 1);
    }
    for (int cnt = 0; cnt <= 3; cnt++)
    {
        packet.ReferenceId += buffer[12 + cnt] << (cnt + 1);
    }
    for (int cnt = 0; cnt <= 7; cnt++)
    {
        packet.ReferenceTimestamp += buffer[16 + cnt] << (cnt + 1);
    }
    for (int cnt = 0; cnt <= 7; cnt++)
    {
        packet.OriginTimestamp += buffer[24 + cnt] << (cnt + 1);
    }
    for (int cnt = 0; cnt <= 7; cnt++)
    {
        packet.ReceiveTimestamp += buffer[32 + cnt] << (cnt + 1);
    }
    for (int cnt = 0; cnt <= 7; cnt++)
    {
        packet.TransmitTimestamp += buffer[40 + cnt] << (cnt + 1);
    }
    
    return packet;
}

byte *NtpPacket::ConvertToBytes(NtpPacket packet)
{
    byte buffer[48];
    buffer[0] = packet.LI;
    buffer[0] = buffer[0] << 3 + packet.VN;
    buffer[0] = buffer[0] << 3 + packet.Mode;
    buffer[1] = packet.Stratum;
    buffer[2] = packet.POll;
    buffer[3] = packet.Precision;

    for (int cnt = 0; cnt <= 3; cnt++)
    {
        buffer[4 + cnt] = packet.RootDelay >> (8 * (3 - cnt));
    }
    for (int cnt = 0; cnt <= 3; cnt++)
    {
        buffer[8 + cnt] = packet.RootDispersion >> (8 * (3 - cnt));
    }
    for (int cnt = 0; cnt <= 3; cnt++)
    {
        buffer[12 + cnt] = packet.ReferenceId >> (8 * (3 - cnt));
    }
    for (int cnt = 0; cnt <= 7; cnt++)
    {
        buffer[16 + cnt] = packet.ReferenceTimestamp >> (8 * (7 - cnt));
    }
    for (int cnt = 0; cnt <= 7; cnt++)
    {
        buffer[24 + cnt] = packet.OriginTimestamp >> (8 * (7 - cnt));
    }
    for (int cnt = 0; cnt <= 7; cnt++)
    {
        buffer[32 + cnt] = packet.ReceiveTimestamp >> (8 * (7 - cnt));
    }
    for (int cnt = 0; cnt <= 7; cnt++)
    {
        buffer[40 + cnt] = packet.TransmitTimestamp >> (8 * (7 - cnt));
    }

    return buffer;
}