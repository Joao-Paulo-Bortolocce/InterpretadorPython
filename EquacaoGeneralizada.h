union conteudo{
	char funcao[20],operador[3];
	float valor;	
};

struct no{
	char terminal;
	union conteudo;
	struct no *cabeca,*cauda;
};
