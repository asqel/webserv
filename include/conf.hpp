#ifndef CONF_HPP
#define CONF_HPP

#include <iostream>
#include <map>
#include <vector>
#include <string>

class Interface {
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

#endif
