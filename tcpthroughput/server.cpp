#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
using namespace std;

int main(int argc, char* argv[]){

    int server_sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("192.168.130.12");  //ip addr
    serv_addr.sin_port = htons(1234);  //port
    bind(server_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    listen(server_sock, 20);

    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    int clnt_sock = accept(server_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);

    int packet_length[9] = {1, 2, 4, 16, 64, 128, 256, 512, 1024};
    int packet_count = 100000;

    char ack[] = "ack";

    for (int j = 0; j < 9; j++){
        char* buf = new char[packet_length[j]];
        for (int i = 0; i < packet_count; ++i) {
            read(clnt_sock, buf, packet_length[j]);
//        printf("the client send data is %s \n", buf);
        }
        // send ack to client
        write(clnt_sock, ack, sizeof(ack));
    }

    close(clnt_sock);
    close(server_sock);

    return 0;
}
