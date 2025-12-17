#include "WebServ.hpp"

void WebServ::handle_client(Client *clt, int can_read, int can_write) {
	if (can_read) {	
	}
	else if (can_write && clt->to_send.length() && clt->fd > 0) {
		size_t len = 512;
		if (len > clt->to_send.length())
			len  = clt->to_send.length();
		int ret = send(clt->fd, clt->to_send.c_str(), len, MSG_NOSIGNAL); 
		if (ret < 0)
			clt->close_fd();
		else
			clt->to_send = to_send.substr(ret);
	}
}
