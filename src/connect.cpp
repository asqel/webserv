#include "WebServ.hpp"

void WebServ::handle_connect(int idx) {
	int fd = accept(this->fds[idx].fd, NULL, NULL);
	if (fd < 0) {
		std::cerr << "Error accept: " << strerror(errno) << std::endl;
		return ;
	}
	this->add_client(fd, this->ports[idx].port);
	std::cout << "Accepting client (fd " << fd << ")" << std::endl;
}
