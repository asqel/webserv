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

class Request {
	public:
		int error; // 1 if has error
		std::string method;
		std::string path;
		std::string version;
		std::map<std::string, std::string> args;
};

class Client {
	public:
		int fd;
		std::string data;
		Client();
		~Client();
		void set_fd(int fd);
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

class FdInfo {
	private:
		int will_close;
		std::string to_read;
		std::string to_write;
	public:
		int fd;
		FdInfo();
		~FdInfo();
		void set_fd(int fd);
		void write(std::string data);
		std::string read();
		void close();
		bool is_closed();

		void tick(int can_read, int can_write);
};

class WebServ {
	private:
		struct pollfd *fds;
		size_t fds_len;
		std::vector<Port> ports;
		std::vector<Client> clients;
		std::vector<FdInfo> fd_infos;
	public:
		int end;
		std::vector<Interface> interfaces;
		typedef std::runtime_error Error;
		void add_interface(Interface conf);
		void remove_interface(int i);
		void open_port(int port) throw(WebServ::Error);
		void add_client(int fd);
		void start() throw(WebServ::Error);
		void loop();
		class ForkError: public std::exception {
			public:
				virtual const char *what() const throw();
		};
		FdInfo *get_fd(int fd);
		void	add_fd(int fd);

		void handle_connect(int idx);

		
};

//parser_utils
std::string get_str_val(std::string str);
int get_int_val(std::string str);
std::string get_key(std::string str);

Request http_parser(std::string request);

int parser(void);
extern WebServ srv;

#endif
