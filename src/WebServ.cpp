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
	this->fds = NULL;
	for (size_t i = 0; i < this->interfaces.size(); i++)
		this->open_port(this->interfaces[i].port);
}

void WebServ::add_client(int fd) {
	Client *clt = new Client();
	std::cout << "pushing" << std::endl;
	this->clients.push_back(clt);
	std::cout << "setting" << std::endl;
	this->clients.back()->set_fd(fd);
	std::cout << "setting end" << std::endl;
}

const char *WebServ::ForkError::what() const throw() {
    return "";
}

WebServ::~WebServ() {
	for (size_t i = 0; i < this->clients.size(); i++) {
		delete this->clients[i];
	}
}