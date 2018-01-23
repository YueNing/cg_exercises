#include <cglib/colors/exercise.h>
#include <cglib/colors/convert.h>
#include <cglib/colors/cmf.h>

#include <cglib/core/glheaders.h>
#include <cglib/core/glmstream.h>

#include <cglib/core/assert.h>
#include <iostream>
/*
 * Draw the given vertices directly as GL_TRIANGLES.
 * For each vertex, also set the corresponding color.
 */
// void draw_triangles(
// 	std::vector<glm::vec3> const& vertices,
// 	std::vector<glm::vec3> const& colors)
// {
// 	cg_assert(vertices.size() == colors.size());
// 	cg_assert(vertices.size() % 3 == 0);
// }
void draw_triangles(
	std::vector<glm::vec3> const& vertices,
	std::vector<glm::vec3> const& colors)
{
	cg_assert(vertices.size() == colors.size());
	cg_assert(vertices.size() % 3 == 0);

	// die ersten Aufgabe Yue
	glBegin(GL_TRIANGLES);
	for(uint i=0;i<vertices.size();i++){
		glColor3f(colors[i].r, colors[i].g, colors[i].b);
		glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
	}
	
	glEnd();
}

/*
 * Generate a regular grid of resolution N*N (2*N*N triangles) in the xy-plane (z=0).
 * Store the grid in vertex-index form.
 *
 * The vertices of the triangles should be in counter clock-wise order.
 *
 * The grid must fill exactly the square [0, 1]x[0, 1], and must
 * be generated as an Indexed Face Set (Shared Vertex representation).
 * 
 * The first vertex should be at position (0,0,0) and the last
 * vertex at position (1,1,0)
 *
 * An example for N = 3:
 *
 *   ^
 *   |  ----------
 *   |  |\ |\ |\ |
 *   |  | \| \| \|
 *   |  ----------
 *   |  |\ |\ |\ |
 * y |  | \| \| \|
 *   |  ----------
 *   |  |\ |\ |\ |
 *   |  | \| \| \|
 *   |  ----------
 *   |
 *   |-------------->
 *          x
 *
 */
void generate_grid(
	std::uint32_t N,
	std::vector<glm::vec3>* vertices,
	std::vector<glm::uvec3>* indices)
{
	cg_assert(N >= 1);
	cg_assert(vertices);
	cg_assert(indices);

	vertices->clear();
	indices->clear();

	for(std::uint32_t i=0;i<=N;i++){
		for(std::uint32_t j=0;j<=N;j++){
			vertices->push_back({(1.0*j)/N, (1.0*i)/N ,0.0f});
		}
	}
	for(uint32_t column=0;column<N;column++){
		for(uint32_t row=0;row<N;row++){
			indices->push_back({column*(N+1)+row, column*(N+1)+row+1, (column+1)*(N+1)+row});
			indices->push_back({(column+1)*(N+1)+row, column*(N+1)+row+1, (column+1)*(N+1)+row+1});
		}
	}
}

/*
 * Draw the given vertices as indexed GL_TRIANGLES using glDrawElements.
 * For each vertex, also set the corresponding color.
 *
 * Don't forget to enable the correct client states. After drawing
 * the triangles, you need to disable the client states again.
 */
void draw_indexed_triangles(
	std::vector<glm::vec3>  const& vertices,
	std::vector<glm::vec3>  const& colors,
	std::vector<glm::uvec3> const& indices)
{
	cg_assert(vertices.size() == colors.size());

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, &colors[0]);
	glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
	glDrawElements(GL_TRIANGLES, 3*indices.size(), GL_UNSIGNED_INT, &indices[0]);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

/*
 * Generate a triangle strip with N segments (2*N triangles)
 * in the xy plane (z=0).
 *
 * The vertices of the triangles should be in counter clock-wise order.
 *
 * The triangle strip must fill exactly the square [0, 1]x[0, 1].
 *
 * The first vertex should be at position (0,1,0) and the last
 * vertex at position (1,0,0)
 *
 * An example for N = 3:
 *
 *   ^
 *   |  ----------
 *   |  | /| /| /|
 * y |  |/ |/ |/ |
 *   |  ----------
 *   |
 *   |-------------->
 *           x
 *
 */
void generate_strip(
	std::uint32_t N,
	std::vector<glm::vec3>* vertices)
{
	cg_assert(N >= 1);
	cg_assert(vertices);

	vertices->clear();
	
	for(uint32_t low =0;low<N;low++){
		vertices->push_back(glm::vec3((low*1.0)/N, 1.0f, 0.0f));
		vertices->push_back(glm::vec3((low*1.0)/N, 0.0f, 0.0f));
	}

}

/*
 * Draw the given vertices as a triangle strip.
 * For each vertex, also set the corresponding color.
 */
void draw_triangle_strip(
	std::vector<glm::vec3> const& vertices,
	std::vector<glm::vec3> const& colors)
{
	cg_assert(vertices.size() == colors.size());

	glBegin(GL_TRIANGLE_STRIP);
	for(std::uint32_t i=0;i<vertices.size();i++){
		glColor3f(colors[i].r, colors[i].g, colors[i].b);
		glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
	}
	glEnd();
}

/*
 * Integrate the given piecewise linear function 
 * using trapezoidal integration.
 *
 * The function is given at points
 *     x[0], ..., x[N]
 * and its corresponding values are
 *     y[0], ..., y[N]
 */
float integrate_trapezoidal(
	std::vector<float> const& x,
	std::vector<float> const& y)
{
	cg_assert(x.size() == y.size());
	cg_assert(x.size() > 1);

	float sum = 0;
	for(std::uint32_t i=0;i<x.size()-1;i++){
		sum += (x[i+1]-x[i])*(y[i+1]+y[i])/2;
	}
	return sum;
}

/*
 * Convert the given spectrum to RGB using your
 * implementation of integrate_trapezoidal(...)
 *
 * The color matching functions and the wavelengths
 * for which they are given can be found in
 *     cglib/colors/cmf.h
 * and
 *     cglib/src/colors/cmf.cpp
 *
 * The wavelengths corresponding to the spectral values 
 * given in spectrum are defined in cmf::wavelengths
 */
glm::vec3 spectrum_to_rgb(std::vector<float> const& spectrum)
{
	cg_assert(spectrum.size() == cmf::wavelengths.size());
	std::vector<float> nx;
	std::vector<float> ny;
	std::vector<float> nz;

	for(std::uint32_t i=0;i<spectrum.size();i++){
		nx.push_back(spectrum[i]*cmf::x[i]);
		ny.push_back(spectrum[i]*cmf::y[i]);
		nz.push_back(spectrum[i]*cmf::z[i]);
	}

	float X = integrate_trapezoidal(cmf::wavelengths, nx);
	float Y = integrate_trapezoidal(cmf::wavelengths, ny);
	float Z = integrate_trapezoidal(cmf::wavelengths, nz);

	return convert::xyz_to_rgb(glm::vec3(X, Y, Z));
}
// CG_REVISION 1d384085f04ade0a730db0ed88bbd9f2df80dad9
