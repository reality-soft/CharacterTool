#include "Widgets.h"
#include "CharacterTool.h"

using namespace KGCA41B;

#define LISTBOX_WIDTH 150.0f
#define TEXT_WIDTH 150.0f

#define GET_VARIABLE_NAME(n) #n

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
			GUI->AddWidget("CharacterTool", new GwCharacterWindow);
		}
	}
	ImGui::EndMainMenuBar();
}

void GwCharacterWindow::Update()
{
	ImGui::SetCurrentContext(GUI->GetContext());
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
}

void GwCharacterWindow::Render()
{
	ImGui::SetNextWindowSize(ImVec2(600, 600));
	ImGui::Begin("Character Tool", &open_, ImGuiWindowFlags_MenuBar);
	{
		string clicked = "";
		ImGui::BeginMenuBar();
		{
			if (loading_data_id_.size() != 0)
				LoadCharacterData();

			if (ImGui::BeginMenu("Current Character"))
			{
				CharacterBoard();
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Load Character"))
			{
				if (ImGui::MenuItem("Loading From DataManager"))
				{
					auto widget = new GwDataViewer;
					GUI->AddWidget("FileViewer", widget);
				}
				ImGui::EndMenu();
			}
		}
		ImGui::EndMenuBar();
	}
	ImGui::End();
}

void GwCharacterWindow::CharacterBoard()
{
	ImVec2 img_size = { 200, 200 };
	ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcItemSize(img_size, img_size.x, img_size.y).x) / 4);

	ImGui::InputText("CharacterName", input_character_data.character_name, 100);


	ImGui::NewLine();
	//SelectFrame(character_data.max_frame, character_data.cur_frame);
	//ImGui::NewLine();

	SelectTexture(input_character_data.texture_id);

	ImGui::SameLine();
	SelectAnimation(input_character_data.anim_id);
	ImGui::Text(input_character_data.texture_id.c_str());
	ImGui::SameLine();
	ImGui::Text(input_character_data.anim_id.c_str());

	SelectSKM(input_character_data.skm_id);
	ImGui::SameLine();
	SelectSKT(input_character_data.skeleton_id);
	ImGui::Text(input_character_data.skm_id.c_str());
	ImGui::SameLine();
	ImGui::Text(input_character_data.skeleton_id.c_str());

	SelectVertexShader(input_character_data.vs_id);
	ImGui::SameLine();
	SelectPixelShader(input_character_data.ps_id);
	ImGui::Text(input_character_data.vs_id.c_str());
	ImGui::SameLine();
	ImGui::Text(input_character_data.ps_id.c_str());

	ImGui::NewLine();
	ImGui::NewLine();
	if (ImGui::Button("Save"))
	{
		SaveCharacterData(input_character_data);
	}
	ImGui::SameLine();
	if (ImGui::Button("Render"))
	{
		auto scene = SCENE->LoadScene("CharacterTool");
		CharacterTool* character_scene = dynamic_cast<CharacterTool*>(scene);
		if (character_scene)
			character_scene->character_actor.SetCharacterData(character_scene->reg_scene, input_character_data);
	}
}

void GwCharacterWindow::SelectFrame(int& max_frame, int& cur_frame)
{
	ImGui::SetNextItemWidth(100.0f);
	ImGui::InputInt("Max Frame", &max_frame);

	ImGui::SameLine();
	ImGui::SetNextItemWidth(200.0f);
	ImGui::SliderInt("Frame", &cur_frame, 1, max_frame);

	static bool bPlay = false;
	static float timer = cur_frame;

	ImGui::SameLine();
	if (ImGui::Button("Play"))
	{
		bPlay = true;
	}
	ImGui::SameLine();
	if (ImGui::Button("Pause"))
	{
		bPlay = false;
	}
	ImGui::SameLine();
	if (ImGui::Button("Stop"))
	{
		bPlay = false;
		cur_frame = 1;
		timer = cur_frame;
	}

	if (bPlay)
	{
		timer += TIMER->GetDeltaTime();
		if (timer > max_frame + 1)
			timer -= max_frame;
		cur_frame = (int)timer;
	}

}

void GwCharacterWindow::SelectVertexShader(string& id)
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
	if (ImGui::BeginListBox("Vertex Shader"))
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
}

void GwCharacterWindow::SelectPixelShader(string& id)
{
	static int item_current_idx = 0;

	auto ps_set = RESOURCE->GetTotalPSID();
	vector<string> ps_vec(ps_set.begin(), ps_set.end());

	for (int i = 0; i < ps_vec.size(); i++)
	{
		if (ps_vec[i] == id)
			item_current_idx = i;
	}

	ImGui::SetNextItemWidth(LISTBOX_WIDTH);
	if (ImGui::BeginListBox("Pixel Shader"))
	{
		for (int n = 0; n < ps_vec.size(); n++)
		{
			const bool is_selected = (item_current_idx == n);
			if (ImGui::Selectable(ps_vec[n].c_str(), is_selected))
				item_current_idx = n;

			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndListBox();
	}

	if (ps_vec.size() != 0) id = ps_vec[item_current_idx];
}

void GwCharacterWindow::SelectTexture(string& id)
{
	int item_current_idx = 0;

	auto tex_set = RESOURCE->GetTotalTexID();
	vector<string> tex_vec(tex_set.begin(), tex_set.end());

	for (int i = 0; i < tex_vec.size(); i++)
	{
		if (tex_vec[i] == id)
			item_current_idx = i;
	}

	ImGui::SetNextItemWidth(LISTBOX_WIDTH);
	if (ImGui::BeginListBox("Texture            "))
	{
		for (int n = 0; n < tex_vec.size(); n++)
		{
			const bool is_selected = (item_current_idx == n);
			if (ImGui::Selectable(tex_vec[n].c_str(), is_selected))
				item_current_idx = n;

			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndListBox();
	}

	if (tex_vec.size() != 0)id = tex_vec[item_current_idx];
}

void GwCharacterWindow::SelectAnimation(string& id)
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
	if (ImGui::BeginListBox("Animation"))
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
}

void GwCharacterWindow::SelectSKM(string& id)
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
	if (ImGui::BeginListBox("SkeletalMesh  "))
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
}

void GwCharacterWindow::SelectSKT(string& id)
{
	int item_current_idx = 0;

	auto skt_set = RESOURCE->GetTotalSKID();
	vector<string> skt_vec(skt_set.begin(), skt_set.end());

	for (int i = 0; i < skt_vec.size(); i++)
	{
		if (skt_vec[i] == id)
			item_current_idx = i;
	}

	ImGui::SetNextItemWidth(LISTBOX_WIDTH);
	if (ImGui::BeginListBox("Skeleton"))
	{
		for (int n = 0; n < skt_vec.size(); n++)
		{
			const bool is_selected = (item_current_idx == n);
			if (ImGui::Selectable(skt_vec[n].c_str(), is_selected))
				item_current_idx = n;

			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndListBox();
	}

	if (skt_vec.size() != 0)id = skt_vec[item_current_idx];
}

void GwCharacterWindow::SaveCharacterData(CharacterData& data)
{
	string sheetName(data.character_name);
	if (sheetName.length() == 0)
		return;
	sheetName += ".csv";

	auto sheet = DATA->AddNewSheet(DATA->directory() + '/' + sheetName);

	auto character = sheet->AddItem(data.character_name);

	sheet->AddCategory("character_name");
	sheet->AddCategory("anim_id");
	sheet->AddCategory("max_frame");
	sheet->AddCategory("cur_frame");
	sheet->AddCategory("skm_id");
	sheet->AddCategory("skeleton_id");
	sheet->AddCategory("vs_id");
	sheet->AddCategory("texture_id");
	sheet->AddCategory("ps_id");

	character->SetValue("character_name", data.character_name);
	character->SetValue("anim_id", data.anim_id);
	character->SetValue("max_frame", to_string(data.max_frame));
	character->SetValue("cur_frame", to_string(data.cur_frame));
	character->SetValue("skm_id", data.skm_id);
	character->SetValue("skeleton_id", data.skeleton_id);
	character->SetValue("vs_id", data.vs_id);
	character->SetValue("texture_id", data.texture_id);
	character->SetValue("ps_id", data.ps_id);

	DATA->SaveSheetFile(DATA->directory() + '/' + sheetName);
}

void GwCharacterWindow::LoadCharacterData()
{
	auto sheet = DATA->LoadSheet(loading_data_id_);

	auto strs1 = split(loading_data_id_, '/');
	auto strs = split(strs1[strs1.size() - 1], '.');
	auto name = strs[0];

	auto item = sheet->LoadItem(name);
	if (item == NULL)
		return;

	strncpy(input_character_data.character_name, item->GetValue("character_name").c_str(), item->GetValue("character_name").size());
	input_character_data.max_frame = stoi(item->GetValue("max_frame"));
	input_character_data.cur_frame = stoi(item->GetValue("cur_frame"));
	input_character_data.texture_id = item->GetValue("texture_id");
	input_character_data.skm_id = item->GetValue("skm_id");
	input_character_data.skeleton_id = item->GetValue("skeleton_id");
	input_character_data.vs_id = item->GetValue("vs_id");
	input_character_data.ps_id = item->GetValue("ps_id");

	loading_data_id_ = "";
}

void GwDataViewer::Update()
{
	ImGui::SetCurrentContext(GUI->GetContext());
}

void GwDataViewer::Render()
{
	ImGui::Begin("Load Character File", &open_);
	{
		static int item_current_idx = 0;

		DATA->LoadAllData();
		auto id_list = DATA->GetAllDataSheetID();
		if (ImGui::BeginListBox("Data File"))
		{
			for (int n = 0; n < id_list.size(); n++)
			{
				const bool is_selected = (item_current_idx == n);
				if (ImGui::Selectable(id_list[n].c_str(), is_selected))
					item_current_idx = n;

				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndListBox();
		}
		if (ImGui::Button("Load"))
		{
			if (id_list.size() == 0)
			{
			}
			else
			{
				auto tool_window = dynamic_cast<GwCharacterWindow*>(GUI->FindWidget("CharacterTool"));
				tool_window->set_loading_data_id(id_list[item_current_idx]);
			}
		}
	}
	ImGui::End();
}
