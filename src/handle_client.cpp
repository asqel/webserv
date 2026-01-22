#include "WebServ.hpp"
#include <stdlib.h>


void WebServ::handle_client(Client *clt, int can_read, int can_write) {
	if (clt->fd < 0)
		return ;
	if (can_read && !clt->need_close) {	
		char buffer[4096 + 1];
		int ret = read(clt->fd, buffer, 4096);
		if (ret <= 0)
			clt->need_close = 1;
		else {
			buffer[ret] = '\0';
			clt->data += buffer;
		}	
	}
	else if (can_write) {
		if (clt->error_fatal.length()) {
			size_t len = 512;
			if (len > clt->error_fatal.length())
				len = clt->error_fatal.length();
			int ret = send(clt->fd, clt->error_fatal.c_str(), len, MSG_NOSIGNAL);
			if (ret < 0) {
				clt->need_close = 1; 
				clt->data = "";
				clt->error_fatal = "";
			}
			else
				clt->error_fatal = clt->error_fatal.substr(ret);

		}
		else if (clt->to_send.length()) {
			size_t len = 512;
			if (len > clt->to_send.length())
				len  = clt->to_send.length();
			int ret = send(clt->fd, clt->to_send.c_str(), len, MSG_NOSIGNAL); 
			if (ret < 0)
				clt->need_close = 1;
			else
				clt->to_send = clt->to_send.substr(ret);
		}
	}
}
