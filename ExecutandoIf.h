union Variavel {
    float quebrado;
    int inteiro;
    char carac;
    char string[500]; // Para lidar com strings
};

typedef struct {
    int *items;
    int top;
} PilhaIf;

char testaCondicao(char terminal, char opera[], union Variavel v1, union Variavel v2) {
	
	if(strcmp(opera, "==") == 0) {
		if(terminal == '0')
			return v1.inteiro == v2.inteiro;
		else if(terminal == '1')
				return v1.quebrado == v2.quebrado;
			else {
				if(strcmp(v1.string, v2.string) == 0)
					return 1;
				return 0;
			}
	} else if(strcmp(opera, "!=") == 0) {
			if(terminal == '0')
				return v1.inteiro != v2.inteiro;
			else if(terminal == '1')
				return v1.quebrado != v2.quebrado;
				else {
					if(strcmp(v1.string, v2.string) != 0)
						return 1;
					return 0;
				}
		
	} else if(strcmp(opera, ">") == 0){
			if(terminal == '0')
				return v1.inteiro > v2.inteiro;
			else if(terminal == '1')
				return v1.quebrado > v2.quebrado;
				else{
					if(strcmp(v1.string, v2.string) > 0)
						return 1;
					return 0;
				}
	} else if(strcmp(opera, ">=") == 0){
			if(terminal == '0')
				return v1.inteiro >= v2.inteiro;
			else if (terminal == '1')
				return v1.quebrado >= v2.quebrado;
				else{
					if(strcmp(v1.string, v2.string) >= 0)
						return 1;
					return 0;
				}
	} else if(strcmp(opera, "<") == 0){
			if(terminal == '0')
				return v1.inteiro < v2.inteiro;
			else if(terminal == '1')
				return v1.quebrado < v2.quebrado;
				else{
					if(strcmp(v1.string, v2.string) < 0)
						return 1;
					return 0;
				}
	} else if(strcmp(opera, "<=") == 0){
			if(terminal == '0')
				return v1.inteiro <=  v2.inteiro;
			else if(terminal == '1')
				return v2.quebrado <= v2.quebrado;
				else{
					if(strcmp(v1.string, v2.string) <= 0)
						return 1;
					return 0;
				}
	} /*else if(strcmp(opera, "in") == 0){
		
	} else if(strcmp(opera, "not in") == 0){
		
	}*/

	return 0; //caso de string não reconhecida 
}


PilhaIf* criarPilha() {
    PilhaIf *p = (PilhaIf*)malloc(sizeof(Pilha));
    p->top = -1;
    p->items = (int*)malloc(sizeof(int));
    return p;
}

int isEmpty(PilhaIf *p) {
    return p->top == -1;
}

void push(PilhaIf *p, int value) {
        p->items[++p->top] = value;
}

int pop(PilhaIf *p) {
    if (!isEmpty(p)) {
        return p->items[p->top--];
    }
    return 0; // Retorna 0 se a pilha estiver vazia
}

void destruirPilha(PilhaIf *p) {
    free(p->items);
    free(p);
}

void exibirPilha(PilhaIf *p) {
	int i;
    printf("Conteúdo da pilha: ");
    for (i = p->top; i >= 0; i--) {
        printf("%d ", p->items[i]);
    }
    printf("\n");
}

int buscaParenteses(const char *string, int *inicio, int *fim) {
    int ultimoInicio = -1, i;
    *inicio = -1;
    *fim = -1;

    for (i = 0; string[i] != '\0'; i++) {
        if (string[i] == '(') {
            ultimoInicio = i;
        } else if (string[i] == ')') {
            if (ultimoInicio != -1) {
                *inicio = ultimoInicio;
                *fim = i;
                return 1; // Encontrou um par de parênteses
            }
        }
    }
    return 0; // Não encontrou parênteses
}

int resolvePilha(PilhaIf *p) {
    int result = 0, right, value;

    while (!isEmpty(p)) {
        value = pop(p);
        if (value == 0 || value == 1) { // Valores booleanos
            result = value;
        } else if (value == 2) { // Representa "and"
            right = pop(p);
            result = result && right; // "&&"
        } else if (value == 3) { // Representa "or"
            right = pop(p);
            result = result || right; // "||"
        } else if (value == 4) { // Representa "!"
            right = pop(p);
            result = !right; // Nega o valor
        }
    }

    return result;
}

char isFloat(char array[])
{
	int i;
	for(i = 0; i < strlen(array) && array[i] != '.'; i++);
	if(i < strlen(array))
		return i;
	return 0;
}


int testaIf(char *string, PilhaIf *p, Pilha *pVariaveis) {
    union Variavel v1, v2;
    int i = 0, pos = 0, verificaFloat;
    char opera[4];
    char buffer[100]; // Para armazenar números temporariamente
    Pilha *pilha;
	
    while (string[i] != ':') {
        if ((string[i] == '1' || string[i] == '0') && (string[i + 2] == 'a' || string[i + 1] == 'o' || string[i + 1] == '\0')) { 
            // Verificando a possibilidade de "1 and 1"
            push(p, string[i] - '0');
        }
        if (string[i] >= 'a' && string[i] <= 'z' || string[i] >= 'A' && string[i] <= 'Z') {
            // Limpa o buffer para armazenar a variável
            pos = 0;
            while (string[i] >= 'a' && string[i] <= 'z' || string[i] >= 'A' && string[i] <= 'Z') {
                buffer[pos++] = string[i++];
            }
            buffer[pos] = '\0';
            
            // Busca a variável na pilha de variáveis
            pilha = BuscaVariavel(buffer, pVariaveis);
            if (pilha != NULL) {
                if (pilha->terminal == 0) {
                    v1.inteiro = pilha->valor.valori;
                } else if (pilha->terminal == 1) {
                    v1.quebrado = pilha->valor.valorf;
                } else {
                    strcpy(v1.string, pilha->valor.valors);
                }
            } else {
                // Se a variável não for encontrada, assumimos que é uma string literal
                strcpy(v1.string, buffer);
            }
        } else if (string[i] >= '0' && string[i] <= '9') {
            // Processa números
            pos = 0;
            while (string[i] >= '0' && string[i] <= '9' || string[i] == '.') {
                buffer[pos++] = string[i++];
            }
            buffer[pos] = '\0';
			
			verificaFloat = isFloat(buffer);
			
            if (verificaFloat) {
                v1.quebrado = atof(buffer); // Converte para float se for decimal
            } else {
                v1.inteiro = atoi(buffer); // Converte para inteiro
            }
        } else if (string[i] == '>' || string[i] == '=' || string[i] == '<' || string[i] == '!') {
            // Lê o operador de comparação
            pos = 0;
            opera[pos++] = string[i];
            if (string[i + 1] == '=' || string[i + 1] == '>' || string[i + 1] == '<') {
                opera[pos++] = string[++i];
            }
            opera[pos] = '\0';
            i++; // Avança para o próximo caractere

            // Lê a segunda variável ou número para comparação
            while (string[i] == ' ') i++; // Ignora espaços
            if (string[i] >= 'a' && string[i] <= 'z' || string[i] >= 'A' && string[i] <= 'Z') {
                pos = 0;
                while (string[i] >= 'a' && string[i] <= 'z' || string[i] >= 'A' && string[i] <= 'Z') {
                    buffer[pos++] = string[i++];
                }
                buffer[pos] = '\0';
                
                pilha = BuscaVariavel(buffer, pVariaveis);
                if (pilha != NULL) {
                    if (pilha->terminal == 0) {
                        v2.inteiro = pilha->valor.valori;
                    } else if (pilha->terminal == 1) {
                        v2.quebrado = pilha->valor.valorf;
                    } else {
                        strcpy(v2.string, pilha->valor.valors);
                    }
                } else {
                    strcpy(v2.string, buffer);
                }
            } else if (string[i] >= '0' && string[i] <= '9') {
                pos = 0;
                while (string[i] >= '0' && string[i] <= '9' || string[i] == '.') {
                    buffer[pos++] = string[i++];
                }
                buffer[pos] = '\0';
				
				verificaFloat = isFloat(buffer);
				
                if (verificaFloat) {
                    v2.quebrado = atof(buffer); // Converte para float
                } else {
                    v2.inteiro = atoi(buffer); // Converte para inteiro
                }
            }

            // Processa a comparação
            push(p, testaCondicao(pilha->terminal, opera, v1, v2));
        } else if (string[i] == 'o' || string[i] == 'a') {
            // Operadores "or" e "and"
            if (string[i] == 'o') {
                i += 1; // Para o "or"
                push(p, 3); // Representa "or"
            } else {
                i += 2; // Para "and"
                push(p, 2); // Representa "and"
            }
        }
        i++;
    }

    return resolvePilha(p); // Retorna o resultado final da pilha
}


int resolveComParenteses(char *string, PilhaIf *p, Pilha *pVariaveis) {
    int inicio, pos, fim, resultado, i;
    char subexpressao[100], novaString[200];

    while (buscaParenteses(string, &inicio, &fim)) {
        pos = 0;

        for (i = inicio + 1; i < fim; i++) {
            subexpressao[pos++] = string[i];
        }
        subexpressao[pos] = '\0';
        resultado = testaIf(subexpressao, p, pVariaveis);

        pos = 0;

        for (i = 0; i < inicio; i++) {
            novaString[pos++] = string[i];
        }

        if (resultado == 0) {
            novaString[pos++] = '0';
        } else {
            novaString[pos++] = '1';
        }

        for (i = fim + 1; string[i] != '\0'; i++) {
            novaString[pos++] = string[i];
        }

        novaString[pos] = '\0';

        strcpy(string, novaString);
    }
    printf("String: %s\n", string);
    return testaIf(string, p, pVariaveis);
}

