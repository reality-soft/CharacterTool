#include "PlayerActor.h"

void reality::PlayerActor::OnInit(entt::registry& registry)
{
	Character::OnInit(registry);

	movement_component_->speed = 100;

	reality::C_SkeletalMesh skm;
	skm.local = XMMatrixIdentity();
	skm.world = XMMatrixIdentity();
	auto& meshes = RESOURCE->UseResource<SkeletalMesh>(skm.skeletal_mesh_id)->meshes;
	registry.emplace_or_replace<reality::C_SkeletalMesh>(entity_id_, skm);

	reality::C_CapsuleCollision capsule_collision;
	registry.emplace<reality::C_CapsuleCollision>(entity_id_, capsule_collision);
	QUADTREE->RegistDynamicCapsule(entity_id_);

	C_Camera camera;
	camera.local = XMMatrixTranslationFromVector({ 0, 70, -90, 0 });
	camera.near_z = 1.f;
	camera.far_z = 10000.f;
	camera.fov = XMConvertToRadians(45);
	camera.tag = "Player";
	registry.emplace<C_Camera>(entity_id_, camera);

	transform_tree_.root_node = make_shared<TransformTreeNode>(TYPE_ID(reality::C_CapsuleCollision));
	transform_tree_.AddNodeToNode(TYPE_ID(reality::C_CapsuleCollision), TYPE_ID(reality::C_SkeletalMesh));
	transform_tree_.AddNodeToNode(TYPE_ID(C_SkeletalMesh), TYPE_ID(C_Camera));

	//AnimationBase animation_base;
	//C_Animation animation_copmonent(animation_base);
	//reg_scene_->emplace_or_replace<reality::C_Animation>(entity_id_, animation_copmonent);

	transform_tree_.root_node->OnUpdate(registry, entity_id_, transform_matrix_);
}

void reality::PlayerActor::OnUpdate()
{
	C_Camera* camera = reg_scene_->try_get<C_Camera>(entity_id_);
	XMVECTOR scale, rotation, translation;
	XMMatrixDecompose(&scale, &rotation, &translation, transform_matrix_);
	XMMATRIX rotation_matrix = XMMatrixRotationY(camera->pitch_yaw.y);
	transform_tree_.root_node->Rotate(*reg_scene_, entity_id_, translation, rotation_matrix);
	front_ = XMVector3Transform({ 0, 0, 1, 0 }, rotation_matrix);
	right_ = XMVector3Transform({ 1, 0, 0, 0 }, rotation_matrix);
}

void reality::PlayerActor::SetCharacterData(const CharacterData& data)
{
	reality::C_CapsuleCollision* capsule_collision_component = reg_scene_->try_get<C_CapsuleCollision>(entity_id_);
	capsule_collision_component->capsule = data.capsule_collision.capsule;
	capsule_collision_component->local = data.capsule_collision.local;

	reality::C_SkeletalMesh* skm = reg_scene_->try_get<C_SkeletalMesh>(entity_id_);
	skm->skeletal_mesh_id = data.skeletal_mesh_component.skeletal_mesh_id;
	skm->local = data.skeletal_mesh_component.local;
	skm->vertex_shader_id = data.skeletal_mesh_component.vertex_shader_id;

	//AnimationBase animation_base;
	//reality::C_Animation animation_component(animation_base);

	//for (auto anim_slot_pair : data.anim_slots) {
	//	auto anim_slot_name = anim_slot_pair.first;
	//	auto anim_slot = anim_slot_pair.second;
	//	animation_component.AddNewAnimSlot<AnimationBase>(anim_slot_name, anim_slot.skeletal_mesh_id, anim_slot.bone_id, anim_slot.range);
	//}

	//reg_scene_->emplace_or_replace<reality::C_Animation>(entity_id_, *animation_component_ptr);

	transform_tree_.root_node->Translate(*reg_scene_, entity_id_, transform_matrix_);
}

void reality::PlayerActor::SetCharacterAnimation(string anim_id)
{
	reality::C_Animation* animation_component_ptr = reg_scene_->try_get<reality::C_Animation>(entity_id_);
	int base_index = animation_component_ptr->name_to_anim_slot_index["Base"];
	animation_component_ptr->anim_slots[base_index].second.anim_object_->SetAnimation(anim_id, 0.3);
	reg_scene_->emplace_or_replace<reality::C_Animation>(entity_id_, *animation_component_ptr);
}

void reality::PlayerActor::MoveRight()
{
	SetCharacterAnimation("A_TP_CH_Jog_RF_Anim_Unreal Take.anim");
	movement_component_->direction += right_;
}

void reality::PlayerActor::MoveRightForward()
{
	SetCharacterAnimation("A_TP_CH_Jog_RF_Anim_Unreal Take.anim");
	movement_component_->direction += front_;
	movement_component_->direction += right_;
}

void reality::PlayerActor::MoveRightBack()
{
	SetCharacterAnimation("A_TP_CH_Jog_RB_Anim_Unreal Take.anim");
	movement_component_->direction -= front_;
	movement_component_->direction += right_;
}

void reality::PlayerActor::MoveLeft()
{
	SetCharacterAnimation("A_TP_CH_Jog_LF_Anim_Unreal Take.anim");
	movement_component_->direction -= right_;
}

void reality::PlayerActor::MoveLeftForward()
{
	SetCharacterAnimation("A_TP_CH_Jog_LF_Anim_Unreal Take.anim");
	movement_component_->direction += front_;
	movement_component_->direction -= right_;
}

void reality::PlayerActor::MoveLeftBack()
{
	SetCharacterAnimation("A_TP_CH_Jog_LB_Anim_Unreal Take.anim");
	movement_component_->direction -= front_;
	movement_component_->direction -= right_;
}

void reality::PlayerActor::MoveForward()
{
	SetCharacterAnimation("A_TP_CH_Jog_F_Anim_Unreal Take.anim");
	movement_component_->direction += front_;
}

void reality::PlayerActor::MoveBack()
{
	SetCharacterAnimation("A_TP_CH_Jog_B_Anim_Unreal Take.anim");
	movement_component_->direction -= front_;
}

void reality::PlayerActor::Idle()
{
	SetCharacterAnimation("A_TP_CH_Breathing_Anim_Unreal Take.anim");
}

void reality::PlayerActor::Fire()
{
	SetCharacterAnimation("A_TP_CH_Handgun_Fire_Anim_Unreal Take.anim");
}