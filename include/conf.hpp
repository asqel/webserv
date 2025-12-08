#ifndef CONF_HPP
#define CONF_HPP

#include <iostream>
#include <map>
#include <string>

#define TYPE_STR 0
#define TYPE_INT 1
#define TYPE_MAP 2

class ConfValue {
	private:
		int type;
		union {
			std::string *str;
			int i;
			std::map<std::string, ConfValue> *map;
		} val;

	public:
		ConfValue();
		~ConfValue();
		int checktype(int type);

		// returns 1 if already present
		int set_str(std::string str);
		int set_int(int i);

		int set_map_str(std::string key, std::string str);
		int set_map_int(std::string key, int i);
		int set_map_map(std::string key, ConfValue *map);

		std::string get_str(std::string key);
		int get_int(std::string key);
		std::map<std::string, ConfValue> *get_map();
};

#endif
