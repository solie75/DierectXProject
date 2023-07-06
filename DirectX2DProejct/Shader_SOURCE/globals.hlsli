cbuffer Transform : register(b0)
{
    row_major matrix WorldMatrix;
    row_major matrix ViewMatrix;
    row_major matrix ProjectionMatrix;
}

cbuffer Grid : register(b2)
{
    float4 CameraPosition;
    float2 CameraScale;
    float2 Resolution;
}

// albedo 는 반사율로 물체가 빛을 받았을 때 반사하는 정도를 나타내는 단위이다.
Texture2D albedoTexture : register(t0); 
SamplerState pointSampler : register(s0);
SamplerState anisotropicSampler : register(s1);
