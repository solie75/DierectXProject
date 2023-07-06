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
		Grid,
		Player,
		Monster,
		UI,
		Background,
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

