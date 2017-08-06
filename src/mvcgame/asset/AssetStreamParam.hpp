
#ifndef mvcgame_AssetStreamParam_hpp
#define mvcgame_AssetStreamParam_hpp

#include <map>
#include <string>
#include <iostream>

namespace mvcgame {
	typedef struct AssetStreamParam {
		typedef std::map<std::string, std::string> Param;
		std::istream input;
		Param args;
	} AssetStreamParam;
}

#endif