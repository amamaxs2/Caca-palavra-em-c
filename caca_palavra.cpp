#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <ctype.h>
#include <conio.c>
#define tam 25
#define maxpal 100

FILE *arqpal;
char pal[tam][tam],palcol[tam][tam];
int qpal=0,x,y,lado,cont;
char palavras[maxpal][20],palavra[20];
char palavrasorteada[20], resposta;

void sorteia();
void mostra();
bool abreArquivo();
void leArquivo();
void mostraPalavras();
void insere();
void solicitarPalavra();
bool procurarPalavra();
void continuar();
void mostraCol();
void limpaVetor();
//---------------------------------------------
int main(){
	setlocale(LC_ALL,"portuguese");
		
	srand(time(NULL));
		
	do{
		limpaVetor();
		system("cls");
		
  		sorteia();
  		
	  		if (abreArquivo()==0)
			    return 0;
		    
		leArquivo();
		
		strcpy(palavrasorteada,palavras[rand()%maxpal]); //copiar a palavra rand do txt na palavra sorteada
		printf("%s \n",palavrasorteada);
		
		insere();
		
		mostra();
		
		solicitarPalavra();
		
		procurarPalavra();
			if(procurarPalavra()){
				system("cls");
				mostraCol();
				printf("A palavra foi encontrada!");
			}else{
				system("cls");
				mostraCol();		
				printf("A palavra não foi encontrada!");
			}
			
		continuar();	
	
	}while(resposta=='S'||resposta=='s');
  		
	system("pause");
	return 0;
}
//---------------------------------------------
void limpaVetor(){ 
	for(x=0 ; x<25 ; x++){
		for(y=0 ; y<25 ; y++){
			palcol[x][y] = ' ';
		}
	}
}
//---------------------------------------------
void sorteia(){ //sortear uma matriz 25 X 25 contendo letras do alfabeto
  char vog[6]="AEIOU";
  char con[22]="BCDFGHJKLMNPQRSTVXWYZ";
  int cont=1;

  for (x=0; x<tam; x++){
	    for (y=0; y<tam; y++){
		      if (cont==1 || cont==3)
		      { 
		         pal[x][y]=vog[rand()%5];
		      }   
		      else
		      {
		         pal[x][y]=con[rand()%21];
		      }   
		      cont++;
		      if (cont>3)
		      {
		        cont=1;
		      }  
    	}
	}   
}
//---------------------------------------------
void mostra(){  //apresentando a matriz
  for ( x=0; x<tam; x++){
     for ( y=0; y<tam; y++)
        printf("%c ",pal[x][y]);
     	printf("\n");   
  }   
}
//---------------------------------------------
void mostraCol(){  //apresentando a matriz
  for ( x=0; x<tam; x++){
     for ( y=0; y<tam; y++){
     		if(palcol[x][y]==pal[x][y]){
     			textcolor(2);
     			printf("%c ", palcol[x][y]);
			 }
			 else
			 {
			 	 textcolor(15);
				 printf("%c ",pal[x][y]);
			 }  
 	 }
     	printf("\n"); 
  }   
}
//---------------------------------------------
bool abreArquivo(){ //verifica se o arquivo existe
  arqpal = fopen("palavras.txt", "r"); //leitura
  if (arqpal == NULL)
  {  // Se houve erro na leitura do arquivo
     printf("Problemas na leitura do arquivo\n");
     system("pause");
     return 0; //não conseguiu abrir o arquivo
  }   
  else
  {
     fclose(arqpal);
     return 1; //conseguiu abrir o arquivo
  }   
}
//---------------------------------------------
void leArquivo(){ //leitura do arquivo
   arqpal = fopen("palavras.txt", "r"); 
cont=0;
   
   while (fgets(palavras[cont],20,arqpal))
   {
      palavras[cont][strlen(palavras[cont])-1]='\0';
      cont++;
   }
   fclose(arqpal);
}
//---------------------------------------------
void insere(){ //insere palavra sorteada na matriz
	int tamSort = strlen(palavrasorteada);
	lado = rand()%4;

	if(lado==0){ //ordem normal
		do{
			x = rand()%25;
			y = rand()%25;
		}while( y + tamSort > 24);	
		
		for(cont=0; cont<tamSort; cont++){
				pal[x][y+cont] = palavrasorteada[cont];
				palcol[x][y+cont] = palavrasorteada[cont];
		}
		
	}
	
	if(lado==1){ //ordem inverso horizontal
		do{
			x = rand()%25;
			y = rand()%25;
		}while( y - tamSort <= 0);	
		
		for(cont=0; cont<tamSort; cont++){
			pal[x][y-cont] = palavrasorteada[cont];
			palcol[x][y-cont] = palavrasorteada[cont];
		}
		
	}
	
	if(lado==2){ //ordem vertical cima pra baixo
		do{
			x = rand()%25;
			y = rand()%25;
		}while( x + tamSort > 24);	
		
		for(cont=0;cont<tamSort;cont++){
				pal[x+cont][y] = palavrasorteada[cont];
				palcol[x+cont][y] = palavrasorteada[cont];
		}
		
	}
	
	if(lado==3){ //ordem vertical de baixo pra cima
		do{
			x = rand()%25;
			y = rand()%25;
		}while( x - tamSort <= 0);	
		
		for(cont=0;cont<tamSort;cont++){
				pal[x-cont][y] = palavrasorteada[cont];
				palcol[x-cont][y] = palavrasorteada[cont];
		}
		
	}	
}
//---------------------------------------------
void solicitarPalavra(){ //solicitando palavra ao usuário
	
	do{ //verificando se o usuário não escreveu palavra inexistente
		printf("Insira uma palavra:(min_4)");
		gets(palavra);

	}while(strlen(palavra) < 4);
	
	strupr(palavra);//tornando a palavra maiuscula que nem na matriz
	
}
//---------------------------------------------
bool procurarPalavra(){ //procurando palavra pela matriz
	cont= 0;
	
		for( x = 0; x < 25; x++){  //de forma horizontal 
			for( y = 0; y < 25; y++){
				if(palavra[cont] == pal[x][y])
				{
					cont++;
				}
				else
				{
					cont = 0;
				}	
					
				if(cont == strlen(palavra))
				{
					return 1;
					break;
				}
			}
		}

		for( x = 0; x < 25; x++){ //de forma horizontal inverso
			for( y = 25; y >= 0; y--){
				if(palavra[cont] == pal[x][y])
				{
					cont++;
				}
				else
				{
					cont = 0;
				}	
					
				if(cont == strlen(palavra))
				{
					return 1;
					break;
				}
			}
		}

		for( y = 0; y < 25; y++){ //vertical cima pra baixo
			for( x = 0; x < 25; x++){
				if(palavra[cont] == pal[x][y])
				{
					cont++;
				}
				else
				{
					cont = 0;
				}
						
				if(cont == strlen(palavra))
				{
					return 1;
					break;
				}
			}
		}
	
		for( y = 0; y < 25; y++){ //vertical baixo pra cima
			for( x = 25; x >= 0; x--){
				if(palavra[cont] == pal[x][y])
				{
					cont++;
				}
				else
				{
					cont = 0;
				}
						
				if(cont == strlen(palavra))
				{
					return 1;
					break;
				}
			}
		}
		
	return 0;
}
//---------------------------------------------
void continuar(){
	
	printf("Deseja continuar? (s/n)");
	scanf("%c", &resposta);
	fflush(stdin);
}
