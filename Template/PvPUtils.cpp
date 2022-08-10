#include "pch.h"
#include "Global.h"
#include <Nlohmann/json.hpp>
#include <KVDBAPI.h>
#include <Utils/FileHelper.h>
#include <unordered_map>
#include <I18nAPI.h>
int cool_down_tm;

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

	void loadConf() {
		auto text = ReadAllFile(CONFIGPATH);
		auto json = nlohmann::json::parse(text.value());
		cool_down_tm = json["cooldown_time"].get<int>();
	}

	int getCoolDownTime() {
		return cool_down_tm;
	}

	void loadLanguage() {
		Translation::load(LANGPATH);
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
		pos["x"] = area.min.x;
		pos["y"] = area.min.y;
		pos["z"] = area.min.z;
		json["a"] = pos;
		pos["x"] = area.max.x;
		pos["y"] = area.max.y;
		pos["z"] = area.max.z;
		json["b"] = pos;
		db->set("dim0", json.dump());
	}

	void setPvPAreaOfDim1(AABB area) {
		nlohmann::json json;
		nlohmann::json pos;
		pos["x"] = area.min.x;
		pos["y"] = area.min.y;
		pos["z"] = area.min.z;
		json["a"] = pos;
		pos["x"] = area.max.x;
		pos["y"] = area.max.y;
		pos["z"] = area.max.z;
		json["b"] = pos;
		db->set("dim1", json.dump());
	}

	void setPvPAreaOfDim2(AABB area) {
		nlohmann::json json;
		nlohmann::json pos;
		pos["x"] = area.min.x;
		pos["y"] = area.min.y;
		pos["z"] = area.min.z;
		json["a"] = pos;
		pos["x"] = area.max.x;
		pos["y"] = area.max.y;
		pos["z"] = area.max.z;
		json["b"] = pos;
		db->set("dim2", json.dump());
	}

	void initPvPArea() {
		area0 = getPvPAreaOfDim0();
		area1 = getPvPAreaOfDim1();
		area2 = getPvPAreaOfDim2();
	}
}