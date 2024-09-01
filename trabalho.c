#include<stdio.h>
#include<string.h>
#define TFL 2000
#define TFC 256

char CaractereEspecialNaoUsado(char c){
	if(c==32 || c==',' || c==':'|| c==10)
		return 1;
	return 0;
}

char CaractereEspecialUsado(char c){
	if(c=='+' || c=='-' || c=='/' || c=='*' || c=='(' || c==')' || c=='%' || c=='=' || c==34 || c==44)
		return 1;
	return 0;
}

/*void RetornaPalavra(char token[TFL],char linha[TFL],int i){
	for(;i<strlen(linha);i++){
		if(!CaractereEspecialNaoUsado(linha[i])){
			if(!CaractereEspecialUsado(linha[i])){
				token[tl]=linha[i];
				tl++;
			}
			else{
				if(tl>0){
					token[tl]='\0';
					printf("%s\n",token);
				}
				
				token[0]=linha[i];
				tl=1;
				if(linha[i]==linha[i+1]){
					token[tl]=linha[i+1];
					tl++;
					i++;
				}
				token[tl]='\0';
				printf("%s\n",token);
				tl=0;
			}
		}
		else{
			if(tl>0){
				token[tl]='\0';
				printf("%s\n",token);
				tl=0;
			}
			
		}
	
}*/

void SeparaTokens(char linha[TFL]){
	char token[TFL];
	int i,tl=0;
	for(i=0;i<strlen(linha);i++){
		if(!CaractereEspecialNaoUsado(linha[i])){
			if(!CaractereEspecialUsado(linha[i])){
				token[tl]=linha[i];
				tl++;
			}
			else{
				if(tl>0){
					token[tl]='\0';
					printf("%s\n",token);
				}
				
				token[0]=linha[i];
				tl=1;
				if(linha[i]==linha[i+1]){
					token[tl]=linha[i+1];
					tl++;
					i++;
				}
				token[tl]='\0';
				printf("%s\n",token);
				tl=0;
			}
		}
		else{
			if(tl>0){
				token[tl]='\0';
				printf("%s\n",token);
				tl=0;
			}
			
		}
	}
}

void RecebeArquivo(char caminho[TFC]){
	char linha[TFL];
	FILE*ponteiro= fopen(caminho,"r");
	if(ponteiro==NULL)
		printf("Seu arquivo nao existe ou nao foi encontrado");
	else{
		while(!feof(ponteiro)){
			fgets(linha,sizeof(linha),ponteiro);
			if(strlen(linha)>1){ // quer dizer que não é apenas um ENTER geralmente sinalizando fim de função
				printf("\n%s\n",linha);
				SeparaTokens(linha);
			}
			else{
				//Função FIM-DEF;
			}
			
			
		}
	}
}

void Executar(){
	char caminho[TFC];
	printf("Informe o caminho do arquivo .py Ex: [C://teste.py]");
	gets(caminho);
	RecebeArquivo(caminho);
}

int main(){
	Executar();
	return 0;
}
