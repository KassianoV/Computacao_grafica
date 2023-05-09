#include "Image.h"
#include <vector>
float G(float x, float y, float cx, float cy, float s){
	float dx = x - cx;
	float dy = y - cy;
	return 100*exp(-(dx*dx + dy*dy)/(s*s));
}

float F(vec2 c0,vec2 c1,float x, float y,int r){
	
	return r - G(x, y,c0[0], c0[1], r) - G(x, y, c1[0],c1[1], r);
}
main(){

    ImageRGB img(600, 600);
    vec2 a={1,0};
    vec2 b= {1,0};
    std::vector<vec3> centros={ 
        //possição do circulo e tamanho para a proxima ligação
        //com repetição de circulos para completar o corpo
        {100,400,45},//mão esquerda
        {200,400,45},//antebraço esquerdo
        {300,400,45},//tronco
        {400,400,45},//antebraço direito
        {500,400,1},//mão direito //1 para n conectar a mão na cabeça

        {300,540,70},//cabeça 
        {300,400,50},//tronco
        {300,300,40},//cintura
        {250,250,75},//coxa esquerda
        {150,150,1},//pé esquerdo// 1 para n conectar o pe na cintura

        {300,300,40},//cintura
        {350,250,75},//coxa direita
        {450,150,75}//pé direito
        };    
    img.fill(white);
		for(int y = 0; y < img.height(); y++)
			for(int x = 0; x < img.width(); x++)
            {  
               for(int i = 0;i<centros.size();i++){
                    a=  {centros[i][0]    ,centros[i][1] };
                    b=  {centros[i+1][0]  ,centros[i+1][1] };
                    
                    if(F(a,b,x,y,centros[i][2])<=0){
                        img(x,y) = red;
                    }
                    
                    
               }
               
            }
		char filename[30];
		sprintf(filename, "anim/output.png");
		puts(filename);
		img.savePNG(filename);

}