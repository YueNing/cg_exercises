/// @ref gtx_optimum_pow
/// @file glm/gtx/optimum_pow.inl

namespace glm
{
	template <typename genType>
	GLM_FUNC_QUALIFIER genType pow2(genType const & x)
	{
		return x * x;
	}

	template <typename genType>
	GLM_FUNC_QUALIFIER genType pow3(genType const & x)
	{
		return x * x * x;
	}

	template <typename genType>
	GLM_FUNC_QUALIFIER genType pow4(genType const & x)
	{
		return (x * x) * (x * x);
	}
}//namespace glm
// CG_REVISION 7996c9a3d23339b38af3641fc67e80c22b00703c
