#include "WebServ.hpp"

void WebServ::handle_connect(int idx) {
	int fd = accept(this->fds[idx], NULL, NULL);
	if (fd < 0) {
		std::cerr << "Error accept: " << strerror(errno) << std::endl;
		return ;
	}
	this->add_client(fd);
	std::cout << "Accepting client (fd " << fd << ")" << std::endl;
}
