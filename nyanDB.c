#include <stdio.h>
#include <stdlib.h>//exit()에서 안에 1이 들어가면 에러 나서 종료 한다는것., atoi()
#include <string.h>//memset()
#include <sys/types.h>//connect()
#include <sys/socket.h>//socket(), connect()
#include <netinet/in.h>//htons()
#include <arpa/inet.h>
#include <unistd.h>//read(), write(), close()

int main(int argc, char *argv[]){//명령행 옵션의 개수가 저장되는 argc, 명령행 옵션의 문자열들이 저장되는 *argv[]
  int client, len, n;
  struct sockaddr_in c_addr;//???
  char query[30];
  char recv[30];//수신된 내용 담을 버퍼

  if(argc < 2){//프로그램 실행에서 1을 먹고 들어가기 때문에 사용자가 추가적으로 명령을 하지 않으면 그대로 1이 된다
    puts("Usage: ./nyanDB -p port");
    exit(1);
  }

  client = socket(PF_INET, SOCK_STREAM, 0);//PF_INET : 인터넷 프로토콜(TCP/IP), SOCK_STREAM : TCP방식
  c_addr.sin_addr.s_addr = inet_addr("127.0.0.1");//문자열 받아 long형 값 반환, NETWORK바이트 형식 가짐.
  c_addr.sin_family = AF_INET;//IPv4인터넷 프로토콜 정의.
  //PF_INET은 프로토콜 체계를 설정, AF_INET은 주소체계 설정.
  c_addr.sin_port = htons(atoi(argv[2]));//htons : 네트워크 바이트로 변경, atoi : 문자열을 정수형으로 변환

  if(connect(client, (struct sockaddr *)&c_addr, sizeof(c_addr)) == -1){
    //connect : 클라이언트 소켓을 생성하고 서버로 연결 요청
    //클라이언트 소켓의 파일 디스트립터, 연결 요청 보낼 서버의 주소 정보 지닌 구조체 변수의 포인터, (2번째 인자)가 가리키는 주소 정보 구조체 변수의 크기
    //반환 : 성공시 0, 실패시 -1
      puts("connect error");
      exit(1);
  }

  printf("\n░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n");
  printf("░░░░░░░░░░▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄░░░░░░░░░\n");
  printf("░░░░░░░░▄▀░░░░░░░░░░░░▄░░░░░░░▀▄░░░░░░░\n");
  printf("░░░░░░░░█░░▄░░░░▄░░░░░░░░░░░░░░█░░░░░░░\n");
  printf("░░░░░░░░█░░░░░░░░░░░░▄█▄▄░░▄░░░█░▄▄▄░░░\n");
  printf("░▄▄▄▄▄░░█░░░░░░▀░░░░▀█░░▀▄░░░░░█▀▀░██░░             Welcome to nyanDB !\n");
  printf("░██▄▀██▄█░░░▄░░░░░░░██░░░░▀▀▀▀▀░░░░██░░             nyan nyan > _ <\n");
  printf("░░░░▀████░▀░░░░▄░░░██░░░▄█░░░░▄░▄█░░██░\n");
  printf("░░░░░░░▀█░░░░▄░░░░░██░░░░▄░░░▄░░▄░░░██░\n");
  printf("░░░░░░░▄█▄░░░░░░░░░░░▀▄░░▀▀▀▀▀▀▀▀░░▄▀░░\n");
  printf("░░░░░░█▀▀█████████▀▀▀▀████████████▀░░░░\n");
  printf("░░░░░░████▀░░███▀░░░░░░▀███░░▀██▀░░░░░░\n");
  printf("░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n\n");


  while(1){
    printf("nyandb> ");
    memset(query, 0, sizeof(query));//메모리 블럭을 채운다
    //(1번째 인자)로부터 시작하는 메모리 주소부터 (3번째 인자)개의 바이트를 (2번째 인자)로 채운다. 
    //값을 채울 메모리의 시작 주소, 채울 값, 채울 바이트 수
    scanf("%s", query);
    write(client, query, 30);
    //데이터 송신 할때 사용됨.
    //소켓 디스크립터, 송신할 때 내용 담을 버퍼, 쓰기 할 바이트 수

    if((n = read(client, recv, sizeof(recv))) < 0){//read인자 순서대로 : 파일(소켓) 디스크립터, 수신된 내용 담을 버퍼, 버퍼의 크기
      //반환 : -1외의 값 : 읽어들인 바이트의 수, -1 : 실패
        exit(1);//프로그램 자체 종료.
    }
    printf("\nSent: %s \n\n", recv);
  }

  close(client);//socket()으로 생성된 소켓 종료, 인자는 소켓 디스크립터
  return 0;
}
