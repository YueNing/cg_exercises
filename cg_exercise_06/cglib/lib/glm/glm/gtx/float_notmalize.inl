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
// CG_REVISION 7996c9a3d23339b38af3641fc67e80c22b00703c
