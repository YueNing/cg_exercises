#include <cglib/gl/renderer.h>

#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

glm::mat4
compute_view_projection_light(
		const glm::vec3 &light_position,  // position of the light source in world space
		const glm::vec3 &light_direction, // light view direction
		float near_clip_plane,            // distance to the near clip plane
		float far_clip_plane,             // distance to the far clip plane
		float field_of_view,              // field of view in radians
		const glm::vec3 &up_vector)       // vector pointing upwards in world space
{
	// TODO: compute the View Projection Matrix for the light source
	glm::mat4 view = glm::lookAt(light_position, light_direction, up_vector);
	glm::mat4 project = glm::perspective(field_of_view, 4.0f / 3.0f, near_clip_plane, far_clip_plane);
	glm::mat4 mvpmatrix = project * view;
	// return glm::mat4(
	// 	-0.3815766573f, -1.5737097263f, -1.0113990307f, -0.7416926026f,
	// 	0.0000000000f, 1.8133978844f, -0.9002042413f, -0.6601497531f,
	// 	-2.3838677406f, 0.2518977523f, 0.1618907899f, 0.1187199131f,
	// 	-1.8690603971f, -5.7146315575f, 11.0477218628f, 25.4349956512f
	// );
	return mvpmatrix;
}

void
initialize_alpha_blending()
{
	// TODO: Set up the blend equation and blend function for 
	// alpha blending.
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void
initialize_additive_blending()
{
	// TODO: Set up the blend equation and blend function for 
	// additive blending.
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_ONE, GL_ONE);
}

void
initialize_premultiplied_blending()
{
	// TODO: Set up the blend equation and blend function for 
	// blending with premultiplied alpha.
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
}

// CG_REVISION 68a09862e9435b9f20eb0c0c2aba09327a0eba71
