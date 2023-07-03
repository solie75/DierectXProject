#pragma once
#include "CComponent.h"
#include "CMesh.h"
#include "CShader.h"
#include "CMaterial.h"

namespace sh
{
	class CMeshRenderer : public Component
	{
	private:
		std::shared_ptr<CMesh> mMesh;
		std::shared_ptr<CMaterial> mMaterial;

	public:
		CMeshRenderer();
		~CMeshRenderer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetMesh(std::shared_ptr<CMesh> mesh) { mMesh = mesh; }
		void SetMaterial(std::shared_ptr<CMaterial> material) { mMaterial = material; }
		std::shared_ptr<CMaterial> GetMaterial() { return mMaterial; }

	};
}


