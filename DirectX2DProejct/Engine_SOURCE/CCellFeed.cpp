#include "CCellFeed.h"
#include "CRenderer.h"
#include <random>

namespace sh
{
	CCellFeed::CCellFeed()
	{
		std::random_device random;
		std::mt19937 gen(random());
		std::uniform_real_distribution<float> dist(-0.8f, 0.8f);

		float x = (dist(gen));
		float y = (dist(gen));

		std::random_device random2;
		std::mt19937 gen2(random2());
		std::uniform_real_distribution<float> dist2(0.03f, 0.12f);

		transform.scale = Vector4(dist2(gen2), 0.f, 0.f, 0.f);
		transform.pos = Vector4(x, y, 0.f, 1.f);

		std::random_device random3;
		std::mt19937 gen3(random3());
		std::uniform_real_distribution<float> dist3(0.f, 1.f);

		float r = (dist3(gen3));
		float g = (dist3(gen3));
		float b = (dist3(gen3));

		transform.color = Vector4(r, g, b, 1.f);
	}
	CCellFeed::~CCellFeed()
	{
	}
	void CCellFeed::Initialize()
	{
	}
	void CCellFeed::Update()
	{
	}
	void CCellFeed::LateUpdate()
	{
	}
	void CCellFeed::Render()
	{
		render::constantBuffer->SetData(&transform);
		render::cellMesh->BindBuffer();
		render::shader->Binds(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		CGameObject::Render();
	}
}