#ifndef GRAPHICS2D_H
#define GRAPHICS2D_H

#include <vector>
#include "Image.h"
#include "Primitives.h"
#include "rasterization.h"
	
class Graphics2D{
	ImageRGB img;

	public:
	Graphics2D(int w, int h) : img{w, h}{}

	void clear(RGB col = white){
		img.fill(col);
	}
	
	void savePNG(std::string filename){
		img.savePNG(filename);	
	}
	
	template<class Prims>
	void draw(const std::vector<vec2>& V, const Prims& P, RGB color){
		for(auto primitive: assemble(P, V))
			drawPrimitive(primitive, color);
	}

	private:
	void drawPrimitive(Line<vec2> line, RGB color){
		for(Pixel p: rasterizeLine(line))
			paint(p, color);
	}
	
	void drawPrimitive(Triangle<vec2> tri, RGB color){
		for(Pixel p: rasterizeTriangle(tri))
			paint(p, color);
	}

	void paint(Pixel p, RGB c){
		if(p.x >= 0 && p.y >= 0 && p.x < img.width() && p.y < img.height())
			img(p.x,p.y) = c;
	}
};

#endif
