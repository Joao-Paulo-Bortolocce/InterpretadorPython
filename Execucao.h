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
	return 7;
	
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

void Atribuicao(ListaGeral *programa, Pilha **pVariaveis){
	Pilha *variavel=BuscaVariavel(programa->tokens->token,*pVariaveis);
	ListaTokens *linha=programa->tokens->prox->prox; //Coloca o ponteiro no 3º token da linha, para saber se a variavel recebe um valor ou um retorno de função
	Valor valor;
	char tipo;
	if(variavel==NULL){
		PushSemTerminal(&(*pVariaveis),programa->tokens->token,"0.0");
		variavel=*pVariaveis;
	}
	if(linha->token[0]==34 || linha->token[0]==39){ //Quer dizer que é uma string
		
	}
	else{ // quer dizer que é um número ou uma função
		tipo=DefineTipo(linha->token); //PAREI AQUI POIS NÃO CONSEGUI DEPURAR CORRETAMENTE
		switch(tipo){
			case 0:
				variavel->valor.valori= atoi(linha->token);
				break;
			case 1:
				variavel->valor.valorf= ATOF(linha->token);
				break;
			case 2:
				//ResolveFunçao();
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

void ExecutarLinha(ListaGeral **programa,Pilha **pVariaveis ){
	switch(VerificaPrimeiroToken((*programa)->tokens)){
		case 0:
			//Condicao(0);
			break;
		case 3:
			Repeticao(&(*programa),&(*pVariaveis),0);
			break;
		case 4:
			Repeticao(&(*programa),&(*pVariaveis),1);
			break;
		case 5:
			//Atribuicao(programa,&(*pVariaveis));
			break;
		case 6:
			*programa=NULL;
			break;
	}
}
