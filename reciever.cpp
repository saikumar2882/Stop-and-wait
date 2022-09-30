#include <iostream>
#include <bits/stdc++.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <time.h>
using namespace std;

int main()
{
     cout << "Creating server socket..." <<  endl;
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == -1)
    {
         cerr << "Can't create a socket!";
        return -1;
    }

    struct sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(7980);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);

     cout << "Binding socket to sockaddr..." <<  endl;
    if (bind(listening, (struct sockaddr *)&hint, sizeof(hint)) == -1) 
    {
         cerr << "Can't bind to IP/port\n";
        return -2;
    }

     cout << "Mark the socket for listening..." <<  endl;
    if (listen(listening, SOMAXCONN) == -1)
    {
         cerr << "Can't listen !";
        return -3;
    }

    sockaddr_in client;
    socklen_t clientSize = sizeof(client);

     cout << "Accept client call..." <<  endl;
    int clientSocket = accept(listening, (struct sockaddr *)&client, &clientSize);

     cout << "Received call..." <<  endl;
    if (clientSocket == -1)
    {
         cerr << "Problem with client connecting!";
        return -4;
    }
 
     cout << "Client address: " << inet_ntoa(client.sin_addr) << " and port: " << client.sin_port <<  endl;

    close(listening);

    char buf[4096];
    int flag;
    while (true) {
        // clear buffer
        memset(buf, 0, 4096);

        // wait for a message
        int bytesRecv = recv(clientSocket, buf, 4096, 0);
        if (bytesRecv == -1)
        {
             cerr << "There was a connection issue." <<  endl;
        }
        if (bytesRecv == 0)
        {
             cout << "The client disconnected" <<  endl;
        }
     
         cout << "Received: " <<  string(buf, 0, bytesRecv) << "\r\n";

        if(buf[strlen(buf)-1]=='0') flag=1;
        else flag=0;
        
        send(clientSocket, ("ack " + to_string(flag)).c_str(), bytesRecv+1, 0);
    }
    // close socket
    close(clientSocket);

    return 0;

}