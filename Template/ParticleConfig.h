#pragma once
#include "pch.h"
#include "Global.h"
#include "ParticleEffect.h"

namespace ParticleEffectSetting {
	inline std::map<ParticleEffectEvent, std::vector<ParticleEff>> Particles;
	void reloadConfig(std::string path);
};