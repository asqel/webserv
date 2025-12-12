#include "WebServ.hpp"

Client::Client() {
	this->fd = -1;
	this->data = "";
}

Client::~Client() {
	FdInfo *fd_info = srv->get_fd(this->fd);
	if (!fd_info)
		return ;
	fd_info->close();
	this->fd = -1;
}

void Client::set_fd(int fd) {
	this->fd = fd;
}
