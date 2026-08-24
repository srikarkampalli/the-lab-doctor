8/19/2026:
- Started working on this project. I will be using SSH for security, but Telnet could be added later on if needed. I really don't like it for security, though. I guess that it is a nice thing to add on, however.
- I will first start with executing SSH commands through sshpass. Keep in mind that this is not really safe to try out, so I will definitely be using a dedicated SSH library in the future.
- Since this project is only meant for Linux, I will be using WSL for development and testing, along with my Ubuntu server.
- I did successfully build the sshpass client and tested it! Gotta love it.
- "g++ main.cpp -o my_program `pkg-config --cflags --libs sdl2`" is a way to automatically link on Linux.

8/20/2026:
- After wrestling with telnet and ports and whatnot, I finally got telnet working on my Ubuntu computer. It's a bit tricky, but it does work. The thing about it is that there are different ways to activate it.
- telnet will only be good for quick connectivity tests.

REQUIRED THINGS TO INSTALL ON BOTH LINUX MACHINES:
- sshpass
- libssh
- g++ (or any other C++ compiler)
- telnet (for quick tests)