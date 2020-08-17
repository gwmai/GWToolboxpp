#pragma once
#include <thread>

#include <GWCA/Constants/Constants.h>

#include <GWCA/Utilities/Hook.h>
#include <GWCA/GameEntities/Agent.h>

#include <ToolboxModule.h>
#include <ToolboxUIElement.h>

class Follower
{
	public:
		static bool isFollowMode;
		static void follow();
		static GW::AgentLiving* target;
		static clock_t init;
};

