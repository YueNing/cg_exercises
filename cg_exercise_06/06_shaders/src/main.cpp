#include <cglib/core/glheaders.h>
#include <cglib/core/assert.h>

#include <cglib/gl/device_rendering_context.h>
#include <cglib/gl/device_render.h>
#include <cglib/gl/renderer.h>

#include "renderers.h"

enum Renderers { CUBE, MONKEY, SPHERE_FLAKE, SPONZA, NUM_RENDERERS };

int
main(int argc, char const**argv)
{
	DeviceRenderingContext context;
    if (!context.params.parse_command_line(argc, argv)) {
        std::cerr << "invalid command line argument" << std::endl;
        return -1;
    }

	context.renderers.push_back(std::make_shared<CubeRenderer>());
	context.renderers.push_back(std::make_shared<MonkeyRenderer>());
	context.renderers.push_back(std::make_shared<SphereFlakeRenderer>());
	context.renderers.push_back(std::make_shared<SponzaRenderer>());

    return DeviceRender::run(context, GUI::DEFAULT_FLAGS);
}

// CG_REVISION 7996c9a3d23339b38af3641fc67e80c22b00703c
