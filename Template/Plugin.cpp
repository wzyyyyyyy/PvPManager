#include "pch.h"
#include "Global.h"
#include "Event.h"
#include "PvPUtils.h"
#include "PMCommand.h"
#include "ParticleConfig.h"
#include <KVDBAPI.h>
#include <LLAPI.h>
#include <I18nAPI.h>

Logger logger("PvPManager");
std::unique_ptr<KVDB> db;
AABB area0(0, 0, 0, 0, 0, 0);
AABB area1(0, 0, 0, 0, 0, 0);
AABB area2(0, 0, 0, 0, 0, 0);

void PluginInit()
{
	auto start = std::chrono::system_clock::now();
	ll::registerPlugin("PvPManager", "PvPManager", ll::Version(1, 1, 5));
	ParticleEffectSetting::reloadConfig(PARTICLEEFFECTPATH);
	PM::initDB();
	PM::initPvPArea();
	PM::loadConf();
	PM::loadLanguage();
	initCommand();
	initEvents();
	auto end = std::chrono::system_clock::now();
	logger.info("load sucessful in {}ms!",
		std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
}
