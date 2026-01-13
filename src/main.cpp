#include "WebServ.hpp"

WebServ srv;

int main() {
	parser();
	srv.start();
	srv.loop();
	return 0;
}
