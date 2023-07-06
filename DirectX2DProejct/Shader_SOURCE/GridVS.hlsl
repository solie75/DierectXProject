#include "globals.hlsli"

struct VSIn
{
    float3 Pos : POSITION;
    float2 UV : TEXCOORD;
};

struct VSOut
{
    float4 Pos : SV_Position;
    float2 UV : TEXCOORD;
    float2 GridPos : POSITION;
};

VSOut main(VSIn In)
{
    VSOut Out = (VSOut) 0.0f;
    float2 gridPos = float2(0.0f, 0.0f);
    
    // grid 의 월드 공간 에서의 좌표값은 입력된 위치값 * 카메라 크기 
    gridPos.x = In.Pos.x * 1.0f * Resolution.x + CameraPosition.x * CameraScale.x;
    gridPos.y = In.Pos.y * 1.0f * Resolution.y + CameraPosition.y * CameraScale.y;
    
    const float meshScale = 2.0f;
    Out.Pos = float4(In.Pos.xy * meshScale, 0.999f, 1.0f);
    Out.UV = In.UV;
    Out.GridPos = gridPos;
    
    return Out;
}