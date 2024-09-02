#define TFL 500
#define TFC 256

struct listatokens{
	struct listatokens *prox;
	char token[TFL];
};

typedef struct listatokens ListaTokens;

void InitTokens(ListaTokens**p){
	*p=NULL;
}

ListaTokens* NovoToken(char token[TFL]){
	ListaTokens *novo=(ListaTokens*)malloc(sizeof(ListaTokens));
	strcpy(novo->token,token);
	novo->prox=NULL;
	return novo;
}

void InsereToken(ListaTokens**lista, char token[TFL]) {
    ListaTokens *nova = NovoToken(token), *aux;
    if (*lista == NULL)
        *lista = nova;
    else {
        aux = *lista;
        while (aux->prox != NULL)
            aux = aux->prox;
        aux->prox = nova;
    }
}


void ExibeTokens(ListaTokens *lista){
	while(lista!=NULL){
		printf("%s %d %c ",lista->token,lista,26);
		lista=lista->prox;
	}
	printf("NULL");
}
