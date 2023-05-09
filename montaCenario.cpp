#include "Image.h"
#include <iostream>
#include "Color.h"
// atualiza o objeto RGB
void over(RGB& Bg, RGBA C){
	vec4 vc = toVec(C);
	float alpha = vc[3];
	vec3 col = lerp(alpha, toVec(Bg), toVec3(vc));
	Bg = toColor(col);
}

ImageRGB colaSprite(ImageRGB img,ImageRGBA sprite,int TS,int Linha, int Col, int R,int D){//TS tamanho do sprite/R repetições/D flag da direção
    //Col  e Lin começão a ser contados do 1
    if(D==1){//D==1 direita//D==2 cima 
       // std::cout<< "montando cenario";
        for(int r=0;r<R;r++){
            if(r!=0){Col++;}
            std::cout<<"r: "<<r<<"  col:"<<Col<<" : Linha:"<<Linha*TS<<"\n";
            for(int i=0;i<TS;i++){
                for(int j=0;j<TS;j++){                    
                    over(img((Col*TS)+i,(Linha*TS)+j),sprite(i,j));
                }   
            }
        }
        
    }
    if(D==2){
        for(int r=0;r<R;r++){
            if(r!=0){Linha++;}
            for(int i=0;i<TS;i++){
                for(int j=0;j<TS;j++){
                    std::cout<<"col:"<<Col*TS<<" : Linha:"<<Linha*TS<<"\n";
                   over(img((Col*TS)+i,(Linha*TS)+j),sprite(i,j));
                }   
            }
        }
        
    }   
    
    return img;
}
main(){
    ImageRGB cenario(320,320);
    ImageRGBA subsolo{"sprites/tile/sprite-2-1.png"};
    ImageRGBA nuvem{"sprites/tile/nuvem.png"};
    ImageRGBA grama{"sprites/tile/sprite-1-3.png"};
    ImageRGBA plataformaE{"sprites/tile/sprite-5-0.png"};
    ImageRGBA plataformaD{"sprites/tile/sprite-7-0.png"};
    ImageRGBA plataformaM{"sprites/tile/sprite-6-0.png"};
    Color<3> ceu;
    vec3 cor{0.5,0.8,1};
    ceu = toColor(cor);
    cenario.fill(ceu);
                /*MONTAR CENARIO*/
    //colasprite(       img,       sprite,TS,lin,col,Repetições,direção)
    cenario =colaSprite(cenario,subsolo,    32,0,0,10,1);// camada de terra
    cenario =colaSprite(cenario,grama,      32,1,0,10,1);//camada de grama
    for(int i =1;i<10;i=i+2){cenario =colaSprite(cenario,nuvem,      32,9,i,1,1);}//fileira de nuvem
    for(int i =0;i<10;i=i+2){cenario =colaSprite(cenario,nuvem,      32,8,i,1,1);}//fileira de nuvem
    cenario =colaSprite(cenario,plataformaE,32,4,3,1,1);//plataforma flutuante
    cenario =colaSprite(cenario,plataformaM,32,4,4,3,1);//plataforma flutuante
    cenario =colaSprite(cenario,plataformaD,32,4,7,1,1);//plataforma flutuante

            /*COLETAVEIS*/
    ImageRGBA gema{"sprites/gemas/4-3.png"};    
    cenario =colaSprite(cenario,gema,32,5,3,2,1);            
    cenario =colaSprite(cenario,gema,32,5,6,2,1);            
            /*COLA PERSONAGEM*/
    ImageRGBA gato{"sprites/cat/cat7-33.png"};    
    ImageRGBA gata{"sprites/cat2/0-13.png"};    
    ImageRGBA capivara{"sprites/capivara/kapibara.png"};    
    cenario =colaSprite(cenario,gata,32,5,9,1,1); 
    cenario =colaSprite(cenario,capivara,32,2,5,1,1); 
    cenario =colaSprite(cenario,gato,32,5,5,1,1);
    cenario.savePNG("sprites/cenario.png");
    system("PAUSE");

}
