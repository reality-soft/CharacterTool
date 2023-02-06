#pragma once
#include "Engine_include.h"

#define GWNAME(gwclass) typeid(gwclass).name()

enum class MsgType
{
	NONE,
	OW_FBX_IMPORTER,
	OW_RES_VIEWER,
};

class GwMainMenu : public KGCA41B::GuiWidget
{
public:
	virtual void Update() override;
	virtual void Render() override;

	MsgType msg_ = MsgType::NONE;
};

class GwFbxImporter : public KGCA41B::GuiWidget
{
public:
	virtual void Update() override;
	virtual void Render() override;

public:
	string filepath_;
};



class GwPorperty : public KGCA41B::GuiWidget
{
public:
	XMMATRIX world_transform_;

public:
	virtual void Update() override;
	virtual void Render() override;
};

