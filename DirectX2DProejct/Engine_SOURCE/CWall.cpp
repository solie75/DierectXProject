#include "CWall.h"
#include "CRenderer.h"

namespace sh
{
	CWall::CWall()
	{
		transform.scale = Vector4(1.0f, 0.f, 0.f, 0.f);
		transform.pos = Vector4(0, 0, 0.f, 1.f);
		transform.color = Vector4(0.f, 0.f, 1.f, 1.f);
	}
	CWall::~CWall()
	{
	}
	void CWall::Initialize()
	{
		for (int i = 0; i < 4; i++)
		{
			render::wallVertexes[i].color = Vector4(0.f, 1.f, 0.f, 1.f);
		}
		render::wallVertexes[0].pos = Vector3(-1.f, 1.f, 0.f);
		render::wallVertexes[1].pos = Vector3(1.f, 1.f, 0.f);
		render::wallVertexes[2].pos = Vector3(1.f, -1.f, 0.f);
		render::wallVertexes[3].pos = Vector3(-1.f, -1.f, 0.f);

		render::wallMesh->CreateVertexBuffer(render::wallVertexes, 4);

		std::vector<UINT> wallIndexes = {};

		for (int i = 0; i < 3; i++)
		{
			wallIndexes.push_back(i);
			wallIndexes.push_back(i+1);
		}
		wallIndexes.push_back(3);
		wallIndexes.push_back(0);
		render::wallMesh->CreateIndexBuffer(wallIndexes.data(), wallIndexes.size());


	}
	void CWall::Render()
	{
		render::constantBuffer->SetData(&(transform));   
		render::wallMesh->BindBuffer();
		render::shader->Binds(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
		
		CGameObject::Render();
	}
	void CWall::Update()
	{
	}
}