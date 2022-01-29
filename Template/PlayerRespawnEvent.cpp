#include "pch.h"
#include "Events.h"

bool PlayerRespawnEV(const Event::PlayerRespawnEvent& ev) {
	auto name = PvP(ev.mPlayer).getLastKilledBy();
	if (name.length() >= 3) {
		ev.mPlayer->sendText(tr("pvp.respawn.text", name));
	}
	return true;
}

THook(void, "?respawn@Player@@UEAAXXZ", Player* pl) {
	original(pl);
	auto eff = MobEffectInstance::MobEffectInstance((int)MobEffect::EffectType::Resistance, 3000, 2, 0, 1, 0);
	if (PvP(pl).isFirstJoin())
		pl->addEffect(eff);
	else
		pl->addEffect(eff);
}

