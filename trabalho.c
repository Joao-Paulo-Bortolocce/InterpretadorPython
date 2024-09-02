#include<stdio.h>
#include<string.h>
#include<malloc.h>



#include"Tokens.h"
#include"ListaPrograma.h"


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
        if (tl > 0) {  // Token j� est� completo e foi parado por encontrar o caractere
            (*i)--;
        } else {  // Caractere especial � a primeira letra da string
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
			//printf("%s\n",token);
			InsereToken(&(*tokens),token);
		}
	}
}

void RecebeArquivo(char caminho[TFC],ListaGeral **programa){
	char linha[TFL];
	ListaTokens *tokens;
	InitTokens(&tokens);
	FILE*ponteiro= fopen(caminho,"r");
	if(ponteiro==NULL)
		printf("Seu arquivo nao existe ou nao foi encontrado");
	else{
		while(!feof(ponteiro)){
			fgets(linha,sizeof(linha),ponteiro);  
			if(strlen(linha)>1){ // quer dizer que n�o � apenas um ENTER geralmente sinalizando fim de fun��o
				//printf("\n%s\n",linha);
				SeparaTokens(linha,&tokens);
			}
			else{
				InitTokens(&tokens);
				strcpy(linha,"FimDef");
				InsereToken(&tokens,linha);
				//Fun��o FIM-DEF;
			}
			InserirGeral(&(*programa),tokens);
			InitTokens(&tokens);
		}
	}
}

void EncontraInicio(ListaGeral** programa){
	char flag=1;
	while(flag){
		if(stricmp((*programa)->tokens->token,"def")==0){
			while(stricmp((*programa)->tokens->token,"FimDef")!=0)
				*programa=(*programa)->prox;
			*programa=(*programa)->prox;
		}
		else
			flag=0;
	}
}

void Executar(){
	char caminho[TFC];
	ListaGeral *programa;
	Init(&programa);
	printf("Informe o caminho do arquivo .py Ex: [C://teste.py]");
	gets(caminho);
	RecebeArquivo(caminho,&programa);
	ExibeGeral(programa);
	EncontraInicio(&programa);
}

int main(){
	Executar();
	return 0;
}
