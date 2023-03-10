#pragma once
#include "Engine_include.h"
#include "CharacterData.h"
#include "Components.h"

using namespace reality;

namespace reality
{
	class PlayerActor : public Character
	{
	public:
		virtual void OnInit(entt::registry& registry) override;
		virtual void OnUpdate() override;
		void SetCharacterData(CharacterData data);
		void SetCharacterAnimation(string anim_id);

		void MoveRight();
		void MoveRightForward();
		void MoveRightBack();
		void MoveLeft();
		void MoveLeftForward();
		void MoveLeftBack();
		void MoveForward();
		void MoveBack();
		void Idle();
		void Fire();
	};
}

