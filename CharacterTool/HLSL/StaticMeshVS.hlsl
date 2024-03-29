#include "include/VertexCommon.hlsli"

cbuffer cb_data : register(b1)
{
    matrix world_matrix;
    matrix local_matrix;
    matrix owner_local;
    matrix local_offset;
    matrix animation_matrix;
};

struct VS_IN
{
    float3 p : F3_POSITION;
    float3 n : F3_NORMAL;
    float2 t : F2_TEXTURE;
};
struct VS_OUT
{
    float4 p : SV_POSITION;
    float4 n : NORMAL;
    float2 t : TEXCOORD;
    float lod : TEXCOORD1;
};

VS_OUT VS(VS_IN input)
{
    VS_OUT output = (VS_OUT)0;

    float4 local = float4(input.p, 1.0f);
    local = mul(local, local_matrix);
    local = mul(local, local_offset);
    float4 animated_local = mul(local, animation_matrix);
    animated_local = mul(animated_local, owner_local);

    float4 normal = float4(input.n, 1.0f);
    normal = mul(normal, local_matrix);
    normal = mul(normal, local_offset);
    float4 animated_normal = mul(normal, animation_matrix);
    animated_normal = mul(animated_normal, owner_local);

    float4 world = mul(animated_local, world_matrix);
    float4 projection = mul(world, ViewProjection());

    output.lod = GetLod(input.p);

    output.p = projection;
    output.n = normal;
    output.t = input.t;

    return output;
}