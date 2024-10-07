#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "ExecutandoIf.h"

int main() {
    // Exemplo de expressões lógicas para testar
    int resultado1;
	char expressao[50];
    
    Pilha *pilha = criarPilha();

    // Testando a primeira expressão
    gets(expressao);
    printf("-------------------------------------------------\n");
    printf("Testando expressao: %s\n", expressao);
    resultado1 = resolveComParenteses(expressao, pilha);
    printf("-------------------------------------------------\n");
    printf("Resultado da expressao: %d\n", resultado1);

    destruirPilha(pilha);
    return 0;
}


/*Variavel v1, v2;
	int i, j, pos;
	char opera[4];
	
	
	for(i=0; i < strlen(string) - 1; i++){
		if(string[i] >= '0' && string[i] <= '9') //aqui acho a primeira variável 
			v1 = string[i];
		else if(string[i] == '>' || string[i] == '=' || string[i] == '<' || string[i] == '!')
			{
				pos=0;
				j=i+1;
				opera[pos] = string[i];
				if(string[j] == '>' || string[j] == '=' || string[j] == '<' || string[j] == '!')
				{
					pos++;
					opera[pos] = string[i];
				}
				pos++;
				opera[pos] = '\0';
				i++;
			}
			if(string[i] >= '0' && string[i] <= '9')
				v2 = string[i];
			if(string[i] == 'o' || string[i] == 'a' || string[i] == 'n'){
				push(&p, itoa(testaCondicao(1, opera, v1, v2)));
				if(string[i] == 'o'){
					i+=2;
					push(&p, "||\0");
				} else if(string[i] == 'a'){
					i+=3;
					push(&p, "&&\0")
				} else{
					i+=3;
					push(&p, "!\0");
				}
				
			}
	}
	push(&p, itoa(testaCondicao(1, opera, v1, v2)));
	return resolvePilha(&p);*/
