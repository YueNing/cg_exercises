#include <cglib/core/image.h>

#include <cglib/gl/scene_graph.h>
#include <cglib/gl/prefilter_envmap.h>

#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

/*
 * Create a sphere flake node and its 5 children. 
 * Recurse if number_of_remaining_recursions > 0.
 */
std::shared_ptr<SceneGraphNode> buildSphereFlakeSceneGraph(
	const std::shared_ptr<GLObjModel>& model, // the geometric model associated with this node (a sphere)
	float sphere_model_radius,				  // the radius of the sphere in local coordinates (hint: should remain constant throughout the recursion)
	float size_factor,						  // growth/shrink factor of the spheres for each recursion level 
	int number_of_remaining_recursions)		  // the number of remaining recursions
{
	// TODO: create root SceneGraphNode and set model
	auto root = std::make_shared<SceneGraphNode>();
	root->model = model;

	// TODO: only create children if there are remaining recursions
	if(number_of_remaining_recursions >0)
	{
		// TODO: create 5 child nodes
		for (int i = 0; i < 5; ++i)
		{
			// TODO: create sphere flake sub graph for each child
			auto subgraph = buildSphereFlakeSceneGraph(model, sphere_model_radius, size_factor, number_of_remaining_recursions -1);

			// TODO: compute transformation matrix from the child node to the parent node (this function call's root node)
			float r = sphere_model_radius + (sphere_model_radius * size_factor);
			float p = 3.1415926 / 2;
			switch(i) {
				case 0: subgraph->parent_to_node = glm::translate(glm::mat4(), glm::vec3(r, 0.0f, 0.0f)) * glm::scale(glm::mat4(), glm::vec3(size_factor))
												 * glm::rotate(-p, glm::vec3(0.0f, 0.0f, 1.0f));
						break;
				case 1: subgraph->parent_to_node = glm::translate(glm::mat4(), glm::vec3(-r, 0.0f, 0.0f)) * glm::scale(glm::mat4(), glm::vec3(size_factor))
												 * glm::rotate(p, glm::vec3(0.0f, 0.0f, 1.0f));
						break;
				case 2: subgraph->parent_to_node = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, r)) * glm::scale(glm::mat4(), glm::vec3(size_factor))
												 * glm::rotate(p, glm::vec3(1.0f, 0.0f, 0.0f));
						break;
				case 3: subgraph->parent_to_node = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, -r)) * glm::scale(glm::mat4(), glm::vec3(size_factor))
												 * glm::rotate(-p, glm::vec3(1.0f, 0.0f, 0.0f));
						break;
				case 4: subgraph->parent_to_node = glm::translate(glm::mat4(), glm::vec3(0.0f, r, 0.0f))
												 * glm::scale(glm::mat4(), glm::vec3(size_factor));
			}
			subgraph->node_to_parent = glm::transpose(subgraph->parent_to_node);
			// TODO: add each subgraph to the children of this function call's root node
			root->children.push_back(subgraph);
		}
	}
	return root;
}


/*
 * Traverse the scene graph and collect all models.
 * Recursivly computes the world transformation for each model.
 */
void SceneGraphNode::collectTransformedModels(
	std::vector<TransformedModel>& transformed_models, // list that contains all models when traversal is complete
	const glm::mat4& parent_to_world,                  // the world transformation of the parent of this node
	const glm::mat4& world_to_parent)                  // the inverse world transformation of this node's parent
	const
{
	// TODO: compute node_to_world and world_to_node transformation matrices for this node
	glm::mat4 ptw = parent_to_world * parent_to_node;
	glm::mat4 wtp = world_to_parent * node_to_parent;
	// TODO: add this node's model to the list of transformed models
	transformed_models.push_back(TransformedModel(ptw, wtp, &(*model)));

	// TODO: recursively transform and add the models of all children (subgraphs)
	if(children.size() !=0) {
		for(std::shared_ptr<SceneGraphNode> x : children) {
			x->collectTransformedModels(transformed_models, ptw, wtp);
		}
	}
}


/*
 * Perform animation by traversing the scene graph recursively 
 * and rotating each scene graph node around the y-axis (in object space).
 */ 
void animateSphereFlake(
	SceneGraphNode& node,  // the current node of the traversal
	float angle_increment) // the incremental rotation angle
{
	// TODO: compute incremental rotation matrix for the given node node
	glm::mat4 rotation = glm::rotate(angle_increment, glm::vec3(0.f, 1.f, 0.f));

	// TODO: compute the parent-relative transformation matrices for this node
	node.node_to_parent = node.node_to_parent * rotation;
	node.parent_to_node = node.parent_to_node * glm::transpose(rotation);

	// TODO: recursively animate child subgraphs
	if(node.children.size() != 0) {
		for(std::shared_ptr<SceneGraphNode> x : node.children) {
			animateSphereFlake(*x, angle_increment);
		}
	}
}


/*
 * compute a prefiltered environment map for diffuse
 * illumination for the given environment map
 */
std::shared_ptr<Image>
prefilter_environment_diffuse(Image const& img)
{
	const int width = img.getWidth();
	const int height = img.getHeight();
	auto filtered = std::make_shared<Image>(width, height);

	// For all texels in the envmap...
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			// TODO: compute normal direction
			glm::ivec2 size = glm::ivec2(width, height);
			glm::vec3 normal = direction_from_lonlat_coord(glm::ivec2(x, y), size);
			glm::vec4 l_d = glm::vec4(0.f, 0.f, 0.f, 1.f);

			// ... integrate over all incident directions.
			for (int dy = 0; dy < height; ++dy) {
				for (int dx = 0; dx < width; ++dx) {
					// TODO: compute incident direction
					glm::vec3 r = direction_from_lonlat_coord(glm::ivec2(dx, dy), size);
					glm::ivec2 position = lonlat_coord_from_direction(r, size);
					// TODO: accumulate samples
					float s = solid_angle_from_lonlat_coord(position, size);
					l_d += img.getPixel(position[0], position[1]) * glm::max(0.f, dot(normal, r)) * s;
				}
			}

			// TODO: write filtered value
			//filtered->setPixel(...);
			filtered->setPixel(x, y, l_d);
		}
	}

	return filtered;
}

/*
 * compute a prefiltered environment map for specular
 * illumination for the given environment map and
 * phong exponent
 */
std::shared_ptr<Image>
prefilter_environment_specular(Image const& img, float n)
{
	const int width = img.getWidth();
	const int height = img.getHeight();

	auto filtered = std::make_shared<Image>(width, height);

	// For all texels in the envmap...
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			// TODO: compute reflection direction
			glm::ivec2 size = glm::ivec2(width, height);
			glm::vec3 R = direction_from_lonlat_coord(glm::ivec2(x, y), size);

			// ... integrate over all incident directions.
			glm::vec4 l_s = glm::vec4(0.f, 0.f, 0.f, 1.f);
			for (int dy = 0; dy < height; ++dy) {
				for (int dx = 0; dx < width; ++dx) {
					glm::vec3 r = direction_from_lonlat_coord(glm::ivec2(dx, dy), size);
					glm::ivec2 position = lonlat_coord_from_direction(r, size);
					// TODO: compute incident direction
					// TODO: accumulate samples
					float s = solid_angle_from_lonlat_coord(position, size);
					l_s += img.getPixel(position[0], position[1]) * glm::pow(glm::max(0.0f, glm::dot(R, r)), n) * s;
				}
			}

			// TODO: write filtered value
			//filtered->setPixel(...);
			filtered->setPixel(x, y, l_s);
		}
	}

	return filtered;
}
// CG_REVISION 7996c9a3d23339b38af3641fc67e80c22b00703c
