#include <cglib/rt/raytracing_parameters.h>

/*
 * ImGui Notes:
 * - every element needs to have a unique name
 * - if you don't want to display a name next to the input field, use prefix ##
 * 		e.g. ImGui::InputFloat("##MyFloat", &some_float);
 * - never give two elements the same name, or they won't work properly
 */

TextureFilterMode RaytracingParameters::get_tex_filter_mode() const
{
	if (tex_filter_mode == TextureFilterMode::NEAREST)
	{
		return NEAREST;
	}
	else if (tex_filter_mode == TextureFilterMode::BILINEAR)
	{
		return BILINEAR;
	}
	else if (tex_filter_mode == TextureFilterMode::TRILINEAR)
	{
		return TRILINEAR;
	}
	else
	{
		return DEBUG_MIP;
	}
}

TextureWrapMode RaytracingParameters::get_tex_wrap_mode() const
{
	if (tex_wrap_mode == TextureWrapMode::REPEAT)
	{
		return REPEAT;
	}
	else if (tex_wrap_mode == TextureWrapMode::CLAMP)
	{
		return CLAMP;
	}
	else
	{
		return ZERO;
	}
}

void RaytracingParameters::initialize()
{
	{
		render_mode_names.resize(render_mode_count);

		render_mode_names[RECURSIVE] = "Recursive";
		render_mode_names[DESATURATE] = "Desaturate";
		render_mode_names[NUM_RAYS] = "Number of Rays";
		render_mode_names[NORMAL] = "Normal";
		render_mode_names[TIME] = "Time";
		render_mode_names[DUDV] = "du dv";
		render_mode = 0;
	}

	{
		scene_names.resize(scene_count);

		scene_names[GO_BOARD] = "Go Board";
		scene_names[POOL_TABLE] = "Pool Table";
		scene_names[TEXTURED_SPHERE] = "Textured Sphere";
		scene_names[ALIASING_PLANE] = "Aliasing Plane";
	}

	{
		tex_filter_mode_names.resize(tex_filter_mode_count);

		tex_filter_mode_names[NEAREST] = "Nearest";
		tex_filter_mode_names[BILINEAR] = "Bilinear";
		tex_filter_mode_names[TRILINEAR] = "Trilinear";
		tex_filter_mode_names[DEBUG_MIP] = "Debug Mip";

		tex_wrap_mode_names.resize(tex_wrap_mode_count);
		tex_wrap_mode_names[REPEAT] = "Repeat";
		tex_wrap_mode_names[CLAMP] = "Clamp";
		tex_wrap_mode_names[ZERO] = "Zero";

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
						"du dv: texture coordinate gradient length\n"
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
			redraw |= ImGui::Checkbox("Stratified Samples", &stratified);
			redraw |= ImGui::InputInt("Pixel Samples", &spp);
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
			redraw |= ImGui::Checkbox("Transform Objects", &transform_objects);
			redraw |= ImGui::Checkbox("Normal Mapping", &normal_mapping);
		}

		if (ImGui::CollapsingHeader("Texture Settings"))
		{
			redraw |= ImGui::Combo("Texture Filter", &tex_filter_mode, &tex_filter_mode_names, tex_filter_mode_names.size());
			redraw |= ImGui::Combo("Texture Wrap", &tex_wrap_mode, &tex_wrap_mode_names, tex_wrap_mode_names.size());
		}

	return redraw;
}

