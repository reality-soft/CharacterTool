#pragma once
#include "AnimSlotData.h"
#include "Engine_include.h"

struct CharacterData
{
	char character_name[256] = "";
	reality::C_CapsuleCollision capsule_collision;
	reality::C_SkeletalMesh skeletal_mesh_component;
	vector<pair<string, AnimSlotData>> anim_slots;
};