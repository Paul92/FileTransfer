FileTransfer
============

This is a client-server application for transferring files between 2 computers
using sockets. It can be used to copy files on the same computer by specifying
the host "localhost". It can be used only on linux platforms.

In order to transfer a file, you need to compile both the server and the
client, using serverCompile and clientCompile scripts. They will generate
2 binary files: server and client. Run the server specifying a port and
a filename. For example:
./server 9000 file.txt
opens the port 9000 and will create a file called file.txt.
The client needs to know the server's ip. For example:
./client 192.168.1.2 9000 /home/user/f.txt
transfers the file f.txt to the server opened at 192.168.1.2, using port 9000.
Notice that you can send a file and save it with another name.
