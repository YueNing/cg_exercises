/// @ref gtx_transform
/// @file glm/gtx/transform.inl

namespace glm
{
	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tmat4x4<T, P> translate(tvec3<T, P> const & v)
	{
		return translate(tmat4x4<T, P>(static_cast<T>(1)), v);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tmat4x4<T, P> rotate(T angle, tvec3<T, P> const & v)
	{
		return rotate(tmat4x4<T, P>(static_cast<T>(1)), angle, v);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tmat4x4<T, P> scale(tvec3<T, P> const & v)
	{
		return scale(tmat4x4<T, P>(static_cast<T>(1)), v);
	}

}//namespace glm
// CG_REVISION e50df956fcfa03a7f7b84df5fdbc0718eb17ea54
