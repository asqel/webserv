#include "WebServ.hpp"

Client::Client() {
	this->fd = -1;
	this->data = "";
}

Client::~Client() {
	close(this->fd);
	this->fd = -1;
}

void Client::set_fd(int fd) {
	this->fd = fd;
}
