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
#include <cstring>

class Client {
	public:
		int fd;
		std::string data;
		std::string to_send;
		std::string error_fatal;
		int need_close;
		Client();
		~Client();
		void set_fd(int fd);
		void close_fd();
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
	public:
		std::string host;
		int port;

		std::map<std::string, std::string> errors;
		
		int max_body_size;

		std::map<std::string, Route> routes;
};

class Port {
	public:
		int fd;
		int port;
		~Port();
		Port();
		void set(int fd, int port);
};

class WebServ {
	private:
		struct pollfd *fds;
		size_t fds_len;
		std::vector<Port> ports;
		std::vector<Client *> clients;
	public:
		int end;
		std::vector<Interface> interfaces;
		typedef std::runtime_error Error;
		void reset_fds();
		void add_interface(Interface conf);
		void remove_interface(int i);
		void open_port(int port) throw(WebServ::Error);
		void add_client(int fd);
		void start() throw(WebServ::Error);
		void loop();
		void handle_connect(int idx);
		void handle_client(Client *clt, int can_read, int can_write);
		void srv_update_client(int idx);
		~WebServ();

		class ForkError: public std::exception {
			public:
				virtual const char *what() const throw();
		};

		
};

int parser(void);
extern WebServ srv;

#endif
