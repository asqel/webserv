#include "WebServ.hpp"

Client::Client() {
	this->fd = -1;
	this->data = "";
	this->to_send = "";
	this->error_fatal = "";
	this->need_close = 0;
	std::cout << "lE CONSTRICOTR" << std::endl;
}

Client::~Client() {
	std::cout << "DESTRUCTOR" << std::endl;
	this->close_fd();
}

void Client::set_fd(int fd) {
	std::cout << "set_fd" << std::endl;
	this->fd = fd;
}

void Client::close_fd() {
	if (this->fd >= 0) {
		std::cout << "Closing fd " << this->fd << std::endl;
		close(this->fd);
	}
	this->fd = -1;
}
