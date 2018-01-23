/// @ref gtx_handed_coordinate_space
/// @file glm/gtx/handed_coordinate_space.inl

namespace glm
{
	template <typename T, precision P>
	GLM_FUNC_QUALIFIER bool rightHanded
	(
		tvec3<T, P> const & tangent,
		tvec3<T, P> const & binormal,
		tvec3<T, P> const & normal
	)
	{
		return dot(cross(normal, tangent), binormal) > T(0);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER bool leftHanded
	(
		tvec3<T, P> const & tangent,
		tvec3<T, P> const & binormal,
		tvec3<T, P> const & normal
	)
	{
		return dot(cross(normal, tangent), binormal) < T(0);
	}
}//namespace glm
// CG_REVISION 5076130387d5a9915bfcd693bb4e6b142e11aa30
