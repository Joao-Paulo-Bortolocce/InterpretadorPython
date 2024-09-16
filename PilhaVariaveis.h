#define TFI 10

union tpvalor{
	long int valori; //0
	double valorf;//1
	char valors[20];//2
	ListaGeral *ponteiro;//3
};

typedef union tpvalor Valor;

struct pilha{
	char id[TFI]; //Nome da variavel
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
		case '0':
			caixa->valor.valori=atoi(token);
			break;
		case '1':
			caixa->valor.valorf = atof(token);
			break;
		case '2':
			strcpy(caixa->valor.valors,token);
			break;
	}
	return caixa;
}

void Push(Pilha **p,char terminal,char id[TFI],char token[TFL]){
	Pilha *nova=NovaVariavel(terminal,id,token);
	if(*p==NULL)
		*p=nova;
	else{
		nova->prox=*p;
		*p=nova;
	}
}

double ATOF(char token[TFL]){
	double num=0,j=1.0,aux;
	int i;
	char flag=0;
	for(i=0;i<strlen(token);i++){
		if(token[i]>=48 && token[i]<=57 ||  token[i]=='.'){
			if(token[i]=='.'){
				flag=1;
			}
			else{
				if(flag){
					j*=10;
				}
				
				num*=10;
				num+=token[i]-48;
			}
			
		}
		else{
			i=strlen(token);
			num=0;
		}
			
	}
	return num/j;
}

char DefineTipo(char token[TFL]){
	double real;
	int inteiro = atoi(token);
	real = ATOF(token);
	if(inteiro == real){
		if(inteiro != 0 || token[0]==0)
			return 0; //Inteiro
		return 2; // String
	}
	return 1; //Float
}

void PushSemTerminal(Pilha **p,char id[TFI],char token[TFL]){
	char terminal;
	terminal=DefineTipo(token);
	Push(&(*p),terminal,id,token);
}

void ExibePilha(Pilha *p){
	while(p!=0){
		switch(p->terminal){
			case 0:
				printf("%s\t%d\tNULL\n",p->id,p->valor.valori);
				break;
			case 1:
				printf("%s\t%f\tNULL\n",p->id,p->valor.valorf);
				break;
			case 2:
				printf("%s\t%s\tNULL\n",p->id,p->valor.valors);
				break;
			case 3:
				printf("%s\t-\t%d\n",p->id,p->valor.ponteiro);
				break;
		}
		p=p->prox;
	}
}

Pilha* BuscaVariavel(char id[TFI],Pilha *pVariaveis){//Essa busca verifica se existe aquela variavel na pilha naquele escopo
	Pilha *aux;
	while(pVariaveis!=NULL && pVariaveis->terminal!=3 && stricmp(pVariaveis->id,id))
		pVariaveis=pVariaveis->prox;
	if(pVariaveis!=NULL && pVariaveis->terminal==3)
		return NULL;
	return pVariaveis;
}
