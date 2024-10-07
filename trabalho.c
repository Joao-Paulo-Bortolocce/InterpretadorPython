#include<stdio.h>
#include<string.h>
#include<math.h>
#include<malloc.h>
#include<locale.h>


#include"Tokens.h"
#include"ListaPrograma.h"
#include"PilhaVariaveis.h"
#include"EquacaoGeneralizada.h"
void Executar(ListaGeral *programa,Pilha **pVariaveis );
#include"Execucao.h"


char isLista(char linha[TFL], int i){
	if(linha[i]=='.' && (linha[i-1]<48 || linha[i-1]>57) && (linha[i+1]<48 || linha[i+1]>57))
		return 1;
	return 0;
}

char CaractereEspecialNaoUsado(char c){
	if(c==32 || c==',' || c==':'|| c==10)
		return 1;
	return 0;
}

char CaractereEspecialUsado(char c){
	if(isEquacao(c) || c=='(' || c==')'|| c=='[' || c==']' || c=='=' /*|| c=='.' || c==34 || c==39 PARTE DA STRING*/)
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

    for (; *i < strlen(linha) && !CaractereEspecialNaoUsado(linha[*i]) && !CaractereEspecialUsado(linha[*i]) && !(linha[*i]==34 || linha[*i]==39) && !isLista(linha,*
	i); (*i)++) {
        token[tl] = linha[*i];
        tl++;
    }
	
	if(linha[*i]==34 || linha[*i]==39){
		token[tl] = linha[*i];
        tl++;
        (*i)++;
		for (; *i <strlen(linha) && linha[*i]!=34 && linha[*i]!=39; (*i)++) {
        	token[tl] = linha[*i];
        	tl++;
    	}
		token[tl] = linha[*i];
        tl++;	
		(*i)++;	
	}
	
    if (CaractereEspecialUsado(linha[*i]) || isLista(linha,*i)) {
        if (tl > 0) {  // Token já está completo e foi parado por encontrar o caractere
            (*i)--;
        } else {  // Caractere especial é a primeira letra da string
            token[0] = linha[*i];
            tl = 1;
            if (linha[*i + 1] == linha[*i] && linha[*i] != '(' && linha[*i] != ')' && linha[*i] != '[' && linha[*i] != ']') {
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
				InserirGeral(&(*programa),tokens,linha);
			}
			else{
				while(identacaoAnt-identacaoAtual >0){
					InitTokens(&tokens);
					InsereToken(&tokens,"@");
					identacaoAnt-=4;
					InserirGeral(&(*programa),tokens,linha);
				}
				if(strlen(linha)>1){
					InitTokens(&tokens);
					SeparaTokens(linha,&tokens);
					InserirGeral(&(*programa),tokens,linha);
				}
				//Função FIM-DEF, FIM-IF, ...;
			}		
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
	exibeLinhas(*programa);
	EncontraInicio(&(*programa)); //Função para encontrar a primeira linha que será executada
	printf("\n\nO inicio do programa esta no endereco: %d",*programa);
}

void exibirPrints(){
	system("cls");
	printf("\t\t\t\t\tTELA DO COMPUTADOR\n");
	char linha[TFL];
	FILE*ponteiro=fopen("Prints.txt","r");
	if(ponteiro==NULL)
		printf("Erro ao exibir prints\n");
	else{
		fgets(linha,TFL,ponteiro);
		while(!feof(ponteiro)){
			printf("%s",linha);
			fgets(linha,TFL,ponteiro);
		}
	}
}

void Executar(ListaGeral *programa,Pilha **pVariaveis ){
	char op,flag=1;
	while(programa!=NULL){
		op=getch();
		switch(op){
			case 13:
				if(flag)
					ExecutarLinha(&programa,&(*pVariaveis));
				break;
			case 65: //F7
				system("cls");
				exibeLinhas(programa);
				flag=1;
				break;
			case 66://F8
				flag=0;
				break;
			case 67://F9
				flag=0;
				ExibePilha(*pVariaveis);
				break;
			case 68://F10
				flag=0;
				exibirPrints();
				break;
			
		}
		if(programa!=NULL && op==13){
			MarcaLinha(programa);
			programa=programa->prox;
		}
	}
	
	
}


void abrirPrints(){
	FILE * ponteiro= fopen("Prints.txt","w");
	fclose(ponteiro);
}

int main(){
	setlocale(LC_NUMERIC, "C");
	abrirPrints();
	ListaGeral *programa;
	Init(&programa);
	Pilha *pVariaveis; //Criando a pilha de variaveis;
	InitPilha(&pVariaveis);
	Preparar(&programa);
	Executar(programa,&pVariaveis);
	return 0;
}
