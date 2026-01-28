#include "WebServ.hpp"

Client::Client() {
	this->fd = -1;
	this->data = "";
	this->to_send = "";
	this->error_fatal = "";
	this->need_close = 0;
	this->req.done = 0;	
}

Client::~Client() {
	this->close_fd();
}

void Client::set_fd(int fd) {
	this->fd = fd;
}

void Client::close_fd() {
	if (this->fd >= 0) {
		close(this->fd);
	}
	this->fd = -1;
}

void Client::set_to_read(size_t b) {
	this->bytes_to_read = b;
}

void Client::unset_to_read() {
	this->bytes_to_read = -1;
}