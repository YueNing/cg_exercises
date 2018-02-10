/// @ref gtx_log_base
/// @file glm/gtx/log_base.inl

namespace glm
{
	template <typename genType> 
	GLM_FUNC_QUALIFIER genType log(genType const & x, genType const & base)
	{
		assert(x != genType(0));
		return glm::log(x) / glm::log(base);
	}

	template <typename T, precision P, template <typename, precision> class vecType>
	GLM_FUNC_QUALIFIER vecType<T, P> log(vecType<T, P> const & x, vecType<T, P> const & base)
	{
		return glm::log(x) / glm::log(base);
	}
}//namespace glm
// CG_REVISION 68a09862e9435b9f20eb0c0c2aba09327a0eba71
