#define TFI 10

union tpvalor{
	long int valori; //0
	double valorf;//1
	char valors[20];//2
	ListaGeral *ponteiro;//3
	//ListaGen *pListaGen //4
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


void ExibePilha(Pilha *p, int colunaInicial, int linhaInicial){
    int i, j, vet[2];
    vet[0] = colunaInicial + 16;
    vet[1] = vet[0] + 16;

    // Topo da caixa
    gotoxy(colunaInicial, linhaInicial);
    printf("%c", 201); // Canto superior esquerdo

    for (i = colunaInicial + 1; i < 97; i++) {
        gotoxy(i, linhaInicial);
        if (i == vet[0] || i == vet[1])
            printf("%c", 203); // Divisões de colunas
        else
            printf("%c", 205); // Linha horizontal
    }

    gotoxy(97, linhaInicial); 
    printf("%c", 187); // Canto superior direito

    // Exibição dos elementos da pilha
    i = linhaInicial;
    while (p != NULL) {
        i++;
        gotoxy(colunaInicial, i);
        printf("%c", 186); // Borda esquerda
        gotoxy(vet[0], i);
        printf("%c", 186); // Divisória
        gotoxy(vet[1], i);
        printf("%c", 186); // Divisória
        gotoxy(97, i);
        printf("%c", 186); // Borda direita

        // Exibe o id centralizado
       gotoxy(vet[0]-10, i);
        printf("%s", p->id);

        // Exibe o valor com base no tipo
        switch (p->terminal) {
            case 0: // Valor inteiro
                gotoxy(vet[1]-10, i);
                printf("%d", p->valor.valori);
                break;
            case 1: // Valor float
                gotoxy(vet[1]-10, i);
                printf("%.2f", p->valor.valorf);
                break;
            case 2: // Valor string
                gotoxy(vet[1]-10, i);
                printf("%s", p->valor.valors);
                break;
        }

        // Exibe ponteiro ou "NULL"
        if (p->terminal != 3) {
            gotoxy(78, i);
            printf("NULL");
        } else {
            gotoxy(78, i);
            printf("%d", p->valor.ponteiro);
        }

        // Linha divisória inferior
        i++;
        gotoxy(colunaInicial, i);
        printf("%c", 204); // Divisão esquerda

        for (j = colunaInicial + 1; j < 97; j++) {
            gotoxy(j, i);
            if (j == vet[0] || j == vet[1])
                printf("%c", 206); // Divisões de colunas
            else
                printf("%c", 205); // Linha horizontal
        }

        gotoxy(97, i);
        printf("%c", 185); // Divisão direita

        // Próximo elemento da pilha
        p = p->prox; 
    }

    // Base da caixa
    gotoxy(colunaInicial, ++i);
    printf("%c", 200); // Canto inferior esquerdo

    for (j = colunaInicial + 1; j < 97; j++) {
        gotoxy(j, i);
        if (j == vet[0] || j == vet[1])
            printf("%c", 202); // Divisões de colunas
        else
            printf("%c", 205); // Linha horizontal
    }

    gotoxy(97, i);
    printf("%c", 188); // Canto inferior direito
}


Pilha* BuscaVariavel(char id[TFI],Pilha *pVariaveis){//Essa busca verifica se existe aquela variavel na pilha naquele escopo
	Pilha *aux;
	while(pVariaveis!=NULL && pVariaveis->terminal!=3 && stricmp(pVariaveis->id,id))
		pVariaveis=pVariaveis->prox;
	if(pVariaveis!=NULL && pVariaveis->terminal==3)
		return NULL;
	return pVariaveis;
}
