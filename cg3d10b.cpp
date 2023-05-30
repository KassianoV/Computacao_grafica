#include "Render3D.h"
#include "ZBuffer.h"
#include "MarchingCubes.h"
#include "MixColorShader.h"
#include "VertexUtils.h"
#include "transforms.h"

float sphere(float x, float y, float z){
	float r = 1.5;
	return x*x + y*y + z*z - r*r;
}

float torus(float x, float y, float z){
	float R = 1.5;
	float r = 0.4;
	return pow(sqrt(x*x + y*y) - R, 2) + z*z - r*r;
}

float treco(float x, float y, float z){
	float r = (x*x + y*y);
	return 2*y*(y*y - 3*x*x)*(1-z*z) + r*r - (9*z*z - 1)*(1 - z*z);
}

int main(){
	vec3 pmin = {-2, -2, -2}; 
	vec3 pmax = { 2,  2,  2};
	
	std::vector<vec3> P = marchingCubes(treco, 50, 50, 50, pmin, pmax);
	
	MixColorShader shader;
	shader.pmin = pmin;
	shader.pmax = pmax;
	shader.C = {
		red, blue, green, yellow, 
		orange, magenta, cyan, purple
	};

	Triangles T{P.size()};

	int w = 1280, h = 720;
	ImageRGB G{w, h};
	
	mat4 View = lookAt({2.5, 2.5, 1.5}, {0, 0, 0}, {0, 0, 1});
	float a = w/(float)h;
	mat4 Projection = perspective(45, a, 0.1, 100);

	int nframes = 80;
	for(int k = 0; k < nframes; k++){
		G.fill(white);
		ImageZBuffer I{G};
		
		float theta = k*2*M_PI/(nframes-1);
		mat4 Model = rotate_z(theta);
		shader.M = Projection*View*Model;

		render(P, T, shader, I);
		
		char filename[30];
		sprintf(filename, "anim/output%03d.png", k);
		puts(filename);
		G.savePNG(filename);
	}
}
