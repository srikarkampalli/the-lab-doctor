// Include the header file
#include "sshpass_cli.h"

// Import in the other libraries
#include <iostream>
#include <cstdio>
#include <memory>
#include <cstdlib>

// Use namespace for simplicity
using namespace std;

// Create the function logic
string execute_ssh_command(
  const string& host,
  const string& user,
  const string& password,
  const string& command){

  // Set the password as an environmental variable
  setenv("SSHPASS", password.c_str(), 1);


  // Create the intended command
  string full_command = "sshpass -e ssh -o StrictHostKeyChecking=no " + user + "@" + host + " '" + command + "'";
  
  // Make a buffer and result string
  char buffer[128];
  string result = "";

  // Create a pipe process
  unique_ptr<FILE, decltype(&pclose)> pipe(popen(full_command.c_str(), "r"), pclose);

  // Clear the password from env variables!
  unsetenv("SSHPASS");

  // Ensure that the pipe is available
  if(!pipe){
    return "Error. Failed to create a pipe process.";
  }

  // Get the result and return it
  while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
    result += buffer;
  }

  return result;

}