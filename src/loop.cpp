#include "WebServ.hpp"
#include <iomanip>
#include <cstdlib>

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
			this->fds[end++].fd = this->clients[i]->fd;
		this->fds_len = end;
	}
	size_t current_client = 0;
	for (size_t i = 0; i < this->fds_len; i++) {
		this->fds[i].events = 0;
		this->fds[i].revents = 0;
		if (i < this->ports.size()) {
			this->fds[i].events = POLLIN;
			this->fds[i].fd = this->ports[i].fd;
		}
		else {
			this->fds[i].events = POLLIN;
			Client *clt = this->clients[current_client];
			this->fds[i].fd = clt->fd;
			if (clt->to_send.length() || clt->error_fatal.length())
				this->fds[i].events |= POLLOUT;
			current_client++;
		}
		if (this->fds[i].fd < 0) {
			this->fds[i].fd = 2;
			this->fds[i].events = POLLIN;
			continue;
		}
	}
}

void WebServ::print_clients() {
	for (size_t i = 0; i < this->clients.size(); i++) {
		std::cout << "Client " << this->clients[i]->fd;
		std::cout << ":" << this->clients[i]->port;
		std::cout << " data len " << this->clients[i]->data.length();
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

void WebServ::loop() {
	while (!this->end) {
		if (this->fds) {
			delete[] this->fds;
			this->fds = NULL;
		}
		this->reset_fds();
		int ret = poll(this->fds, this->fds_len, -1);
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
				this->handle_client(this->clients[current_client], can_read, can_write);
				current_client++;
			}
		}
		print_clients();
		for (size_t i = 0; i < this->clients.size(); i++) {
			Client *clt = this->clients[i];
			if (clt->fd != -1)
				srv_update_client(i);
			if (!clt->error_fatal.length() && clt->need_close) {
				clt->close_fd();
				clt->data = "";
			}
			if (clt->fd == -1 && !clt->data.length()) {
				delete this->clients[i];
				this->clients.erase(this->clients.begin() + i);
				i--;
				continue;
			}
		}
	}
}
