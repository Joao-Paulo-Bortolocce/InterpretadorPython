
struct listageral{
	struct listageral *ant,*prox;
	char linha[TFL];
	ListaTokens *tokens;
};

typedef struct listageral ListaGeral;


void Init(ListaGeral**p){
	*p=NULL;
}

ListaGeral* NovaGeral(ListaTokens *tokens,char linha[TFL]){
	ListaGeral *nova=(ListaGeral*)malloc(sizeof(ListaGeral));
	nova->prox=NULL;
	nova->ant=NULL;
	nova->tokens=tokens;
	if(stricmp(tokens->token,"@"))
		strcpy(nova->linha,linha);
	return nova;
}

void InserirGeral(ListaGeral **lista,ListaTokens *tokens,char linha[TFL]){
	ListaGeral *nova=NovaGeral(tokens,linha),*aux;
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

void ExibeGeral(ListaGeral *lista){
	printf("NULL\n");
	while(lista!=NULL){
		printf("%c\n",24);
		//printf(" %c ",26);
		printf("%d %c ",lista,26);
		ExibeTokens(lista->tokens);
		printf("\n%c\n",25);
		lista=lista->prox;
	}
	printf("NULL");
}

void exibeLinhas(ListaGeral *lista,int coluna, int linha){
	while(lista->ant!=NULL)
		lista=lista->ant;
	while(lista!=NULL){
		gotoxy(coluna,linha);
		if(stricmp(lista->tokens->token,"@")){
			printf("%s",lista->linha);
			linha++;
		}
		lista=lista->prox;
	}
}

void printaLinhaNormal(ListaGeral *lista,int coluna,int linha){
	gotoxy(coluna,linha);
	textcolor(15);
	textbackground(0);
	printf("%s",lista->linha);
}

void printaLinhaMarcada(ListaGeral *lista,int coluna,int linha){
	gotoxy(coluna,linha);
	textcolor(0);
	textbackground(3);
	printf("%s",lista->linha);
}

void encontraLinhaInicial(ListaGeral *lista,int coluna,int *linha){
	ListaGeral *aux=lista;
	while(aux->ant!=NULL)
		aux=aux->ant;
	while(aux!=lista && aux->prox!=lista){
		aux=aux->prox;
		if(stricmp(aux->tokens->token,"@"))
			(*linha)+=1;
	}
	if(aux!=lista){
		printaLinhaNormal(aux,coluna,*linha);
		(*linha)+=1;
	}
		
}

void MarcaLinha(ListaGeral *lista,int coluna,int linha){
	exibeLinhas(lista,coluna,linha);
	encontraLinhaInicial(lista,coluna,&linha);
	printaLinhaMarcada(lista,coluna,linha);
	textcolor(15);
	textbackground(0);
	
}
