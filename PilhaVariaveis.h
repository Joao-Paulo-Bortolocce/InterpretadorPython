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
	float real;
	int inteiro = atoi(token);
	real=ATOF(token);
	/*char result =sscanf(token,"%f",&real);;
	if(result==1)
		if(real ==inteiro)
			return 0;
		else
			return 1;
	return 2;*/
		if(inteiro == real){
			if(inteiro != 0 || token[0]=='0')
				return 0; //Inteiro
			return 2; // String
		}
		return 1; //Float
}

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
			//sscanf(token,"%f",&caixa->valor.valorf);
			caixa->valor.valorf=ATOF(token);
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


void PushSemTerminal(Pilha **p,char id[TFI],char token[TFL]){
	char terminal;
	terminal=DefineTipo(token);
	Push(&(*p),terminal,id,token);
}


void ExibePilha(Pilha *p){
	system("cls");
	printf("\t\t\tPILHA DE VARIAVEIS\n");
	int i,j;
	gotoxy(1,2);
	printf("%c",201);
	for(i=2;i<63;i++){
		gotoxy(i,2);
		printf("%c",205);
		if(i==21 || i==42){
			gotoxy(i,2);
			printf("%c",203);
		}
	}
	gotoxy(i,2);
		printf("%c",187);
	i=3;
	while(p!= NULL){
		gotoxy(1,i);
		printf("%c",186);
		gotoxy(21,i);
		printf("%c",186);
		gotoxy(42,i);
		printf("%c",186);
		gotoxy(63,i);
		printf("%c",186);
		gotoxy(10-(int)strlen(p->id)/2,i);
		if(p->terminal!=3)
			printf("%s",p->id);
		else
			printf("-----");
		gotoxy(31-(int)strlen(p->id)/2,i);
		switch(p->terminal){
			case 0:
				printf("%d",p->valor.valori);
				gotoxy(52-(int)strlen(p->id)/2,i);
				printf("NULL");
				break;
			case 1:
				printf("%f",p->valor.valorf);
				gotoxy(52-(int)strlen(p->id)/2,i);
				printf("NULL");
				break;
			case 2:
				printf("%s",p->valor.valors);
				gotoxy(52-(int)strlen(p->id)/2,i);
				printf("NULL");
				break;
			case 3:
				printf("",p->valor.valori);
				gotoxy(52-(int)strlen(p->id)/2,i);
				printf("%d",p->valor.ponteiro);
				break;
		}
		
		i++;
		p=p->prox;
		if(p!=NULL){
			gotoxy(1,i);
			printf("%c",204);
			j=i;
			for(i=2;i<63;i++){
				gotoxy(i,j);
				printf("%c",205);
				if(i==21 || i==42){
					gotoxy(i,j);
					printf("%c",206);
				}
			}
			gotoxy(i,j);
				printf("%c",185);
			i=j+1;
		}	
	}
	gotoxy(1,i);
	printf("%c",200);
	j=i;
	for(i=2;i<63;i++){
		gotoxy(i,j);
		printf("%c",205);
		if(i==21 || i==42){
			gotoxy(i,j);
			printf("%c",202);
		}
	}
	gotoxy(i,j);
		printf("%c",188);
}

Pilha* BuscaVariavel(char id[TFI],Pilha *pVariaveis){//Essa busca verifica se existe aquela variavel na pilha naquele escopo
	Pilha *aux;
	while(pVariaveis!=NULL && pVariaveis->terminal!=3 && stricmp(pVariaveis->id,id))
		pVariaveis=pVariaveis->prox;
	if(pVariaveis!=NULL && pVariaveis->terminal==3)
		return NULL;
	return pVariaveis;
}
