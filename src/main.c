#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 4096

int main(void) {
    int server_fd, client_fd;
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);
    char buffer[BUFFER_SIZE];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        return 1;
    }

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind");
        return 1;
    }

    if (listen(server_fd, 10) < 0) {
        perror("listen");
        return 1;
    }

    printf("HTTP server listening on port %d...\n", PORT);

    client_fd = accept(server_fd, (struct sockaddr *)&addr, &addr_len);
    if (client_fd < 0) {
        perror("accept");
        return 1;
    }

    // Read HTTP request
    int bytes = recv(client_fd, buffer, BUFFER_SIZE - 1, 0);
    if (bytes > 0) {
        buffer[bytes] = '\0';
        printf("Request:\n%s\n", buffer);
    }

    // HTTP response body
    const char *body = "Hello from your C HTTP server!\n";

    // Build HTTP response
    char response[BUFFER_SIZE];
    snprintf(response, sizeof(response),
        "HTTP/1.1 200 OK\r\n"
        "Content-Length: %zu\r\n"
        "Content-Type: text/plain\r\n"
        "Connection: close\r\n"
        "\r\n"
        "%s",
        strlen(body), body
    );

    send(client_fd, response, strlen(response), 0);

    close(client_fd);
    close(server_fd);

    return 0;
}
