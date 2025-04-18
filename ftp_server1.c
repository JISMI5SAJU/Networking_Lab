#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
    FILE *fp;
    int sockfd, newsd, ser, n, a, cli, pid, bd, port, clilen;
    char name[100], fileread[100], fname[100], ch, file[100], rcv[100];
    struct sockaddr_in x, cliaddr;

    printf("Enter the port address\n");
    scanf("%d", &port);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
        printf("Cant create\n");
    else
        printf("Socket is created\n");

    x.sin_family = AF_INET;
    x.sin_addr.s_addr = htonl(INADDR_ANY);
    x.sin_port = htons(port);
    a = sizeof(x);

    bd = bind(sockfd, (struct sockaddr *)&x, a);
    if(bd < 0)
        printf("Cant bind\n");
    else
        printf("Binded\n");

    listen(sockfd, 5);
    clilen = sizeof(cliaddr);

    newsd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen);
    if(newsd < 0)
    {
        printf("Cant accept\n");
    }
    else
        printf("Accepted\n");

    n = recv(newsd, rcv, 100, 0);
    rcv[n] = '\0';

    fp = fopen(rcv, "r");
    if(fp == NULL)
    {
        send(newsd, "error", 5, 0);
        close(newsd);
    }
    else
    {
        while(fgets(fileread, sizeof(fileread), fp))
        {
            if(send(newsd, fileread, sizeof(fileread), 0) < 0)
            {
                printf("Can’t send file contents\n");
            }
            sleep(1);
        }
        if(!fgets(fileread, sizeof(fileread), fp))
        {
            // when file pointer reaches end of file, file transfer “completed” message is sent
            send(newsd, "completed", 10, 0);
        }
    }

    return 0;
}
