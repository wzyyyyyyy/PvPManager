#pragma once
#include <memory>
#define DBPATH "./plugins/PvPManager/DB"
#define LANGPATH "plugins/PvPManager/Lang/lang.json"
#define CONFIGPATH "./plugins/PvPManager/setting.json"
#define PARTICLEEFFECTPATH "./plugins/PvPManager/ParticleEffect.json"

class Logger;
class KVDB;

extern Logger logger;
extern std::unique_ptr<KVDB> db;
extern AABB area0;
extern AABB area1;
extern AABB area2;
