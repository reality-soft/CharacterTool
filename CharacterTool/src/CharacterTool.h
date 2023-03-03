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

	string camera_mode = "Player";
	entt::registry reg_scene;
	PlayerActor character_actor;
	KGCA41B::CameraSystem sys_camera_;
private:
	KGCA41B::Level level;

	entt::entity   debug_entity_;

	KGCA41B::C_Camera		debug_camera_;


	KGCA41B::LightingSystem sys_light_;

	KGCA41B::RenderSystem  sys_render_;
};

