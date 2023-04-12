#pragma once
#include <string>
#include "CharacterData.h"
#include "Engine_include.h"
using namespace reality;

class GwCharacterWindow : public GuiWidget
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