#pragma once
#include <EventAPI.h>

bool PlayerAttackEV(const Event::PlayerAttackEvent& ev);
bool PlayerDieEV(const Event::PlayerDieEvent& ev);
bool PlayerHurtEV(const Event::MobHurtEvent& ev);
bool PlayerRespawnEV(const Event::PlayerRespawnEvent& ev);

void initEvents();
