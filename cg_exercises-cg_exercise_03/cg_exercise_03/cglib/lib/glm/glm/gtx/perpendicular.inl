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
// CG_REVISION 5076130387d5a9915bfcd693bb4e6b142e11aa30
