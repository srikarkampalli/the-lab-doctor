#ifndef TELNET_CLI_H
#define TELNET_CLI_H
#include <string>
using namespace std;

void handle_telnet_communication(int sock, unsigned char* buffer, ssize_t length);

string test_telehack_command();

#endif