#pragma once
#include "stdafx.h"
using namespace std;

enum class ANIM_OBJECT_TYPE {
	ANIMATION_BASE,
	ANIMATION_STATE_MACHINE
};

struct AnimSlotData {
	string anim_slot_name; 
	string skeletal_mesh_id;
	string bone_id; 
	string animation_name;
	int range = 0;
	ANIM_OBJECT_TYPE anim_object_type = ANIM_OBJECT_TYPE::ANIMATION_BASE;
};