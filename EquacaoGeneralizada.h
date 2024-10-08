union conteudo{
	char funcao[20],operador[3];
	float valor;	
};

typedef union conteudo TpConteudo;

struct no{
	char terminal;
	TpConteudo conteudo;
	struct no *cabeca,*cauda;
};

typedef struct no No;

struct tppilhaRes{
	char terminal;
	TpConteudo conteudo;
	struct tppilhaRes *prox;
};

typedef struct tppilhaRes TpPilhaRes;

struct pilhagen{
	No *info;
	struct pilhagen *prox;
};

typedef struct pilhagen PilhaGen;

void InitPilhaGen(PilhaGen **p){
	*p=NULL;
}

void PushPilhaGen(PilhaGen **p,No *aux){
	PilhaGen *nova=(PilhaGen*)malloc(sizeof(PilhaGen));
	nova->info=aux;
	nova->prox=*p;
	*p=nova;
	
}

void PopPilhaGen(PilhaGen **p,No **aux){
	PilhaGen *pop=*p;
	*aux=(*p)->info;
	*p=pop->prox;
	free (pop);
}

char IsEmpty(PilhaGen *p){
	return p==NULL;
}


void PushSolucao(TpPilhaRes **p,TpConteudo Conteudo, char terminal){
	TpPilhaRes *nova=(TpPilhaRes*)malloc(sizeof(TpPilhaRes));
	nova->conteudo=Conteudo;
	nova->terminal=terminal;
	nova->prox=*p;
	*p=nova;
}

void PopSolucao(TpPilhaRes **p,TpConteudo *Conteudo, char *terminal){
	TpPilhaRes *aux=*p;
	*Conteudo=aux->conteudo;
	*terminal=aux->terminal;
	*p=aux->prox;
	free (aux);
}

char isEmptySolucao(TpPilhaRes *p){
	return p==NULL;
}

void InserirListaGen(No **lista,char terminal,TpConteudo Conteudo,char isCauda){
	No *nova=(No*)malloc(sizeof(No));
	nova->terminal= terminal;
	if(terminal =='v')
		nova->conteudo.valor=Conteudo.valor;
	else
		strcpy(nova->conteudo.operador,Conteudo.operador);
	nova->cabeca=NULL;
	nova->cauda=NULL;
	if(*lista==NULL)
		*lista=nova;
	else{
		if(isCauda)
			(*lista)->cauda=nova;
		else
			(*lista)->cabeca=nova;
	}
		
}

No* montaLista(ListaTokens* linha,Pilha *pVariaveis){
	No *inicio=NULL,*aux=inicio;
	PilhaGen *p;
	char cauda=1,flag=0;
	Pilha *var;
	InitPilhaGen(&p);
	TpConteudo valor;
	while(linha!=NULL){
		if(DefineTipo(linha->token) <2){
			valor.valor=ATOF(linha->token);
			//sscanf(linha->token,"%f",&valor.valor);
			InserirListaGen(&aux,'v',valor,cauda);
			if(inicio==NULL)
				inicio=aux;
			else{
				if(cauda)
					aux=aux->cauda;
				else{
					PushPilhaGen(&p,aux);
					aux=aux->cabeca;
					cauda=1;
				}
			}
		}
		else{
			valor.valor=0;
			if(!stricmp(linha->token,"(")){
					InserirListaGen(&aux,'v',valor,cauda);
					if(inicio==NULL){
						inicio=aux;
					}
					else{
						if(cauda)
							aux=aux->cauda;
						else{
							PushPilhaGen(&p,aux);
							aux=aux->cabeca;
							cauda=1;
						}
					}
					cauda=0;
			}
			else{
				if(!stricmp(linha->token,")")){
					PopPilhaGen(&p,&aux);
					flag=0;
				}
					
				else{
					if(!strcmp(linha->token,"+") || !strcmp(linha->token,"-") || !strcmp(linha->token,"/") || !strcmp(linha->token,"*") || !strcmp(linha->token,"//") || !strcmp(linha->token,"**") || !strcmp(linha->token,"%")){
						strcpy(valor.operador,linha->token);
						InserirListaGen(&aux,'o',valor,cauda);
					}
					else //AINDA PODE SER O NOME DE UMA VARIAVEL OU UMA FUNÇÃO
					{
						var=BuscaVariavel(linha->token,pVariaveis);
						if(var!=NULL){
							if(var->terminal){
								valor.valor=var->valor.valorf;
							}
							else{
								valor.valor=(float)var->valor.valori;
							}
							InserirListaGen(&aux,'v',valor,cauda);
						}
					}
					if(inicio==NULL){
						inicio=aux;
					}
					else{
						if(cauda)
							aux=aux->cauda;
						else{
							PushPilhaGen(&p,aux);
							aux=aux->cabeca;
							cauda=1;
						}
					}			
				}
			}
		}
		
		linha=linha->prox;
	}
	return inicio;
}

float ResolveOperacao(float num1,int num2,char operador[3]){
	if(!stricmp(operador,"+")){
		return num1+num2;
	}
	if(!stricmp(operador,"-")){
		return num1-num2;
	}
	if(!stricmp(operador,"*")){
		return num1*num2;
	}
	if(!stricmp(operador,"/")){
		return num1/num2;
	}
	if(!stricmp(operador,"%")){
		return (int)num1%(int)num2;
	}
	if(!stricmp(operador,"//")){
		return (int)num1/(int)num2;
	}
	if(!stricmp(operador,"**")){
		return pow(num1,num2);
	}
	
	
}

float calcula(TpPilhaRes **p){
	float num1,num2,resultado;
	char operador[3];
	TpConteudo valor;
	char terminal;
	PopSolucao(&(*p),&valor,&terminal);
	while(!isEmptySolucao(*p)){
		num1=valor.valor;
		PopSolucao(&(*p),&valor,&terminal);
		strcpy(operador,valor.operador);
		PopSolucao(&(*p),&valor,&terminal);
		num2=valor.valor;
		valor.valor=ResolveOperacao(num1,num2,operador);			
	}
	return valor.valor;
}

char prioridade(char operador[3]){
	if(!stricmp(operador,"+") || !stricmp(operador,"-"))
		return 0;
	if(!stricmp(operador,"*") || !stricmp(operador,"/")|| !stricmp(operador,"//"))
		return 1;
	if(!stricmp(operador,"**"))
		return 2;
	return 3;
}

float SolucionaExpressao(No *expressao){
	char terminal,flag=1;
	TpConteudo valor;
	TpPilhaRes *p=NULL,*aux=NULL;
	int i;
	while(expressao !=NULL){
		if(expressao->cabeca !=NULL)
			expressao->conteudo.valor=SolucionaExpressao(expressao->cabeca);
		if(expressao->terminal=='o'){
			PopSolucao(&p,&valor,&terminal);
			while(!isEmptySolucao(p) && terminal!='o'){
				PushSolucao(&aux,valor,terminal);
				PopSolucao(&p,&valor,&terminal);
			}
			PushSolucao(&p,valor,terminal);
			if(!isEmptySolucao(p) && prioridade(expressao->conteudo.operador)>prioridade(valor.operador)){ // NÃO PODE COLOCAR UM * EM CIMA DE UM +
				while(!isEmptySolucao(aux)){
					PopSolucao(&aux,&valor,&terminal);
					PushSolucao(&p,valor,terminal);
					
				}
				
				PushSolucao(&p,expressao->conteudo,expressao->terminal);
				expressao=expressao->cauda;
				PushSolucao(&p,expressao->conteudo,expressao->terminal);
				flag=0;
				for(i=0;i<3;i++){
					PopSolucao(&p,&valor,&terminal);
					PushSolucao(&aux,valor,terminal);
				}
				valor.valor= calcula(&aux);
				PushSolucao(&p,valor,terminal);
			}
			else
				while(!isEmptySolucao(aux)){
					PopSolucao(&aux,&valor,&terminal);
					PushSolucao(&p,valor,terminal);	
				}
		}
		if(flag)
			PushSolucao(&p,expressao->conteudo,expressao->terminal);
		expressao=expressao->cauda;
		flag=1;
	}
	while(!isEmptySolucao(p)){
		PopSolucao(&p,&valor,&terminal);
		PushSolucao(&aux,valor,terminal);
	}
	return calcula(&aux);
}

No* destruirNos(No *l){
	if(l!=NULL){
		l->cauda=destruirNos(l->cauda);
		l->cabeca=destruirNos(l->cabeca);
		free(l);
	}
	return NULL;
}

float  ResolveExpressao(ListaTokens* linha,Pilha *pVariaveis){
	No *expressao=montaLista(linha,pVariaveis);
	float resp = SolucionaExpressao(expressao);
	expressao = destruirNos(expressao);
	return resp;
}
