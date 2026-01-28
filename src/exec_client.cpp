#include "WebServ.hpp"

void WebServ::exec_client(Client *clt) {
	if (!clt->req.args.count("Host")) {
		clt->req = Request();
		clt->error_fatal = \
			"HTTP/1.1 400 Bad Request (Host)\r\n" \
			"Server: webserv\r\n" \
			"Content-Length: 0\r\n" \
			"Content-Type: text/html\r\n" \
			"Cache-Control: no-store\r\n" \
			"\r\n";
		clt->to_send = "";
		clt->data = "";
		clt->need_close = 1;
		return ;
	}
	std::string host = "";
	std::string port_str = 0;
	std::string pair = clt->req.args["Host"];
	size_t col_pos = pair.find(':');
	if (NOFOUND == col_pos)
		host = pair;
	else {
		host = pair.substr(0, col_pos);
		port_str = pair.substr(col_pos);
	}
	int port = atoi(port_str);
	if (clt->req.method == "GET")
	else if (clt->req.method == "POST")
	else if (clt->req.method == "DELETE")
	else {
			
	}
}
