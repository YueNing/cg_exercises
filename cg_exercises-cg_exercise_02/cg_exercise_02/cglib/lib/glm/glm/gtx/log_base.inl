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
// CG_REVISION 0b499c51037b55f8a55bc2b58f19cac16b11de4c
