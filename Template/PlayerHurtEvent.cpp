#include "pch.h"
#include "EventHeaders.h"

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
			::Global<Level>->spawnParticleEffect("minecraft:lava_particle", ev.mMob->getPos().add(0, 0.7, 0), &ac->getDimension());
			::Global<Level>->spawnParticleEffect("minecraft:lava_particle", ev.mMob->getPos().add(0, 1, 0), &ac->getDimension());
			::Global<Level>->spawnParticleEffect("minecraft:lava_particle", ev.mMob->getPos().add(0, 1.3, 0), &ac->getDimension());
		}
	}
	return true;
}