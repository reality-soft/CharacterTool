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

public:
	GwMainMenu gw_main_menu_;

private:
	entt::registry reg_scene;
	entt::entity   debug_entity_;

	PlayerActor character;

	KGCA41B::Camera debug_camera_;

	KGCA41B::RenderSystem sys_render;
	KGCA41B::CameraSystem sys_camera;
	KGCA41B::InputSystem  sys_input;
	KGCA41B::AnimationSystem sys_animation;

};

