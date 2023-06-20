#include "CMeshRenderer.h"
#include "CTransform.h"
#include "CRenderer.h"
#include "CGameObject.h"

namespace sh
{
	CMeshRenderer::CMeshRenderer()
		: Component(sh::enums::eComponentType::MeshRenderer)
	{
	}

	CMeshRenderer::~CMeshRenderer()
	{
	}

	void CMeshRenderer::Initialize()
	{
	}

	void CMeshRenderer::Update()
	{
	}

	void CMeshRenderer::LateUpdate()
	{
	}

	void CMeshRenderer::Render()
	{
		CTransform* tr = GetOwner()->GetComponent<CTransform>();
		tr->BindConstantBuffer();

		render::RectangleMesh->BindBuffer();
		render::shader->Binds();
		GetDevice()->DrawIndexed(render::RectangleMesh->GetIndexCount(), 0, 0);
	}
}


