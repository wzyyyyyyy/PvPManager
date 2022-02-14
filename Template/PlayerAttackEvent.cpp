#include "pch.h"
#include "EventHeaders.h"

bool PlayerAttackEV(const Event::PlayerAttackEvent& ev) {
	return checkPvPStatus(ev.mPlayer, (Player*)ev.mTarget);
}
