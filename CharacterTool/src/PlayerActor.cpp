#include "PlayerActor.h"

void reality::PlayerActor::OnInit(entt::registry& registry)
{
	Character::OnInit(registry);

	movement_component_->speed = 100;

	collision_box_ = AABBShape();

	reality::C_SkeletalMesh skm;
	skm.local = XMMatrixIdentity();
	skm.world = XMMatrixIdentity();
	auto& meshes = RESOURCE->UseResource<SkeletalMesh>(skm.skeletal_mesh_id)->meshes;
	registry.emplace_or_replace<reality::C_SkeletalMesh>(entity_id_, skm);


	reality::C_BoundingBox bounding_box;
	bounding_box.local = XMMatrixIdentity();
	bounding_box.world = XMMatrixIdentity();
	bounding_box.SetXYZ(0, 0, 0);
	registry.emplace<reality::C_BoundingBox>(entity_id_, bounding_box);

	C_Camera camera;
	camera.local = XMMatrixTranslationFromVector({ 0, 70, -90, 0 });
	camera.near_z = 1.f;
	camera.far_z = 10000.f;
	camera.fov = XMConvertToRadians(45);
	camera.tag = "Player";
	registry.emplace<C_Camera>(entity_id_, camera);

	transform_tree_.root_node = make_shared<TransformTreeNode>(TYPE_ID(reality::C_BoundingBox));
	transform_tree_.AddNodeToNode(TYPE_ID(reality::C_BoundingBox), TYPE_ID(reality::C_SkeletalMesh));
	transform_tree_.AddNodeToNode(TYPE_ID(C_SkeletalMesh), TYPE_ID(C_Camera));

	AnimationBase animation_base;
	reg_scene_->emplace_or_replace<reality::C_Animation>(entity_id_, C_Animation(&animation_base));

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

void reality::PlayerActor::SetCharacterData(CharacterData data)
{
	reality::C_BoundingBox& bounding_box = reg_scene_->get<C_BoundingBox>(entity_id_);
	bounding_box.SetXYZ(data.x, data.y, data.z);
	reg_scene_->emplace_or_replace<reality::C_BoundingBox>(entity_id_, bounding_box);

	reality::C_SkeletalMesh skm;
	skm.skeletal_mesh_id = data.skm_id;
	skm.local = XMMatrixIdentity() * XMMatrixRotationY(XMConvertToRadians(180)) * XMMatrixScalingFromVector({ 0.3, 0.3, 0.3, 0.0 });
	skm.vertex_shader_id = data.vs_id;
	reg_scene_->emplace_or_replace<reality::C_SkeletalMesh>(entity_id_, skm);

	reality::C_Animation* animation_component_ptr = reg_scene_->try_get<reality::C_Animation>(entity_id_);

	animation_component_ptr->AddNewAnimSlot<AnimationBase>("UpperBody", data.skm_id, "Spine_02", 6);
	animation_component_ptr->GetAnimSlotByName("UpperBody").anim_object_->SetAnimation("A_TP_CH_Handgun_Fire_Anim_Retargeted_Unreal Take.anim", 0.3);
	reg_scene_->emplace_or_replace<reality::C_Animation>(entity_id_, *animation_component_ptr);

	SetCharacterAnimation(data.anim_id);

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