#include "CharacterTool.h"
#include "ComponentSystem.h"

using namespace KGCA41B;

void CharacterTool::OnInit()
{
	DINPUT->Init(ENGINE->GetWindowHandle(), ENGINE->GetInstanceHandle());

	LoadResource();
		
	ComponentSystem::GetInst()->OnInit(reg_scene);

	character.Regist(reg_scene);
	character.InitComponents();
	character.BindComponents(reg_scene);

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