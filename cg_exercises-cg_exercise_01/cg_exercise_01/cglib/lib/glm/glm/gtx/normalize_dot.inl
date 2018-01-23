/// @ref gtx_normalize_dot
/// @file glm/gtx/normalize_dot.inl

namespace glm
{
	template <typename T, precision P, template <typename, precision> class vecType>
	GLM_FUNC_QUALIFIER T normalizeDot(vecType<T, P> const & x, vecType<T, P> const & y)
	{
		return glm::dot(x, y) * glm::inversesqrt(glm::dot(x, x) * glm::dot(y, y));
	}

	template <typename T, precision P, template <typename, precision> class vecType>
	GLM_FUNC_QUALIFIER T fastNormalizeDot(vecType<T, P> const & x, vecType<T, P> const & y)
	{
		return glm::dot(x, y) * glm::fastInverseSqrt(glm::dot(x, x) * glm::dot(y, y));
	}
}//namespace glm
// CG_REVISION 1d384085f04ade0a730db0ed88bbd9f2df80dad9
