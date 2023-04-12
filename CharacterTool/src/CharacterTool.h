#pragma once
#include "Engine_Include.h"
using namespace reality;

class CharacterTool : public reality::Scene
{
public:
	virtual void OnInit();
	virtual void OnUpdate();
	virtual void OnRender();
	virtual void OnRelease();

public:
	void LoadResource();

	string camera_mode = "Debug";
	reality::CameraSystem sys_camera_;
private:
	StaticMeshLevel level;
	Environment environment_;

	LightingSystem sys_light_;
	RenderSystem  sys_render_;
	MovementSystem  sys_movement_;
	AnimationSystem  sys_animation_;
};

