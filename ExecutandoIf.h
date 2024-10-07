union Variavel {
    float quebrado;
    int inteiro;
    char carac;
    char string[500]; // Para lidar com strings
};

char testaCondicao(char terminal, char opera[], Variavel v1, Variavel v2) {
	
	
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


typedef struct {
    int *items;
    int top;
} Pilha;

Pilha* criarPilha() {
    Pilha *p = (Pilha*)malloc(sizeof(Pilha));
    p->top = -1;
    p->items = (int*)malloc(sizeof(int));
    return p;
}

int isEmpty(Pilha *p) {
    return p->top == -1;
}

void push(Pilha *p, int value) {
        p->items[++p->top] = value;
}

int pop(Pilha *p) {
    if (!isEmpty(p)) {
        return p->items[p->top--];
    }
    return 0; // Retorna 0 se a pilha estiver vazia
}

void destruirPilha(Pilha *p) {
    free(p->items);
    free(p);
}

void exibirPilha(Pilha *p) {
	
    printf("Conteúdo da pilha: ");
    for (int i = p->top; i >= 0; i--) {
        printf("%d ", p->items[i]);
    }
    printf("\n");
}

int buscaParenteses(const char *string, int *inicio, int *fim) {
    int ultimoInicio = -1;
    *inicio = -1;
    *fim = -1;

    for (int i = 0; string[i] != '\0'; i++) {
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

int resolvePilha(Pilha *p) {
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

 // 0 == 1 and 1 == 1
int testaIf(char *string, Pilha *p) {
    Variavel v1, v2;
    int i = 0;
    char opera[4];
    char buffer[100]; // Para armazenar números temporariamente
    int pos = 0;

    while (string[i] != '\0') {
    	if((string[i] == '1' || string[i] == '0') && (string[i+2] == 'a' || string[i+1] == 'o' || string[i+1] == '\0')){ //verificando a possibilidade 1 and 1 
    		push(p, string[i] - '0');
		}
        if (isdigit(string[i])) {
            // Limpa o buffer para armazenar o número
            pos = 0;
            while (isdigit(string[i])) {
                buffer[pos++] = string[i++];
            }
            buffer[pos] = '\0';
            v1.inteiro = atoi(buffer); // Converte para inteiro
        } else if (string[i] == '>' || string[i] == '=' || string[i] == '<' || string[i] == '!') {
            pos = 0;
            opera[pos++] = string[i];
            if (string[i + 1] == '=' || string[i + 1] == '>' || string[i + 1] == '<') {
                opera[pos++] = string[++i]; // Adiciona o segundo caractere
            }
            opera[pos] = '\0';
            i++; // Avança para o próximo caractere
            printf("OPERADOR: %s\n", opera);

            // A segunda variável
            while (string[i] == ' ') i++; // Ignora espaços em branco
            if (isdigit(string[i])) {
                pos = 0;
                while (isdigit(string[i])) {
                    buffer[pos++] = string[i++];
                }
                buffer[pos] = '\0';
                v2.inteiro = atoi(buffer); // Converte para inteiro
            }

            // Processa a condição
            push(p, testaCondicao('0', opera, v1, v2));
        } else if (string[i] == 'o' || string[i] == 'a') {
            if (string[i] == 'o') {
                i += 1; // Para o "or"
                push(p, 3); // Representando "or"
            } else {
                i += 2; // Para "and"
                push(p, 2); // Representando "and"
            }
        }
        i++;
    }
	/*printf("Exibindo pilha:\n");
	exibirPilha(p);*/
	 
    return resolvePilha(p); // Retorna o resultado final da pilha
}


int resolveComParenteses(char *string, Pilha *p) {
    int inicio, pos, fim, resultado, i;
    char subexpressao[100], novaString[200];

    while (buscaParenteses(string, &inicio, &fim)) {
        pos = 0;

        for (i = inicio + 1; i < fim; i++) {
            subexpressao[pos++] = string[i];
        }
        subexpressao[pos] = '\0';
        resultado = testaIf(subexpressao, p);

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
    return testaIf(string, p);
}

