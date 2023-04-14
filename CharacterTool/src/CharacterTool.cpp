#include "CharacterTool.h"
#include "Movements.h"
#include "PlayerActor.h"
#include "GwMainMenu.h"

using namespace reality;

void CharacterTool::OnInit()
{
	AABBShape aabb;
	
	COMPONENT->OnInit(reg_scene_);

	SCENE_MGR->AddPlayer<PlayerActor>();
	sys_camera_.OnCreate(reg_scene_);
	sys_camera_.TargetTag(reg_scene_, camera_mode);

	// Manager Init
	DATA->Init("../../Contents/Data");
	DATA->LoadDir("../../Contents/Data");
	RESOURCE->Init("../../Contents");
	LoadResource();

	level.Create("DeadPoly_FullLevel_04.stmesh", "LevelVS.cso");
	// Component Init
	ComponentSystem::GetInst()->OnInit(reg_scene_);

	sys_render_.OnCreate(reg_scene_);

	//GUI
	GUI->AddWidget<GwMainMenu>("MainMenu", reg_scene_);
	
	auto character_actor = SCENE_MGR->GetPlayer<PlayerActor>(0);

	environment_.CreateEnvironment();
	environment_.SetWorldTime(60, 60, true);
	environment_.SetSkyColorByTime(RGB_TO_FLOAT(201, 205, 204), RGB_TO_FLOAT(11, 11, 19));
	environment_.SetFogDistanceByTime(5000, 1000);
	environment_.SetLightProperty(0.2f, 0.2f);

	INPUT_EVENT->SubscribeKeyEvent({ DIK_1 }, Movements::CameraModeChange, KEY_PUSH);

	sys_light_.OnCreate(reg_scene_);
}

void CharacterTool::OnUpdate()
{
	level.Update();
	sys_camera_.OnUpdate(reg_scene_);

	INPUT_EVENT->PollEvents();
	sys_light_.OnUpdate(reg_scene_);

	environment_.Update(&sys_camera_, &sys_light_);
	
	sys_movement_.OnUpdate(reg_scene_);
	sys_animation_.OnUpdate(reg_scene_);
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