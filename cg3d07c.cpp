#include "Render3D.h"
#include "ZBuffer.h"
#include "TextureShader.h"
#include "transforms.h"

struct Vertex{
	vec3 position;
	vec2 texCoords;
};

int main(){
	unsigned int m = 30, n = 30, N = m*n;

	float u0 = -5, u1 = 5, du = (u1-u0)/(m-1),
              v0 = -5, v1 = 5, dv = (v1-v0)/(n-1);

	std::vector<Vertex> V(N);
	for(unsigned int i = 0; i < m; i++){
		for(unsigned int j = 0; j < n; j++){
			float u = u0 + i*du;
			float v = v0 + j*dv;

			unsigned int ij = i + j*m;
			V[ij].position = {u, v, sinf(u*v/4)};
			
			float s = i/(m-1.0);
			float t = j/(n-1.0);
			V[ij].texCoords = {s, t};
		}
	}

	std::vector<unsigned int> indices;
	for(unsigned int i = 0; i < m-1; i++){
		for(unsigned int j = 0; j < n-1; j++){	
			unsigned int ij = i + j*m;
			indices.insert(indices.end(), {
				ij, ij+1, ij+m,
				ij+m+1, ij+m, ij+1
			});
		}
	}
	Elements<Triangles> T{indices};

	int w = 600, h = 600;
	ImageRGB G{w, h};
	mat4 View = lookAt({10,10,10}, {0, 0, 0}, {0, 0, 1});
	float a = w/(float)h;
	mat4 Projection = perspective(50, a, 0.1, 50);

	TextureShader shader;
	shader.texture.img = ImageRGB{"bob.jpg"};
	shader.texture.filter = BILINEAR;
	shader.texture.wrapX = REPEAT;
	shader.texture.wrapY = REPEAT;

	int nframes = 40;
	for(int k = 0; k < nframes; ++k){
		G.fill(white);
		ImageZBuffer I{G};

		float theta = k*2*M_PI/nframes;
		mat4 Model = rotate_z(theta);

		shader.M = Projection*View*Model;
		render(V, T, shader, I);

		char filename[50];
		sprintf(filename, "anim/output%03d.bmp", k);
		puts(filename);
		G.saveBMP(filename);
	}
}
