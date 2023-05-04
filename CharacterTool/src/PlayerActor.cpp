#include "PlayerActor.h"
#include "AnimationStateMachine.h"

void reality::PlayerActor::OnInit(entt::registry& registry)
{
	Character::OnInit(registry);

	GetMovementComponent()->speed = 100;

	reality::C_SkeletalMesh skm;
	skm.local = XMMatrixIdentity();
	skm.world = XMMatrixIdentity();
	auto& meshes = RESOURCE->UseResource<SkeletalMesh>(skm.skeletal_mesh_id)->meshes;
	registry.emplace_or_replace<reality::C_SkeletalMesh>(entity_id_, skm);

	reality::C_CapsuleCollision capsule_collision;
	registry.emplace<reality::C_CapsuleCollision>(entity_id_, capsule_collision);

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

	transform_tree_.root_node->OnUpdate(registry, entity_id_, XMMatrixTranslationFromVector(cur_position_));
}

void reality::PlayerActor::OnUpdate()
{
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

	SkeletalMesh* skeletal_mesh = RESOURCE->UseResource<SkeletalMesh>(skm->skeletal_mesh_id);
	reality::C_Animation animation_component(skeletal_mesh->skeleton.bone_name_id_map.size());
	if (data.anim_slots[0].second.anim_object_type == ANIM_OBJECT_TYPE::ANIMATION_BASE) {
		animation_component.SetBaseAnimObject<AnimationBase>(skm->skeletal_mesh_id, 0);
	}
	else if (data.anim_slots[0].second.anim_object_type == ANIM_OBJECT_TYPE::ANIMATION_STATE_MACHINE) {
		animation_component.SetBaseAnimObject<AnimationStateMachine>(entity_id_, skm->skeletal_mesh_id, 0);
	}
	
	animation_component.GetAnimSlotByName("Base")->SetAnimation(data.anim_slots[0].second.animation_name, 0.3, true);

	for (int i = 1;i < data.anim_slots.size();i++) {
		const auto& anim_slot_pair = data.anim_slots[i];
		const auto& anim_slot_name = anim_slot_pair.first;
		const auto& anim_slot_data = anim_slot_pair.second;

		if (anim_slot_data.anim_object_type == ANIM_OBJECT_TYPE::ANIMATION_BASE) {
			animation_component.AddNewAnimSlot<AnimationBase>(anim_slot_name, anim_slot_data.skeletal_mesh_id, anim_slot_data.range, anim_slot_data.bone_id);
		}
		else if (anim_slot_data.anim_object_type == ANIM_OBJECT_TYPE::ANIMATION_STATE_MACHINE) {
			animation_component.AddNewAnimSlot<AnimationStateMachine>(anim_slot_name, entity_id_, anim_slot_data.skeletal_mesh_id, anim_slot_data.range, anim_slot_data.bone_id);
		}

		animation_component.GetAnimSlotByName(anim_slot_name)->SetAnimation(anim_slot_data.animation_name, 0.3, true);
	}

	reg_scene_->emplace_or_replace<reality::C_Animation>(entity_id_, animation_component);

	reality::C_Socket socket_component;

	for (const auto& cur_socket : data.sockets) {
		const auto& socket_name = cur_socket.first;
		const auto& socket = cur_socket.second;
		socket_component.AddSocket(socket_name, socket.bone_id, socket.owner_local, socket.local_offset);

		reg_scene_->emplace_or_replace<reality::C_StaticMesh>(entity_id_, data.socket_static_meshes.at(socket_name));
	}

	reg_scene_->emplace_or_replace<reality::C_Socket>(entity_id_, socket_component);

	transform_tree_.root_node->Translate(*reg_scene_, entity_id_, XMMatrixTranslationFromVector(cur_position_));
}

void reality::PlayerActor::SetCharacterAnimation(string anim_id)
{
	reality::C_Animation* animation_component_ptr = reg_scene_->try_get<reality::C_Animation>(entity_id_);
	int base_index = animation_component_ptr->name_to_anim_slot_index["Base"];
	animation_component_ptr->anim_slots[base_index].second->SetAnimation(anim_id, 0.3, true);
	reg_scene_->emplace_or_replace<reality::C_Animation>(entity_id_, *animation_component_ptr);
}

void reality::PlayerActor::MoveRight()
{
	SetCharacterAnimation("A_TP_CH_Jog_RF_Anim_Unreal Take.anim");
}

void reality::PlayerActor::MoveRightForward()
{
	SetCharacterAnimation("A_TP_CH_Jog_RF_Anim_Unreal Take.anim");
}

void reality::PlayerActor::MoveRightBack()
{
	SetCharacterAnimation("A_TP_CH_Jog_RB_Anim_Unreal Take.anim");
}

void reality::PlayerActor::MoveLeft()
{
	SetCharacterAnimation("A_TP_CH_Jog_LF_Anim_Unreal Take.anim");
}

void reality::PlayerActor::MoveLeftForward()
{
	SetCharacterAnimation("A_TP_CH_Jog_LF_Anim_Unreal Take.anim");
}

void reality::PlayerActor::MoveLeftBack()
{
	SetCharacterAnimation("A_TP_CH_Jog_LB_Anim_Unreal Take.anim");
}

void reality::PlayerActor::MoveForward()
{
	SetCharacterAnimation("A_TP_CH_Jog_F_Anim_Unreal Take.anim");
}

void reality::PlayerActor::MoveBack()
{
	SetCharacterAnimation("A_TP_CH_Jog_B_Anim_Unreal Take.anim");
}

void reality::PlayerActor::Idle()
{
	SetCharacterAnimation("A_TP_CH_Breathing_Anim_Unreal Take.anim");
}

void reality::PlayerActor::Fire()
{
	SetCharacterAnimation("A_TP_CH_Handgun_Fire_Anim_Unreal Take.anim");
}