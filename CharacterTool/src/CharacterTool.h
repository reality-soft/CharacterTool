#pragma once
#include "Widgets.h"

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
	reality::StaticMeshLevel level;
	Environment environment_;

	reality::LightingSystem sys_light_;
	reality::RenderSystem  sys_render_;
	reality::MovementSystem  sys_movement_;
	reality::AnimationSystem  sys_animation_;
};

