#include<stdio.h>
#include<string.h>
#include<malloc.h>



#include"Tokens.h"
#include"ListaPrograma.h"
#include"PilhaVariaveis.h"
#include"Execucao.h"

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

int QtdIdentacao(char linha[TFL]){
	int i;
	for(i=0;i<strlen(linha) && linha[i]==32;i++);
	return i;
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
			//printf("%s\n",token);
			InsereToken(&(*tokens),token);
		}
	}
}

void RecebeArquivo(char caminho[TFC],ListaGeral **programa){
	char linha[TFL];
	int identacaoAnt=0,identacaoAtual=0;
	ListaTokens *tokens;
	InitTokens(&tokens);
	FILE*ponteiro= fopen(caminho,"r");
	if(ponteiro==NULL)
		printf("Seu arquivo nao existe ou nao foi encontrado");
	else{
		while(!feof(ponteiro)){
			fgets(linha,sizeof(linha),ponteiro); 
			identacaoAtual=QtdIdentacao(linha);
			if(/*strlen(linha)>1 &&*/ identacaoAtual>=identacaoAnt){ // quer dizer que não é apenas um ENTER geralmente sinalizando fim de função
				//printf("\n%s\n",linha);
				SeparaTokens(linha,&tokens);
			}
			else{
				InitTokens(&tokens);
				InsereToken(&tokens,"@");
				if(strlen(linha)>1){
					InserirGeral(&(*programa),tokens);
					InitTokens(&tokens);
					SeparaTokens(linha,&tokens);	
				}
				//Função FIM-DEF, FIM-IF, ...;
			}
			InserirGeral(&(*programa),tokens);
			InitTokens(&tokens);
			identacaoAnt=identacaoAtual;
		}
	}
}

void EncontraInicio(ListaGeral **programa){
	char flag=1;
	while(flag){
		if(stricmp((*programa)->tokens->token,"def")==0){
			while(stricmp((*programa)->tokens->token,"@")!=0)
				*programa=(*programa)->prox;
			*programa=(*programa)->prox;
		}
		else
			flag=0;
	}
}

void Preparar(ListaGeral** programa){
	char caminho[TFC];
	printf("Informe o caminho do arquivo .py Ex: [C://teste.py]");
	gets(caminho);
	RecebeArquivo(caminho,&(*programa));
	ExibeGeral(*programa);
	EncontraInicio(&(*programa)); //Função para encontrar a primeira linha que será executada
	printf("\n\nO inicio do programa esta no endereco: %d",*programa);
}

void Executar(ListaGeral *programa,Pilha **pVariaveis ){
	char op;
	while(programa!=NULL){
		op=getch();
		while(op!=32)
			op=getch();
		switch(op){
			case 32:
				ExecutarLinha(programa,&(*pVariaveis));
				break;
		}
		programa=programa->prox;
	}
	
	
}

int main(){
	ListaGeral *programa;
	Init(&programa);
	Pilha *pVariaveis; //Criando a pilha de variaveis;
	InitPilha(&pVariaveis);
	Preparar(&programa);
	Executar(programa,&pVariaveis);
	return 0;
}
