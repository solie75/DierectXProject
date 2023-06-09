#include "CCell.h"
#include "CRenderer.h"

namespace sh
{
	CCell::CCell()
		: degree(3.1215926 / 180)
		, position(Vector3(0.0f, 0.0f, 0.0f))
	{
	}
	CCell::~CCell()
	{
	}
	void CCell::SetCellPosition(Vector3 _v3)
	{
		position = _v3;
	}
	void CCell::Initialize()
	{
		render::cellVertexes[0].pos = Vector3(0.0f, 0.0f, 0.0f);
		render::cellVertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		for (int i = 1; i < 360; i++)
		{
			render::cellVertexes[i].pos = Vector3(cos(i * degree)* 0.5, sin(i * degree)*0.5, 0.0f);
			render::cellVertexes[i].color = Vector4(1.f, 0.0f, 0.0f, 1.0f);
		}
		render::cellMesh->CreateVertexBuffer(render::cellVertexes, 361);

		std::vector<UINT> cellIndexes = {};
		for (int i = 1; i < 360; i++)
		{
			cellIndexes.push_back(i);
			cellIndexes.push_back(0);
			cellIndexes.push_back(i + 1);
		}
		cellIndexes.push_back(359);
		cellIndexes.push_back(0);
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