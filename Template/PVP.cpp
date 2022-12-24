#include "pch.h"
#include "PVP.h"
#include "Global.h"
#include "PvPUtils.h"
#include <KVDBAPI.h>
#include <Nlohmann/json.hpp>
#include <PlayerInfoAPI.h>
#include <MC/Player.hpp>
#include <MC/Level.hpp>
#include <MC/AABB.hpp>
#include <unordered_map>

std::unordered_map<Player*, std::string> hist;
std::unordered_map<Player*, bool> area_status;
std::unordered_map<Player*, std::chrono::system_clock::time_point> cooldown;

PvP::PvP(Player* player) {
	this->pl = player;
	this->isinpvparea = area_status[this->pl];
	std::string tmp;
	if (db->get(pl->getXuid(), tmp)) {
		isfirstjoin = false;
		this->status = atoi(tmp.c_str()) ? PvPStatus::allow : PvPStatus::disallow;
		return;
	}
	this->status = PvPStatus::allow;
	isfirstjoin = true;
	db->put(pl->getXuid(), "1");
}

PvPStatus PvP::getStatus() {
	return this->status;
}

void PvP::setStatus(PvPStatus status) {
	this->status = status;
	db->set(pl->getXuid(), std::to_string((int)status));
}

bool PvP::isStatus(PvPStatus status) {
	return this->status == status;
}

std::string PvP::getLastKilledBy() {
	return hist[this->pl];
}

void PvP::setLastKilledBy(std::string pl) {
	hist[this->pl] = pl;
}

bool PvP::isFirstJoin()
{
	return this->isfirstjoin;
}

bool PvP::isInPvPArea() {
	return this->isinpvparea;
}

void PvP::SetInPvPAreaStatus(bool val) {
	this->isinpvparea = val;
	area_status[this->pl] = val;
}

void PvP::StartCoolDown() {
	cooldown[this->pl] = std::chrono::system_clock::now();
}

bool PvP::isInCoolDown() {
	auto& time_a = cooldown[this->pl];
	auto now = std::chrono::system_clock::now();
	return std::chrono::duration_cast<std::chrono::seconds>(now - time_a).count() <= PM::getCoolDownTime();
}

bool PvP::checkPvPStatus(Player* attacker, Player* target) {
	if (attacker->isOP()) return true;
	if (target) {
		auto dimid = attacker->getDimensionId();
		switch (dimid)
		{
		case 0: {
			if (area0.contains(attacker->getPos()))
				return true;
			break;
		}
		case 1: {
			if (area1.contains(attacker->getPos()))
				return true;
			break;
		}
		case 2: {
			if (area2.contains(attacker->getPos()))
				return true;
			break;
		}
		default:
			break;
		}
		if (target->isPlayer()) {
			PvP pl(attacker);
			PvP tar((Player*)target);
			if (pl.isStatus(PvPStatus::allow) && tar.isStatus(PvPStatus::allow))
				return true;

			if (pl.getStatus() == PvPStatus::allow) {
				attacker->sendText(tr("pvp.target.disallow"));
				return false;
			}

			if (pl.getStatus() == PvPStatus::disallow) {
				attacker->sendText(tr("pvp.self.disallow"));
				return false;
			}
		}
	}
	return true;
}
