﻿#include "pch.h"
#include "EventHeaders.h"

bool PlayerRespawnEV(const Event::PlayerRespawnEvent& ev) {
	auto name = PvP(ev.mPlayer).getLastKilledBy();
	if (name.length() >= 3) {
		ev.mPlayer->sendText(tr("pvp.respawn.text", name));
	}
	return true;
}

THook(void, "?respawn@Player@@UEAAXXZ", Player* pl) {
	original(pl);
	if (PvP(pl).isFirstJoin()) {
		auto eff = MobEffectInstance::MobEffectInstance((int)MobEffect::EffectType::Resistance, 3500, 3, 0, 1, 1);
		pl->addEffect(eff);
	}
	else {
		auto eff = MobEffectInstance::MobEffectInstance((int)MobEffect::EffectType::Resistance, 200, 1, 0, 1, 1);
		pl->addEffect(eff);
	}
}

