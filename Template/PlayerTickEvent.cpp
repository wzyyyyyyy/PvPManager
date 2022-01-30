#include "pch.h"
#include "EventHeaders.h"

THook(void, "?tickWorld@ServerPlayer@@UEAAXAEBUTick@@@Z",
	Player* self, void* tick) {
	auto pos = self->getPos();
	PvP pvp(self);
	switch (self->getDimensionId())
	{
	case 0: {
		if (area0.contains(pos)) {
			if (!pvp.isInPvPArea()) {
				self->sendText(tr("pvp.attend.pvparea"));
				pvp.SetInPvPAreaStatus(1);
				return original(self, tick);
			}
		}
		else {
			if (pvp.isInPvPArea()) {
				self->sendText(tr("pvp.leave.pvparea"));
				pvp.SetInPvPAreaStatus(0);
				return original(self, tick);
			}
		}
		break;
	}
	case 1: {
		if (area1.contains(pos)) {
			if (!pvp.isInPvPArea()) {
				self->sendText(tr("pvp.attend.pvparea"));
				pvp.SetInPvPAreaStatus(1);
				return original(self, tick);
			}
		}
		else {
			if (pvp.isInPvPArea()) {
				self->sendText(tr("pvp.leave.pvparea"));
				pvp.SetInPvPAreaStatus(0);
				return original(self, tick);
			}
		}
		break;
	}
	case 2: {
		if (area2.contains(pos)) {
			if (!pvp.isInPvPArea()) {
				self->sendText(tr("pvp.attend.pvparea"));
				pvp.SetInPvPAreaStatus(1);
				return original(self, tick);
			}
		}
		else {
			if (pvp.isInPvPArea()) {
				self->sendText(tr("pvp.leave.pvparea"));
				pvp.SetInPvPAreaStatus(0);
				return original(self, tick);
			}
		}
		break;
	}
	default:
		return original(self, tick);
	}
	return original(self, tick);
}