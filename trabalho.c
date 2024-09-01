#include<stdio.h>
#include<string.h>
#define TFL 500
#define TFC 256

char CaractereEspecialNaoUsado(char c){
	if(c==32 || c==',' || c==':'|| c==10)
		return 1;
	return 0;
}

char CaractereEspecialUsado(char c){
	if(c=='+' || c=='-' || c=='/' || c=='*' || c=='(' || c==')' || c=='%' || c=='=' || c==34 || c==39)
		return 1;
	return 0;
}

void RetornaPalavra(char token[TFL], char linha[TFL], int *i) {
    int tl = 0;

    for (; *i < strlen(linha) && !CaractereEspecialNaoUsado(linha[*i]) && !CaractereEspecialUsado(linha[*i]); (*i)++) {
        token[tl] = linha[*i];
        tl++;
    }

    if (CaractereEspecialUsado(linha[*i])) {
        if (tl > 0) {  // Token já está completo e foi parado por encontrar o caractere
            (*i)--;
        } else {  // Caractere especial é a primeira letra da string
            token[0] = linha[*i];
            tl = 1;
            if (linha[*i + 1] == linha[*i] && linha[*i] != '(' && linha[*i] != ')') {
                token[tl] = linha[*i];
                tl++;
                (*i)++;
            }
        }
    }
    token[tl] = '\0';
}

void SeparaTokens(char linha[TFL],ListaTokens**tokens){
	char token[TFL];
	int i;
	for(i=0;i<strlen(linha);i++){
		RetornaPalavra(token,linha,&i);
		if(strlen(token)>0){
			printf("%s\n",token);
			InsereToken(&(*tokens),token);
		}
	}
}

void RecebeArquivo(char caminho[TFC],ListaGeral **programa){
	char linha[TFL];
	ListaTokens *tokens;
	init(&tokens);
	FILE*ponteiro= fopen(caminho,"r");
	if(ponteiro==NULL)
		printf("Seu arquivo nao existe ou nao foi encontrado");
	else{
		while(!feof(ponteiro)){
			fgets(linha,sizeof(linha),ponteiro);  
			if(strlen(linha)>1){ // quer dizer que não é apenas um ENTER geralmente sinalizando fim de função
				printf("\n%s\n",linha);
				SeparaTokens(linha,&tokens);
			}
			else{
				InsereToken(&(*tokens),"FimDef");
				//Função FIM-DEF;
			}
			InserirGeral(&(*programa),tokens);
			init(&tokens);
		}
	}
}

void Executar(){
	char caminho[TFC];
	ListaGeral *programa;
	init(&programa);
	printf("Informe o caminho do arquivo .py Ex: [C://teste.py]");
	gets(caminho);
	RecebeArquivo(caminho,&programa);
}

int main(){
	Executar();
	return 0;
}
