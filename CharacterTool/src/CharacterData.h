#pragma once
#include "AnimSlotData.h"
#include "Engine_include.h"
#include "Components.h"

struct TransformData {
	TransformData() {
		rotation_vector_ = XMVectorZero();
		transform_ = XMMatrixIdentity();
	}

	XMVECTOR rotation_vector_;
	XMMATRIX transform_;
};

struct SocketData {
	Socket socket_;
	TransformData transform_data_;
};

struct CharacterData
{
	char character_name[256] = "";
	reality::C_CapsuleCollision capsule_collision;
	TransformData capsule_collision_transform_data;
	reality::C_SkeletalMesh skeletal_mesh_component;
	TransformData skeletal_mesh_transform_data;
	vector<pair<string, AnimSlotData>> anim_slots;
	unordered_map<string, SocketData> sockets;
	unordered_map<string, reality::C_StaticMesh> socket_static_meshes;
	unordered_map<string, TransformData> socket_static_mesh_transforms;
};