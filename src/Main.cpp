#include <iostream>
#include "Server.hpp"
#include <signal.h>

void handle_sigint(int sig) { 
    printf("\nProgram terminated\n"); 
    exit(0); // Exit the program 
} 

int main() {
	signal(SIGINT, handle_sigint); 

	Server server = Server(8000, ".");
	server.run();
	return 0;
}