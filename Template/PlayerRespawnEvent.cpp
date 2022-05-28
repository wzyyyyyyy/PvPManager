#include "pch.h"
#include "EventHeaders.h"

bool PlayerRespawnEV(const Event::PlayerRespawnEvent& ev) {
	auto name = PvP(ev.mPlayer).getLastKilledBy();
	if (name.length() >= 3) {
		ev.mPlayer->sendText(tr("pvp.respawn.text", name));
	}
	return true;
}

THook(void, "?respawn@Player@@UEAAXXZ", Player* pl) {
	original(pl);
	if (PvP(pl).isFirstJoin()) {
		auto eff = MobEffectInstance::MobEffectInstance((int)MobEffect::EffectType::Resistance, 3500, 3, 0, 1, 1);
		pl->addEffect(eff);
	}
	else {
		auto eff = MobEffectInstance::MobEffectInstance((int)MobEffect::EffectType::Resistance, 200, 1, 0, 1, 1);
		pl->addEffect(eff);
	}
}
/*
if ( *((_BYTE *)this + 616) )
  {
	v2 = 0;
	v3 = (*(__int64 (__fastcall **)(_QWORD))(***((_QWORD ***)this + 9) + 1760i64))(**((_QWORD **)this + 9));
	v4 = *(const struct OwnerStorageEntity **)(v3 + 8);
	for ( i = *(const struct OwnerStorageEntity **)v3; i != v4; i = (const struct OwnerStorageEntity *)((char *)i + 24) )
	{
	  StackResultStorageEntity::StackResultStorageEntity((StackResultStorageEntity *)v16, i);
	  if ( Actor::tryGetFromEntity((StackResultStorageEntity *)v16) )
		++v2;
	}
	v6 = ServiceLocator<AppPlatform>::get(v16);
	v7 = (*(__int64 (__fastcall **)(_QWORD))(***(_QWORD ***)(v6 + 16) + 1584i64))(**(_QWORD **)(v6 + 16));
	ServiceReference<AppPlatform>::~ServiceReference<AppPlatform>(v16);
	v8 = *((_QWORD *)this + 13);
	v9 = *(void (__fastcall **)(__int64, char *, __int64, _QWORD, int, int, char))(*(_QWORD *)v8 + 24i64);
	v10 = *((_DWORD *)this + 188);
	v11 = (*(__int64 (__fastcall **)(_QWORD))(***((_QWORD ***)this + 9) + 1160i64))(**((_QWORD **)this + 9));
	GameType = LevelData::getGameType(v11);
	v13 = (*(__int64 (__fastcall **)(_QWORD))(***((_QWORD ***)this + 9) + 1160i64))(**((_QWORD **)this + 9));
	BoneAnimations = ActorSkeletalAnimation::getBoneAnimations(v13);
	v15 = v7;
	v9(v8, (char *)this + 632, BoneAnimations, GameType, v2, v10, v15);
  }*/
