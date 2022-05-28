#include "pch.h"
#include "EventHeaders.h"
#include "ParticleConfig.h"

bool PlayerDieEV(const Event::PlayerDieEvent& ev) {
	auto ac = ev.mDamageSource->getEntity();
	if (!ac) return true;
	if (ac->isPlayer()) {
		ac->addEffect(MobEffect::EffectType::Strength, 5, 2);
		PvP(ev.mPlayer).setLastKilledBy(ac->getNameTag());
		for (auto& i : ParticleEffectSetting::Particles[ParticleEffectEvent::onDie]) {
			i.Spawn(ac->getPos(), &ac->getDimension());
		}
	}
	else PvP(ev.mPlayer).setLastKilledBy("");
	return true;
}