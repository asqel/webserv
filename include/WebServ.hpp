#ifndef WEBSERV_HPP
#define WEBSERV_HPP


#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/poll.h>
#include <map>
#include <vector>
#include <string>
#include <fstream>

class Client {
	private:
		int fd;

	public:
		std::string data;
};

class Route {
	public :
		std::vector<std::string> methods;

		std::string root;
		std::map<std::string, std::string> redir;

		int listing;
		std::string default_file;

		std::map<std::string, std::string> cgi;
		std::string storage_path;
};

class Interface {
	private:
		int server_fd;
		std::vector<Client> clients;
		std::vector<int> incomming_fds;
	
	public:
		std::string host;
		int port;

		std::map<std::string, std::string> errors;
		
		int max_body_size;

		std::map<std::string, Route> routes;
};

class WebServ {
	private:
		struct pollfd *fds;
		int fds_len;
	public:
		std::vector<Interface> interfaces;
		void add_interface(Interface conf);
		void remove_interface(int i);
		
};

int parser(void);
extern WebServ srv;

#endif
