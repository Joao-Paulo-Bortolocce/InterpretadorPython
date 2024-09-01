struct listatokens{
	struct listatokens *prox;
	char token[TFL];
};

typedef struct listatokens ListaTokens;

void initToken(ListaTokens **p){
	*p=NULL;
}

ListaToken* NovoToken(char token[TFL]){
	ListaTokens *novo=(ListaTokens*)malloc(sizeof(ListaTokens));
	novo->token=token;
	novo->prox=NULL;
	return novo;
}

void InsereToken(ListaTokens **lista, char token[TFL]){
	ListaTokens *nova=NovoToken(token),*aux;
	if(*lista==NULL)
		*lista=nova;
	else{
		aux=*lista;
		while(aux->prox!=NULL)
			aux=aux->prox;
		aux->prox=nova;
	}
}
