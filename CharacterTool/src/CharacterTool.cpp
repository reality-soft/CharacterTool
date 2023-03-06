#include "CharacterTool.h"
#include "ComponentSystem.h"
#include "EventMgr.h"
#include "Movements.h"

using namespace reality;

void CharacterTool::OnInit()
{
	AABBShape aabb;
	character_actor.CharacterInit(reg_scene, aabb);
	sys_camera_.OnCreate(reg_scene);
	sys_camera_.TargetTag(reg_scene, camera_mode);

	SCENE->PushScene("CharacterTool", this);

	// Manager Init
	DATA->Init("../../Contents/Data");
	DATA->LoadDir("../../Contents/Data");
	RESOURCE->Init("../../Contents");
	LoadResource();

	level.CreateLevel(3, 30, 30, { 32 , 32 });
	level.vs_id_ = "LevelVS.cso";
	level.ps_id_ = "LevelPS.cso";
	level.texture_id = { "Ground.png" };

	reality::QUADTREE->Init(&level);
	level.SetCamera(sys_camera_.GetCamera());
	
	// Component Init
	ComponentSystem::GetInst()->OnInit(reg_scene);

	sys_render_.OnCreate(reg_scene);

	//GUI
	GUI->AddWidget("MainMenu", new GwMainMenu());
	
	// Key Settings
	EVENT->Subscribe({ DIK_D }, std::bind(&PlayerActor::MoveRight, &character_actor), KEY_HOLD);
	EVENT->Subscribe({ DIK_W, DIK_D }, std::bind(&PlayerActor::MoveRightForward, &character_actor), KEY_HOLD);
	EVENT->Subscribe({ DIK_S, DIK_D }, std::bind(&PlayerActor::MoveRightBack, &character_actor), KEY_HOLD);
	EVENT->Subscribe({ DIK_A }, std::bind(&PlayerActor::MoveLeft, &character_actor), KEY_HOLD);
	EVENT->Subscribe({ DIK_W, DIK_A }, std::bind(&PlayerActor::MoveLeftForward, &character_actor), KEY_HOLD);
	EVENT->Subscribe({ DIK_S, DIK_A }, std::bind(&PlayerActor::MoveLeftBack, &character_actor), KEY_HOLD);
	EVENT->Subscribe({ DIK_W }, std::bind(&PlayerActor::MoveForward, &character_actor), KEY_HOLD);
	EVENT->Subscribe({ DIK_S }, std::bind(&PlayerActor::MoveBack, &character_actor), KEY_HOLD);

	std::function<void()> idle = std::bind(&PlayerActor::Idle, &character_actor);
	EVENT->Subscribe({ DIK_D }, idle, KEY_UP);
	EVENT->Subscribe({ DIK_S }, idle, KEY_UP);
	EVENT->Subscribe({ DIK_W }, idle, KEY_UP);
	EVENT->Subscribe({ DIK_A }, idle, KEY_UP);
	EVENT->Subscribe({ DIK_SPACE }, idle, KEY_UP);

	EVENT->Subscribe({ DIK_SPACE }, std::bind(&PlayerActor::Fire, &character_actor), KEY_HOLD);


	EVENT->Subscribe({ DIK_1 }, Movements::CameraModeChange, KEY_PUSH);

	sys_light_.OnCreate(reg_scene);
}

void CharacterTool::OnUpdate()
{
	sys_camera_.OnUpdate(reg_scene);

	character_actor.OnUpdate(reg_scene);

	reality::QUADTREE->Frame(&sys_camera_);
	EVENT->PollEvents();
	sys_light_.OnUpdate(reg_scene);
	
	sys_movement_.OnUpdate(reg_scene);
}

void CharacterTool::OnRender()
{   
	reality::QUADTREE->Render();
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