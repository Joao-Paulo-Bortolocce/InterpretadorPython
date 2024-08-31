#include<stdio.h>

void RecebeArquivo(char caminho[]){
	char linha[2000];
	FILE*ponteiro= fopen(caminho,"r");
	if(ponteiro==NULL)
		printf("Seu arquivo nao existe ou nao foi encontrado");
	else{
		while(!feof(ponteiro)){
			fgets(linha,sizeof(linha),ponteiro);
			printf("%s",linha);
		}
	}
}

void Executar(){
	char caminho[256];
	printf("Informe o caminho do arquivo .py Ex: [C://teste.py]");
	gets(caminho);
	RecebeArquivo(caminho);
}

int main(){
	Executar();
	return 0;
}
