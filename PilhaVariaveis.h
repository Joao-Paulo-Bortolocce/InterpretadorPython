#define TFI 10

union tpvalor{
	long int valori; //0
	double valorf;//1
	char valors[20];//2
	ListaGeral *ponteiro;//3
};

typedef union tpvalor Valor;

struct pilha{
	char id[TFI];
	Valor valor;
	char terminal;
	struct pilha *prox;
};

typedef struct pilha Pilha;

void InitPilha(Pilha **p){
	*p=NULL;
}

Pilha* NovaVariavel(char terminal,char id[TFI],char token[TFL]){
	Pilha *caixa=(Pilha*)malloc(sizeof(Pilha));
	strcpy(caixa->id,id);
	caixa->terminal=terminal;
	caixa->prox=NULL;
	switch(terminal){
		case 0:
			caixa->valor.valori=atoi(token);
			break;
		case 1:
			caixa->valor.valorf = atof(token);
			break;
		case 2:
			strcpy(caixa->valor.valors,token);
			break;
	}
	return caixa;
}

void Push(Pilha **p,char terminal,char id[TFI],char token[TFL]){
	Pilha *nova=NovaVariavel(terminal,id,token),*aux;
	if(*p==NULL)
		*p=nova;
	else{
		aux=*p;
		while(aux->prox!=NULL)
			aux=aux->prox;
		aux->prox=nova;
	}
}

char DefineTipo(char token[TFL]){
	int inteiro = atoi(token);
	double real= atof(token);
	if(inteiro == real){
		if(inteiro != 0 || token[0]==0)
			return 0;
		return 2;
	}
	return 1;
}

void PushSemTerminal(Pilha **p,char id[TFI],char token[TFL]){
	char terminal;
	terminal=DefineTipo(token);
	Push(&(*p),terminal,id,token);
}
