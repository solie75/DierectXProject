
struct VSIn
{
    float3 Pos : POSITION;
    float4 Color : COLOR;
};

struct VSOut
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
};

cbuffer Transform : register(b0)
{
    float4 Pos;
}


VSOut main(VSIn In)
{
    VSOut Out = (VSOut) 0.0f;
    
    Out.Pos = float4(In.Pos, 1.0f);
    // Out.Pos.x += 0.4f; // 상수버퍼를 통해 데이터(inputPosX)가 넘어와야 한다.
    Out.Pos.x += Pos.x;
    Out.Color = In.Color;
    
    return Out;
}