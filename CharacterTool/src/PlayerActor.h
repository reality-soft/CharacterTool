#pragma once
#include "Engine_include.h"

using namespace KGCA41B;

class PlayerActor : public Actor
{
public:
	Camera comp_camera_;
	InputMapping comp_input_;

	SkeletalMesh comp_skm_;
	Skeleton comp_skeleton_;
	Animation comp_animation_;
	Material comp_material_;

	void InitComponents();
	void BindComponents(entt::registry& reg);
};

