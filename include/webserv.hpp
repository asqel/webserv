#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include <iostream>
#include <map>
#include <vector>
#include <string>

class Client {
	private:
		int fd;

	public:
		std::string data;
}

class Interface {
	private:
		int server_fd;
		std::vector<Client> clients;
		std::vector<int> incomming_fds;
	
	public:
		std::string host;
		int port;

		std::map<int, std::string> errors;
		int max_body_size;

		std::vector<std::string> methods;

		std::string root;
		std::map<std::string, std::string> redir;

		int listing;
		std::string default_file;

		std::map<std::string, std::string> cgi;
		std::string storage_path;

};

class WebServ {
	private:
		std::vector<Interface> interfaces;
		struct pollfd *fds;
		int fds_len;

	public:
			


}

#endif
