#include "../src/telnet_cli/telnet_cli.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){
  string output =  test_telehack_command();
  cout << output;
  return 0;
}