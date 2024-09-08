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
	if(!stricmp(cabeca->token,"def"))
		return 5;
	return 6;
	
}

void ExecutarLinha(ListaGeral *programa,Pilha **pVariaveis ){
	while(programa!=NULL){
		switch(VerificaPrimeiroToken(programa->tokens)){
			case 0:
				Condicao(0);
				break;
			case 5:
				Atribuicao(&(*pVariaveis));
		}
	}
}
