/*
* We measure the througput of localhost(127.0.0.1), the result is shown as follows.
* 1       12.2083  Mbps
* 2       17.0505  Mbps
* 4       33.4459  Mbps
* 16      135.262  Mbps
* 64      530.257  Mbps
* 128     1006.67  Mbps
* 256     1969.06  Mbps
* 512     3659.53  Mbps
* 1024    6716.41  Mbps
*/
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string>
#include "timer.h"
timer* newtime;

using namespace std;
int main(int argc, char* args[]){
    if (argc == 1){
        cout << "Usage: ./client <IP>" << endl;
        exit(1);
    }

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(args[1]);  //IP
    serv_addr.sin_port = htons(1234);  //port
    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    newtime = (timer*)malloc(sizeof(timer));
    double alltime;
    double total_data;
    int packet_length[9] = {1, 2, 4, 16, 64, 128, 256, 512, 1024};
    int packet_count = 100000; // We send 100000 messages every test cycle. This num is big enough to reduce mistakes.

    for(int j = 0; j < 9; j++){
        string data(packet_length[j], 'x');
        const char* realdata = data.c_str();
        char buffer[10];
        start(newtime);
        for (int i = 0; i < packet_count; ++i) {
            write(sock, realdata, packet_length[j]);
        }
        //ack
        read(sock, buffer, sizeof(buffer)-1);

        end(newtime);
        alltime = duration(newtime)/1000000000.0; //s

        reset(newtime);
        total_data = (double)(packet_length[j] * packet_count)/1000000.0; // MB

        cout << packet_length[j] << "\t" << 8*total_data/alltime << "\t Mbps" << endl;
    }

    close(sock);
    return 0;
}
