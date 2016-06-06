#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>//bind(), accept()
#include <sys/socket.h>//socklen_t, bind(), listen(), accept()
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

void makelog(char *query);

int main(int argc, char *argv[]){
    int client, server, n;
    struct sockaddr_in c_addr, s_addr;
    socklen_t len;
    char recv_query[30];

    if(argc < 2)
    {
      puts("Usage: ./server -p port");
      exit(1);
    }

    server = socket(PF_INET, SOCK_STREAM, 0);
    memset(&s_addr, 0, sizeof(s_addr));
    s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    //htonl : htons는 short형 데이터를 보낼때 바이트 오더를 네트워크로 바꿔줬다면, htonl은 long형 데이터의 바이트 오더를 바꾸어준다.
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(atoi(argv[2]));

    if(bind(server, (struct sockaddr*)&s_addr, sizeof(s_addr)) == -1)
        //소켓에 주소를 할당해 주는 함수.
        //소켓 식별자 또는 소켓 디스크립터, 주소정보 할당, (2번째 인자)구조체의 크기
        //반환 0 : 주소 할당 성공, 반환 -1 : 주소 할당 실패
        /*
        이때, 2번째 인자 : 주소정보 할당에서 인터넷을 통해 통신하는 AF_INET인 경우에는 struct sockaddr_in을 사용한다.
        struct sockadd_in{
            sa_family_t         sin_family; //소켓 주소체계(AF_INET)
            unsigned short int  sin_port;   //포트 주소
            struct in_addr      sin_addr;   //IP주소
            unsigned char       sin_zero[8];//사용되지 않는 필드 0을 채워준다.
        }
        */
    {
        puts("bind() error");
        exit(1);
    }

    if(listen(server, 5) == -1)
    //클라이언트의 접속 요청을 기다리도록 설정한다.
    //소켓 식별자 또는 소켓 디스크립터, 연결 요청을 대기시킬 공간 설정(백로그큐)
    {
        puts("listen() error");
        exit(1);
    }

    len = sizeof(c_addr);
    client = accept(server, (struct sockaddr*)&c_addr, &len);
    //클라이언트의 접속 요청을 받아드리고 클라이언트와 통신하는 전용 소켓 생성
    //서버의 소켓 디크스립터, 클라이언트 주소 정보 담을 구조체, 클라이언트 주소 정보를 담을 구조체 크기
    //반환 -1 외의 값 : 클라이언트 소켓 디스크립터, 반환 -1 : 연결 실패
    if(client == -1)
    {
      puts("Client connection failed");
      exit(1);
    }

    while(1)
    {
        read(client, recv_query, 30);
        n = strlen(recv_query);
        makelog(recv_query);
        write(client, recv_query, n+1);
        puts(recv_query);
    }
    close(client);
    return 0;
}

void makelog(char *query)
{
    FILE *fp;
    fp = fopen("log", "a+");//a+은 파일의 현재 내용 뒤에 추가 기록하거나 읽기 위해서 사용
    fprintf(fp, "%s\n", query);
    fclose(fp);
}
