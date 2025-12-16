#include "WebServ.hpp"


FdInfo::FdInfo() {
	this->fd = -1;
	this->to_read = "";
	this->to_write = "";
	this->will_close = 0;
}

FdInfo::~FdInfo() {
	if (this->fd > 0)
		::close(this->fd);
	this->fd = -1;
}

void FdInfo::set_fd(int fd) {
	this->fd = fd;
}

void FdInfo::write(std::string data) {
	if (this->fd < 0)
		return ;
	this->to_write += data;
}

std::string FdInfo::read() {
	if (this->fd < 0)
		return "";
	std::string res = this->to_read;
	this->to_read = "";
	return res;
}

void FdInfo::close() {
	::close(this->fd);
	this->fd = -1;
	// TODO remove client 
}

void FdInfo::tick(int can_read, int can_write) {
	if (this->fd < 0)
		return ;
	if (can_read) {
		char buffer[513] = {0};
		int ret = ::read(this->fd, buffer, 512);
		if (ret <= 0) {
			this->close();
			return ;
		}
		buffer[ret] = '\0';
		this->to_read += buffer;
	}
	if (can_write && this->to_write.length()) {
		size_t len = 512;
		if (len > this->to_write.length())
			len = this->to_write.length();
		int ret = ::send(this->fd, this->to_write.c_str(), len, MSG_NOSIGNAL);
		if (ret <= 0) {
			this->close();
			return ;
		}
		this->to_write = this->to_write.substr(ret);
	}
}

bool FdInfo::is_closed() {
	return this->fd == -1;
}
