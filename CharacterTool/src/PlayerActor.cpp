#include "PlayerActor.h"

void PlayerActor::InitComponents()
{
	comp_camera_.position = { 0, 0, -50, 0 };
	comp_camera_.look = { -50, 0, 0, 0 };
	comp_camera_.target = { -50, 0, 0, 0 };
	comp_camera_.up = { 0, 1, 0, 0 };
	comp_camera_.near_z = 1.f;
	comp_camera_.far_z = 10000.f;
	comp_camera_.fov = XMConvertToRadians(45);
	comp_camera_.yaw = 0;
	comp_camera_.pitch = 0;
	comp_camera_.roll = 0;
	comp_camera_.speed = 30;
	comp_camera_.tag = "Player";

	comp_input_.tag = "Player";

	comp_skm_.mesh_id = "player";
	comp_skm_.shader_id = "player";

	comp_skeleton_.skeleton_id = "player";
	comp_animation_.anim_id = "player";

	comp_material_.shader_id = "player";
	comp_material_.texture_id = "null";
}

void PlayerActor::BindComponents(entt::registry& reg)
{
	reg.emplace<Camera>(ent, comp_camera_);
	reg.emplace<InputMapping>(ent, comp_input_);
	reg.emplace<SkeletalMesh>(ent, comp_skm_);
	reg.emplace<Skeleton>(ent, comp_skeleton_);
	reg.emplace<Animation>(ent, comp_animation_);
	reg.emplace<Material>(ent, comp_material_);
	reg.emplace<Transform>(ent, comp_transform_);
}
