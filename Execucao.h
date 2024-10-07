char VerificaPrimeiroToken(ListaTokens *cabeca){ //Descobrindo o que a linha significa, qual a função deve ser realizada
	if(!stricmp(cabeca->token,"if") )
		return 0;
	if(!stricmp(cabeca->token,"elif"))
		return 1;
	if(!stricmp(cabeca->token,"else"))
		return 2;
	if(!stricmp(cabeca->token,"while"))
		return 3;
	if(!stricmp(cabeca->token,"for"))
		return 4;
	if(!stricmp(cabeca->token,"print"))
		return 5;
	if(!stricmp(cabeca->token,"@"))
		return 6;
	if(!stricmp(cabeca->prox->token,"."))//Saber se é uma função de lista
		return 7;
	if(!stricmp(cabeca->prox->token,"="))//Saber se é uma função de lista
		return 8;
	return 9;
	
}

void recebeEquacao(ListaTokens **linha,ListaTokens **linhaAux){
	*linhaAux=NULL;
	char carac=(*linha)->token[0],carac2=(*linha)->prox->token[0];
	while((*linha)!=NULL && stricmp((*linha)->token,")") && (isEquacao(carac)!=isEquacao(carac2))){
		InsereToken(&(*linhaAux),(*linha)->token);
		*linha=(*linha)->prox;
		carac=(*linha)->token[0];
		carac2=(*linha)->prox->token[0];
	}
	InsereToken(&(*linhaAux),(*linha)->token);
}

void posicionaCorretamente(ListaGeral **programa){
	int cont=1,op;
	while(cont>0){ //Repetição para saber onde colocar corretamente o programa em execução
		*programa=(*programa)->prox;
		op=VerificaPrimeiroToken((*programa)->tokens);
		if(op<5) 
			cont++;
		else
			if(op==6)
				cont--;
	}
}

void selecionaString(char string[TFL],char original[TFL]){
	int i,tl;
	for(i=1,tl=0;i<strlen(original)-1;tl++,i++)
		string[tl]=original[i];
	string[tl]='\0';
}

char ResolveCondicao(Valor variavel,char terminal,char operador[],Valor parada){ //Recebe union para fazer 
	int i,j;
	char aux[TFL];
	if(!strcmp(operador,"<")){
		switch(terminal){
			case 0:
				return variavel.valori< parada.valori;
				break;
			case 1:
				return variavel.valorf< parada.valorf;
				break;
			case 2:
				if(strcmp(variavel.valors,parada.valors)<0)
					return 1;
				return 0;
				break;
		}
	}
	else
		if(!strcmp(operador,">")){
			switch(terminal){
				case 0:
					return variavel.valori > parada.valori;
					break;
				case 1:
					return variavel.valorf > parada.valorf;
					break;
				case 2:
					if(strcmp(variavel.valors,parada.valors)>0)
						return 1;
					return 0;
					break;
			}
		}
		else
			if(!strcmp(operador,"<=")){
				switch(terminal){
					case 0:
						return variavel.valori <= parada.valori;
						break;
					case 1:
						return variavel.valorf <= parada.valorf;
						break;
					case 2:
						if(strcmp(variavel.valors,parada.valors)<=0)
							return 1;
						return 0;
						break;
				}
			}
			else
				if(!strcmp(operador,">=")){
					switch(terminal){
						case 0:
							return variavel.valori >= parada.valori;
							break;
						case 1:
							return variavel.valorf >= parada.valorf;
							break;
						case 2:
							if(strcmp(variavel.valors,parada.valors)>=0)
								return 1;
							return 0;
							break;
					}
				}
				else
					if(!strcmp(operador,"==")){
						switch(terminal){
							case 0:
								return variavel.valori == parada.valori;
								break;
							case 1:
								return variavel.valorf == parada.valorf;
								break;
							case 2:
								if(strcmp(variavel.valors,parada.valors)==0)
									return 1;
								return 0;
								break;
						}
					}
					else
						if(!strcmp(operador,"in")){
							switch(terminal){
								/*case 0:
									return variavel.valori == parada.valori;
									break;
								case 1:
									return variavel.valorf == parada.valorf;
									break;*/
								case 2:
									for(i=0;i<strlen(parada.valors)-strlen(variavel.valors);i++){
										for(j=i;j<strlen(variavel.valors);j++)
											aux[j-i]=parada.valors[j];
										aux[j-i]='\0';
										if(strcmp(variavel.valors,aux)==0)
											return 1;
									}	
									return 0;
									break;
							}
						}
}

void Repeticao(ListaGeral **programa, Pilha **pVariaveis,char flag){
	int incremento;
	Valor p;
	ListaTokens *aux=(*programa)->tokens;
	char operador[3];
	Pilha *var = BuscaVariavel(aux->prox->token,*pVariaveis);
	if(var==NULL){
		Push(&(*pVariaveis),0,aux->prox->token,0);
		var=*pVariaveis;
	}
		
	if(flag){ //RECEBI FLAG 1 QUANDO A REPETIÇÃO FOR "FOR" E 0 QUANDO FOR WHILE
		while(stricmp(aux->token,"(")) //Encontra o primeiro parenteses do for, para verificar incremento, parada e inicio
			aux=aux->prox;
		aux=aux->prox;
		if(!stricmp(aux->prox->token,")")){//verificar quantos critérios póssuem inicio, parada e incremento, NESTE CASO O FOR SÓ PASSA CRITÉRIO DE PARADA
			p.valori=atoi(aux->token);
			incremento=1;
			var->valor.valori=0;
		}
		else{
			var->valor.valori=atoi(aux->token);
			p.valori=atoi(aux->prox->token);
			aux=aux->prox;
			aux=aux->prox;
			if(stricmp(aux->token,")"))
				incremento=atoi(aux->token);
			else
				incremento=1;
		}
		while(var->valor.valori <p.valori){
			Executar((*programa)->prox,&(*pVariaveis)); //Executa até encontrar o fim "@"
			var->valor.valori+=incremento;
		}
		
	}
	else{
		aux=aux->prox;
		aux=aux->prox;
		strcpy(operador,aux->token);
		aux=aux->prox;
		p.valori = atoi(aux->token); //Só funciona com numero.
		while(ResolveCondicao(var->valor,var->terminal,operador,p)){
			Executar((*programa)->prox,&(*pVariaveis));
			var->valor.valori+=1; //ESSA PARTE É SÓ PARA NÃO FICAR INFINITO, POIS ATRIBUIÇÃO AINDA NÃO EXISTE
		}
			
	}
	posicionaCorretamente(&(*programa));
}

void Print(ListaGeral *programa, Pilha **pVariaveis){
	FILE * ponteiro= fopen("Prints.txt","a");
	char print[TFL],string[TFL],aux[TFL];
	float var;
	int i=1,tl=0;
	print[0]='\0';
	Pilha *variavel;
	ListaTokens *tokens=programa->tokens,*auxL,*listaAux;
	tokens=tokens->prox->prox;
	if(tokens->token[0]==34 || tokens->token[0]==39){
		strcpy(string,tokens->token);
		tokens=tokens->prox;
		auxL=tokens;
		while(i<strlen(string)-1){
			while(i<strlen(string)-1 && string[i]!='%'){
				print[tl]=string[i];
				i++;tl++;
			}
				
			print[tl]='\0';
			if(tl>0)
				tl++;
			if(i<strlen(string)-1){
				tokens=tokens->prox;
				if(!stricmp(tokens->token,"("))
					tokens=tokens->prox;
				variavel=BuscaVariavel(tokens->token,*pVariaveis);
				
				if(variavel!=NULL){
					var=variavel->valor.valorf;
					if(isEquacao(tokens->prox->token[0])){
						recebeEquacao(&tokens,&listaAux);
						variavel->valor.valorf=ResolveExpressao(listaAux,*pVariaveis);
					}
					switch(variavel->terminal){
						case 0:
							itoa(variavel->valor.valori, aux, 10);
							break;
						case 1:
							sprintf(aux, "%.2f", variavel->valor.valorf);
							break;
						case 2:
							strcpy(aux,variavel->valor.valors);
							break;
					}
				}
				else
					strcpy(aux,tokens->token);	
				i+=2;
				strcat(print,aux);
				tl=strlen(print);
				if(variavel!=NULL)
					variavel->valor.valorf=var;
			}
		}
		if(stricmp(auxL->token,"%")){
			variavel=BuscaVariavel(tokens->token,*pVariaveis);
				if(variavel!=NULL){
					var=variavel->valor.valorf;
					if(isEquacao(tokens->prox->token[0])){
						recebeEquacao(&tokens,&listaAux);
						variavel->valor.valorf=ResolveExpressao(listaAux,*pVariaveis);
					}
					switch(variavel->terminal){
						case 0:
							itoa(variavel->valor.valori, aux, 10);
							break;
						case 1:
							sprintf(aux, "%.2f", variavel->valor.valorf);
							break;
						case 2:
							strcpy(aux,variavel->valor.valors);
							break;
					}
				}
				else
					strcpy(aux,tokens->token);	
			strcat(print,aux);
			if(variavel!=NULL)
				variavel->valor.valorf=var;
		}
		tl=strlen(print);
		print[tl]='\n';
		print[tl+1]='\0';
	}
	else{
		variavel=BuscaVariavel(tokens->token,*pVariaveis);
		if(variavel!=NULL){
			var=variavel->valor.valorf;
			if(isEquacao(tokens->prox->token[0])){
				recebeEquacao(&tokens,&listaAux);
				variavel->valor.valorf=ResolveExpressao(listaAux,*pVariaveis);
			}
			switch(variavel->terminal){
				case 0:
					itoa(variavel->valor.valori, aux, 10);
					break;
				case 1:
					sprintf(aux, "%.2f", variavel->valor.valorf);
					break;
				case 2:
					strcpy(aux,variavel->valor.valors);
					break;
			}
		}
		else
			strcpy(aux,tokens->token);	
		strcat(print,aux);
		tl=strlen(print);
		print[tl]='\n';
		print[tl+1]='\0';
		if(variavel!=NULL)
				variavel->valor.valorf=var;
	}
	fputs(print,ponteiro);
	fclose(ponteiro);
}

void Atribuicao(ListaGeral *programa, Pilha **pVariaveis){
	Pilha *variavel=BuscaVariavel(programa->tokens->token,*pVariaveis),*aux;
	ListaTokens *linha=programa->tokens->prox->prox; //Coloca o ponteiro no 3º token da linha, para saber se a variavel recebe um valor ou um retorno de função
	Valor valor;
	char tipo,string[TFL];
	if(variavel==NULL){
		PushSemTerminal(&(*pVariaveis),programa->tokens->token,"0.0");
		variavel=*pVariaveis;
	}
	if(linha->token[0]==34 || linha->token[0]==39){ //Quer dizer que é uma string
		selecionaString(string,linha->token);
		strcpy(variavel->valor.valors,string);
		variavel->terminal=2;
	}
	else{ // quer dizer que é um número ou uma função ou lista ou variavel
		if(stricmp(linha->token,"("))
			aux=BuscaVariavel(linha->token,*pVariaveis);	
		else
			aux=BuscaVariavel(linha->prox->token,*pVariaveis);
		if(aux!=NULL)
			tipo=aux->terminal;
		else
			tipo=DefineTipo(linha->token);
		switch(tipo){
			case 0: case 1:
				variavel->valor.valorf= ResolveExpressao(linha,*pVariaveis);
				variavel->terminal=1;
				break;
			case 2:
				//ResolveFunçao();
				break;
		}
	}
	
}

void ExecutarLinha(ListaGeral **programa,Pilha **pVariaveis ){
	switch(VerificaPrimeiroToken((*programa)->tokens)){
		case 0:
			posicionaCorretamente(&(*programa));
			//Condicao(0);
			break;
		case 3:
			Repeticao(&(*programa),&(*pVariaveis),0);
			break;
		case 4:
			Repeticao(&(*programa),&(*pVariaveis),1);
			break;
		case 5:
			Print(*programa,&(*pVariaveis));
			break;
		case 6:
			*programa=NULL;
			break;
		case 8:
			Atribuicao(*programa,&(*pVariaveis));
			break;
	}
}
