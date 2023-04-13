#include "GwMainMenu.h"
#include "GwCharacterWindow.h"
#include "GwFbxLoader.h"

void GwMainMenu::Init()
{
	file_dialog_.SetTitle("CharacterLoader");
	file_dialog_.SetTypeFilters({ ".chardata" });
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
		if (ImGui::MenuItem("Load Character"))
		{
			file_dialog_.Open();
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


	if (file_dialog_.HasSelected())
	{
		string name = file_dialog_.GetSelected().string();

		file_dialog_.ClearSelected();
	}

	file_dialog_.Display();
}