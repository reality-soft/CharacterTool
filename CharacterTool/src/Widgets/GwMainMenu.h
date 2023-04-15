#pragma once
#include "Engine_include.h"

class GwMainMenu : public reality::GuiWidget
{
public:
	GwMainMenu(entt::registry& reg_scene) : reg_scene_(reg_scene) {};

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	ImGui::FileBrowser file_dialog_;

private:
	entt::registry& reg_scene_;
};