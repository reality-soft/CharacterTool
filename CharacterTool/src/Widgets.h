#pragma once
#include "PlayerActor.h"

#define GWNAME(gwclass) typeid(gwclass).name()
using namespace reality;

enum class MsgType
{
	NONE,
	OW_RES_VIEWER,
	OW_COMP_VIEWER,
};

class GwMainMenu : public reality::GuiWidget
{
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	MsgType msg_ = MsgType::NONE;
	ImGui::FileBrowser file_dialog;

};

class GwCharacterWindow : public reality::GuiWidget
{
public:
	virtual void Update() override;
	virtual void Render() override;
private:
	void	CharacterBoard();
	void	SelectFrame(int& max_frame, int& cur_frame);
	void	SelectVertexShader(std::string& id);
	void	SelectPixelShader(std::string& id);
	void	SelectTexture(std::string& id);
	void	SelectAnimation(std::string& id);
	void	SelectSKM(std::string& id);
	void	SetBoundingBox(int& x, int& y, int& z);

private:
	void SaveCharacterData(CharacterData& data);
public:
	void LoadCharacterData(std::string loading_data_id);
public:
	CharacterData input_character_data;
};

class GwDataViewer : public reality::GuiWidget
{
	virtual void Update() override;
	virtual void Render() override;
};

