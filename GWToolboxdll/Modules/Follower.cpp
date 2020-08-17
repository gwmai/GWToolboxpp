#include "Follower.h"
#include "stdafx.h"

#include <GWCA/Constants/Constants.h>
#include <GWCA/Constants/Maps.h>

#include <GWCA/GameContainers/Array.h>
#include <GWCA/GameContainers/GamePos.h>

#include <GWCA/GameEntities/Map.h>
#include <GWCA/GameEntities/NPC.h>
#include <GWCA/GameEntities/Agent.h>
#include <GWCA/GameEntities/Guild.h>
#include <GWCA/GameEntities/Skill.h>
#include <GWCA/GameEntities/Player.h>

#include <GWCA/Context/GameContext.h>
#include <GWCA/Context/WorldContext.h>
#include <GWCA/Context/GuildContext.h>

#include <GWCA/Managers/MapMgr.h>
#include <GWCA/Managers/ChatMgr.h>
#include <GWCA/Managers/ItemMgr.h>
#include <GWCA/Managers/StoCMgr.h>
#include <GWCA/Managers/AgentMgr.h>
#include <GWCA/Managers/GuildMgr.h>
#include <GWCA/Managers/CameraMgr.h>
#include <GWCA/Managers/MemoryMgr.h>
#include <GWCA/Managers/PlayerMgr.h>
#include <GWCA/Managers/SkillbarMgr.h>
#include <GWCA/Managers/FriendListMgr.h>
#include <GWCA/Managers/GameThreadMgr.h>
#include <GWCA/Managers/PartyMgr.h>
#include <GWCA/Managers/CtoSMgr.h>

#include <GuiUtils.h>
#include <GWToolbox.h>
#include <Keys.h>
#include <Logger.h>

#include <GWCA\GameContainers\GamePos.h>
#include <Timer.h>

bool Follower::isFollowMode = false; //you must do this in .cpp file
GW::AgentLiving* Follower::target;
clock_t Follower::init = TIMER_INIT();

void Follower::follow()
{

	//known issue that the client may crash if you are following a party member and that member zones before you zone while you try to move to him
	if (TIMER_DIFF(Follower::init) < 200) {
		return;
	}
	else {
		Follower::init = TIMER_INIT();
	}
	if (GW::Map::GetInstanceType() == GW::Constants::InstanceType::Loading)
		return;

	GW::Agent* currentTarget = GW::Agents::GetAgentByID(Follower::target->agent_id);
	if (currentTarget == nullptr) {
		Follower::isFollowMode = false;
		return Log::Error("Please select a target to follow");
	}
	GW::AgentLiving* targetLiving = currentTarget->GetAsAgentLiving();
	GW::AgentLiving* me = GW::Agents::GetPlayerAsAgentLiving();
	if (me->GetIsDead()) {
		return;
	}

	if (Follower::target == nullptr || targetLiving == nullptr) {
		Follower::isFollowMode = false;
		return Log::Error("Please select a target to follow");
	}

	GW::Vec2f p1 = GW::Vec2f(me->x, me->y);
	GW::Vec2f p2 = GW::Vec2f(target->x, target->y);

	float distance = GW::GetDistance(p1, p2);

	if (distance > GW::Constants::Range::Nearby) {
		GW::Agents::Move(target->x, target->y);
	}
}


