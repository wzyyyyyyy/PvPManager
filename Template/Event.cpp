#include "pch.h"
#include "Event.h"
#include "EventHeaders.h"


void initEvents() {
	Event::PlayerAttackEvent::subscribe(PlayerAttackEV);
	Event::PlayerDieEvent::subscribe(PlayerDieEV);
	Event::MobHurtEvent::subscribe(PlayerHurtEV);
	Event::PlayerRespawnEvent::subscribe(PlayerRespawnEV);
}
