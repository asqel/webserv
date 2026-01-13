#include <iostream>
#include <vector>

std::vector<std::string> split(std::string str, std::string sep, int keep_null) {
	std::vector<std::string> ret;
	size_t start = 0;
	size_t nb = 0;
	std::string sub;

	while (start < str.length()) {
		nb = str.find(sep, start) - start;
		std::cout << "find: " << nb << std::endl;
		sub = str.substr(start, nb);
		if (keep_null || sub.length())		
			ret.push_back(str.substr(start, nb));
		start += nb + sep.length();
	}
	return (ret);
}

int parse_fisrt_line(std::string str, Request &request) {
	std::vector<std::string> elements = split(str, " ", 0);
	if (elements.size() != 3) 
		return (0);
	request.method = elements[0];
	request.path = elements[1];
	request.version = elements[2];
}

int parse_other_line(std::string str, Request &request) {
	if (!str.length())
		return (1);
	std::string key = get_key(str);
	std::string val = get_str_val(str);
	if (!key.length() || !val.length())
		return (0);
	request.args[key] = val;
	return (1);
}

Request http_parser(std::string request) {

	Request ret;

	if (request.find("/r/n") == NOFOUND) {
		ret.error = 1;
		return (ret);
	}
	std::vector<std::string> lines = split(request, "\r\n", 1);
	if (!parse_fisrt_line(lines[0], ret)) {
		ret.error = 1;
		return (ret);
	}
	for (int i = 1; i < lines.size(); i++) {
		if (!parse_other_line(lines[i], ret)) {
			ret.error = 1;
			return (ret);
		}
	}
	return (ret);
}

int main(void) {
	std::string test = "salut je suis \r\n car je vaut \r\n je suis la \r\n\r\n";

	std::vector<std::string> vec = split(test, "\r\n");
	for (size_t i = 0; i < vec.size(); i++)
	{
		std::cout << "|" << vec[i] << "|" << std::endl;
	}
	return 1;
}