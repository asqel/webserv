#include "WebServ.hpp"

WebServ srv;

int main() {
	parser();
	srv.start();
	srv.loop();
	//int fd = socket(AF_INET, SOCK_STREAM, 0);
	//struct pollfd fds[1000];
	//int fds_len  = 0;
	//static struct sockaddr_in addr;
	//int opt = 1;
	//if (fd < 0) {
	//	std::cerr << "CA MARCHE PAS" << std::endl;
	//	return 1;
	//}
	//addr.sin_family = AF_INET;
	//addr.sin_addr.s_addr = htonl(INADDR_ANY);
	//addr.sin_port = htons(8000);
	//if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	//	goto err;
//
	//if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
	//	goto err;
//
	//if (listen(fd, 256) < 0)
	//	goto err;
//
	//fds[fds_len].fd = fd;
	//fds[fds_len].revents = 0;
	//fds[fds_len].events = POLLIN;
	//fds_len++;
	//while (1) {
	//	int ret = poll(fds, fds_len, -1);
	//	if (ret <= 0) {
	//		return 1;
	//	}
	//	for (int i = 0; i < fds_len && ret; i++) {
	//		if (i == 0 && fds[i].revents) {
	//			fds[fds_len].fd = accept(fds[i].fd, NULL, NULL);
	//			fds[fds_len].revents = 0;
	//			fds[fds_len].events = POLLIN;
	//			fds[i].revents = 0;
	//			fds[i].events = POLLIN;
	//			std::cout << "LE CONNECTIOINF DANS LE FD " << fds[fds_len].fd << std::endl; 
	//			fds_len++;
	//			ret--;
	//		}
	//		else if (fds[i].fd >= 0 && fds[i].revents){
	//			char buffer[4096];
	//			int ret = read(fds[i].fd, buffer, 4095);
	//			fds[i].revents = 0;
	//			fds[i].events = POLLIN;
	//			if (ret <= 0) {
	//				close(fds[i].fd);
	//				std::cout << "DISCO FD " << fds[i].fd << std::endl;
	//				fds[i].fd = -1;
	//				fds[i].events = 0;
	//			}
	//			buffer[ret] = 0;
	//			std::cout << buffer << std::endl;
	//			ret--;
	//		}
	//	}
	//}
	//return 0;
	//err:
	//	perror("");
	//	std::cerr << "AAAAAAAAAAAAA" << std::endl;
	//	return 1;
	//return 0;
}
