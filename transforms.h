#ifndef TRANSFORMS_H
#define TRANSFORMS_H

#include "matrix.h"
#include "vec.h"

inline mat4 loadIdentity(){
    return Id<4>();
}

inline mat4 translate(vec3 u){
	return {
		1, 0, 0, u[0],
		0, 1, 0, u[1],
		0, 0, 1, u[2],
		0, 0, 0,    1
	};
}

inline mat4 translate(float x, float y, float z){
    return translate(vec3{x, y, z});
}

inline mat4 scale(float x, float y, float z){
	return {
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1
	};
}

inline mat4 rotate_x(float angle){
	float c = cos(angle);
	float s = sin(angle);

	return {
		1, 0,  0, 0,
		0, c, -s, 0,
		0, s,  c, 0,
		0, 0,  0, 1
	};
}

inline mat4 rotate_y(float angle){
	float c = cos(angle);
	float s = sin(angle);

	return {
		 c, 0, s, 0,
		 0, 1, 0, 0,
		-s, 0, c, 0,
		 0, 0, 0, 1
	};
}

inline mat4 rotate_z(float angle){
	float c = cos(angle);
	float s = sin(angle);

	return {
		c, -s, 0, 0,
		s,  c, 0, 0,
		0,  0, 1, 0,
		0,  0, 0, 1
	};
}

inline vec3 Rn(vec3 n, vec3 v, float theta) {
	return ((1 - cos(theta)) * (dot(v, n)*n)) + (cos(theta)*v) + (sin(theta)*cross(n, v));
}

inline mat4 rotate(vec3 n, float theta){
	/* TAREFA - AULA 10 */
	n = normalize(n);

	vec3 a = Rn(n, {1,0,0}, theta);
	vec3 b = Rn(n, {0,1,0}, theta);
	vec3 c = Rn(n, {0,0,1}, theta);

	return toMat4(toMat(a,b,c));
}

inline mat4 lookAt(vec3 eye, vec3 center, vec3 up){
	/* TAREFA - AULA 11 */
	up = normalize(up);
	
	vec3 f = normalize(center-eye);
	vec3 s = normalize(cross(f,up));
	vec3 u = cross(s,f);
	mat4 mview = (toMat4(transpose(toMat(s,u,-f)))) * translate(-eye);
	return mview;

}

inline mat4 orthogonal(float l, float r, float b, float t, float n, float f){
	return {
		2/(r-l),      0,     0,      (l+r)/(l-r),
			0,  2/(t-b),     0,      (b+t)/(b-t),
			0,        0, -2/(f-n),   (n+f)/(n-f),
			0,        0,      0,               1
	};	
}

inline mat4 frustum(float l, float r, float b, float t, float n, float f){
	mat4 Persp = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0,-(n+f)/n, -f,
		0, 0, -1/n, 0
	};
	mat4 Volume = {
		2/(r-l),      0,     0,      (l+r)/(l-r),
			0,  2/(t-b),     0,      (b+t)/(b-t),
			0,        0, 2/(f-n),    (n+f)/(n-f),
			0,        0,      0,               1
	};	
	return Volume*Persp;
}

inline mat4 perspective(float fovy, float aspect, float Near, float Far){
	/* TAREFA - AULA 12 */
	return {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
}


#endif
