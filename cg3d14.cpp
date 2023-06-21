#include "Render3D.h"
#include "ZBuffer.h"
#include "TextureShader.h"
#include "ObjMesh.h"
#include "transforms.h"
#include "ImageSet.h"

class Mesh{
	std::vector<ObjMesh::Vertex> tris;
	std::vector<MaterialRange> materials;
	ImageSet image_set;
	public:
	mat4 Model;

	Mesh(std::string obj_file, mat4 _Model, std::string default_texture = ""){
		ObjMesh mesh{obj_file};
		tris = mesh.getTriangles();

		MaterialInfo std_mat;
		std_mat.map_Kd = default_texture;

		materials = mesh.getMaterials(std_mat);

		for(MaterialRange range: materials)
			image_set.load_texture(mesh.path, range.mat.map_Kd);

		Model = _Model;
	}

	void draw(ImageZBuffer& G, TextureShader& shader) const{
		for(MaterialRange range: materials){
			shader.texture.default_color = toColor(range.mat.Kd);
			image_set.get_texture(range.mat.map_Kd, shader.texture.img);
			TrianglesRange T{range.first, range.count};
			render(tris, T, shader, G);
		}
	}
};

int main(){
	std::vector<Mesh> meshes;

	
	meshes.emplace_back(
		"modelos/3d/sb-2/source/sb_2.obj", 
		translate(1, 1, -6)*rotate_y(-0.4)*scale(0.4, 0.4, 0.4)
		);

	meshes.emplace_back(
		"modelos/3d/patrick-star/source/paaattt.obj", 
		translate(-1,2.5f, -1)*rotate_y(0.2)*scale(.01, .01, .01));

	meshes.emplace_back(
		"modelos/3d/abacaxi/source/abacaxi.obj", 
		translate(2, 0, 0)*scale(0.1, 0.1, 0.1));

	meshes.emplace_back(
		"modelos/House Complex/House Complex/House Complex.obj", 
		translate(4, 0, 0)*rotate_y(0.5*3.141592653589793238462643383279f)*scale(.15, .15, .15));

	

	TextureShader shader;
	shader.texture.filter = BILINEAR;
	shader.texture.wrapX = REPEAT;
	shader.texture.wrapY = REPEAT;

	int w = 800, h = 600;
	ImageRGB G{w, h};

	float a = w/(float)h;
	mat4 Projection = perspective(45, a, 0.1, 1000);

	vec3 p0 = {2, 1.7, 10};
	vec3 p1 = {-1, 2.7, -18};

	int nframes = 5;
	for(int k = 0; k < nframes; k++){
		G.fill(0x00A5DC_rgb);
		ImageZBuffer I{G};

		float t = k/(nframes-1.0);
		vec3 pos = lerp(t, p0, p1);
		mat4 View = lookAt(pos, vec3{0, 1.5, 0}, {0, 1, 0});

		for(const Mesh& mesh: meshes){
			shader.M = Projection*View*mesh.Model;
			mesh.draw(I, shader);
		}

		char filename[30];
		sprintf(filename, "anim/output%03d.png", k);
		puts(filename);
		G.savePNG(filename);
	}
}
