#include "PlayerActor.h"
#include "SceneMgr.h"
#include "CharacterTool.h"

void KGCA41B::PlayerActor::OnInit(entt::registry& registry, AABBShape collision_box)
{
	collision_box_ = collision_box;

	transform_ = XMMatrixIdentity();

	KGCA41B::C_Transform transform;
	transform.local = XMMatrixIdentity();
	transform.world = XMMatrixIdentity();
	registry.emplace<KGCA41B::C_Transform>(entity_id_, transform);


	KGCA41B::C_SkeletalMesh skm;
	skm.local = XMMatrixIdentity();//* XMMatrixScalingFromVector({ 0.1, 0.1, 0.1, 0.0 });
	skm.world = XMMatrixIdentity();
	auto& meshes = RESOURCE->UseResource<SkeletalMesh>(skm.skeletal_mesh_id)->meshes;
	registry.emplace_or_replace<KGCA41B::C_SkeletalMesh>(entity_id_, skm);


	KGCA41B::C_BoundingBox bounding_box;
	bounding_box.local = XMMatrixIdentity();
	bounding_box.world = XMMatrixIdentity();
	bounding_box.SetXYZ(0, 0, 0);
	registry.emplace<KGCA41B::C_BoundingBox>(entity_id_, bounding_box);


	C_Camera camera;
	camera.local = XMMatrixTranslationFromVector({ 0, 30, -30, 0 });
	camera.near_z = 1.f;
	camera.far_z = 10000.f;
	camera.fov = XMConvertToRadians(45);
	camera.tag = "Player";
	registry.emplace<C_Camera>(entity_id_, camera);

	transform_tree_.root_node = make_shared<TransformTreeNode>(TYPE_ID(C_Transform));
	transform_tree_.AddNodeToNode(TYPE_ID(KGCA41B::C_Transform), TYPE_ID(KGCA41B::C_SkeletalMesh));
	transform_tree_.AddNodeToNode(TYPE_ID(KGCA41B::C_SkeletalMesh), TYPE_ID(KGCA41B::C_BoundingBox));
	transform_tree_.AddNodeToNode(TYPE_ID(C_SkeletalMesh), TYPE_ID(C_Camera));

	transform_tree_.root_node->OnUpdate(registry, entity_id_, transform_);
}

void KGCA41B::PlayerActor::OnUpdate(entt::registry& registry)
{
	//this->node_num_ = SpacePartition::GetInst()->UpdateNodeObjectBelongs(0, collision_box_, entity_id_);
	//vector<int> node_to_search = SpacePartition::GetInst()->FindCollisionSearchNode(0, collision_box_);
	transform_tree_.root_node->OnUpdate(registry, entity_id_, transform_);
}

void KGCA41B::PlayerActor::SetCharacterData(entt::registry& registry, CharacterData data)
{
	KGCA41B::C_Animation animation;
	animation.anim_id = data.anim_id;
	registry.emplace_or_replace<KGCA41B::C_Animation>(entity_id_, animation);

	KGCA41B::C_BoundingBox& bounding_box = registry.get<C_BoundingBox>(entity_id_);
	bounding_box.SetXYZ(data.x, data.y, data.z);
	registry.emplace_or_replace<KGCA41B::C_BoundingBox>(entity_id_, bounding_box);

	KGCA41B::C_SkeletalMesh skm;
	skm.skeletal_mesh_id = data.skm_id;
	skm.local = XMMatrixIdentity() * XMMatrixRotationY(XMConvertToRadians(180)) * XMMatrixScalingFromVector({ 0.1, 0.1, 0.1, 0.0 });
	skm.vertex_shader_id = data.vs_id;
	registry.emplace_or_replace<KGCA41B::C_SkeletalMesh>(entity_id_, skm);

	transform_tree_.root_node->OnUpdate(registry, entity_id_, transform_);
}

void KGCA41B::PlayerActor::SetCharacterAnimation(entt::registry& registry, string anim_id)
{
	C_Animation animation;
	animation.anim_id = anim_id;
	registry.emplace_or_replace<KGCA41B::C_Animation>(entity_id_, animation);
}

void KGCA41B::PlayerActor::MoveRight()
{
	auto scene = SCENE->LoadScene("CharacterTool");
	CharacterTool* character_scene = dynamic_cast<CharacterTool*>(scene);

	if (character_scene) {
		SetCharacterAnimation(character_scene->reg_scene, "A_TP_CH_Jog_RF_Anim.anim");
		movement_component_->direction.m128_f32[0]++;
	}
}

void KGCA41B::PlayerActor::MoveRightForward()
{
	auto scene = SCENE->LoadScene("CharacterTool");
	CharacterTool* character_scene = dynamic_cast<CharacterTool*>(scene);

	if (character_scene) {
		SetCharacterAnimation(character_scene->reg_scene, "A_TP_CH_Jog_RF_Anim.anim");
		movement_component_->direction.m128_f32[2]++;
		movement_component_->direction.m128_f32[0]++;

		movement_component_->direction = XMVector3Normalize(movement_component_->direction);
	}
}

void KGCA41B::PlayerActor::MoveRightBack()
{
	auto scene = SCENE->LoadScene("CharacterTool");
	CharacterTool* character_scene = dynamic_cast<CharacterTool*>(scene);

	if (character_scene) {
		SetCharacterAnimation(character_scene->reg_scene, "A_TP_CH_Jog_RB_Anim.anim");
		movement_component_->direction.m128_f32[2]--;
		movement_component_->direction.m128_f32[0]++;

		movement_component_->direction = XMVector3Normalize(movement_component_->direction);
	}
}

void KGCA41B::PlayerActor::MoveLeft()
{
	auto scene = SCENE->LoadScene("CharacterTool");
	CharacterTool* character_scene = dynamic_cast<CharacterTool*>(scene);

	if (character_scene) {
		SetCharacterAnimation(character_scene->reg_scene, "A_TP_CH_Jog_LF_Anim.anim");
		movement_component_->direction.m128_f32[0]--;
	}
}

void KGCA41B::PlayerActor::MoveLeftForward()
{
	auto scene = SCENE->LoadScene("CharacterTool");
	CharacterTool* character_scene = dynamic_cast<CharacterTool*>(scene);

	if (character_scene) {
		SetCharacterAnimation(character_scene->reg_scene, "A_TP_CH_Jog_LF_Anim.anim");
		movement_component_->direction.m128_f32[2]++;
		movement_component_->direction.m128_f32[0]--;

		movement_component_->direction = XMVector3Normalize(movement_component_->direction);
	}
}

void KGCA41B::PlayerActor::MoveLeftBack()
{
	auto scene = SCENE->LoadScene("CharacterTool");
	CharacterTool* character_scene = dynamic_cast<CharacterTool*>(scene);

	if (character_scene) {
		SetCharacterAnimation(character_scene->reg_scene, "A_TP_CH_Jog_LB_Anim.anim");
		movement_component_->direction.m128_f32[2]--;
		movement_component_->direction.m128_f32[0]--;

		movement_component_->direction = XMVector3Normalize(movement_component_->direction);
	}
}

void KGCA41B::PlayerActor::MoveForward()
{
	auto scene = SCENE->LoadScene("CharacterTool");
	CharacterTool* character_scene = dynamic_cast<CharacterTool*>(scene);

	if (character_scene) {
		SetCharacterAnimation(character_scene->reg_scene, "A_TP_CH_Jog_F_Anim.anim");
		movement_component_->direction.m128_f32[2]++;
	}
}

void KGCA41B::PlayerActor::MoveBack()
{
	auto scene = SCENE->LoadScene("CharacterTool");
	CharacterTool* character_scene = dynamic_cast<CharacterTool*>(scene);

	if (character_scene) {
		SetCharacterAnimation(character_scene->reg_scene, "A_TP_CH_Jog_B_Anim.anim");
		movement_component_->direction.m128_f32[2]--;
	}
}

void KGCA41B::PlayerActor::Idle()
{
	auto scene = SCENE->LoadScene("CharacterTool");
	CharacterTool* character_scene = dynamic_cast<CharacterTool*>(scene);
	if (character_scene) {
		movement_component_->direction = { 0, 0, 0, 0 };
		character_scene->character_actor.SetCharacterAnimation(character_scene->reg_scene, "A_TP_CH_Breathing_Anim.anim");
	}
}

void KGCA41B::PlayerActor::Fire()
{
	auto scene = SCENE->LoadScene("CharacterTool");
	CharacterTool* character_scene = dynamic_cast<CharacterTool*>(scene);
	if (character_scene) {
		character_scene->character_actor.SetCharacterAnimation(character_scene->reg_scene, "A_TP_CH_Handgun_Fire_Anim.anim");
	}
}