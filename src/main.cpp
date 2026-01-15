#include "WebServ.hpp"

WebServ srv;

int main() {
	Client client;
	client.data = "GET /contact HTTP/1.1/r/nHost: xample.com/r/nUser-Agent: curl/8.6.0/r/nAccept: */*/r/n/r/n";
	http_parser(&client);
	std::cout << client.data << std::endl;
	std::cout << client.req.error << std::endl;
	//parser();
	//srv.start();
	//srv.loop();
	return 0;
}
