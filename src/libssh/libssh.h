#ifndef LIBSSH_H
#define LIBSSH_H

#include <string>
using namespace std;

// Create the function declaration
string execute_libssh_command(const string& host, const string& username, const string& password, const string& command);

#endif