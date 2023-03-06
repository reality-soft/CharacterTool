#include "Movements.h"
#include "CharacterTool.h"

void Movements::CameraModeChange()
{
	auto scene = SCENE->LoadScene("CharacterTool");
	CharacterTool* character_scene = dynamic_cast<CharacterTool*>(scene);
	if (character_scene->camera_mode == "Player") {
		character_scene->camera_mode = "Debug";
		character_scene->sys_camera_.TargetTag(character_scene->reg_scene, character_scene->camera_mode);
	}
	else {
		character_scene->camera_mode = "Player";
		character_scene->sys_camera_.TargetTag(character_scene->reg_scene, character_scene->camera_mode);
	}
}
