#include <iostream>
#include <fstream>
#include <sstream>
#include <rapidjson/document.h>
#include "monster.h"
using namespace rapidjson;

bool LoadFromJson(const char* filename, std::vector<Monster>& monsters)
{
	std::ifstream ifs;

	ifs.exceptions(std::ifstream::badbit | std::ifstream::failbit);
	std::stringstream ss;

	try
	{
		ifs.open(filename);
		ss << ifs.rdbuf();
		ifs.close();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "파일을 읽는 도중에 문제 발생 : " << e.what() << std::endl;
		ifs.close();
		return false;
	}

	std::cout << ss.str().c_str();
	return true;
}


int main()
{
	std::vector<Monster> monsters;
	LoadFromJson("data/monsters.json", monsters);
}