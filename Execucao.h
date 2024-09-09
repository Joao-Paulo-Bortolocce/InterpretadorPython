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
	if(!stricmp(cabeca->prox->token,"="))
		return 5;
	if(!stricmp(cabeca->token,"print"))
		return 6;
	if(!stricmp(cabeca->token,"@"))
		return 7;
	return 8;
	
}

void Atribuicao(ListaGeral *programa, Pilha **pVariaveis){
	Pilha *variavel=BuscaVariavel(programa->tokens->token,*pVariaveis);
	ListaTokens *linha=programa->tokens->prox->prox; //Coloca o ponteiro no 3º token da linha, para saber se a variavel recebe um valor ou um retorno de função
	Valor valor;
	char tipo;
	if(variavel==NULL){
		PushSemTerminal(&(*pVariaveis),programa->tokens->token,"0.0\0");
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
				variavel->valor.valorf= atof(linha->token);
				break;
			case 2:
				//ResolveFunçao();
				break;
		}
	}
	
}

void ExecutarLinha(ListaGeral *programa,Pilha **pVariaveis ){
	switch(VerificaPrimeiroToken(programa->tokens)){
		case 0:
			//Condicao(0);
			break;
		case 5:
			Atribuicao(programa,&(*pVariaveis));
	}
}
