#include "pch.h"
#include "Event.h"
#include "Events.h"

void initEvents() {
	Event::PlayerAttackEvent::subscribe(PlayerAttackEV);
	Event::PlayerDieEvent::subscribe(PlayerDieEV);
	Event::MobHurtEvent::subscribe(PlayerHurtEV);
	Event::PlayerRespawnEvent::subscribe(PlayerRespawnEV);
}