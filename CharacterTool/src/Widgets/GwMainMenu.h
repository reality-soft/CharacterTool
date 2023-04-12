#pragma once
#include "Engine_include.h"

class GwMainMenu : public reality::GuiWidget
{
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	ImGui::FileBrowser file_dialog_;
};