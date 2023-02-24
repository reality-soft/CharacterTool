#include "Movements.h"
#include "CharacterTool.h"

void Movements::MoveRightStart()
{
	auto scene = SCENE->LoadScene("CharacterTool");
	CharacterTool* character_scene = dynamic_cast<CharacterTool*>(scene);
	if (character_scene) {
		character_scene->character_actor.SetCharacterAnimation(character_scene->reg_scene, "A_TP_CH_Jog_RF.anim");
	}	
}

void Movements::MoveRight()
{
	auto scene = SCENE->LoadScene("CharacterTool");
	CharacterTool* character_scene = dynamic_cast<CharacterTool*>(scene);
	if (character_scene) {
		float movement = TimeMgr::GetInst()->GetDeltaTime() * character_scene->character_actor.GetSpeed();
		character_scene->character_actor.PlayerMovement(character_scene->reg_scene, -movement, 0, 0);
	}
}

void Movements::Idle()
{
	auto scene = SCENE->LoadScene("CharacterTool");
	CharacterTool* character_scene = dynamic_cast<CharacterTool*>(scene);
	if (character_scene) {
		character_scene->character_actor.SetCharacterAnimation(character_scene->reg_scene, "A_TP_CH_Breathing.anim");
	}
}
