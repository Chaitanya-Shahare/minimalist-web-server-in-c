#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int s = socket(AF_INET, SOCK_STREAM, 0);  // PF_INET to AF_INET
    struct sockaddr_in addr = {
        .sin_family = AF_INET,               // PF_INET to AF_INET
        .sin_port = htons(8080),             // Specify a port (e.g., 8080)
        .sin_addr.s_addr = INADDR_ANY        // Use any available interface
    };

    bind(s, (struct sockaddr*)&addr, sizeof(addr));  // Cast to struct sockaddr*
    listen(s, 10);
    int client_fd = accept(s, 0, 0);

    char buffer[256] = {0};
    recv(client_fd, buffer, 255, 0);  // Adjust buffer size and check for errors

    // Extracting the file path from the HTTP request
    char* f = strtok(buffer + 5, " ");
    int opened_fd = open(f, O_RDONLY);

    #ifdef __linux__
    // Linux-specific code
    ssize_t len = sendfile(client_fd, opened_fd, NULL, 256);
    #else
    // macOS-specific code
    off_t len = 256;
    sendfile(opened_fd, client_fd, 0, &len, NULL, 0);
    #endif

    close(opened_fd);
    close(client_fd);
    close(s);

    return 0;
}
