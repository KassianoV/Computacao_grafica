#include"Graphics2D_v1.h"
#include"bezier.h"
#include"matrix.h"
#include"polygon_triangulation.h"

int main(){
    std::vector<vec2> CP = loadCurve("borboleta.txt");
	std::vector<vec2> P = sample_bezier_spline<3>(CP, 30);

    std::vector<unsigned int> indices = triangulate_polygon(P); // Triangulação para preenchimento de cor

    vec2 v = {400,300};

    Graphics2D G(800,300);
    G.clear();

    float t = 0;
    for(float l=0; l<1;l+=0.084){
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

         mat3 R = {
            cos(t), -sin(t), 0.0,
            sin(t),  cos(t), 0.0,
            0.0,     0.0, 1.0
        };
     Elements<Triangles> L{indices};
       // TriLines<Elements<Triangles>> A{indices};   ////2 opção - Usando trilines para marcar a triangulação
       
        auto cor = lerp(l, red, yellow);
       // auto cor2 = lerp(l, purple, green); //2 opção - cores para a marcação da triangulação
        G.draw((T*R*Ti)*P, L, cor);
       // G.draw((T*R*Ti)*P, A, cor2); //2 opção - desenhando a marcação da triangulação
        t+=0.525;
    }
	
	G.savePNG("Borboleta_circle.png");

}