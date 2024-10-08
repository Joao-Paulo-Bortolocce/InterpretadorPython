void LimpaMenu()
{
	int i, j;
	textbackground(0);
	for(i=5;i<26;i++)
		for(j=10;j<26;j++)
		{
			gotoxy(i,j);
			printf(" ");
		}
}

void LimpaMensagem()
{
	int i, j = 7;
	textbackground(0);
	for(i=16;i<98;i++)
	{
		gotoxy(i,j);
		printf(" ");
	}
}

void LimpaTela()
{
	int i, j;
	textbackground(0);
	for(i=28;i<99;i++)
		for(j=10;j<26;j++)
		{
			gotoxy(i,j);
			printf(" ");
		}
}

void LimpaRelatorio(int j)
{
	int i, k;
	textbackground(0);
	for(i=2;i<=101;i++)
		for(k=27;k<=j;k++)
		{
			gotoxy(i,k);
			printf(" ");
		}
}

void Bordas(int ci, int li, int cf, int lf, int corTexto) {
	int i;
 	textcolor(corTexto);
	gotoxy(ci, li);
	printf("%c", 201);
	gotoxy(cf, li);
	printf("%c", 187);
	gotoxy(ci, lf);
	printf("%c", 200);
	gotoxy(cf, lf);
	printf("%c", 188);

	for(i=ci+1; i<cf; i++) {
		gotoxy(i, li);
		printf("%c", 205);
		gotoxy(i, lf);
		printf("%c", 205);
	}

	for(i=li+1; i<lf; i++) {
		gotoxy(ci, i);
		printf("%c", 186);
		gotoxy(cf, i);
		printf("%c", 186);
	}
	textcolor(7);
}

void LimpaTudo(int ci, int li, int cf, int lf)
{
	int i,j;

	for(i=ci; i<cf; i++) {
		for(j=li;j<lf; j++){
			gotoxy(i, j);
			printf(" ");
		}
	}


}
void Moldura()
{
	int i;
	
	Bordas(2,2,101,28,6);//Principal
	textcolor(6);
	gotoxy(38,3); printf("TRABALHO ESTRUTURA DE DADOS II");
	gotoxy(45,4); printf("Interpretador Python");
	textcolor(1);
	gotoxy(36, 3); printf("%c",245);
	gotoxy(68, 3); printf("%c",245);
	gotoxy(36, 4); printf("%c",245);
	gotoxy(68, 4); printf("%c",245);
	
	Bordas(4,6,99,8,1);//Mensagem
	Bordas(4,9,35,26,1);// Menu de Escolha
	Bordas(36,9,99,26,1);//Menu de Apresentar
}

void LimpaBorda()
{
	int i, j;
	for(i = 28; i < 99; i++)
	{
		gotoxy(i,26);
		printf(" ");
	}
	for(i = 3; i < 101; i++)
	{
		gotoxy(i,28);
		printf(" ");
	}
	
}
