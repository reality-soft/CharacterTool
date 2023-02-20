#include "CharacterTool.h"
#include "ComponentSystem.h"

using namespace KGCA41B;

void CharacterTool::OnInit()
{
	DINPUT->Init(ENGINE->GetWindowHandle(), ENGINE->GetInstanceHandle());

	// Manager Init
	DATA->Init("../../Contents/Data");
	DATA->LoadDir("../../Contents/Data");
	RESOURCE->Init("../../Contents");
	LoadResource();
	
	// Component Init
	ComponentSystem::GetInst()->OnInit(reg_scene);
	debug_entity_ = reg_scene.create();
	debug_camera_.position = { 0, 10, 0, 0 };
	debug_camera_.look = { 0, 0, 0, 0 };
	debug_camera_.target = { 0, 0, 0, 0 };
	debug_camera_.up = { 0, 1, 0, 0 };
	debug_camera_.near_z = 1.f;
	debug_camera_.far_z = 1000.f;
	debug_camera_.fov = XMConvertToRadians(45);
	debug_camera_.yaw = 0;
	debug_camera_.pitch = XMConvertToRadians(90);
	debug_camera_.roll = 0;
	debug_camera_.speed = 30;
	debug_camera_.tag = "Player";
	reg_scene.emplace<Camera>(debug_entity_, debug_camera_);

	sys_camera_.TargetTag(reg_scene, "Player");
	sys_camera_.OnCreate(reg_scene);
	sys_input_.OnCreate(reg_scene);
	sys_render_.OnCreate(reg_scene);

	//GUI
	GUI->AddWidget("MainMenu", new GwMainMenu());
}

void CharacterTool::OnUpdate()
{
	sys_input_.OnUpdate(reg_scene);
	sys_camera_.OnUpdate(reg_scene);

}

void CharacterTool::OnRender()
{   
	sys_animation_.OnUpdate(reg_scene);
	sys_render_.OnUpdate(reg_scene);

	// GUI
	GUI->RenderWidgets();

	sys_render_.OnUpdate(reg_scene);
}

void CharacterTool::OnRelease()
{
	RESOURCE->Release();
}

void CharacterTool::LoadResource()
{
	RESOURCE->Init("../../Contents/");
}