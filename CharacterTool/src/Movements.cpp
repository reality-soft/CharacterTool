#include "stdafx.h"
#include "Movements.h"
#include "CharacterTool.h"

void Movements::CameraModeChange()
{
	auto scene = SCENE_MGR->GetCurScene();
	shared_ptr<CharacterTool> character_scene = dynamic_pointer_cast<CharacterTool>(scene.lock());
	if (character_scene->camera_mode == "Player") {
		character_scene->camera_mode = "Debug";
		character_scene->sys_camera_.TargetTag(character_scene->GetRegistryRef(), character_scene->camera_mode);
	}
	else {
		character_scene->camera_mode = "Player";
		character_scene->sys_camera_.TargetTag(character_scene->GetRegistryRef(), character_scene->camera_mode);
	}
}
