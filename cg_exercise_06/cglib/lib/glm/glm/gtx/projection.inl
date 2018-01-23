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
// CG_REVISION 7996c9a3d23339b38af3641fc67e80c22b00703c
