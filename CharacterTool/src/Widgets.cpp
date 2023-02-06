#include "Widgets.h"

using namespace KGCA41B;

void GwMainMenu::Update()
{
    msg_ = MsgType::NONE;
	ImGui::SetCurrentContext(GUI->GetContext());
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
}

void GwMainMenu::Render()
{
    ImGui::BeginMainMenuBar();
    {
        if (ImGui::BeginMenu("Open"))
        {
            if (ImGui::MenuItem("FBX"))
            {
                msg_ = MsgType::OW_FBX_IMPORTER;
            }

            ImGui::EndMenu();
        }
    }
    ImGui::EndMainMenuBar();
}

void GwFbxImporter::Update()
{

}

void GwFbxImporter::Render()
{
    ImGui::Begin("FbxImporter", &open_, ImGuiWindowFlags_NoDocking);

    {
        ImGui::SetWindowSize(ImVec2(300, 600));;
    }


    ImGui::End();
}
