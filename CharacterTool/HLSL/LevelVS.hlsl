#include "LevelHeader.hlsli"
#include "VSHeader.hlsli"

cbuffer cb_data : register(b1)
{
	matrix g_matWorld;
};

VS_OUT VS(VS_IN input)
{
	VS_OUT output = (VS_OUT)0;

	float4 vLocal = float4(input.p, 1.0f);
	float4 vWorld = mul(vLocal, IdentityMatrix());
	float4 vView = mul(vWorld, g_matView);
	float4 vProj = mul(vView, g_matProj);

	output.p = vProj;
	output.n = input.n;
	output.t = input.t;

	return output;
}