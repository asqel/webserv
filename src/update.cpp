#include "WebServ.hpp"

void WebServ::srv_update_client(int idx) {
	Client *clt = this->clients[idx];
	if (clt->data.length()) {
		http_parser(clt);
		std::cout << "client " << idx << " | " << clt->req.done << std::endl;
		if (clt->req.done == 1) {
			this->exec_client(clt);
		}
	}
}
