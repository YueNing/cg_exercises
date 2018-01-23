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
// CG_REVISION 1d384085f04ade0a730db0ed88bbd9f2df80dad9
