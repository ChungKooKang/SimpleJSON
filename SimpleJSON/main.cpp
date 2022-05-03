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
	Document d;
	d.Parse(ss.str().c_str());

	for (const auto& e : d["monsters"].GetArray())
	{
		Monster monster;

		monster.SetName(e["name"].GetString());

		Status status;
		auto statObj = e["status"].GetObject();
		status.mLevel = statObj["level"].GetInt();
		status.mHP = statObj["hp"].GetInt();
		status.mMP = statObj["mp"].GetInt();

		monster.SetStatus(status);

		for (const auto& item : e["item"].GetArray())
		{
			Item tmpItem;
			tmpItem.mName = item["items"].GetString();
			tmpItem.mGold = item["gold"].GetInt();

			monster.Additem(tmpItem);
		}
		monsters.push_back(monster);
	}

	return true;
}


int main()
{
	std::vector<Monster> monsters;
	LoadFromJson("data/monsters.json", monsters);
}