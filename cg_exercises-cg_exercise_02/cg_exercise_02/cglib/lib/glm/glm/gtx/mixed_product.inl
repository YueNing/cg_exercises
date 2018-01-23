/// @ref gtx_mixed_product
/// @file glm/gtx/mixed_product.inl

namespace glm
{
	template <typename T, precision P>
	GLM_FUNC_QUALIFIER T mixedProduct
	(
		tvec3<T, P> const & v1,
		tvec3<T, P> const & v2,
		tvec3<T, P> const & v3
	)
	{
		return dot(cross(v1, v2), v3);
	}
}//namespace glm
// CG_REVISION 0b499c51037b55f8a55bc2b58f19cac16b11de4c
