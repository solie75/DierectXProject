#pragma once
#include "CComponent.h"
#include "CMesh.h"
#include "CShader.h"

namespace sh
{
	class CMeshRenderer : public Component
	{
	private:
		CMesh* mMesh;
		CShader* mShader;

	public:
		CMeshRenderer();
		~CMeshRenderer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	};
}


