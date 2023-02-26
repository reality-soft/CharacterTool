#include "CharacterTool.h"
#include "ComponentSystem.h"
#include "EventMgr.h"
#include "Movements.h"

using namespace KGCA41B;

void CharacterTool::OnInit()
{
	AABBShape aabb;
	character_actor.OnInit(reg_scene, aabb);

	SCENE->PushScene("CharacterTool", this);

	level.CreateLevel(200, 200, 10, 10);
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
	debug_camera_.position = { 0, 1000, -1000, 0 };
	debug_camera_.look = { 0, -1, 0, 0 };
	debug_camera_.up = { 0, 1, 0, 0 };
	debug_camera_.near_z = 1.f;
	debug_camera_.far_z = 10000.f;
	debug_camera_.fov = XMConvertToRadians(45);
	debug_camera_.yaw = 0;
	debug_camera_.pitch = XMConvertToRadians(45);
	debug_camera_.roll = 0;
	debug_camera_.speed = 100;
	debug_camera_.tag = "Player";
	reg_scene.emplace<C_Camera>(debug_entity_, debug_camera_);


	sys_camera_.TargetTag(reg_scene, "Player");
	sys_camera_.OnCreate(reg_scene);
	sys_render_.OnCreate(reg_scene);

	//GUI
	GUI->AddWidget("MainMenu", new GwMainMenu());


	// Key Settings
	EVENT->Subscribe({ 'D' }, Movements::MoveRight, KEY_HOLD);
	EVENT->Subscribe({ 'W', 'D' }, Movements::MoveRightForward, KEY_HOLD);
	EVENT->Subscribe({ 'S', 'D' }, Movements::MoveRightBack, KEY_HOLD);
	EVENT->Subscribe({ 'A' }, Movements::MoveLeft, KEY_HOLD);
	EVENT->Subscribe({ 'W', 'A' }, Movements::MoveLeftForward, KEY_HOLD);
	EVENT->Subscribe({ 'S', 'A' }, Movements::MoveLeftBack, KEY_HOLD);
	EVENT->Subscribe({ 'W' }, Movements::MoveForward, KEY_HOLD);
	EVENT->Subscribe({ 'S' }, Movements::MoveBack, KEY_HOLD);

	EVENT->Subscribe({ 'D' }, Movements::Idle, KEY_UP);
	EVENT->Subscribe({ 'S' }, Movements::Idle, KEY_UP);
	EVENT->Subscribe({ 'W' }, Movements::Idle, KEY_UP);
	EVENT->Subscribe({ 'A' }, Movements::Idle, KEY_UP);

	EVENT->Subscribe({ VK_SPACE }, Movements::Fire, KEY_HOLD);
	EVENT->Subscribe({ VK_SPACE }, Movements::Idle, KEY_UP);

	sys_light_.OnCreate(reg_scene);
}

void CharacterTool::OnUpdate()
{
	sys_camera_.OnUpdate(reg_scene);
	KGCA41B::QUADTREE->Frame(&sys_camera_);
	EVENT->PollEvents();
	sys_light_.OnUpdate(reg_scene);
}

void CharacterTool::OnRender()
{   
	sys_render_.OnUpdate(reg_scene);
	KGCA41B::QUADTREE->Render();

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