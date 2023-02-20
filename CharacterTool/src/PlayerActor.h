#pragma once
#include "Engine_include.h"
#include "CharacterData.h"
#include "Components.h"

using namespace KGCA41B;

namespace KGCA41B
{
	class PlayerActor : public Actor
	{
	public:
		virtual void OnInit(entt::registry& registry, AABBShape collision_box) override;
		virtual void OnUpdate(entt::registry& registry) override;
		void SetCharacterData(entt::registry& registry, CharacterData data);
	};
}

