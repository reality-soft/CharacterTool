#pragma once
#include "stdafx.h"

struct CharacterData
{
	char character_name[256] = "";
	std::string anim_id;
	std::string skm_id;
	std::string vs_id;
	int x = 0, y = 0, z = 0;
};



