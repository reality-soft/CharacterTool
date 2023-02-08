#pragma once
#include "Engine_include.h"
#include "PlayerActor.h"

#define GWNAME(gwclass) typeid(gwclass).name()
using namespace KGCA41B;

enum class MsgType
{
	NONE,
	OW_RES_VIEWER,
	OW_COMP_VIEWER,
};

class GwMainMenu : public KGCA41B::GuiWidget
{
public:
	virtual void Update() override;
	virtual void Render() override;

	MsgType msg_ = MsgType::NONE;
};

class GwResViewer : public KGCA41B::GuiWidget
{
public:
	virtual void Update() override;
	virtual void Render() override;

private:
	map<string, string> res_id_map;
};

class GwCompViewer : public KGCA41B::GuiWidget
{
public:
	GwCompViewer(PlayerActor& player_actor);
	virtual void Update() override;
	virtual void Render() override;
private:
	shared_ptr<PlayerActor> player_actor_;
	int select = -1;
};

class GwPorperty : public KGCA41B::GuiWidget
{
public:
	XMMATRIX world_transform_;

public:
	virtual void Update() override;
	virtual void Render() override;
};

