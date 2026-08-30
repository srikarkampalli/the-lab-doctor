#include "telnet_cli.h"

#include <iostream>
#include <string>
#include <cstring>

#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>

using namespace std;

constexpr int TELNET_IAC = 255;
constexpr int TELNET_DONT = 254;
constexpr int TELNET_DO = 253;
constexpr int TELNET_WONT = 252;
constexpr int TELNET_WILL = 251;

void handle_telnet_communication(int sock, unsigned char* buffer, ssize_t length){
  for (ssize_t i = 0; i < length; i++){
    if (buffer[i] == TELNET_IAC && i + 2 < length) {
      unsigned char command = buffer[i+1];
      unsigned char option = buffer[i+2];

      unsigned char response[3];
      response[0] = TELNET_IAC;

      if (command == TELNET_WILL){
        response[1] = TELNET_WONT;
      } else if (command == TELNET_DO) {
        response[1] = TELNET_WONT;
      } else {
        i += 1;
        continue;
      }

      response[2] = option;
      send(sock, response, 3, 0);
      i += 2;
    }
  }
}

string test_telehack_command(){
  int sock = -1;
  string host = "telehack.com";
  string port = "23";
  struct addrinfo hints, *res;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  if(getaddrinfo(host.c_str(), port.c_str(), &hints, &res) != 0){
    cout << "Failed to resolve host.\n";
    return "";
  }

  // create the socket
  sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if (sock < 0){
    cout << "Failed to create the socket.\n";
    freeaddrinfo(res);
    return "";
  }

  // Connect to telehack
  if (connect(sock, res->ai_addr, res->ai_addrlen) < 0) {
    cout << "Connection failed.\n";
    close(sock);
    freeaddrinfo(res);
    return "";
  }
  freeaddrinfo(res);
  cout << "Connected to telehack!\n";

  unsigned char buffer[4096];
  ssize_t bytes_received;

  bytes_received = recv(sock, buffer, sizeof(buffer) - 1, 0);
  if (bytes_received > 0){
    handle_telnet_communication(sock, buffer, bytes_received);
  }

  bytes_received = recv(sock, buffer, sizeof(buffer) - 1, 0);
  if (bytes_received > 0){
    buffer[bytes_received] = '\0';
    cout << buffer;
  }

  string cmd = "eliza\r\n";
  if (send(sock, cmd.c_str(), cmd.length(), 0) < 0) {
    cout << "Could not send command.\n";
    close(sock);
    return "";
  }

  usleep(500000);

  bytes_received = recv(sock, buffer, sizeof(buffer) - 1, 0);
  if (bytes_received > 0){
    buffer[bytes_received] = '\0';
    cout << "Command output: ";
    cout << buffer << "\n";
  }

  close(sock);

  string buffer_string = reinterpret_cast<const char*>(buffer);

  return buffer_string;
}