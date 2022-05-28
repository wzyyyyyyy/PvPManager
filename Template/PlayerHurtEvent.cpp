#include "pch.h"
#include "EventHeaders.h"
#include "ParticleEffect.h"
#include "ParticleConfig.h"

bool PlayerHurtEV(const Event::MobHurtEvent& ev) {
	if (ev.mMob->isPlayer()) {
		auto ac = ev.mDamageSource->getEntity();
		if (!ac)
			return true;

		auto owner = ac->getOwner();
		if (owner &&
			owner->isPlayer()) {
			if (!checkPvPStatus((Player*)owner, (Player*)ev.mMob))
				return false;
		}

		if (ac->isPlayer()) {
			for (auto& i : ParticleEffectSetting::Particles[ParticleEffectEvent::onDie]) {
				i.Spawn(ac->getPos(), &ac->getDimension());
			}
		}
	}
	return true;
}