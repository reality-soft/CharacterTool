#include "stdafx.h"

#pragma once
struct CharacterData
{
	char character_name[256] = "";
	string anim_id;
	int max_frame, cur_frame;
	string skm_id;
	string skeleton_id;
	string vs_id;
	string texture_id;
	string ps_id;
};



