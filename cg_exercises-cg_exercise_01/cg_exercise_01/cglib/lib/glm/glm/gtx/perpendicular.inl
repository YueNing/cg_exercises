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
// CG_REVISION 1d384085f04ade0a730db0ed88bbd9f2df80dad9
