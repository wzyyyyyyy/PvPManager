#pragma once
#include <Nlohmann/json.hpp>

class Player;
enum PvPStatus { allow = 1, disallow = 0 };

class PvP {
	Player* pl;
	PvPStatus status;
	bool isfirstjoin;
	bool isinpvparea;
public:
	PvP(Player* player);
	PvPStatus getStatus();
	void setStatus(PvPStatus status);
	bool isStatus(PvPStatus status);
	std::string getLastKilledBy();
	void setLastKilledBy(std::string pl);
	bool isFirstJoin();
	bool isInPvPArea();
	void SetInPvPAreaStatus(bool val);
	void StartCoolDown();
	bool isInCoolDown();
};