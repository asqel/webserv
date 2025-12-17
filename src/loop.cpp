#include "WebServ.hpp"

void WebServ::reset_fds() {
	if (!this->fds) {
		size_t count = 0;
		count += this->ports.size();
		count += this->clients.size();
		this->fds = new struct pollfd[count];

		size_t end = 0;
		for (size_t i = 0; i < this->ports.size(); i++)
			this->fds[end++].fd = this->ports[i].fd;
		for (size_t i = 0; i < this->clients.size(); i++)
			this->fds[end++].fd = this->clients[i].fd;
		this->fds_len = end;
	}
	for (size_t i = 0; i < this->fds_len; i++) {
		this->fds[i].events = POLLIN | POLLOUT;
		this->fds[i].revents = 0;
	}

}

void WebServ::loop() {
	while (!this->end) {
		this->reset_fds();
		int ret = poll(this->fds, this->fds_len, -1);
		std::cout << "poll " << ret << std::endl;
		if (ret <= 0)
			break;
		size_t current_client = 0;
		for (size_t i = 0; i < this->fds_len && ret; i++) {
			if (this->fds[i].revents == 0)
				continue;
			ret--;
			int can_read = this->fds[i].revents & POLLIN;
			int can_write = this->fds[i].revents & POLLOUT;
			if (i < this->ports.size())
				this->handle_connect(i);
			else {
				this->handle_client(can_read, can_write);
				current_client++;
			}
		}
		for (size_t i = 0; i < this->clients.size(); i++) {
			Client *clt = &this->clients[i];
			if (clt->fd == -1 && clt->data == "") {
				std::cout << "Removing client (fd " << clt->fd << ")" << std::endl;
				this->clients.erase(this->clients.begin() + i);
				i--;
			}
		}
	}
}
