#include "PlayerStateFactory.h"

#include "../IdleState.h"
#include "../JumpingState.h"
#include "../WalkState.h"

#include "../../Player/Player.h"

PlayerStateFactory* PlayerStateFactory::instance = nullptr;

void PlayerStateFactory::Initialize(class Player& player)
{
	idle = new IdleState(&player);
	jump = new JumpingState(&player);
	walk = new WalkState(&player);
}

void PlayerStateFactory::Finalize()
{
	instance->idle->Finalize();
	instance->jump->Finalize();
	instance->walk->Finalize();

	delete instance->idle;
	delete instance->jump;
	delete instance->walk;
}

PlayerStateBase* PlayerStateFactory::Get(Player& player, ePlayerState state)
{
	if (instance == nullptr)
	{
		instance = new PlayerStateFactory();
		instance->Initialize(player);
	}

	PlayerStateBase* ret = nullptr;
	switch (state)
	{
	case ePlayerState::eIDLE:
		instance->idle->Initialize();
		ret = instance->idle;
		break;
	case ePlayerState::eJUMP:
		instance->jump->Initialize();
		ret = instance->jump;
		break;
	case ePlayerState::eWALK:
		instance->walk->Initialize();
		ret = instance->walk;
	case ePlayerState::eNONE:
	default:
		break;
	}

	return ret;
}