#include "pch.h"
#include "Events.h"

bool PlayerAttackEV(const Event::PlayerAttackEvent& ev) {
	if (ev.mPlayer->isOP()) return true;
	if (ev.mTarget) {
		auto dimid = ev.mPlayer->getDimensionId();
		switch (dimid)
		{
		case 0: {
			if (area0.contains(ev.mPlayer->getPos()))
				return true;
			break;
		}
		case 1: {
			if (area1.contains(ev.mPlayer->getPos()))
				return true;
			break;
		}
		case 2: {
			if (area2.contains(ev.mPlayer->getPos()))
				return true;
			break;
		}
		default:
			break;
		}

		auto target = ev.mTarget;
		if (target->isPlayer()) {
			PvP pl(ev.mPlayer);
			PvP tar((Player*)target);
			if (pl.isStatus(PvPStatus::allow) && tar.isStatus(PvPStatus::allow))
				return true;

			if (pl.getStatus() == PvPStatus::allow) {
				ev.mPlayer->sendText(tr("pvp.target.disallow"));
				return false;
			}

			if (pl.getStatus() == PvPStatus::disallow) {
				ev.mPlayer->sendText(tr("pvp.self.disallow"));
				return false;
			}
		}
	}
	return true;
}
