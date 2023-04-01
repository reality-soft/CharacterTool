#include "CharacterTool.h"
#include "PlayerActor.h"
#include "Movements.h"

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

	level.Create("DeadPoly_FullLevel_04.stmesh", "LevelVS.cso", "DeadPoly_Level_Collision_04.stmesh");
	//level.ImportGuideLines("../../Contents/BinaryPackage/DeadPoly_Blocking1.mapdat", GuideLine::GuideType::eBlocking);
	level.ImportGuideLines("../../Contents/BinaryPackage/DeadPoly_NpcTrack_01.mapdat", GuideLine::GuideType::eNpcTrack);
	// Component Init
	ComponentSystem::GetInst()->OnInit(reg_scene_);

	sys_render_.OnCreate(reg_scene_);

	//GUI
	GUI->AddWidget("MainMenu", new GwMainMenu());
	
	auto character_actor = SCENE_MGR->GetPlayer<PlayerActor>(0);
	// Key Settings
	//INPUT_EVENT->SubscribeKeyEvent({ DIK_D }, std::bind(&PlayerActor::MoveRight, character_actor), KEY_HOLD);
	//INPUT_EVENT->SubscribeKeyEvent({ DIK_W, DIK_D }, std::bind(&PlayerActor::MoveRightForward, character_actor), KEY_HOLD);
	//INPUT_EVENT->SubscribeKeyEvent({ DIK_S, DIK_D }, std::bind(&PlayerActor::MoveRightBack, character_actor), KEY_HOLD);
	//INPUT_EVENT->SubscribeKeyEvent({ DIK_A }, std::bind(&PlayerActor::MoveLeft, character_actor), KEY_HOLD);
	//INPUT_EVENT->SubscribeKeyEvent({ DIK_W, DIK_A }, std::bind(&PlayerActor::MoveLeftForward, character_actor), KEY_HOLD);
	//INPUT_EVENT->SubscribeKeyEvent({ DIK_S, DIK_A }, std::bind(&PlayerActor::MoveLeftBack, character_actor), KEY_HOLD);
	//INPUT_EVENT->SubscribeKeyEvent({ DIK_W }, std::bind(&PlayerActor::MoveForward, character_actor), KEY_HOLD);
	//INPUT_EVENT->SubscribeKeyEvent({ DIK_S }, std::bind(&PlayerActor::MoveBack, character_actor), KEY_HOLD);

	//std::function<void()> idle = std::bind(&PlayerActor::Idle, character_actor);
	//INPUT_EVENT->SubscribeKeyEvent({ DIK_D }, idle, KEY_UP);
	//INPUT_EVENT->SubscribeKeyEvent({ DIK_S }, idle, KEY_UP);
	//INPUT_EVENT->SubscribeKeyEvent({ DIK_W }, idle, KEY_UP);
	//INPUT_EVENT->SubscribeKeyEvent({ DIK_A }, idle, KEY_UP);

	//INPUT_EVENT->SubscribeMouseEvent({ MouseButton::L_BUTTON }, std::bind(&PlayerActor::Fire, character_actor), KEY_HOLD);
	//INPUT_EVENT->SubscribeMouseEvent({ MouseButton::L_BUTTON }, idle, KEY_UP);

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