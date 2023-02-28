#include "PlayerActor.h"

void KGCA41B::PlayerActor::OnInit(entt::registry& registry, AABBShape collision_box)
{
	collision_box_ = collision_box;

	entity_id_ = registry.create();

	transform_ = XMMatrixIdentity();

	speed_ = 200;

	entt::type_hash<KGCA41B::C_Transform> type_hash_transform;
	KGCA41B::C_Transform transform;
	transform.local = XMMatrixIdentity();
	transform.world = XMMatrixIdentity();
	registry.emplace<KGCA41B::C_Transform>(entity_id_, transform);
	transform_tree_.root_node = make_shared<TransformTreeNode>(TYPE_ID(C_Transform));

	KGCA41B::C_SkeletalMesh skm;
	skm.local = XMMatrixIdentity();
	skm.world = XMMatrixIdentity();
	auto& meshes = RESOURCE->UseResource<SkeletalMesh>(skm.skeletal_mesh_id)->meshes;
	registry.emplace_or_replace<KGCA41B::C_SkeletalMesh>(entity_id_, skm);
	transform_tree_.AddNodeToNode(TYPE_ID(KGCA41B::C_Transform), TYPE_ID(KGCA41B::C_SkeletalMesh));

	C_Camera camera;
	camera.local = XMMatrixTranslationFromVector({ 0, 0, -300, 0 });
	camera.near_z = 1.f;
	camera.far_z = 10000.f;
	camera.fov = XMConvertToRadians(45);
	camera.tag = "Player";
	registry.emplace<C_Camera>(entity_id_, camera);

	transform_tree_.AddNodeToNode(TYPE_ID(C_SkeletalMesh), TYPE_ID(C_Camera));

	transform_tree_.root_node->OnUpdate(registry, entity_id_, transform_);
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
	skm.skeletal_mesh_id = data.skm_id;
	skm.local = XMMatrixRotationX(XMConvertToRadians(-90.0f)) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	auto& meshes = RESOURCE->UseResource<SkeletalMesh>(skm.skeletal_mesh_id)->meshes;
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

void KGCA41B::PlayerActor::PlayerMovement(entt::registry& registry, float x, float y, float z)
{
	transform_ *= XMMatrixTranslation(x, y, z);
	transform_tree_.root_node->OnUpdate(registry, entity_id_, transform_);
}
