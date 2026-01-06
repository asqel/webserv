#include "WebServ.hpp"

void WebServ::srv_update_client(int idx) {
	Client *clt = this->clients[idx];
	if (clt->data.length()) {
		std::cout << "AAAA" << std::endl;
		clt->data = "";
		clt->error_fatal = \
		"HTTP/1.1 200 pas trouve\r\n" \
		"Server: webserv\r\n" \
		"Content-Length: 6\r\n" \
		"Content-Type: text/html\r\n" \
		"Cache-Control: no-store\r\n" \
		"\r\n" \
		"ya pa ";
		clt->need_close = 1;
	}
}
