/// @ref gtx_projection
/// @file glm/gtx/projection.inl

namespace glm
{
	template <typename vecType>
	GLM_FUNC_QUALIFIER vecType proj(vecType const & x, vecType const & Normal)
	{
		return glm::dot(x, Normal) / glm::dot(Normal, Normal) * Normal;
	}
}//namespace glm
// CG_REVISION ab290eedfc16bcf76a3816f6664e85db04a6520c
