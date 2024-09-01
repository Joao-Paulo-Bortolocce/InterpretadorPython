#include"Tokens.h"

struct listageral{
	struct listageral *ant,*prox;
	ListaTokens *tokens;
};

typedef struct listageral ListaGeral;


void Init(ListaGeral **p){
	*p=NULL;
}

ListaGeral* NovaGeral(ListaTokens *tokens){
	ListaGeral *nova=(ListaGeral*)malloc(sizeof(ListaGeral));
	nova->prox=NULL;
	nova->ant=NULL;
	nova->tokens=tokens;
	return nova;
}

void InserirGeral(ListaGeral **lista,ListaTokens *tokens){
	ListaGeral *nova=NovaGeral(tokens),*aux;
	if(*lista==NULL)
		*lista=nova;
	else{
		aux=*lista;
		while(aux->prox!=NULL)
			aux=aux->prox;
		nova->ant=aux;
		aux->prox=nova;
	}
}
