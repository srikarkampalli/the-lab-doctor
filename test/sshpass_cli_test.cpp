#include "../src/ssh_cli/sshpass_cli.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){
  // Get the host IP
  ifstream file("host.txt");

  if (!file.is_open()){
    cerr << "File cannot be opened. Host error.\n";
    return 1;
  }

  string host = "";
  string line;
  while(getline(file, line)){
    host = host + line;
  }

  file.close();

  // Obtain the host password
  ifstream file_password("password.txt");

  if (!file_password.is_open()){
    cerr << "File cannot be opened. Password error.\n";
    return 1;
  }

  string password = "";
  string line_password;
  while(getline(file_password, line_password)){
    password = password + line_password;
  }

  file_password.close();

  // Test out SSH command - ls
  string user = "srikar-server-1";
  string command = "ls";

  string ls_output =  execute_ssh_command(host, user, password, command);
  cout << ls_output;

  return 0;
}