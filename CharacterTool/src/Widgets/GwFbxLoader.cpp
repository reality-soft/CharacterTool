#include "GwFbxLoader.h"
#include "FbxMgr.h"

void GwFbxLoader::Init()
{
}

void GwFbxLoader::Update()
{
}

void GwFbxLoader::Render()
{
	ImGui::SetNextWindowSize(ImVec2(600, 600));
	ImGui::Begin("FbxLoader", &open_, ImGuiWindowFlags_MenuBar);
	{
		string clicked = "";
		ImGui::BeginMenuBar();
		{
			if (ImGui::BeginMenu("Set Loading Option"))
			{
				FbxLoaderBoard();
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Load Fbx"))
			{
				file_dialog_.Open();
				ImGui::EndMenu();
			}

			if (file_dialog_.HasSelected())
			{
				string name = file_dialog_.GetSelected().string();
				reality::FbxImportOption option;

				FBX->ImportAndSaveFbx(name, option, vertex_option_);
				file_dialog_.ClearSelected();
			}

			file_dialog_.Display();
		}
		ImGui::EndMenuBar();
	}
	ImGui::End();
}

void GwFbxLoader::FbxLoaderBoard()
{
	ImGui::Text("Mesh vertex option");
	ImGui::RadioButton("By polygon vertex", (int*)&vertex_option_, static_cast<int>(FbxVertexOption::BY_POLYGON_VERTEX)); ImGui::SameLine();
	ImGui::RadioButton("By control point", (int*)&vertex_option_, static_cast<int>(FbxVertexOption::BY_CONTROL_POINT));
}