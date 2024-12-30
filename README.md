![image](https://github.com/user-attachments/assets/98a532b8-fe10-4bd5-a27b-721f4cffd1e5)# reverse-shell-c
Reverse Shell with C

-reverse shell for windows

-the code exploits win32 api functions to create a connection to a listener, then creates a cmd.exe process where stderr, stdin and stdout are all directed to the listener

-add the listener address and port before compiling

-compile the code:
      
    gcc -o reverse_shell reverse_shell.c -lws2_32

-unfortunately, the backdoor is detectable by windows defender, but I'm already working on exploiting more win32 api functions for evasion

---------------------------------------------------------

30/12/2024

-I added obfuscation techniques to the backdoor.

-it loads the necessary dlls independently and deals with all the API function as offsets which drastically decreased detection rates.

-EXECUTION (bear in mind that windows defender is turned on):


![image](https://github.com/user-attachments/assets/02027d91-ddad-436f-ae0f-694b974ff517)


![image](https://github.com/user-attachments/assets/55a7ea2c-0e11-48be-8504-557007d124bb)


![image](https://github.com/user-attachments/assets/2b2d82b4-1036-433e-bb60-4e26578fb8c9)



The VirusTotal analysis:

![image](https://github.com/user-attachments/assets/893ec2db-b608-4c88-bed4-5c99e69bbc10)


