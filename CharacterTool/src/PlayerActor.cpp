#include "PlayerActor.h"

void KGCA41B::PlayerActor::OnInit(entt::registry& registry, AABBShape collision_box)
{
	collision_box_ = collision_box;

	entity_id_ = registry.create();

	entt::type_hash<KGCA41B::C_Transform> type_hash_transform;
	KGCA41B::C_Transform transform;
	transform.local = XMMatrixIdentity();
	transform.world = XMMatrixIdentity();
	registry.emplace<KGCA41B::C_Transform>(entity_id_, transform);

	transform_tree_.root_node = make_shared<TransformTreeNode>(TYPE_ID(C_Transform));

	transform_tree_.root_node->OnUpdate(registry, entity_id_);


}

void KGCA41B::PlayerActor::OnUpdate(entt::registry& registry)
{
	//this->node_num_ = SpacePartition::GetInst()->UpdateNodeObjectBelongs(0, collision_box_, entity_id_);
	//vector<int> node_to_search = SpacePartition::GetInst()->FindCollisionSearchNode(0, collision_box_);
	transform_tree_.root_node->OnUpdate(registry, entity_id_);
}

void KGCA41B::PlayerActor::SetCharacterData(entt::registry& registry, CharacterData data)
{
	KGCA41B::C_Animation animation;
	animation.anim_id = data.anim_id;
	registry.emplace_or_replace<KGCA41B::C_Animation>(entity_id_, animation);

	KGCA41B::C_SkeletalMesh skm;
	skm.local = XMMatrixScaling(0.5, 0.5, 0.5) * XMMatrixRotationX(XMConvertToRadians(-90.0f)) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	skm.world = XMMatrixIdentity();
	skm.skeletal_mesh_id = data.skm_id;
	auto& meshes = RESOURCE->UseResource<SkeletalMesh>(skm.skeletal_mesh_id)->meshes;
	for (auto& mesh : meshes) {
		mesh.material.texture_id = data.texture_id;
		mesh.material.shader_id = data.ps_id;
	}
	skm.vertex_shader_id = data.vs_id;
	registry.emplace_or_replace<KGCA41B::C_SkeletalMesh>(entity_id_, skm);

	skm = registry.get<C_SkeletalMesh>(entity_id_);
}
