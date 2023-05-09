#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "vec.h"

inline float tri_area(vec2 a, vec2 b, vec2 c){
        /*  TAREFA - AULA 2 */	
	//area ((Cx-Ax)*(By-Ay)/2)-((Bx-Ax)*(Cy-Ay)/2)
	//		   X1       Y1         X2      Y2
	//area (X1*Y1)/2-(X2*Y2)/2
	float x1,x2,y1,y2,area;
	x1=c[0]-a[0];
	x2=b[0]-a[0];
	y1=b[1]-a[1];
	y2=c[1]-a[1];
	area = (x1*y1)/2-(x2*y2)/2;
 	
	return area;
}

template<class Tri>
vec3 barycentric_coords(vec2 p, const Tri& P){	
	/*  TAREFA - AULA 2 */	
	//a = (area(p,p2,p3)/area(p1,p2,p3))
	//b = (area(p1,p,p3)/area(p1,p2,p3))
	//c = (area(p1,p2,p)/area(p1,p2,p3))
	float area,area1,area2,area3;
	area   = tri_area(P[0],P[1],P[2]);
	area1  = tri_area(p,P[1],P[2]);
	area2  = tri_area(P[0],p,P[2]);
	area3  = tri_area(P[0],P[1],p);
	float a= area1/area;
	float b= area2/area;
	float c= area3/area;

	return {a, b, c};
}

template<class Tri>
bool is_inside(vec2 v, const Tri& P){
	float aT = tri_area(P[0], P[1], P[2]);

	if(fabs(aT) < 1e-5){
		float M[] = {
			norm(P[0]-P[1]),
			norm(P[1]-P[2]),
			norm(P[2]-P[0])
		};

		float maxM = M[0];
		int i = 0, j = 1;

		if(M[1] > maxM){
			i = 1;
			j = 2;
			maxM = M[1];
		}

		if(M[2] > maxM){
			i = 2;
			j = 0;
			maxM = M[2];
		}

		return fabs(norm(v - P[i]) + norm(v - P[j]) - maxM) < 1e-3;
		
	}

	vec3 b = barycentric_coords(v, P);
	return b[0] >= 0 && b[1] >= 0 && b[2] >= 0;
}

#endif
