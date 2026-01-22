#include "WebServ.hpp"

int isDigit(char c) {
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
int isPrint(char c) {
	if (c >= ' ' && c <= '~')
		return (1);
	return (0);
}

int isKey(char c) {
	if (!isPrint(c))
		return (0);
	std::string illegal = " (),/:;<=>?@[\\]{}";
	if (illegal.find(c) != NOFOUND)
		return (0);
	return (1);
}

int isVal(unsigned char c) {
	if (c <= 8)
		return (0);
	if (c >= 0xA && c <= 0x1F)
		return (0);
	if (c == 0x7F)
		return (0);
	return (1);
}

int check_version(std::string ver) {
	if (ver.length() != 8)
		return (0);
	if (ver[0] == 'H' && ver[1] == 'T'
		&& ver[2] == 'T' && ver[3] == 'P' && ver[4] == '/'
		&& isDigit(ver[5]) && ver[6] == '.' && isDigit(ver[7]))
		return (0);
	return (1);
}

int check_path(std::string path) {
	for (size_t i = 0; i < path.length(); i++)
		if (!isPrint(path[i]))
			return (0);
	return (1);
}

int check_method(std::string met) {
	if (met == "GET")
		return (0);
	if (met == "POST")
		return (0);
	if (met == "DELETE")
		return (0);
	return (1);
}

int has_first_line(Request &req) {
	if (req.method.length() < 1)
		return 0;
	if (req.path.length() < 1)
		return 0;
	if (req.version.length() < 1)
		return 0;
	return 1;
}

int check_first_line(Request &req) {
	if (!has_first_line(req))
		return (0);
	if (!check_version(req.version))
		return (0);
	if (!check_method(req.method))
		return (0);
	if (!check_path(req.path))
		return (0);
	return (1);
}

int check_other_line(std::string line) {
	size_t sep = line.find(':');
	for (size_t i = 0; i < sep; i++) {
		if (!isKey(line[i]))
			return (0);
	}
	for (size_t i = sep + 1; i < line.length(); i++) {
		if (!isVal(line[i]))
			if (line[i] != '\t' && line[i] != ' ')
				return (0);
	}
	return (1);
}

static int parse_fisrt_line(std::string str, Request &request) {
	size_t i = 0;
	size_t start = 0;

	if (str[0] == ' ' || str[str.length() - 1] == ' ')
		return (1);
	while (str[i] != ' ' && i < str.length())
		i++;
	request.method = str.substr(start, i);
	while (str[i] == ' ' && i < str.length())
		i++;
	start = i;
	while (str[i] != ' ' && i < str.length())
		i++;
	request.path = str.substr(start, i - start);
	while (str[i] == ' ' && i < str.length())
		i++;
	start = i;
	while (i < str.length())
		i++;
	request.version = str.substr(start, i - start);
	return (!check_first_line(request));
}

int parse_other_line(std::string str, Request &request) {
	if (!str.length())
		return (2);
	if (!check_other_line(str)) {
		return (0);
	}
	std::string key = get_key(str);
	std::string val = get_str_val(str);
	if (!key.length() || !val.length())
		return (0);
	request.args[key] = val;
	return (1);
}

void error_client(Client *client) {
	client->data = "";
	client->error_fatal = \
	"HTTP/1.1 400 requeest error\r\n" \
	"Server: webserv\r\n" \
	"Content-Length: 0\r\n" \
	"Content-Type: text/html\r\n" \
	"Cache-Control: no-store\r\n" \
	"\r\n";
	client->need_close = 1;
}

void http_parser(Client *client) {

	size_t len = 0;
	while (1) {
		if (client->req.done == 1)
			return;
		len = client->data.find("\r\n");
		if (len == NOFOUND) {
			client->req.done = 0;
			if (client->data.length() > MAX_LINE_LEN) {
				error_client(client);
			}
			return;
		}
		std::string line = client->data.substr(0, len);
		client->data = client->data.substr(len + 2);
		if (!has_first_line(client->req)){
			if(!parse_fisrt_line(line, client->req)) {
				error_client(client);
				return ;
			}
		}
		else {
			int ret = parse_other_line(line, client->req);
			if (ret == 2)
				client->req.done = 1;
			if(ret == 0) {
				error_client(client);
				return ;
			}
		}
	}
}
