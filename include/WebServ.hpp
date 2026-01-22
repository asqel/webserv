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
#define NOFOUND (std::string::npos)
#define MAX_LINE_LEN 4096


class Request {
	public:
		int error; // 0: not finish, 1: good, 2: bad
		std::string method;
		std::string path;
		std::string version;
		std::map<std::string, std::string> args;
};

class Client {
	public:
		int port;
		int fd;
		std::string to_send;
		std::string error_fatal;
		int need_close;
		std::string data;

		Request req;

		Client();
		~Client();
		void set_fd(int fd);
		void close_fd();
		void rm_data(int pos, int len);
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
		void add_client(int fd, int port);
		void start() throw(WebServ::Error);
		void loop();
		void handle_connect(int idx);
		void handle_client(Client *clt, int can_read, int can_write);
		void srv_update_client(int idx);
		~WebServ();

		void print_clients();

		class ForkError: public std::exception {
			public:
				virtual const char *what() const throw();
		};

		
};

//parser_utils
std::string get_str_val(std::string str);
int get_int_val(std::string str);
std::string get_key(std::string str);

void http_parser(Client *client);

int parser(void);
extern WebServ srv;

#endif
