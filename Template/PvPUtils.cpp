#include "pch.h"
#include "Global.h"
#include <Nlohmann/json.hpp>
#include <KVDBAPI.h>
#include <Utils/FileHelper.h>
#include <unordered_map>
#include <TranslationAPI.h>

namespace PM {
	void initDB() {
		db = KVDB::create(DBPATH);
		std::string tmp;
		if (db->get("dim0", tmp))
			return;
		nlohmann::json json;
		nlohmann::json pos;
		pos["x"] = 0;
		pos["y"] = 0;
		pos["z"] = 0;
		json["a"] = pos;
		json["b"] = pos;
		db->put("dim0", json.dump());
		db->put("dim1", json.dump());
		db->put("dim2", json.dump());
	}

	std::string getLanguage() {
		auto text = ReadAllFile(CONFIGPATH);
		auto json = nlohmann::json::parse(text.value());
		return json["language"].get<std::string>();
	}

	void loadLanguage() {
		Translation::load("plugins/PvPManager/Lang/" + getLanguage() + ".json");
	}

	AABB getPvPAreaOfDim0() {
		std::string tmp;
		db->get("dim0", tmp);
		auto json = nlohmann::json::parse(tmp);
		auto ax = json["a"]["x"].get<int>();
		auto ay = json["a"]["y"].get<int>();
		auto az = json["a"]["z"].get<int>();
		auto bx = json["b"]["x"].get<int>();
		auto by = json["b"]["y"].get<int>();
		auto bz = json["b"]["z"].get<int>();
		return AABB{ (float)ax,(float)ay,(float)az,(float)bx,(float)by,(float)bz };
	}

	AABB getPvPAreaOfDim1() {
		std::string tmp;
		db->get("dim1", tmp);
		auto json = nlohmann::json::parse(tmp);
		auto ax = json["a"]["x"].get<int>();
		auto ay = json["a"]["y"].get<int>();
		auto az = json["a"]["z"].get<int>();
		auto bx = json["b"]["x"].get<int>();
		auto by = json["b"]["y"].get<int>();
		auto bz = json["b"]["z"].get<int>();
		return AABB{ (float)ax,(float)ay,(float)az,(float)bx,(float)by,(float)bz };
	}

	AABB getPvPAreaOfDim2() {
		std::string tmp;
		db->get("dim2", tmp);
		auto json = nlohmann::json::parse(tmp);
		auto ax = json["a"]["x"].get<int>();
		auto ay = json["a"]["y"].get<int>();
		auto az = json["a"]["z"].get<int>();
		auto bx = json["b"]["x"].get<int>();
		auto by = json["b"]["y"].get<int>();
		auto bz = json["b"]["z"].get<int>();
		return AABB{ (float)ax,(float)ay,(float)az,(float)bx,(float)by,(float)bz };
	}

	void setPvPAreaOfDim0(AABB area) {
		nlohmann::json json;
		nlohmann::json pos;
		pos["x"] = area.pointA.x;
		pos["y"] = area.pointA.y;
		pos["z"] = area.pointA.z;
		json["a"] = pos;
		pos["x"] = area.pointB.x;
		pos["y"] = area.pointB.y;
		pos["z"] = area.pointB.z;
		json["b"] = pos;
		db->set("dim0", json.dump());
	}

	void setPvPAreaOfDim1(AABB area) {
		nlohmann::json json;
		nlohmann::json pos;
		pos["x"] = area.pointA.x;
		pos["y"] = area.pointA.y;
		pos["z"] = area.pointA.z;
		json["a"] = pos;
		pos["x"] = area.pointB.x;
		pos["y"] = area.pointB.y;
		pos["z"] = area.pointB.z;
		json["b"] = pos;
		db->set("dim1", json.dump());
	}

	void setPvPAreaOfDim2(AABB area) {
		nlohmann::json json;
		nlohmann::json pos;
		pos["x"] = area.pointA.x;
		pos["y"] = area.pointA.y;
		pos["z"] = area.pointA.z;
		json["a"] = pos;
		pos["x"] = area.pointB.x;
		pos["y"] = area.pointB.y;
		pos["z"] = area.pointB.z;
		json["b"] = pos;
		db->set("dim2", json.dump());
	}

	void initPvPArea() {
		area0 = getPvPAreaOfDim0();
		area1 = getPvPAreaOfDim1();
		area2 = getPvPAreaOfDim2();
	}
}