#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <unordered_map>
#include "student.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <string>

#define PORT 8080
#define BUFFER_SIZE 1024

void handle_client(int client_socket);
void start_server();
std::string create_response(const std::string& status, const std::string& body);
std::string get_response_for_test();
std::string get_response_for_daniel();
std::string get_response_for_404();

#endif
