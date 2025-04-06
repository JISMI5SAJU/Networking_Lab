#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>

int main()
{
    FILE *fp;
    int sockfd, s, cport;
    char name[100], rcvg[100], fname[100];
    struct sockaddr_in x;

    printf("Enter the port: ");
    scanf("%d", &cport);

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(1);
    }
    printf("Socket is created\n");

    // Set up server address structure
    x.sin_family = AF_INET;
    x.sin_addr.s_addr = htonl(INADDR_ANY);
    x.sin_port = htons(cport);

    // Connect to the server
    if (connect(sockfd, (struct sockaddr *)&x, sizeof(x)) < 0) {
        perror("Error in connection");
        exit(1);
    }
    printf("Connected\n");

    // Get file names
    printf("Enter the existing file name: ");
    scanf("%s", name);
    printf("Enter the new file name: ");
    scanf("%s", fname);

    // Open file for writing
    fp = fopen(fname, "w");
    if (fp == NULL) {
        perror("Error opening file to write");
        close(sockfd);
        exit(1);
    }

    // Send file name to server
    send(sockfd, name, sizeof(name), 0);

    // Receive data
    while (1) {
        s = recv(sockfd, rcvg, sizeof(rcvg) - 1, 0);
        if (s <= 0)
            break;

        rcvg[s] = '\0';

        if (strcmp(rcvg, "error") == 0) {
            printf("File is not available\n");
            break;
        }

        if (strcmp(rcvg, "completed") == 0) {
            printf("File is transferred........\n");
            break;
        }

        // Write to file and display
        fputs(rcvg, fp);
        fputs(rcvg, stdout);
    }

    fclose(fp);
    close(sockfd);
    return 0;
}
