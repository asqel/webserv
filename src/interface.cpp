#include "WebServ.hpp"

Interface *WebServ::find_interface(int port, std::string host) {
	for (size_t i = 0; i < this->interfaces.size(); i++) {
		Interface *interface = &this->interfaces[i];
		if (interface->host == host && interface->port == port)
			return interface;
	}
	if (port)
		return NULL;

	int last_idx = -1;
	for (size_t i = 0; i < this->interfaces.size(); i++) {
		if (this->interfaces[i].host == host) {
			if (last_idx != -1)
				return NULL;
			last_idx = i;
		}
	}
	if (last_idx == -1)
		return NULL;
	return &this->interfaces[last_idx];
}
