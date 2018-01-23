/// @ref gtx_normal
/// @file glm/gtx/normal.inl

namespace glm
{
	template <typename T, precision P> 
	GLM_FUNC_QUALIFIER tvec3<T, P> triangleNormal
	(
		tvec3<T, P> const & p1, 
		tvec3<T, P> const & p2, 
		tvec3<T, P> const & p3
	)
	{
		return normalize(cross(p1 - p2, p1 - p3));
	}
}//namespace glm
// CG_REVISION 5076130387d5a9915bfcd693bb4e6b142e11aa30
