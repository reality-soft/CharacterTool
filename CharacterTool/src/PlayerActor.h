#pragma once
#include "Engine_include.h"
#include "CharacterData.h"
#include "Components.h"

using namespace KGCA41B;

namespace KGCA41B
{
	class PlayerActor : public Actor
	{
		XMMATRIX transform_;
		float speed_;
	public:
		float GetSpeed() { return speed_; };
		virtual void OnInit(entt::registry& registry, AABBShape collision_box) override;
		virtual void OnUpdate(entt::registry& registry) override;
		void SetCharacterData(entt::registry& registry, CharacterData data);
		void SetCharacterAnimation(entt::registry& registry, string anim_id);
		void PlayerMovement(entt::registry& registry, float x, float y, float z);
	};
}

