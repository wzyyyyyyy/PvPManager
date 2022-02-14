#include "pch.h"
#include "Event.h"
#include "EventHeaders.h"

void initEvents() {
	Event::PlayerAttackEvent::subscribe(PlayerAttackEV);
	Event::PlayerDieEvent::subscribe(PlayerDieEV);
	Event::MobHurtEvent::subscribe(PlayerHurtEV);
	Event::PlayerRespawnEvent::subscribe(PlayerRespawnEV);
}

bool checkPvPStatus(Player* attacker, Player* target) {
	if (attacker->isOP()) return true;
	if (target) {
		auto dimid = attacker->getDimensionId();
		switch (dimid)
		{
		case 0: {
			if (area0.contains(attacker->getPos()))
				return true;
			break;
		}
		case 1: {
			if (area1.contains(attacker->getPos()))
				return true;
			break;
		}
		case 2: {
			if (area2.contains(attacker->getPos()))
				return true;
			break;
		}
		default:
			break;
		}
		if (target->isPlayer()) {
			PvP pl(attacker);
			PvP tar((Player*)target);
			if (pl.isStatus(PvPStatus::allow) && tar.isStatus(PvPStatus::allow))
				return true;

			if (pl.getStatus() == PvPStatus::allow) {
				attacker->sendText(tr("pvp.target.disallow"));
				return false;
			}

			if (pl.getStatus() == PvPStatus::disallow) {
				attacker->sendText(tr("pvp.self.disallow"));
				return false;
			}
		}
	}
	return true;
}