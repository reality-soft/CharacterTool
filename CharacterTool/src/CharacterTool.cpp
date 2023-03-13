#include "CharacterTool.h"
#include "Engine_include.h"
#include "Movements.h"

using namespace reality;

void CharacterTool::OnInit()
{
	AABBShape aabb;
	
	SCENE_MGR->AddPlayer<PlayerActor>();
	sys_camera_.OnCreate(reg_scene_);
	sys_camera_.TargetTag(reg_scene_, camera_mode);

	// Manager Init
	DATA->Init("../../Contents/Data");
	DATA->LoadDir("../../Contents/Data");
	RESOURCE->Init("../../Contents");
	LoadResource();

	level.Create("DeadPoly_FullLevel.ltmesh", "LevelVS.cso", "LevelGS.cso");
	
	// Component Init
	ComponentSystem::GetInst()->OnInit(reg_scene_);

	sys_render_.OnCreate(reg_scene_);

	//GUI
	GUI->AddWidget("MainMenu", new GwMainMenu());
	
	shared_ptr<PlayerActor> character_actor = dynamic_pointer_cast<PlayerActor>(SCENE_MGR->GetPlayer(0).lock());
	// Key Settings
	INPUT_EVENT->Subscribe({ DIK_D }, std::bind(&PlayerActor::MoveRight, character_actor.get()), KEY_HOLD);
	INPUT_EVENT->Subscribe({ DIK_W, DIK_D }, std::bind(&PlayerActor::MoveRightForward, character_actor.get()), KEY_HOLD);
	INPUT_EVENT->Subscribe({ DIK_S, DIK_D }, std::bind(&PlayerActor::MoveRightBack, character_actor.get()), KEY_HOLD);
	INPUT_EVENT->Subscribe({ DIK_A }, std::bind(&PlayerActor::MoveLeft, character_actor.get()), KEY_HOLD);
	INPUT_EVENT->Subscribe({ DIK_W, DIK_A }, std::bind(&PlayerActor::MoveLeftForward, character_actor.get()), KEY_HOLD);
	INPUT_EVENT->Subscribe({ DIK_S, DIK_A }, std::bind(&PlayerActor::MoveLeftBack, character_actor.get()), KEY_HOLD);
	INPUT_EVENT->Subscribe({ DIK_W }, std::bind(&PlayerActor::MoveForward, character_actor.get()), KEY_HOLD);
	INPUT_EVENT->Subscribe({ DIK_S }, std::bind(&PlayerActor::MoveBack, character_actor.get()), KEY_HOLD);

	std::function<void()> idle = std::bind(&PlayerActor::Idle, character_actor.get());
	INPUT_EVENT->Subscribe({ DIK_D }, idle, KEY_UP);
	INPUT_EVENT->Subscribe({ DIK_S }, idle, KEY_UP);
	INPUT_EVENT->Subscribe({ DIK_W }, idle, KEY_UP);
	INPUT_EVENT->Subscribe({ DIK_A }, idle, KEY_UP);
	INPUT_EVENT->Subscribe({ DIK_SPACE }, idle, KEY_UP);

	INPUT_EVENT->Subscribe({ DIK_SPACE }, std::bind(&PlayerActor::Fire, character_actor.get()), KEY_HOLD);


	INPUT_EVENT->Subscribe({ DIK_1 }, Movements::CameraModeChange, KEY_PUSH);

	sys_light_.OnCreate(reg_scene_);
}

void CharacterTool::OnUpdate()
{
	level.Update();
	sys_camera_.OnUpdate(reg_scene_);

	INPUT_EVENT->PollEvents();
	sys_light_.OnUpdate(reg_scene_);
	
	sys_movement_.OnUpdate(reg_scene_);
}

void CharacterTool::OnRender()
{   
	level.Render();
	sys_render_.OnUpdate(reg_scene_);

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