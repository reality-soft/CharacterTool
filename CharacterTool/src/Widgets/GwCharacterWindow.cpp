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
		ImGui::InputText("##Character Name", input_character_data_.character_name, 100);
		ImGui::Separator();

		SetCapsuleCollision();

		SetSkeletalMesh();

		if (is_skm_set_ == false) {
			ImGui::NewLine();
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
			ImGui::Text("Please select valid Skeletal Mesh and Vertex Shader first");
			ImGui::PopStyleColor();
			ImGui::BeginDisabled();
		}

		SetAnimSlots();

		if (ImGui::Button("Save"))
		{
			SaveCharacterData(input_character_data_);
		}
		ImGui::SameLine();
		if (ImGui::Button("Render"))
		{
			auto player = SCENE_MGR->GetPlayer<PlayerActor>(0);
			if (player != nullptr) {
				player->SetCharacterData(input_character_data_);
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
		SelectSKM(input_character_data_.skeletal_mesh_component.skeletal_mesh_id);
		SelectVertexShader(input_character_data_.skeletal_mesh_component.vertex_shader_id);
		ImGui::NewLine();

		SkeletalMesh* skm_ptr = RESOURCE->UseResource<SkeletalMesh>(input_character_data_.skeletal_mesh_component.skeletal_mesh_id);
		VertexShader* vs_ptr = RESOURCE->UseResource<VertexShader>(input_character_data_.skeletal_mesh_component.vertex_shader_id);

		if (skm_ptr != nullptr && vs_ptr != nullptr) {
			is_skm_set_ = true;

			bone_name_id_map_ = skm_ptr->skeleton.bone_name_id_map;

			valid_animation_list_.clear();
			auto anim_set = RESOURCE->GetTotalANIMID();
			for (const auto& anim_id : anim_set)
			{
				auto anim = RESOURCE->UseResource<OutAnimData>(anim_id);
				if (anim->animations.size() - 3 == bone_name_id_map_.size()) {
					valid_animation_list_.push_back(anim_id);
				}
			}
		}
		else {
			is_skm_set_ = false;
		}
	}
}

void GwCharacterWindow::SetTransform(C_Transform& transform)
{
	static XMVECTOR scale_vector{ 1.0f, 1.0f, 1.0f, 1.0f };	
	static XMVECTOR rotation_vector{ .0f, .0f, .0f, .0f };
	static XMVECTOR translation_vector{ .0f, .0f, .0f, .0f };

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
				scale_vector = { 1.0f, 1.0f, 1.0f, 1.0f };
			}

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Rotation"))
		{
			ImGui::Text("Yaw");	ImGui::SameLine();
			ImGui::InputFloat("##inputY", &rotation_vector.m128_f32[1]);

			ImGui::Text("Pitch");	ImGui::SameLine();
			ImGui::InputFloat("##inputX", &rotation_vector.m128_f32[0]);

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

	PrintSelectedItem("Vertex Shader", input_character_data_.skeletal_mesh_component.vertex_shader_id);
	ImGui::Separator();
}

void GwCharacterWindow::SetAnimSlots()
{
	for (auto& anim_slot_pair : input_character_data_.anim_slots) {
		auto& anim_slot_name = anim_slot_pair.first;
		auto& anim_slot = anim_slot_pair.second;
		
		string anim_slot_name_title = "anim_slot_name: " + anim_slot_name;
		if (ImGui::TreeNode(anim_slot_name_title.c_str()))
		{

			int item_current_idx = 0;

			string id = "";

			for (int i = 0; i < valid_animation_list_.size(); i++)
			{
				if (valid_animation_list_[i] == id)
					item_current_idx = i;
			}

			ImGui::SetNextItemWidth(LISTBOX_WIDTH);
			string anim_slot_name_example_anim = "Set animation on " + anim_slot_name;
			if (ImGui::BeginListBox(anim_slot_name_example_anim.c_str()))
			{
				for (int n = 0; n < valid_animation_list_.size(); n++)
				{
					const bool is_selected = (item_current_idx == n);
					if (ImGui::Selectable(valid_animation_list_[n].c_str(), is_selected))
						item_current_idx = n;

					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndListBox();
			}

			if (valid_animation_list_.size() != 0) id = valid_animation_list_[item_current_idx];
			ImGui::TreePop();
	
		}
		ImGui::Separator();
	}

	static char anim_slot_name_input[100];
	ImGui::InputText("New anim slot name", anim_slot_name_input, 100);
	if (ImGui::Button("Add new anim slot")) {
		string anim_slot_name = anim_slot_name_input;
		input_character_data_.anim_slots.push_back({ anim_slot_name, AnimSlotData() });
		ZeroMemory(anim_slot_name_input, 100);
	}

	PrintSelectedItem("Animation", "animation");
}

void GwCharacterWindow::SetAnimation(std::string& id)
{
}

void GwCharacterWindow::SelectSKM(string& id)
{
	if (ImGui::TreeNode("Skeletal Mesh"))
	{
		SetTransform(input_character_data_.skeletal_mesh_component);

		if (ImGui::TreeNode("Skeletal Mesh##1")) {
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
		ImGui::TreePop();
	}
	PrintSelectedItem("Skeletal Mesh", input_character_data_.skeletal_mesh_component.skeletal_mesh_id);
	ImGui::Separator();
}

void GwCharacterWindow::SetCapsuleCollision()
{
	SetTransform(input_character_data_.capsule_collision);

	if (ImGui::CollapsingHeader("Capsule Collision"))
	{
		ImGui::InputFloat("height", &input_character_data_.capsule_collision.capsule.height);
		ImGui::InputFloat("radius", &input_character_data_.capsule_collision.capsule.radius);

		if (ImGui::Button("Reset")) {
			input_character_data_.capsule_collision.capsule.height = 0;
			input_character_data_.capsule_collision.capsule.radius = 0;
		}
	}
	ImGui::Separator();
}

void GwCharacterWindow::PrintSelectedItem(std::string category, std::string selected_item)
{
	category = "Selected " + category + ": ";
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.7f, 0.7f, 0.7f, 1.0f));
	ImGui::Text(category.c_str());
	ImGui::PopStyleColor();
	ImGui::SameLine();
	ImGui::Text(selected_item.c_str());
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

	strncpy(input_character_data_.character_name, item->GetValue("character_name").c_str(), item->GetValue("character_name").size());
	input_character_data_.skeletal_mesh_component.skeletal_mesh_id = item->GetValue("skm_id");
	input_character_data_.skeletal_mesh_component.vertex_shader_id = item->GetValue("vs_id");

	loading_data_id = "";
}
