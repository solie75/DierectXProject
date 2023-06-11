#include "CCell.h"
#include "CRenderer.h"

namespace sh
{
	CCell::CCell()
		: degree(3.1215926f / 180.f)
		, position(Vector3(0.0f, 0.0f, 0.0f))
	{
	}
	CCell::~CCell()
	{
	}
	void CCell::Initialize()
	{
		

		for (int i = 0; i <= 360; i++)
		{
			render::cellVertexes[i].pos = Vector3(std::cos(i * degree), std::sin(i * degree), 0.0f);
			render::cellVertexes[i].color = Vector4(1.f, 0.0f, 0.0f, 1.0f);
		}
		render::cellVertexes[361].pos = Vector3(0.0f, 0.0f, 0.0f);
		render::cellVertexes[361].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		render::cellMesh->CreateVertexBuffer(render::cellVertexes, 362);

		std::vector<UINT> cellIndexes = {};
		for (int i = 0; i <= 360; i++)
		{
			cellIndexes.push_back(i);
			cellIndexes.push_back(361);
		}
		cellIndexes.push_back(1);

		render::cellMesh->CreateIndexBuffer(cellIndexes.data(), cellIndexes.size());
	}
	void CCell::Update()
	{
	}
	void CCell::LateUpdate()
	{
	}
	void CCell::Render()
	{
		render::cellMesh->BindBuffer();
	}
}
