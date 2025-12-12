#include "WebServ.hpp"

Port::Port() {
	this->fd = -1;
	this->port = 0;
}

Port::~Port() {
	if (this->fd >= 0)
		close(this->fd);
	this->fd = -1;
}

void Port::set(int fd, int port) {
	this->fd = fd;
	this->port = port;
}
