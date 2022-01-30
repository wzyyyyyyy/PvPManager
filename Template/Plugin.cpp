#include "pch.h"
#include "Global.h"
#include "Event.h"
#include "PvPUtils.h"
#include "PMCommand.h"
#include <KVDBAPI.h>
#include <LoggerAPI.h>
#include <LLAPI.h>
#include <TranslationAPI.h>

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

/*THook(std::vector<ItemStack>*, "?getRandomItems@LootTable@@QEBA?AV?$vector@VItemStack@@V?$allocator@VItemStack@@@std@@@std@@AEAVRandom@@AEAVLootTableContext@@@Z",
	LootTable* a1, void* a2, void* a3, LootTableContext* a4) {
	auto items = original(a1, a2, a3, a4);
	auto ac = a4->getThisEntity();
	if (ac)
		std::cout << ac->getTypeName() << std::endl;
	for (auto& i : *items) {
		std::cout << i.getName() << i.getCount() << std::endl;
	}
	auto item = ItemStack::create("minecraft:diamond_block", 64);
	items->push_back(*item);
	return items;
}*/
