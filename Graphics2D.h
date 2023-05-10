#ifndef GRAPHICS2D_H
#define GRAPHICS2D_H

#include <vector>
#include "geometry.h"
#include "Image.h"
#include "VertexUtils.h"
#include "Primitives.h"
#include "rasterization.h"
#include "Clip2D.h"
#include "vec.h"
	
class Graphics2D{
	ImageRGB img;

	public:
	Graphics2D(int w, int h) : img{w, h}{}

	void clear(RGB color = white){
		img.fill(color);
	}
	
	void savePNG(std::string filename){
		img.savePNG(filename);	
	}
	
	template<class Prims>
	void draw(const std::vector<vec2>& V, const Prims& P, RGB color){
		std::vector<Vec2Col> VC;
		for(vec2 v: V)
			VC.push_back({v, color});
		draw(VC, P);
	}

	template<class Prims>
	void draw(const std::vector<Vec2Col>& V, const Prims& P){
		ClipRectangle R = {-0.5f, -0.5f, img.width()-0.5f, img.height()-0.5f};
		for(auto primitive: clip(assemble(P, V), R))
			drawPrimitive(primitive);
	}

	void paint(Pixel p, RGB c){
		if(p.x >= 0 && p.y >= 0 && p.x < img.width() && p.y < img.height())
			img(p.x,p.y) = c;
	}

	void drawPrimitive(Line<Vec2Col> line){
		vec2 L[] = { line[0].position, line[1].position };
		RGB  C[] = { line[0].color,    line[1].color    };

		for(Pixel p: rasterizeLine(L)){
			float t = find_mix_param(toVec2(p), L[0], L[1]);
			RGB color = lerp(t, C[0], C[1]);
			paint(p, color);
		};
	}

	void drawPrimitive(Triangle<Vec2Col> tri){
	/**************** TAREFA - AULA 09 **************/

		vec2  L[] = { tri[0].position, tri[1].position, tri[2].position };
		RGB C[] = { tri[0].color,    tri[1].color,    tri[2].color    };
		vec3 c0 = toVec(C[0]);
		vec3 c1 = toVec(C[1]);
		vec3 c2 = toVec(C[2]);

		for(Pixel p: rasterizeTriangle(L)) {
			vec3 bc = barycentric_coords(toVec2(p), L);
			RGB color = toColor(toMat(c0, c1, c2) * bc);
			paint(p, color);
		}
	}

};

#endif

