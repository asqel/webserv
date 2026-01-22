#include "WebServ.hpp"

static std::string stash;

int get_line(std::ifstream &fileIn, std::string &str) {
	if (stash.length()) {
		str = stash;
		stash = "";
		return 1;
	}
	return !!getline(fileIn, str);
}

void set_stash(std::string str) {
	stash = str;
}

int is_whitespaces(std::string str) {
	for (size_t i = 0; i < str.length(); i++) {
		if (!(str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r')))
			return (0);
	}
	return (1);
}

int	ft_atoi(std::string nbstr)
{
	if (!nbstr.length())
		return (-2);
	for (size_t i = 0; i < nbstr.length(); i++)
		if (nbstr[i] < '0' || nbstr[i] > '9')
			return (-2);
	int	nbr = 0;
	int	i = 0;
	int	sign = 1;
	while (nbstr[i] >= '0' && nbstr[i] <= '9')
		nbr = nbr * 10 + (nbstr[i++] - '0');
	return (nbr * sign);
}

int count_tab(std::string str) {
	int i = 0;
	while (str[i] == '\t')
		i++;
	return (i);
}

std::string remove_spaces(std::string str) {
	std::string ret;
	size_t i = 0;
	size_t y = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	y = i;
	while (!(str[y] == ' ' || (str[y] >= '\t' && str[y] <= '\r')) && y < str.length())
		y++;
	ret = str.substr(i, y);
	return (ret);
}


std::vector<std::string> get_vec_val(std::ifstream &fileIn, int tab) {
	std::string str;
	std::vector<std::string> ret;
	while (1) {
		getline(fileIn, str);
		if (is_whitespaces(str))
			continue;
		else if (count_tab(str) != tab) {
			set_stash(str);
			break;
		}
		ret.push_back(remove_spaces(str));
	}
	return (ret);
}
std::map<std::string, std::string> get_map_val(std::ifstream &fileIn, int tab) {
	std::string str;
	std::map<std::string, std::string> ret;
	std::string key;
	std::string val;
	while (1) {
		if (!get_line(fileIn, str))
			break;
		if (is_whitespaces(str))
			continue;
		else if (count_tab(str) != tab) {
			set_stash(str);
			break;
		}
		key = remove_spaces(get_key(str));
		val = remove_spaces(get_str_val(str));
		ret[key] =  val;
	}
	return (ret);
}

Route get_route_val(std::ifstream &fileIn) {
	Route route;
	std::string str;

	while (1) {
		if (!get_line(fileIn, str))
			break;
		if (is_whitespaces(str))
			continue;
		else if (count_tab(str) != 2) {
			set_stash(str);
			break;
		}
		std::string key = get_key(str);
		if(key == "allowed_methods")
			route.methods = get_vec_val(fileIn, 3);
		else if(key == "root")
			route.root = get_str_val(str);
		else if(key == "redir")
			route.redir = get_map_val(fileIn, 3);
		else if(key == "listing")
			route.listing = get_int_val(str);
		else if(key == "default_file")
			route.default_file = get_str_val(str);
		else if(key == "cgi")
			route.cgi = get_map_val(fileIn, 3);
		else if(key == "storage")
			route.storage_path = get_str_val(str);
	}
	return (route);
}

int parser(void) {
	Interface config = Interface();
	std::ifstream fileIn;
	fileIn.open("conf");
	std::string str;
	while (get_line(fileIn, str)) {
		if(str == "server:") {
			srv.add_interface(config);
			config = Interface();
		}
		else if (is_whitespaces(str)){
			continue;
		}
		else if (count_tab(str) == 1){
			std::string key = get_key(str);
			if (!key.length()) {
				std::cerr << "line {" << str << "} incorrectly formatted, missing \':\'" << std::endl;
				return (1);
			}
			else if(key == "host")
				config.host = get_str_val(str);
			else if(key == "port")
				config.port = get_int_val(str);
			else if(key == "errors")
				config.errors = get_map_val(fileIn, 2);
			else if(key == "max_body_size")
				config.max_body_size = get_int_val(str);
			else if(key == "route")
				config.routes[get_str_val(str)] = get_route_val(fileIn);
		}
	}
	srv.add_interface(config);
	srv.remove_interface(0);
	return (1);
}