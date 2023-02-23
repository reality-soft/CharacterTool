#include "CharacterTool.h"
#include "ComponentSystem.h"

using namespace KGCA41B;

void CharacterTool::OnInit()
{
	DINPUT->Init(ENGINE->GetWindowHandle(), ENGINE->GetInstanceHandle());

	AABBShape aabb;
	character_actor.OnInit(reg_scene, aabb);

	SCENE->PushScene("CharacterTool", this);

	level.ImportFromFile("../../Contents/BinaryPackage/Mountains.lv");
	level.vs_id_ = "LevelVS.cso";
	level.ps_id_ = "LevelPS.cso";
	level.texture_id = { "Ground.png" };

	KGCA41B::QUADTREE->Init(&level, 4);

	// Manager Init
	DATA->Init("../../Contents/Data");
	DATA->LoadDir("../../Contents/Data");
	RESOURCE->Init("../../Contents");
	LoadResource();
	
	// Component Init
	ComponentSystem::GetInst()->OnInit(reg_scene);
	debug_entity_ = reg_scene.create();
	debug_camera_.position = { 0, 100, -200, 0 };
	debug_camera_.look = { 0, -1, 0, 0 };
	debug_camera_.up = { 0, 1, 0, 0 };
	debug_camera_.near_z = 1.f;
	debug_camera_.far_z = 10000.f;
	debug_camera_.fov = XMConvertToRadians(45);
	debug_camera_.yaw = 0;
	debug_camera_.pitch = 0;
	debug_camera_.roll = 0;
	debug_camera_.speed = 100;
	debug_camera_.tag = "Player";
	reg_scene.emplace<C_Camera>(debug_entity_, debug_camera_);

	debug_input_.tag = "Player";
	reg_scene.emplace<C_InputMapping>(debug_entity_, debug_input_);

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
	KGCA41B::QUADTREE->Frame(&sys_camera_);
}

void CharacterTool::OnRender()
{   
	sys_animation_.OnUpdate(reg_scene);
	KGCA41B::QUADTREE->Render();
	sys_render_.OnUpdate(reg_scene);

	// GUI
	GUI->RenderWidgets();
}

void CharacterTool::OnRelease()
{
	RESOURCE->Release();
}

void CharacterTool::LoadResource()
{
	RESOURCE->Init("../../Contents/");
}