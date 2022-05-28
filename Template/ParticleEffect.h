#pragma once
#include "pch.h"
#include <MC/Vec3.hpp>

enum ParticleEffectEvent {
	onHurt,
	onDie
};
class Dimension;
class ParticleEff {
public:
	std::string particleType;
	float offset_x, offset_y, offset_z;
	ParticleEff(std::string particleType, float x, float y, float z);
	void Spawn(Vec3 pos, Dimension* dim);
};