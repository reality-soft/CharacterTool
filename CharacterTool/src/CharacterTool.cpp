#include "CharacterTool.h"
#include "Movements.h"
#include "GwMainMenu.h"

using namespace reality;

void CharacterTool::OnInit()
{
	QUADTREE->view_collisions_ = true;
	QUADTREE->Init(&level, reg_scene_);
	QUADTREE->ImportQuadTreeData("../../Contents/BinaryPackage/QuadTreeData_01.mapdat");
	COMPONENT->OnInit(reg_scene_);

	sys_camera_.OnCreate(reg_scene_);
	sys_camera_.TargetTag(reg_scene_, camera_mode);

	// Manager Init
	DATA->Init("../../Contents/Data");
	DATA->LoadDir("../../Contents/Data");
	RESOURCE->Init("../../Contents");
	LoadResource();

	level.Create("DNDLevel_WithCollision_01.stmesh", "LevelVS.cso");
	// Component Init
	ComponentSystem::GetInst()->OnInit(reg_scene_);

	sys_render_.OnCreate(reg_scene_);

	//GUI
	GUI->AddWidget<GwMainMenu>("MainMenu", reg_scene_);

	environment_.CreateEnvironment();
	environment_.SetWorldTime(60, 60);
	environment_.SetSkyColorByTime(RGB_TO_FLOAT(201, 205, 204), RGB_TO_FLOAT(11, 11, 19));
	environment_.SetFogDistanceByTime(5000, 1000);
	environment_.SetLightProperty(XMFLOAT4(1, 1, 1, 1), XMFLOAT4(1, 1, 1, 1), 0.15, 0.3);

	INPUT_EVENT->SubscribeKeyEvent({ DIK_1 }, Movements::CameraModeChange, KEY_PUSH);

	sys_light_.OnCreate(reg_scene_);

	QUADTREE->InitCollisionMeshes();
}

void CharacterTool::OnUpdate()
{
	level.Update();
	sys_camera_.OnUpdate(reg_scene_);

	INPUT_EVENT->PollEvents();
	sys_light_.OnUpdate(reg_scene_);

	environment_.Update(sys_camera_.GetCamera()->camera_pos, &sys_light_);
	
	sys_movement_.OnUpdate(reg_scene_);
	sys_animation_.OnUpdate(reg_scene_);

	QUADTREE->Frame(&sys_camera_);
}

void CharacterTool::OnRender()
{   
	environment_.Render();
	level.Render();

	sys_render_.OnUpdate(reg_scene_);

	QUADTREE->RenderCollisionMeshes();

	// GUI
	GUI->RenderWidgets();
}

void CharacterTool::OnRelease()
{
	QUADTREE->Release();
	RESOURCE->Release();
}

void CharacterTool::LoadResource()
{
	RESOURCE->Init("../../Contents/");
}