#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include "config.h"

#define MESSAGE_SIZE (BUF_SIZE / 2)

int main(int argc, char* argv[]) {
    if(argc < 2){
        printf("Entrer ip address!\n");
        return 1;
    }
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUF_SIZE] = {0};
    
    // 1. Создание сокета
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    // 2. Настройка адреса сервера
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(DEFAULT_PORT);
    inet_pton(AF_INET, argv[1], &server_addr.sin_addr);
    
    // 3. Подключение к серверу
    connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    
    // 4. Получение и отправка данных
    char message[MESSAGE_SIZE];

    printf("Print your message to server:\n");

    if (fgets(message, MESSAGE_SIZE, stdin) != NULL) {
        // Attempt to parse the line
        // sscanf returns the number of items successfully read
        if (sscanf(message, "%s", message) == 1) {
            printf("Successfully read message: %s\n", message);
            // Additional validation can be done here (e.g., range checks)
        } else {
            printf("Invalid input format.\n");
        }
    } else {
        printf("Error reading input or EOF reached.\n");
    }

    send(sockfd, message, strlen(message), 0);
    
    // 5. Получение ответа
    read(sockfd, buffer, BUF_SIZE);
    printf("Server response: %s\n", buffer);
    
    // 6. Закрытие соединения
    close(sockfd);
    
    return 0;
}
