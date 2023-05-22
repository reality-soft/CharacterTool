#pragma once
#include <string>
#include "PlayerActor.h"
using namespace reality;

class GwCharacterWindow : public GuiWidget
{
public:
	GwCharacterWindow(entt::registry& reg_scene) : reg_scene_(reg_scene) {};

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
private:
	void	SetSkeletalMesh();
	void	SetTransform(XMMATRIX& transform);
	void	SetCapsuleCollision();

private:
	void	SelectVertexShader(std::string& id);
	void	SelectSKM(std::string& id);

private:
	void	SetAnimSlots();
	void	SetAnimation(std::string& id, const std::string& anim_slot_name);
	void	SetAnimSlotData(AnimSlotData& anim_slot_data);
	void	SetAnimObject(AnimSlotData& anim_slot_data);

private:
	void	SetSocket();
	void	SetSocketData(Socket& socket_data);
	void	SetSocketStaticMesh(C_StaticMesh& static_mesh_component);

private:
	void	SetBone(string& bone_id);

private: 
	void	PrintSelectedItem(std::string category, std::string selected_item);

private:
	void SaveCharacterData(const CharacterData& data);

public:
	void LoadCharacterData(std::string loading_data_id);

public:
	CharacterData input_character_data_;
	vector<string> valid_animation_list_;
	map<string, UINT> bone_name_id_map_;

private:
	bool is_skm_set_ = false;
	bool is_all_anim_set_ = false;

private:
	entt::registry& reg_scene_;
};