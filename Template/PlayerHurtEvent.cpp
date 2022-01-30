#include "pch.h"
#include "EventHeaders.h"

bool PlayerHurtEV(const Event::MobHurtEvent& ev) {
	auto ac = ev.mDamageSource->getEntity();
	if (!ac) return true;
	if (ac->isPlayer() && ev.mMob->isPlayer()) {
		::Global<Level>->spawnParticleEffect("minecraft:lava_particle", ev.mMob->getPos().add(0, 0.7, 0), &ac->getDimension());
		::Global<Level>->spawnParticleEffect("minecraft:lava_particle", ev.mMob->getPos().add(0, 1, 0), &ac->getDimension());
		::Global<Level>->spawnParticleEffect("minecraft:lava_particle", ev.mMob->getPos().add(0, 1.3, 0), &ac->getDimension());
	}
	return true;
}