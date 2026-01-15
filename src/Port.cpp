#include "WebServ.hpp"

Port::Port() {
	this->fd = -1;
	this->port = 0;
}

Port::~Port() {
}

void Port::set(int fd, int port) {
	this->fd = fd;
	this->port = port;
}
