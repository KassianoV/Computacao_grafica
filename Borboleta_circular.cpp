#include"Render2D_v1.h"
#include"bezier.h"
#include"matrix.h"
#include"polygon_triangulation.h"

int main(){
    std::vector<vec2> CP = loadCurve("borboleta.txt");
	std::vector<vec2> P = sample_bezier_spline<3>(CP, 30);

    std::vector<unsigned int> indices = triangulate_polygon(P); // Triangulação para preenchimento de cor

    vec2 v = {400,300};
    ImageRGB imG(800, 600);

    mat3 T = {
		1.0, 0.0, v[0],
		0.0, 1.0, v[1],
		0.0, 0.0, 1.0
	};

    mat3 Ti = {
		1.0, 0.0, -v[0],
		0.0, 1.0, -v[1],
		0.0, 0.0, 1.0
	};
    LineStrip L{P.size()};

    for(int t=0;t<12;t++){
        float r = 2*3.14/12*(t+1);
	    mat3 R = {
		    cos(r), -sin(r), 0.0,
		    sin(r),  cos(r), 0.0,
		    0.0,     0.0,    1.0
	    };

        imG.fill(white);
        render2d(P, L, red, imG);
        render2d((T*R*Ti)*P, L, yellow, imG);
    }
    imG.savePNG("Borboleta_circular.png");
}