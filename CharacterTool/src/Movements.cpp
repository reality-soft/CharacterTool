#include "Movements.h"
#include "CharacterTool.h"

void Movements::MoveRight()
{
	auto scene = SCENE->LoadScene("CharacterTool");
	CharacterTool* character_scene = dynamic_cast<CharacterTool*>(scene);
	if (character_scene) {
		character_scene->character_actor.SetCharacterAnimation(character_scene->reg_scene, "A_TP_CH_Jog_RF.anim");
		float movement = TimeMgr::GetInst()->GetDeltaTime() * character_scene->character_actor.GetSpeed();
		character_scene->character_actor.PlayerMovement(character_scene->reg_scene, movement, 0, 0);
	}
}

void Movements::MoveRightForward()
{
	auto scene = SCENE->LoadScene("CharacterTool");
	CharacterTool* character_scene = dynamic_cast<CharacterTool*>(scene);
	if (character_scene) {
		character_scene->character_actor.SetCharacterAnimation(character_scene->reg_scene, "A_TP_CH_Jog_RF.anim");
		float movement = TimeMgr::GetInst()->GetDeltaTime() * character_scene->character_actor.GetSpeed();
		character_scene->character_actor.PlayerMovement(character_scene->reg_scene, movement, 0, movement);
	}
}

void Movements::MoveRightBack()
{
	auto scene = SCENE->LoadScene("CharacterTool");
	CharacterTool* character_scene = dynamic_cast<CharacterTool*>(scene);
	if (character_scene) {
		character_scene->character_actor.SetCharacterAnimation(character_scene->reg_scene, "A_TP_CH_Jog_RB.anim");
		float movement = TimeMgr::GetInst()->GetDeltaTime() * character_scene->character_actor.GetSpeed();
		character_scene->character_actor.PlayerMovement(character_scene->reg_scene, movement, 0, -movement);
	}
}

void Movements::MoveLeft()
{
	auto scene = SCENE->LoadScene("CharacterTool");
	CharacterTool* character_scene = dynamic_cast<CharacterTool*>(scene);
	if (character_scene) {
		character_scene->character_actor.SetCharacterAnimation(character_scene->reg_scene, "A_TP_CH_Jog_LF.anim");
		float movement = TimeMgr::GetInst()->GetDeltaTime() * character_scene->character_actor.GetSpeed();
		character_scene->character_actor.PlayerMovement(character_scene->reg_scene, -movement, 0, 0);
	}
}

void Movements::MoveLeftForward()
{
	auto scene = SCENE->LoadScene("CharacterTool");
	CharacterTool* character_scene = dynamic_cast<CharacterTool*>(scene);
	if (character_scene) {
		character_scene->character_actor.SetCharacterAnimation(character_scene->reg_scene, "A_TP_CH_Jog_LF.anim");
		float movement = TimeMgr::GetInst()->GetDeltaTime() * character_scene->character_actor.GetSpeed();
		character_scene->character_actor.PlayerMovement(character_scene->reg_scene, -movement, 0, movement);
	}
}

void Movements::MoveLeftBack()
{
	auto scene = SCENE->LoadScene("CharacterTool");
	CharacterTool* character_scene = dynamic_cast<CharacterTool*>(scene);
	if (character_scene) {
		character_scene->character_actor.SetCharacterAnimation(character_scene->reg_scene, "A_TP_CH_Jog_LB.anim");
		float movement = TimeMgr::GetInst()->GetDeltaTime() * character_scene->character_actor.GetSpeed();
		character_scene->character_actor.PlayerMovement(character_scene->reg_scene, -movement, 0, -movement);
	}
}

void Movements::MoveForward()
{
	auto scene = SCENE->LoadScene("CharacterTool");
	CharacterTool* character_scene = dynamic_cast<CharacterTool*>(scene);
	if (character_scene) {
		character_scene->character_actor.SetCharacterAnimation(character_scene->reg_scene, "A_TP_CH_Jog_F.anim");
		float movement = TimeMgr::GetInst()->GetDeltaTime() * character_scene->character_actor.GetSpeed();
		character_scene->character_actor.PlayerMovement(character_scene->reg_scene, 0, 0, movement);
	}
}

void Movements::MoveBack()
{
	auto scene = SCENE->LoadScene("CharacterTool");
	CharacterTool* character_scene = dynamic_cast<CharacterTool*>(scene);
	if (character_scene) {
		character_scene->character_actor.SetCharacterAnimation(character_scene->reg_scene, "A_TP_CH_Jog_B.anim");
		float movement = TimeMgr::GetInst()->GetDeltaTime() * character_scene->character_actor.GetSpeed();
		character_scene->character_actor.PlayerMovement(character_scene->reg_scene, 0, 0, -movement);
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

void Movements::Fire()
{
	auto scene = SCENE->LoadScene("CharacterTool");
	CharacterTool* character_scene = dynamic_cast<CharacterTool*>(scene);
	if (character_scene) {
		character_scene->character_actor.SetCharacterAnimation(character_scene->reg_scene, "A_TP_CH_Handgun_Fire.anim");
	}
}
