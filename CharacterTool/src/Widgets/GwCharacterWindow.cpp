#include "GwCharacterWindow.h"
#include "PlayerActor.h"
using namespace reality;

#define LISTBOX_WIDTH 300.0f
#define TEXT_WIDTH 150.0f

#define GET_VARIABLE_NAME(n) #n

void GwCharacterWindow::Init()
{
	SCENE_MGR->AddPlayer<PlayerActor>();
}

void GwCharacterWindow::Update()
{
	ImGui::SetCurrentContext(GUI->GetContext());
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
}

void GwCharacterWindow::Render()
{
	ImGui::SetNextWindowSize(ImVec2(600, 600));
	ImGui::Begin("Current Character", &open_);
	{
		ImGui::Text("Character Name:");
		ImGui::SameLine();
		ImGui::InputText("##Character Name", input_character_data.character_name, 100);
		ImGui::Separator();

		SetBoundingBox(input_character_data.x, input_character_data.y, input_character_data.z);

		SetSkeletalMesh();

		if (is_skm_set_ == false) {
			ImGui::NewLine();
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
			ImGui::Text("Please select valid Skeletal Mesh and Vertex Shader first");
			ImGui::PopStyleColor();
			ImGui::NewLine();
			ImGui::BeginDisabled();
		}

		ImGui::NewLine();
		if (ImGui::Button("Save"))
		{
			SaveCharacterData(input_character_data);
		}
		ImGui::SameLine();
		if (ImGui::Button("Render"))
		{
			auto player = SCENE_MGR->GetPlayer<PlayerActor>(0);
			if (player != nullptr) {
				player->SetCharacterData(input_character_data);
			}
		}

		if (is_skm_set_ == false) {
			ImGui::EndDisabled();
		}
	}
	ImGui::End();
}

void GwCharacterWindow::SetSkeletalMesh()
{
	ImGui::SetNextItemOpen(true, ImGuiCond_FirstUseEver);
	if (ImGui::CollapsingHeader("Mesh vertex option"))
	{
		SelectSKM(input_character_data.skeletal_mesh_component.skeletal_mesh_id);
		SelectVertexShader(input_character_data.skeletal_mesh_component.vertex_shader_id);
		SetTransform(input_character_data.skeletal_mesh_component);
		ImGui::NewLine();

		SkeletalMesh* skm_ptr = RESOURCE->UseResource<SkeletalMesh>(input_character_data.skeletal_mesh_component.skeletal_mesh_id);
		VertexShader* vs_ptr = RESOURCE->UseResource<VertexShader>(input_character_data.skeletal_mesh_component.vertex_shader_id);

		if (skm_ptr != nullptr && vs_ptr != nullptr) {
			is_skm_set_ = true;
		}
		else {
			is_skm_set_ = false;
		}
	}
}

void GwCharacterWindow::SetTransform(C_Transform& transform)
{
	static XMVECTOR translation_vector{ .0f, .0f, .0f, .0f };
	static XMVECTOR rotation_vector{ .0f, .0f, .0f, .0f };
	static XMVECTOR scale_vector{ .0f, .0f, .0f, .0f };

	if (ImGui::TreeNode("Transform")) {
		if (ImGui::TreeNode("Scale"))
		{
			ImGui::Text("X");	ImGui::SameLine();
			ImGui::InputFloat("##inputX", &scale_vector.m128_f32[0]);

			ImGui::Text("Y");	ImGui::SameLine();
			ImGui::InputFloat("##inputY", &scale_vector.m128_f32[1]);

			ImGui::Text("Z");	ImGui::SameLine();
			ImGui::InputFloat("##inputZ", &scale_vector.m128_f32[2]);

			if (ImGui::Button("Reset##Y"))
			{
				scale_vector = XMVectorZero();
			}

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Rotation"))
		{
			ImGui::Text("Yaw");	ImGui::SameLine();
			ImGui::InputFloat("##inputX", &rotation_vector.m128_f32[0]);


			ImGui::Text("Pitch");	ImGui::SameLine();
			ImGui::InputFloat("##inputY", &rotation_vector.m128_f32[1]);

			ImGui::Text("Roll");	ImGui::SameLine();
			ImGui::InputFloat("##inputZ", &rotation_vector.m128_f32[2]);

			if (ImGui::Button("Reset##Y"))
			{
				rotation_vector = XMVectorZero();
			}

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Translation"))
		{
			ImGui::Text("X");	ImGui::SameLine();
			ImGui::InputFloat("##inputX", &translation_vector.m128_f32[0]);


			ImGui::Text("Y");	ImGui::SameLine();
			ImGui::InputFloat("##inputY", &translation_vector.m128_f32[1]);

			ImGui::Text("Z");	ImGui::SameLine();
			ImGui::InputFloat("##inputZ", &translation_vector.m128_f32[2]);

			if (ImGui::Button("Reset##Y"))
			{
				translation_vector = XMVectorZero();
			}

			ImGui::TreePop();
		}
		ImGui::TreePop();
	}

	XMMATRIX scale_matrix = XMMatrixScalingFromVector(scale_vector);
	XMMATRIX rotation_matrix = XMMatrixRotationX(XMConvertToRadians(rotation_vector.m128_f32[0])) *
							   XMMatrixRotationY(XMConvertToRadians(rotation_vector.m128_f32[1])) *
							   XMMatrixRotationZ(XMConvertToRadians(rotation_vector.m128_f32[2]));
	XMMATRIX translation_matrix = XMMatrixTranslationFromVector(translation_vector);

	transform.local = scale_matrix * rotation_matrix * translation_matrix;
}

void GwCharacterWindow::SelectVertexShader(string& id)
{
	if (ImGui::TreeNode("Vertex Shader"))
	{
		static int item_current_idx = 0;

		auto vs_set = RESOURCE->GetTotalVSID();
		vector<string> vs_vec(vs_set.begin(), vs_set.end());

		for (int i = 0; i < vs_vec.size(); i++)
		{
			if (vs_vec[i] == id)
				item_current_idx = i;
		}

		ImGui::SetNextItemWidth(LISTBOX_WIDTH);
		if (ImGui::BeginListBox(""))
		{
			for (int n = 0; n < vs_vec.size(); n++)
			{
				const bool is_selected = (item_current_idx == n);
				if (ImGui::Selectable(vs_vec[n].c_str(), is_selected))
					item_current_idx = n;

				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndListBox();
		}

		if (vs_vec.size() != 0) id = vs_vec[item_current_idx];
		ImGui::TreePop();
	}

	PrintSelectedItem("Vertex Shader", input_character_data.skeletal_mesh_component.vertex_shader_id);
}

void GwCharacterWindow::SelectAnimation(string& id)
{
	if (ImGui::TreeNode("Animation"))
	{
		int item_current_idx = 0;

		auto anim_set = RESOURCE->GetTotalANIMID();
		vector<string> anim_vec(anim_set.begin(), anim_set.end());

		for (int i = 0; i < anim_vec.size(); i++)
		{
			if (anim_vec[i] == id)
				item_current_idx = i;
		}

		ImGui::SetNextItemWidth(LISTBOX_WIDTH);
		if (ImGui::BeginListBox(""))
		{
			for (int n = 0; n < anim_vec.size(); n++)
			{
				const bool is_selected = (item_current_idx == n);
				if (ImGui::Selectable(anim_vec[n].c_str(), is_selected))
					item_current_idx = n;

				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndListBox();
		}

		if (anim_vec.size() != 0)id = anim_vec[item_current_idx];
		ImGui::TreePop();
	}

	PrintSelectedItem("Animation", "animation");
}

void GwCharacterWindow::SelectSKM(string& id)
{
	if (ImGui::TreeNode("Skeletal Mesh"))
	{
		int item_current_idx = 0;

		auto skm_set = RESOURCE->GetTotalSKMID();
		vector<string> skm_vec(skm_set.begin(), skm_set.end());

		for (int i = 0; i < skm_vec.size(); i++)
		{
			if (skm_vec[i] == id)
				item_current_idx = i;
		}

		ImGui::SetNextItemWidth(LISTBOX_WIDTH);
		if (ImGui::BeginListBox(""))
		{
			for (int n = 0; n < skm_vec.size(); n++)
			{
				const bool is_selected = (item_current_idx == n);
				if (ImGui::Selectable(skm_vec[n].c_str(), is_selected))
					item_current_idx = n;

				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndListBox();
		}

		if (skm_vec.size() != 0)id = skm_vec[item_current_idx];
		ImGui::TreePop();
	}
	PrintSelectedItem("Skeletal Mesh", input_character_data.skeletal_mesh_component.skeletal_mesh_id);
}

void GwCharacterWindow::SetBoundingBox(int& x, int& y, int& z)
{
	if (ImGui::CollapsingHeader("Bounding Box"))
	{
		ImGui::InputInt("x", &x, 1, 10, ImGuiInputTextFlags_CharsDecimal);
		ImGui::InputInt("y", &y, 1, 10, ImGuiInputTextFlags_CharsDecimal);
		ImGui::InputInt("z", &z, 1, 10, ImGuiInputTextFlags_CharsDecimal);
	}
}

void GwCharacterWindow::PrintSelectedItem(std::string category, std::string selected_item)
{
	category = "Selected " + category + ": ";
	ImGui::Separator();
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.7f, 0.7f, 0.7f, 1.0f));
	ImGui::Text(category.c_str());
	ImGui::PopStyleColor();
	ImGui::SameLine();
	ImGui::Text(selected_item.c_str());
	ImGui::Separator();
}

void GwCharacterWindow::SaveCharacterData(const CharacterData& data)
{
	string sheet_name(data.character_name);
	if (sheet_name.length() == 0)
		return;

	auto sheet = DATA->AddNewSheet(sheet_name);

	auto character = sheet->AddItem(data.character_name);

	sheet->AddCategory("character_name");
	sheet->AddCategory("anim_id");
	sheet->AddCategory("skm_id");
	sheet->AddCategory("vs_id");
	sheet->AddCategory("x");
	sheet->AddCategory("y");
	sheet->AddCategory("z");

	character->SetValue("character_name", data.character_name);
	character->SetValue("skm_id", data.skeletal_mesh_component.skeletal_mesh_id);
	character->SetValue("vs_id", data.skeletal_mesh_component.vertex_shader_id);
	character->SetValue("x", to_string(data.x));
	character->SetValue("y", to_string(data.y));
	character->SetValue("z", to_string(data.z));

	DATA->SaveSheetFile(sheet_name);
}

void GwCharacterWindow::LoadCharacterData(string loading_data_id)
{
	auto sheet = DATA->LoadSheet(loading_data_id);

	auto strs1 = split(loading_data_id, '/');
	auto strs = split(strs1[strs1.size() - 1], '.');
	auto name = strs[0];

	auto item = sheet->LoadItem(name);
	if (item == NULL)
		return;

	strncpy(input_character_data.character_name, item->GetValue("character_name").c_str(), item->GetValue("character_name").size());
	input_character_data.skeletal_mesh_component.skeletal_mesh_id = item->GetValue("skm_id");
	input_character_data.skeletal_mesh_component.vertex_shader_id = item->GetValue("vs_id");
	input_character_data.x = stoi(item->GetValue("x"));
	input_character_data.y = stoi(item->GetValue("y"));
	input_character_data.z = stoi(item->GetValue("z"));

	loading_data_id = "";
}
