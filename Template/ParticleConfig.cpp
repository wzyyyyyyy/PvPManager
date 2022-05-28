#include "pch.h"
#include "Global.h"
#include "ParticleConfig.h"
#include <Utils/FileHelper.h>
#include <Nlohmann/json.hpp>

void ParticleEffectSetting::reloadConfig(std::string path) {
	try {
		auto conf = ReadAllFile(path);
		if (!conf.has_value())
			return;
		auto j = nlohmann::json::parse(conf.value());

		auto node_onHurt = j["ParticleEffects"]["onHurt"];
		std::vector<ParticleEff> tmp;
		for (auto& i : node_onHurt.items()) {
			ParticleEff p(
				i.value()["ParticleEffectType"].get<std::string>(),
				i.value()["x"].get<float>(),
				i.value()["y"].get<float>(),
				i.value()["z"].get<float>()
			);
			tmp.push_back(p);
		}
		ParticleEffectSetting::Particles[ParticleEffectEvent::onHurt] = tmp;

		auto node_onDie = j["ParticleEffects"]["onDie"];
		std::vector<ParticleEff> tmp_;
		for (auto i : node_onDie.items()) {
			ParticleEff p_(
				i.value()["ParticleEffectType"].get<std::string>(),
				i.value()["x"].get<float>(),
				i.value()["y"].get<float>(),
				i.value()["z"].get<float>()
			);
			tmp_.push_back(p_);
		}
		ParticleEffectSetting::Particles[ParticleEffectEvent::onHurt] = tmp_;
	}
	catch (nlohmann::detail::exception e) {
		logger.error(e.what());
	}
}
