#pragma once
#include "Engine_include.h"
#include "CharacterData.h"
#include "Components.h"

using namespace reality;

namespace reality
{
	class PlayerActor : public Character
	{
		XMMATRIX transform_;
	public:
		virtual void OnInit(entt::registry& registry, AABBShape collision_box) override;
		virtual void OnUpdate(entt::registry& registry) override;
		void SetCharacterData(entt::registry& registry, CharacterData data);
		void SetCharacterAnimation(entt::registry& registry, string anim_id);

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

