#include <sys/types.h>
#include <arpa/inet.h>

#define ETHERSIZE 14 //Ethernet basic size
#define IPTYPE 0x0800 //IPv4 Hextype
#define TCPTYPE 0x06 //TCP Hextype

typedef struct Ethernet{
    u_char destmac[6]; //6bytes
    u_char srcmac[6]; //6bytes
    u_short ethertype; //2bytes
}Etherheader;

typedef struct IP{
    u_char headerlen:4; //4bit
    u_char ver:4; //4bit
    u_char srvtype;
    u_short totallen;
    u_short id;
    u_short flags;
    u_char ttl;
    u_char protocol;
    u_short headerchecksum;
    u_char srcIP[4];
    u_char destIP[4];
}IPheader;


typedef struct TCP{
    u_short srcport;
    u_short destPort;
    u_int seqnum;
    u_int acknum;
    u_char reserv:4; //4bit
    u_char headerlen:4; //4bit
    u_char flag;
    u_short winsize;
    u_short checksum;
    u_short urgent;
}TCPheader;

typedef struct Packet{
    Etherheader *etherheader;
    IPheader *ipheader;
    TCPheader *tcpheader;
    int datalen;
    const u_char *data;
}Packetdata;

void print_Data(Packetdata packetdata);

Packetdata Packetlen(const u_char *packetIn);
