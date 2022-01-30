#include "pch.h"
#include "PVP.h"
#include "Global.h"
#include "PvPUtils.h"
#include "PMCommand.h"
#include <EventAPI.h>
#include <MC/Level.hpp>
#include <TranslationAPI.h>
#include <RegCommandAPI.h>
#include <MC/ServerPlayer.hpp>
std::unordered_map<int, Vec3> pointa;

class PMCommand :public Command {
	enum PMOP :int {
		help = 1,
		allow = 2,
		disallow = 3,
		list = 4,
		a = 5,
		b = 6,
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
			outp.addMessage(tr("pvp.command.allow", pl->getNameTag()));
			::Global<Level>->broadcastText(tr("pvp.bc.allowpvp", pl->getNameTag()), TextType::RAW);
			break;
		}
		case PMCommand::disallow: {
			PvP(pl).setStatus(PvPStatus::disallow);
			outp.addMessage(tr("pvp.command.disallow"));
			::Global<Level>->broadcastText(tr("pvp.bc.disallowpvp", pl->getNameTag()), TextType::RAW);
			break;
		}
		case PMCommand::list: {
			auto pls = ::Global<Level>->getAllPlayers();
			std::string allowlist = "";
			std::string disallowlist = "";
			for (auto& i : pls) {
				if (PvP(i).isStatus(PvPStatus::allow))
					allowlist = allowlist.append(i->getNameTag()).append(" , ");
				else
					disallowlist = disallowlist.append(i->getNameTag()).append(" , ");
			}
			outp.addMessage(tr("pvp.command.list", allowlist, disallowlist));
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
		registry->addEnum<PMCommand::PMOP>(
			"PMOP",
			{
				{"help", PMOP::help},
				{"allow", PMOP::allow},
				{"disallow", PMOP::disallow},
				{"list",PMOP::list},
				{"a",PMOP::a},
				{"b",PMOP::b}
			});
		registry->registerOverload<PMCommand>("pm", makeMandatory<CommandParameterDataType::ENUM>(&PMCommand::op, "op", "PMOP"));
	}
};

void initCommand() {
	Event::RegCmdEvent::subscribe([](const Event::RegCmdEvent& e) {
		PMCommand::setup(e.mCommandRegistry);
		return true;
		});
}
