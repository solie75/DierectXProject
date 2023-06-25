#pragma once

namespace sh::enums
{
	enum class eComponentType
	{
		None,
		Transform,
		Mesh,
		MeshRenderer,
		Particle,
		Script,
		Camera,
		End,
	};

	enum class eLayerType
	{
		Player,
		Monster,
		UI,
		End,
	};

	enum class eResourceType
	{
		Texture,
		Shader,
		Material,
		Mesh,
		End,
	};
}

