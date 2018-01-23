/// @ref gtx_extend
/// @file glm/gtx/extend.inl

namespace glm
{
	template <typename genType>
	GLM_FUNC_QUALIFIER genType extend
	(
		genType const & Origin, 
		genType const & Source, 
		genType const & Distance
	)
	{
		return Origin + (Source - Origin) * Distance;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> extend
	(
		tvec2<T, P> const & Origin,
		tvec2<T, P> const & Source,
		T const & Distance
	)
	{
		return Origin + (Source - Origin) * Distance;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> extend
	(
		tvec3<T, P> const & Origin,
		tvec3<T, P> const & Source,
		T const & Distance
	)
	{
		return Origin + (Source - Origin) * Distance;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> extend
	(
		tvec4<T, P> const & Origin,
		tvec4<T, P> const & Source,
		T const & Distance
	)
	{
		return Origin + (Source - Origin) * Distance;
	}
}//namespace glm
// CG_REVISION 1d384085f04ade0a730db0ed88bbd9f2df80dad9
