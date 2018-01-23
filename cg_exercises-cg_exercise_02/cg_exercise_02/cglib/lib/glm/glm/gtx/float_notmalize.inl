/// @ref gtx_float_normalize
/// @file glm/gtx/float_normalize.inl

#include <limits>

namespace glm
{
	template <typename T, precision P, template <typename, precision> class vecType>
	GLM_FUNC_QUALIFIER vecType<float, P> floatNormalize(vecType<T, P> const & v)
	{
		return vecType<float, P>(v) / static_cast<float>(std::numeric_limits<T>::max());
	}

}//namespace glm
// CG_REVISION 0b499c51037b55f8a55bc2b58f19cac16b11de4c
