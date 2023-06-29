
struct VSIn
{
    float3 Pos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

struct VSOut
{
    float4 Pos : SV_Position;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

//Texture2D smileTexture : register(t0);
Texture2D albedoTexture : register(t0); // albedo 는 반사율로 물체가 빛을 받았을 때 반사하는 정도를 나타내는 단위이다.

SamplerState pointSampler : register(s0);
SamplerState anisotropicSampler : register(s1);


float4 main(VSOut In) : SV_TARGET
{
    //return In.Color;
    float4 color = (float4) 0.0f;
    //color = smileTexture.Sample(anisotropicSampler, In.UV);
    color = albedoTexture.Sample(anisotropicSampler, In.UV);
    
    return color;
}