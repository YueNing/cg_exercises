/// @ref gtx_perpendicular
/// @file glm/gtx/perpendicular.inl

namespace glm
{
	template <typename vecType> 
	GLM_FUNC_QUALIFIER vecType perp
	(
		vecType const & x, 
		vecType const & Normal
	)
	{
		return x - proj(x, Normal);
	}
}//namespace glm
// CG_REVISION 0b499c51037b55f8a55bc2b58f19cac16b11de4c
