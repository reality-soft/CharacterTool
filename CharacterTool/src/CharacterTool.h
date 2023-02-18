#pragma once
#include "PlayerActor.h"
#include "Widgets.h"

class CharacterTool : public KGCA41B::Scene
{
public:
	virtual void OnInit();
	virtual void OnUpdate();
	virtual void OnRender();
	virtual void OnRelease();

public:
	void LoadResource();

private:
	entt::registry reg_scene;
	entt::entity   debug_entity_;

	KGCA41B::Camera			debug_camera_;
	KGCA41B::InputMapping	debug_input_;

	KGCA41B::CameraSystem sys_camera_;
	KGCA41B::InputSystem  sys_input_;
	KGCA41B::RenderSystem  sys_render_;
	KGCA41B::AnimationSystem  sys_animation_;
};

