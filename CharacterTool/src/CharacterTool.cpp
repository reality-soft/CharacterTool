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

	//sys_camera_.TargetTag(reg_scene, "Player");
	sys_camera_.OnCreate(reg_scene);
	sys_render_.OnCreate(reg_scene);

	//GUI
	GUI->AddWidget("MainMenu", new GwMainMenu());

	// Key Settings
	//EVENT->Subscribe({ DIK_D }, Movements::MoveRight, KEY_HOLD);
	//EVENT->Subscribe({ DIK_W, DIK_D }, Movements::MoveRightForward, KEY_HOLD);
	//EVENT->Subscribe({ DIK_S, DIK_D }, Movements::MoveRightBack, KEY_HOLD);
	//EVENT->Subscribe({ DIK_A }, Movements::MoveLeft, KEY_HOLD);
	//EVENT->Subscribe({ DIK_W, DIK_A }, Movements::MoveLeftForward, KEY_HOLD);
	//EVENT->Subscribe({ DIK_S, DIK_A }, Movements::MoveLeftBack, KEY_HOLD);
	//EVENT->Subscribe({ DIK_W }, Movements::MoveForward, KEY_HOLD);
	//EVENT->Subscribe({ DIK_S }, Movements::MoveBack, KEY_HOLD);

	//EVENT->Subscribe({ DIK_D }, Movements::Idle, KEY_UP);
	//EVENT->Subscribe({ DIK_S }, Movements::Idle, KEY_UP);
	//EVENT->Subscribe({ DIK_W }, Movements::Idle, KEY_UP);
	//EVENT->Subscribe({ DIK_A }, Movements::Idle, KEY_UP);

	//EVENT->Subscribe({ DIK_SPACE }, Movements::Fire, KEY_HOLD);
	//EVENT->Subscribe({ DIK_SPACE }, Movements::Idle, KEY_UP);

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