#include "WebServ.hpp"

static int	ft_atoi(std::string nbstr)
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

static std::string remove_spaces(std::string str) {
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

std::string get_key(std::string str){
	std::string ret;
	size_t sep;
	sep = str.find(':');
	if (sep == std::string::npos)
		return (ret);
	ret = remove_spaces(str.substr(0, sep));
	return (ret);
}

int get_int_val(std::string str){
	int ret = -1;
	size_t sep;
	sep = str.find(':');
	if (sep == std::string::npos)
		return (ret);
	ret = ft_atoi(remove_spaces(str.substr(sep + 1)));
	return (ret);
}

std::string get_str_val(std::string str){
	std::string ret;
	size_t sep;
	sep = str.find(':');
	if (sep == std::string::npos)
		return (ret);
	ret = remove_spaces(str.substr(sep + 1));
	return (ret);
}