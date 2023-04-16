#pragma once
#include "Engine_include.h"
#include "FbxLoader.h"
using namespace reality;

class GwFbxLoader : public reality::GuiWidget
{
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
private:
	void		 FbxLoaderBoard();
public:
	reality::FbxVertexOption GetVertexOption() {
		return vertex_option_;
	};

private:
	reality::FbxVertexOption vertex_option_;
	ImGui::FileBrowser file_dialog_;
};


