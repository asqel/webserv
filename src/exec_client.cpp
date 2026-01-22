#include "WebServ.hpp"

void WebServ::exec_client(Client *clt) {
	(void)clt;
	clt->to_send = \
	"HTTP/1.1 404 Not found\r\n" \
	"Server: webserv\r\n" \
	"Content-Length: 20\r\n" \
	"Content-Type: text/html\r\n" \
	"Cache-Control: no-store\r\n" \
	"\r\n" \
	"jai pas trouver chef";
	clt->req = Request();
}
