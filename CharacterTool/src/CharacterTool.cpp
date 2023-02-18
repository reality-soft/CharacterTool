#include "CharacterTool.h"
#include "ComponentSystem.h"

using namespace KGCA41B;

void CharacterTool::OnInit()
{
	DINPUT->Init(ENGINE->GetWindowHandle(), ENGINE->GetInstanceHandle());

	LoadResource();
		
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

	sys_render.OnCreate(reg_scene);
	sys_animation.OnCreate(reg_scene);
	sys_camera.TargetTag(reg_scene, "Player");
	sys_camera.OnCreate(reg_scene);
	sys_input.OnCreate(reg_scene);

	//GUI
	GUI->AddWidget("main_menu", &gw_main_menu_);
}

void CharacterTool::OnUpdate()
{
	sys_input.OnUpdate(reg_scene);
	sys_camera.OnUpdate(reg_scene);

}

void CharacterTool::OnRender()
{   
	sys_animation.OnUpdate(reg_scene);
	sys_render.OnUpdate(reg_scene);

	// GUI
	GUI->RenderWidgets();

	switch (gw_main_menu_.msg_)
	{
	case MsgType::NONE: break;

	case MsgType::OW_RES_VIEWER:
	{
		GwResViewer* gw_res_viewer = new GwResViewer;
		if (GUI->FindWidget(GWNAME(gw_res_viewer)) == nullptr)
		{
			GUI->AddWidget(GWNAME(gw_res_viewer), gw_res_viewer);
		}
	}
	case MsgType::OW_COMP_VIEWER:
	{
		GwCompViewer* gw_comp_viewer = new GwCompViewer(character);
		if (GUI->FindWidget(GWNAME(gw_comp_viewer)) == nullptr)
		{
			GUI->AddWidget(GWNAME(gw_comp_viewer), gw_comp_viewer);
		}
	}
	}
}

void CharacterTool::OnRelease()
{
	RESOURCE->Release();
}

void CharacterTool::LoadResource()
{
	RESOURCE->Init("../../Contents/");
}