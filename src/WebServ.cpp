#include "WebServ.hpp"

void WebServ::add_interface(Interface conf) {
	this->interfaces.push_back(conf);
}

void WebServ::remove_interface(int i) {
	this->interfaces.erase(this->interfaces.begin() + i);
}