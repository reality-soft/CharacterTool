#pragma once
#include <string>
#include "CharacterData.h"
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
	void	SetTransform(C_Transform& transform);

private:
	void	SelectVertexShader(std::string& id);
	void	SelectAnimation(std::string& id);
	void	SelectSKM(std::string& id);
	void	SetCapsuleCollision();

private: 
	void	PrintSelectedItem(std::string category, std::string selected_item);

private:
	void SaveCharacterData(const CharacterData& data);

public:
	void LoadCharacterData(std::string loading_data_id);

public:
	CharacterData input_character_data;

private:
	bool is_skm_set_ = false;

private:
	entt::registry& reg_scene_;
};