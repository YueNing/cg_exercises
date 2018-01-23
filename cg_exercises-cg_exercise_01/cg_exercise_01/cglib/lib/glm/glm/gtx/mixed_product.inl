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
// CG_REVISION 1d384085f04ade0a730db0ed88bbd9f2df80dad9
