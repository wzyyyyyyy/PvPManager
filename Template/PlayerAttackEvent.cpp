#include "pch.h"
#include "EventHeaders.h"
#include "ParticleConfig.h"

bool PlayerAttackEV(const Event::PlayerAttackEvent& ev) {
	return PvP::checkPvPStatus(ev.mPlayer, (Player*)ev.mTarget);
}
