#include "pch.h"
#include "ParticleEffect.h"
#include <MC/Level.hpp>

ParticleEff::ParticleEff(std::string particleType, float x, float y, float z) {
	this->particleType = particleType;
	this->offset_x = x;
	this->offset_y = y;
	this->offset_z = z;
}

class Dimension;
void ParticleEff::Spawn(Vec3 pos, Dimension* dim) {
	auto particle_type = this->particleType;
	auto offset_x = this->offset_x;
	auto offset_y = this->offset_y;
	auto offset_z = this->offset_z;
	::Global<Level>->spawnParticleEffect(
		particle_type,
		pos.add(offset_x, offset_y, offset_z),
		dim);
}
