#include <pcap.h>
#include <stdio.h>

//struct ether{
//    unsigned char ether[5]; //dest, source packet 6byte
//};

struct etherheader{
//    struct ether etherdest; //ethernet destination xx:xx:xx:xx:xx:xx
//    struct ether ethersource; //ethernet source xx:xx:xx:xx:xx:xx
    unsigned char etherdest:6;
    unsigned char ethersource:6;
    unsigned short etherver; //ethernet ipver 4 or 6 2byte
};

//struct ipaddress{
//    unsigned char sourceip[3];
//    unsigned char destination[3];
//};

struct ipheader{
    unsigned char ipver; //ipheader ipver check 4 or 6 1byte
    unsigned char ipprotocol; //ip protocol 1byte
    //struct ipaddress sourceip;
    //struct ipaddress destination;
    unsigned char ipsource:4;
    unsigned char ipdest:4;
};
struct tcpheader{
    unsigned char sourceport:2;
    unsigned char destport:2;

};

void usage() {
  printf("syntax: pcap_test <interface>\n");
  printf("sample: pcap_test wlan0\n");
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    usage();
    return -1;
  }

  char* dev = argv[1];
  char errbuf[PCAP_ERRBUF_SIZE];
  pcap_t* handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
  if (handle == NULL) {
    fprintf(stderr, "couldn't open device %s: %s\n", dev, errbuf);
    return -1;
  }

  while (true) {
    struct pcap_pkthdr* header;
    const u_char* packet;
    int res = pcap_next_ex(handle, &header, &packet);
    if (res == 0) continue;
    if (res == -1 || res == -2) break;
    printf("%u bytes captured\n", header->caplen);
    printf("%02x %02x %02x %02x %02x %02x\n",packet[0],packet[1],packet[2],packet[3],packet[4],packet[5]);
    printf("");
  }

  pcap_close(handle);
  return 0;
}
