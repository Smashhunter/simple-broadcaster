#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "config.h"

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[BUF_SIZE] = {0};
    
    // 1. Создание сокета
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    // 2. Настройка адреса сервера
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(DEFAULT_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    
    // 3. Привязка сокета
    bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    
    // 4. Начало прослушивания
    listen(server_fd, QUEUE_SIZE);
    printf("Server listening on %d...\n", DEFAULT_PORT);

    for(int i = 0;i < 5; ++i){
        // 5. Принятие соединения
        client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);

        printf("Connection accepted!\n");

        // 6. Чтение данных
        read(client_fd, buffer, BUF_SIZE);
        printf("Recieved: %s\n", buffer);

        // 7. Отправка ответа
        char *response = "Message recieved.";
        send(client_fd, response, strlen(response), 0);

        // 8. Закрытие соединений
        close(client_fd);

    }
    printf("Server is tired! Closing...\n");
    close(server_fd);
    
    return 0;
}
