#include <Arduino.h>
#include <WiFiUdp.h>
#include <IPAddress.h>

class NTP
{
private:
    IPAddress _address;
    WiFiUDP udp;
    const int port = 123;
    byte ntpPacket[48];

public:
    void SendTimeReq();

    NTP(IPAddress addr);
    ~NTP();
};

typedef struct NtpPacket
{
    int LI; //2
    int VN;
    int Mode;
    int Stratum;
    int POll;
    int Precision;
    uint32_t RootDelay;
    uint32_t RootDispersion;
    uint32_t ReferenceId;
    uint64_t ReferenceTimestamp;
    uint64_t OriginTimestamp;
    uint64_t ReceiveTimestamp;
    uint64_t TransmitTimestamp;

    static NtpPacket ParseFromBytes();
    static byte *ParseToBytes();
};
