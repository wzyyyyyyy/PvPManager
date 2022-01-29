#include "pch.h"
#include "PVP.h"
#include "PvPUtils.h"
#include <RegCommandAPI.h>
#include <TranslationAPI.h>
#include <MC/ServerPlayer.hpp>
#include <EventAPI.h>
#include "Global.h"
std::unordered_map<int, Vec3> pointa;

class PMCommand :public Command {
	enum PMOP :int {
		help = 1,
		allow = 2,
		disallow = 3,
		a = 4,
		b = 5
	} op;
public:
	void execute(CommandOrigin const& ori, CommandOutput& outp) const {
		if (!ori.getPlayer()) {
			outp.addMessage(tr("pvp.only.player"));
			return;
		}
		auto pl = ori.getPlayer();
		switch (op)
		{
		case PMCommand::help: {
			outp.addMessage(tr("pvp.command.help"));
			break;
		}
		case PMCommand::allow: {
			PvP(pl).setStatus(PvPStatus::allow);
			outp.addMessage(tr("pvp.command.allow"));
			break;
		}
		case PMCommand::disallow: {
			PvP(pl).setStatus(PvPStatus::disallow);
			outp.addMessage(tr("pvp.command.disallow"));
			break;
		}
		case PMCommand::a: {
			if (!pl->isOP()) {
				outp.addMessage(tr("pvp.nopermission"));
				return;
			}
			pointa[pl->getDimensionId()] = pl->getPos();
			outp.addMessage(tr("pvp.command.a"));
			break;
		}
		case PMCommand::b: {
			if (!pl->isOP()) {
				outp.addMessage(tr("pvp.nopermission"));
				return;
			}
			auto dimid = pl->getDimensionId();
			auto a = pointa[dimid];
			switch (dimid) {
			case 0: {
				PM::setPvPAreaOfDim0(AABB(a, pl->getPos()));
				break;
			}
			case 1: {
				PM::setPvPAreaOfDim1(AABB(a, pl->getPos()));
				break;
			}
			case 2: {
				PM::setPvPAreaOfDim2(AABB(a, pl->getPos()));
				break;
			}
			}
			PM::initPvPArea();
			outp.addMessage(tr("pvp.command.b"));
			break;
		}
		default:
			break;
		}
	}

	static void setup(CommandRegistry* registry) {
		using RegisterCommandHelper::makeMandatory;
		using RegisterCommandHelper::makeOptional;
		registry->registerCommand("pm", "PvPManager", CommandPermissionLevel::Any, { (CommandFlagValue)0 }, { (CommandFlagValue)0x80 });
		registry->addEnum<PMCommand::PMOP>("PMOP", { {"help", PMOP::help}, {"allow", PMOP::allow}, {"disallow", PMOP::disallow}, {"a",PMOP::a},{"b",PMOP::b} });
		registry->registerOverload<PMCommand>("pm", makeMandatory<CommandParameterDataType::ENUM>(&PMCommand::op, "op", "PMOP"));
	}
};

void initCommand() {
	Event::RegCmdEvent::subscribe([](const Event::RegCmdEvent& e) {
		PMCommand::setup(e.mCommandRegistry);
		return true;
		});
}
