#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

int main() {
    // Create a socket for the proxy server
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Error creating server socket");
        exit(1);
    }

    // Bind the socket to the local address and port (6668)
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(6668);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error binding server socket");
        exit(1);
    }

    // Listen for incoming connections
    if (listen(serverSocket, 5) == -1) {
        perror("Error listening for incoming connections");
        exit(1);
    }

	printf("Command and Conquer Red Alert 3\n");
	printf("IRC/Game Lobby Relay: Bypass TCP Port 6667 blocked by ISP\n");
	printf("=========================================================\n");
    printf("Listening on port 6668...\n");

    while (1) {
        // Accept an incoming connection
        struct sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);

        if (clientSocket == -1) {
            perror("Error accepting client connection");
            continue;
        }

		// Convert the client's IP address to a string
		char clientIP[INET_ADDRSTRLEN];
		if (inet_ntop(AF_INET, &(clientAddr.sin_addr), clientIP, INET_ADDRSTRLEN) == NULL) {
			perror("Error converting client IP address");
			close(clientSocket);
			continue;
		}

        printf("Accepted a client connection from %s.\n", clientIP);

        // Create a socket for the remote server
        int remoteSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (remoteSocket == -1) {
            perror("Error creating remote socket");
            close(clientSocket);
            continue;
        }

        // Set up the address of the remote server (185.17.144.132:6667)
        struct sockaddr_in remoteAddr;
        memset(&remoteAddr, 0, sizeof(remoteAddr));
        remoteAddr.sin_family = AF_INET;
        remoteAddr.sin_port = htons(6667);
        if (inet_pton(AF_INET, "185.17.144.132", &(remoteAddr.sin_addr)) <= 0) {
            perror("Error setting up remote server address");
            close(clientSocket);
            close(remoteSocket);
            continue;
        }

        // Connect to the remote server
        if (connect(remoteSocket, (struct sockaddr*)&remoteAddr, sizeof(remoteAddr)) == -1) {
            perror("Error connecting to the remote server");
            close(clientSocket);
            close(remoteSocket);
            continue;
        }

        // Create two-way communication between the client and the remote server
        fd_set fds;
        int maxFd = clientSocket > remoteSocket ? clientSocket : remoteSocket;
        char buffer[4096];
        int bytesRead;

        while (1) {
            FD_ZERO(&fds);
            FD_SET(clientSocket, &fds);
            FD_SET(remoteSocket, &fds);

            if (select(maxFd + 1, &fds, NULL, NULL, NULL) == -1) {
                perror("Error in select");
                break;
            }

            if (FD_ISSET(clientSocket, &fds)) {
                bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
                if (bytesRead <= 0) {
                    break;
                }
                send(remoteSocket, buffer, bytesRead, 0);
            }

            if (FD_ISSET(remoteSocket, &fds)) {
                bytesRead = recv(remoteSocket, buffer, sizeof(buffer), 0);
                if (bytesRead <= 0) {
                    break;
                }
                send(clientSocket, buffer, bytesRead, 0);
            }
        }

        // Close the client and remote sockets
        close(clientSocket);
        close(remoteSocket);

        printf("Closed the client connection.\n");
    }

    // Close the server socket (unreachable in this code as it runs indefinitely)
    close(serverSocket);

    return 0;
}

