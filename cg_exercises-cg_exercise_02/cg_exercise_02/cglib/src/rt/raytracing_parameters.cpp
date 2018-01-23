#include <cglib/rt/raytracing_parameters.h>

/*
 * ImGui Notes:
 * - every element needs to have a unique name
 * - if you don't want to display a name next to the input field, use prefix ##
 * 		e.g. ImGui::InputFloat("##MyFloat", &some_float);
 * - never give two elements the same name, or they won't work properly
 */

void RaytracingParameters::initialize()
{
	{
		render_mode_names.resize(render_mode_count);

		render_mode_names[RECURSIVE] = "Recursive";
		render_mode_names[DESATURATE] = "Desaturate";
		render_mode_names[NUM_RAYS] = "Number of Rays";
		render_mode_names[NORMAL] = "Normal";
		render_mode_names[TIME] = "Time";
		render_mode = 0;
	}

	{
		scene_names.resize(scene_count);

		scene_names[CORNELL_BOX] = "Cornell Box";
		scene_names[SPHERE_PORTRAIT] = "Sphere Portrait";
		scene_names[SPHERE_REFLECTION] = "Sphere Reflection";
	}

	{
	}

}

bool RaytracingParameters::display_parameters()
{
	bool redraw = false;

	redraw |= ImGui::Combo("Scene", &scene, &scene_names, scene_names.size());
		ImGui::DragFloat("Exposure", &exposure, 0.1f, -100.f, 100.f);
		ImGui::DragFloat("Gamma", &gamma, 0.05f, 0.0f, 100.f);


		if(ImGui::CollapsingHeader("Render Settings"))
		{
			redraw |= ImGui::Combo("Render Mode", &render_mode, &render_mode_names, render_mode_names.size());
			if (ImGui::IsItemHovered())
			{
				ImGui::SetTooltip("Recursive: Whitted Style Raytracing\n"
						"Desaturate: Luminance of Whitted Style Raytracing\n"
						"Number of Rays: Number of rays created during recursive traversal\n"
						"Normal: Surface normals\n"
						"Time: Time spent on each pixel\n"
						);
			}
			if (render_mode == TIME)
			{
				redraw |= ImGui::DragFloat("Render Time Exposure", &scale_render_time, 0.1f, 0.f, 1000.f);
			}
			redraw |= ImGui::InputInt("Max Recursion Depth", &max_depth);
			redraw |= ImGui::DragFloat("Ray Epsilon", &ray_epsilon, 0.00001f, 0.0f, 0.f, "%.7f");
			redraw |= ImGui::DragFloat("Field of View Y", &fovy);
			redraw |= ImGui::InputInt("Render Threads", &num_threads);
			redraw |= ImGui::Checkbox("Stereo Rendering", &stereo);
			if (stereo) {
				redraw |= ImGui::DragFloat("Eye Separation", &eye_separation, 0.01f, 0.f, 0.f);
				redraw |= ImGui::DragFloat("Focal Distance", &focal_distance, 0.01f, 0.f, 0.f);
			}
		}

		if (ImGui::CollapsingHeader("Shading Settings"))
		{
			redraw |= ImGui::Checkbox("Diffuse White", &diffuse_white_mode);
			redraw |= ImGui::Checkbox("Shadows", &shadows);
			redraw |= ImGui::Checkbox("Ambient Lighting", &ambient);
			redraw |= ImGui::Checkbox("Diffuse Lighting", &diffuse);
			redraw |= ImGui::Checkbox("Specular Lighting", &specular);
			redraw |= ImGui::Checkbox("Reflection", &reflection);
			redraw |= ImGui::Checkbox("Transmission", &transmission);
			redraw |= ImGui::Checkbox("Fresnel", &fresnel);
			redraw |= ImGui::Checkbox("Dispersion", &dispersion);
		}

		if (scene == SPHERE_PORTRAIT)
		{
			if (ImGui::CollapsingHeader("Spotlight Settings"))
			{
				redraw |= ImGui::Checkbox("Spotlight", &spot_light);
				redraw |= ImGui::InputFloat("Falloff", &spot_light_falloff);
			}
		}

	return redraw;
}

