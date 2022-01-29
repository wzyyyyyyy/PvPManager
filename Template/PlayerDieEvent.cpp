#include "pch.h"
#include "Events.h"

bool PlayerDieEV(const Event::PlayerDieEvent& ev) {
	auto ac = ev.mDamageSource->getEntity();
	if (!ac) return true;
	if (ac->isPlayer()) {
		ac->addEffect(MobEffect::EffectType::Strength, 5, 2);
		PvP(ev.mPlayer).setLastKilledBy(ac->getNameTag());
		::Global<Level>->spawnParticleEffect("minecraft:soul_particle", ev.mPlayer->getPos().add(0, 1, 0), &ac->getDimension());
		::Global<Level>->spawnParticleEffect("minecraft:soul_particle", ev.mPlayer->getPos().add(0, 1, 0), &ac->getDimension());
		::Global<Level>->spawnParticleEffect("minecraft:soul_particle", ev.mPlayer->getPos().add(0, 1, 0), &ac->getDimension());
		::Global<Level>->spawnParticleEffect("minecraft:lava_particle", ev.mPlayer->getPos().add(0, 1, 0), &ac->getDimension());
		::Global<Level>->spawnParticleEffect("minecraft:lava_particle", ev.mPlayer->getPos().add(0, 1, 0), &ac->getDimension());
		::Global<Level>->spawnParticleEffect("minecraft:lava_particle", ev.mPlayer->getPos().add(0, 1, 0), &ac->getDimension());
		::Global<Level>->spawnParticleEffect("minecraft:lava_particle", ev.mPlayer->getPos().add(0, 1, 0), &ac->getDimension());
	}
	else PvP(ev.mPlayer).setLastKilledBy("");
	return true;
}