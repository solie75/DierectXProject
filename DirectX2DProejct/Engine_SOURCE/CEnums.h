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
		End,
	};

	enum class eLayerType
	{
		Player,
		Monster,
		UI,
		End,
	};
}