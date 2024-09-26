# reverse-shell-c
Reverse Shell with C

-reverse shell for windows

-the code exploits win32 api functions to create a connection to a listener, then creates a cmd.exe process where stderr,stdin and stdout are all directed to the listener

-add the listener address and port before compiling

-compile the code:
      
    gcc -o backdoor backdoor.c -lws2_32

-unfortunately, the backdoor is detectable by windows defender, but I'm already working on exploiting more win32 api functions for evasion
