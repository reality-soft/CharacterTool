#include "GwMainMenu.h"
#include "GwCharacterWindow.h"
#include "GwFbxLoader.h"

void GwMainMenu::Init()
{
	file_dialog_.SetTitle("FbxLoader");
	file_dialog_.SetTypeFilters({ ".fbx" });
}

void GwMainMenu::Update()
{
	ImGui::SetCurrentContext(GUI->GetContext());
	//ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
}

void GwMainMenu::Render()
{
	ImGui::BeginMainMenuBar();
	{
		if (ImGui::MenuItem("Character"))
		{
			if (GUI->FindWidget("CharacterTool") == nullptr) {
				GUI->AddWidget("CharacterTool", new GwCharacterWindow);
			}
			else {
				GUI->FindWidget("CharacterTool")->InvertOpen();
			}
		}
		if (ImGui::MenuItem("Load Fbx"))
		{
			if (GUI->FindWidget("FbxOption") == nullptr) {
				GUI->AddWidget("FbxOption", new GwFbxLoader);
			}
			else {
				GUI->FindWidget("FbxOption")->InvertOpen();
			}
		}
	}
	ImGui::EndMainMenuBar();
}