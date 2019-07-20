#include "packetdata.h"
#include <memory>
#include <stdio.h>
#include <arpa/inet.h>

//ethernet header mac address
char* macadd(u_char *macadd){
    char *ret = reinterpret_cast<char*>(malloc(17));
    sprintf(ret, "%02X:%02X:%02X:%02X:%02X:%02X", macadd[0], macadd[1], macadd[2], macadd[3], macadd[4], macadd[5]);
    return ret;
}
//ip header ip address
char* ipadd(u_char *ipadd){
    char *res = reinterpret_cast<char*>(malloc(15));
    sprintf(res, "%d.%d.%d.%d", ipadd[0], ipadd[1], ipadd[2], ipadd[3]); //sprintf : string에 데이터를 쓴다.
    return res;
}

//source, destination mac, ip, port
void print_Data(Packetdata packetdata){
    if(packetdata.etherheader != nullptr){
        printf("source mac : %s \n", macadd(packetdata.etherheader->destmac));
        printf("destination mac : %s \n", macadd(packetdata.etherheader->srcmac));

        if(packetdata.ipheader != nullptr){
            printf("source ip : %s\n", ipadd(packetdata.ipheader->destIP));
            printf("destination ip : %s\n", ipadd(packetdata.ipheader->srcIP));

            if(packetdata.tcpheader != nullptr){
                printf("source port : %d\n", ntohs(packetdata.tcpheader->srcport));
                printf("destination port : %d\n", ntohs(packetdata.tcpheader->destPort));
            }

            if(packetdata.datalen > 0){
                printf("packet length : %d\n", packetdata.datalen);
                printf("=======data=======\n");
                for(int i = 0; i < 10; i++){
                    if(i == packetdata.datalen)
                        break;
                    printf("%02X ", packetdata.data[i]);
                }
                printf("\n");
            }
        }
    }
}

//size calculator
Packetdata Packetlen(const u_char *packetIn){
    Packetdata res { nullptr, nullptr, nullptr, 0, nullptr};
    int transbyte = 0;
    res.etherheader = reinterpret_cast<Etherheader*>(const_cast<u_char*>(&packetIn[transbyte]));
    transbyte = transbyte + ETHERSIZE; //
    if(htons(res.etherheader->ethertype)==IPTYPE){
        res.ipheader = reinterpret_cast<IPheader*>(const_cast<u_char*>(&packetIn[transbyte]));
        transbyte = transbyte + res.ipheader->headerlen*4;

        if(res.ipheader->protocol==TCPTYPE){
            res.tcpheader = reinterpret_cast<TCPheader*>(const_cast<u_char*>(&packetIn[transbyte]));
            transbyte = res.tcpheader->headerlen*4;
            res.datalen = htons(res.ipheader->totallen) - res.ipheader->headerlen*4 - res.tcpheader->headerlen*4;
            //data = total length - ip header length - tcp header length
            res.data = &packetIn[transbyte];
        }
    }
    return res;
}

