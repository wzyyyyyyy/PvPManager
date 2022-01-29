#include "pch.h"
#include "Global.h"
#include "Event.h"
#include "PvPUtils.h"
#include "PMCommand.h"
#include <KVDBAPI.h>
#include <LoggerAPI.h>
#include <LLAPI.h>
#include <TranslationAPI.h>
#include <unordered_map>

Logger logger("PvPManager");
std::unique_ptr<KVDB> db;
AABB area0(0, 0, 0, 0, 0, 0);
AABB area1(0, 0, 0, 0, 0, 0);
AABB area2(0, 0, 0, 0, 0, 0);

void PluginInit()
{
	LL::registerPlugin("PvPManager", "PvPManager", LL::Version(1, 0, 0));
	PM::initDB();
	PM::initPvPArea();
	PM::loadLanguage();
	initCommand();
	initEvents();
	logger.info("load sucess!");
}
