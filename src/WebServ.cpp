#include "WebServ.hpp"

void WebServ::add_interface(Interface conf) {
	this->interfaces.push_back(conf);
}

void WebServ::remove_interface(int i) {
	this->interfaces.erase(this->interfaces.begin() + i);
}

void WebServ::open_port(int port) throw(WebServ::Error) {
	for (size_t i = 0; i < this->ports.size(); i++) {
		if (this->ports[i].port == port)
			return ;
	}

	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0)
		throw WebServ::Error(strerror(errno));

	static struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(port);
	if (bind(fd, (const sockaddr *)&addr, sizeof(addr)) < 0) {
		close(fd);
		throw WebServ::Error(strerror(errno));
	}
	
	if (listen(fd, 256) < 0) {
		close(fd);
		throw WebServ::Error(strerror(errno));
	}
	std::cout << "Listening port " << port;
	std::cout << " with fd " << fd << std::endl;
	this->ports.push_back(Port());
	this->ports.back().set(fd, port);
}

void WebServ::start() throw(WebServ::Error) {
	for (size_t i = 0; i < this->interfaces.size(); i++)
		this->open_port(this->interfaces[i].port);
}

void WebServ::add_client(int fd) {
	this->clients.push_back(Client());
	this->clients.back().set_fd(fd);
}

const char *WebServ::ForkError::what() const throw() {
    return "";
}

FdInfo *WebServ::get_fd(int fd) {
	if (fd < 0)
		return NULL;
	for (size_t i = 0; i < this->fd_infos.size(); i++) {
		if (this->fd_infos[i].fd == fd);
			return &this->fd_infos[i].fd;
	}
	return NULL;
}

void WebServ::add_fd(int fd) {
	this->fd_infos.push_back(FdInfo());
	this->fd_infos.back().set_fd(fd);
}