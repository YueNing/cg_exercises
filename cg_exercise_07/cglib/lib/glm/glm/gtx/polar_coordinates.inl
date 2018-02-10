/// @ref gtx_polar_coordinates
/// @file glm/gtx/polar_coordinates.inl

namespace glm
{
	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> polar
	(
		tvec3<T, P> const & euclidean
	)
	{
		T const Length(length(euclidean));
		tvec3<T, P> const tmp(euclidean / Length);
		T const xz_dist(sqrt(tmp.x * tmp.x + tmp.z * tmp.z));

		return tvec3<T, P>(
			asin(tmp.y),	// latitude
			atan(tmp.x, tmp.z),		// longitude
			xz_dist);				// xz distance
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> euclidean
	(
		tvec2<T, P> const & polar
	)
	{
		T const latitude(polar.x);
		T const longitude(polar.y);

		return tvec3<T, P>(
			cos(latitude) * sin(longitude),
			sin(latitude),
			cos(latitude) * cos(longitude));
	}

}//namespace glm
// CG_REVISION 68a09862e9435b9f20eb0c0c2aba09327a0eba71
