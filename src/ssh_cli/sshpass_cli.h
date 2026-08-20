#ifndef SSHPASS_CLI_H
#define SSHPASS_CLI_H
#include <string>

using namespace std;

// Define the SSH command function
string execute_ssh_command(
  const string& host,
  const string& user,
  const string& password,
  const string& command);

#endif