#version 330

uniform sampler2D tex; // the texture containing the diffuse material parameter k_d

#define MAX_LIGHT_COUNT 16
uniform int light_count;                        // the number of lights (always smaller than MAX_LIGHT_COUNT
uniform vec3 light_world_pos[MAX_LIGHT_COUNT];  // the position of the lights in world space
uniform vec3 light_intensity[MAX_LIGHT_COUNT];  // the intensity of the lights

uniform vec3 k_s; // the specular material parameter
uniform float n;  // phong exponent of the material

uniform vec3 cam_world_pos; // the camera position in world space

in vec3 world_position;            // the (interpolated) world space position corresponding to the fragment
in vec3 world_normal_interpolated; // the (interpolated) world space normal
in vec2 tex_coord;                 // the (interpolated) uv coordinate

out vec4 frag_color; // the resulting color value (will be written into the framebuffer)

void
main()
{
	// TODO: read k_d from texture
	 vec3 k_d = texture(tex, tex_coord).xyz; 

	// TODO: iterate over all lights and accumulate illumination
	// according the the phong illumination model on the exercise sheet
	vec3 x = world_position;
	vec3 N = world_normal_interpolated;
	vec3 V = normalize(cam_world_pos - x);
	vec3 R = reflect(V, N);
	vec3 sum;
	for (int i = 0; i < light_count; ++i)
	{
		vec3 x_l = light_world_pos[i];
		vec3 I_l = light_intensity[i];
		vec3 L = normalize(x_l - x);
		sum += (k_d * max(0, dot(L, N)) + k_s * pow(max(0, dot(R, L)), n)) 
				* I_l/ pow(dot(x - x_l, x - x_l), 2.0);
	}
	
	frag_color = vec4(sum, 1.0);
}
