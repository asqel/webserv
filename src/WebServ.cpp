#include "WebServ.hpp"

void WebServ::add_interface(Interface conf) {
	this->interfaces.push_back(conf);
}

void WebServ::remove_interface(int i) {
	this->interfaces.erase(this->interfaces.begin() + i);
}


void WebServ::end() {
	delete this->fds;	
	this->fds_len = 0;
	this->interfaces.clear();
	for (std::vector<int_pair_t>::iterator it = this->fd_ports.begin(); it != this->fd_ports.end(); it++)
		close(it->a);
	this->fd_ports.clear();
}

void WebServ::open_port(int port) throw(std::runtime_error) {
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0)
		throw std::runtime_error(strerror(errno));

	static struct sockaddr_in addr;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;
}

void WebServ::start() {
	for (size_t i = 0; i < this->interfaces.size(); i++)
		this->open_port(this->interfaces[i].port);
}