#include "libssh.h"
#include <iostream>
#include <libssh/libssh.hpp>

using namespace std;

string execute_libssh_command(const string& host, const string& username, const string& password, const string& command){
  string result = "";
  try{
    ssh::Session session;

    session.setOption(SSH_OPTIONS_HOST, host);
    session.setOption(SSH_OPTIONS_USER, username);

    session.connect();
    cout << "Connected to the server. Trying to log in...\n";

    if (session.userauthPassword(password) != SSH_AUTH_SUCCESS) {
      cerr << "Authentication failed!";
      return "Failed!";
    }

    cout << "Authentication successful!\n";

    ssh::Channel channel(session);
    channel.openSession();

    channel.requestExec(command.c_str());

    char buffer[128];
    int bytes_received = channel.read(buffer, sizeof(buffer), 0);

    while (bytes_received > 0) {
      result.append(buffer, bytes_received);
      bytes_received = channel.read(bbuffer, sizeof(buffer), 0);
    }

    // 6. Properly close the channel
    channel.sendEof();
    channel.close();

  } catch (const exception& e) {
    cout << "Error! " << e.what() << "\n";
  }

  return result;
}