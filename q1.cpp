#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//vari�veis globais
//Ao trocar os caminhos lembrar de colocar duas barras (\\) 

//Al�m de ser feio, tenho pregui�a de ficar declarando vari�veis dentro de fun��es
//Declarei todas as vari�veis como globais. 
//Motivo 1 - n�o preciso ficar criando 1001 outras vari�veis no projeto
//Motivo 2 - por elas serem globais, nesse caso, � muito mais f�cil manipular as refer�ncias e valores delas do que ficar passando valores entre fun��es

//Na leitura do c�digo voc�s ir�o ver que eu chamo algumas vezes o m�todo zerarNumeroAuxiliar(); 
//Da�, voc�s v�o conseguir entender que com uma �nica vari�vel eu consigo fazer 5/6/7/n opera��es

int tamanhoDaSequencia = 0, numeroAuxiliar = 0;
char *dna, *cromossomo1, *cromossomo2, *descendencia1, *descendencia2;
char digitos[2], base = 'A',
url[] = "C:\\Users\\Ygor Reis\\Documents\\trabalhoAuriLinda\\dna.txt", 
urlSaida[] = "C:\\Users\\Ygor Reis\\Documents\\trabalhoAuriLinda\\dna_saida.txt",
urlCromossomo1[] = "C:\\Users\\Ygor Reis\\Documents\\trabalhoAuriLinda\\cromossomo1.txt",
urlCromossomo2[] = "C:\\Users\\Ygor Reis\\Documents\\trabalhoAuriLinda\\cromossomo2.txt",
urlCromossomoSaida[] = "C:\\Users\\Ygor Reis\\Documents\\trabalhoAuriLinda\\cromossomo_saida.txt",
urlCromossomoSaida2[] = "C:\\Users\\Ygor Reis\\Documents\\trabalhoAuriLinda\\cromossomo_saida__2.txt";

//declara��o de m�todos
void lerArquivo(char *url, char *digitos, int opcaoImpressao);
void obterTamanhoSequencia(char *digitos);
void criarCadeiaCorrespondente(char *dna);
void salvarArquivo(char *url, char *dna);
void gerarMutacao(char *dna, char baseDesejada);
void obterCromossomo(char *url, char *cromossomo);
void imprimirResultados(int opcao);
void copiarVetor(char *vetorDestino, char *vetorOrigem);
void zerarNumeroAuxiliar();
void criarNumeroRandomico();
void gerarCruzamento();
void gerarCromossomosDescendecias();

int main(){
	
	//vcs sabem que um la�o s� executa quando uma condi��o � verdadeira
	//qualquer linguagem de programa��o 1 � verdade e 0 � mentira
	//criei a vari�vel fakeBool para que o menu fique ativo para o usu�rio (executar o c�digo vai fazer voc�s entenderem isso melhor)
	int fakeBool = 1;
	int opcaoMenu = 0;
	
	while(fakeBool){
		printf("\nEscolha uma opcao: \n");
		printf("1 - Criar Cadeia Correspondente \n");
		printf("2 - Gerar Mutacao \n");
		printf("3 - Gerar Cruzamento \n");
		printf("4 - Sair \n");
		scanf("%d", &opcaoMenu);
		
		switch(opcaoMenu){
			case 1:
				//system cls � um comando para a janela do terminal ser limpa
				//� s� mais um "comando de est�tica"
				system("cls");
				lerArquivo(url,digitos,0);	
				criarCadeiaCorrespondente(dna);
				salvarArquivo(urlSaida,dna);
				break;
			
			case 2:
				system("cls");
				gerarMutacao(dna, base);
				break;
				
			case 3:
				system("cls");
				gerarCruzamento();
				break;
				
			case 4:
				system("cls");
				printf("Adios, cabron..");
				fakeBool = 0;
				break;
				
			default:
				break;
		}
	}
    
	return 0;
}

//esse m�todo tem tr�s par�metros, 
//1 - a url do arquivo que tem o dna, 
//2 - o vetor com a quantidade de linhas do arquivo
//3 - o c�digo referente a impress�o, esse c�digo voc� v�o entender ele quando voc�s olharem o m�todo imprimirResultados();
 
//esse m�todo vai ver se o arquivo t� sucesso, se tiver, ele pega o dados do arquivo
//caso contr�rio, � porque deu shit!
void lerArquivo(char *url, char *digitos, int opcaoImpressao){	
	FILE *arq = fopen(url, "r");
	if(arq == NULL){
		printf("ERRO NA LEITURA");
	}else{
		while((fscanf(arq,"%s\n", digitos)) != EOF){
			if(numeroAuxiliar == 0){
				obterTamanhoSequencia(digitos);
				numeroAuxiliar++;
			}else{
				dna = (char *) malloc(tamanhoDaSequencia * sizeof(char));
				copiarVetor(dna,digitos);
				numeroAuxiliar = 0;
			}
		}
	}
	fclose(arq);
	imprimirResultados(opcaoImpressao);
}

//esse m�todo dispensa explica��o
void copiarVetor(char *vetorDestino, char *vetorOrigem){
	
	zerarNumeroAuxiliar();
	while (vetorOrigem[numeroAuxiliar] != '\0') {
		vetorDestino[numeroAuxiliar] = vetorOrigem[numeroAuxiliar];
		numeroAuxiliar++;
	}
	vetorDestino[numeroAuxiliar] = '\0';
	zerarNumeroAuxiliar();
	
}

void obterTamanhoSequencia(char *digitos){
	//todo arquio tem o tamanho do DNA esse m�todo(atoi) converte a string '13' no inteiro 13
	//se falarem besteira, falem que o foco do trabalho � no manuseio de vetores, uso do malloc, manipula�a� de strings e arquivos. Focar nessa fun��o � irrelevante.
	tamanhoDaSequencia = atoi(digitos);
}

void criarCadeiaCorrespondente(char *dna){
	
	//la�o respons�vel por trocar os nucleot�deos do DNA
	for(numeroAuxiliar; numeroAuxiliar < tamanhoDaSequencia; numeroAuxiliar++){
		if(dna[numeroAuxiliar] == 'A'){
			dna[numeroAuxiliar] = 'T';
		}else if(dna[numeroAuxiliar] == 'T'){
			dna[numeroAuxiliar] = 'A';
		}else if(dna[numeroAuxiliar] == 'C'){
			dna[numeroAuxiliar] = 'G';
		}else if(dna[numeroAuxiliar] == 'G'){
			dna[numeroAuxiliar] = 'C';
		}
	}
	imprimirResultados(1);
	zerarNumeroAuxiliar();
}

//esse m�todo tem dois par�metros, a url do arquivo de sa�da e o dna a ser escrito nele
//o m�todo vai ver se o arquivo t� sucesso, se tiver ele escreve o dna no arquivo e salva ele
//caso contr�rio, � porque deu shit!
void salvarArquivo(char *urlSaida, char *dna){
	
	FILE *arq = fopen(urlSaida, "w");
	if(arq == NULL){
		printf("ERRO NA LEITURA");
	}else{
		fprintf(arq,dna);
		printf("\n");
		printf("CONSULTAR ENDERECO: %s", urlSaida);
		printf("\n");
	}
	fclose(arq);
}

//esse m�todo dispensa explica��o, � um m�todo pra deixar centralizar as impress�es e deixar as coisas bonitinhas
void imprimirResultados(int opcao){
	
	if(opcao == 0){
		printf("DNA ORIGINAL       - %s\n", dna);	
	}else if(opcao == 1){
		printf("DNA CORRESPONDENTE - %s\n", dna);
	}else if(opcao == 2){
		printf(" TROCADA PELA BASE - %c\n", base);
		printf("DNA COM MUTACAO    - %s\n", dna);
		
		//esse printf pode ser apagado
		//eu coloquei ele aqui s� pra voc�s lembrarem que devem mostrar o arquivo, que cont�m o dna original, e comparar ele com o dna mostrado no terminal
		//para voc�s terem a certeza que houve a troca da base
		printf("PARA MELHOR VISUALIZACAO DA TROCA DE BASE, OLHAR ARQUIVO: %s\n", urlSaida);
	}else{
		printf("\n");
		printf("CROMOSSOMO         - %s\n", dna);
	}
}

void criarNumeroRandomico(){
	
	//a """"""""dica"""""""" da quest�o 2 diz para usar um n�mero random para gerar a muta��o #olharRequisitoDoTrabalho
	//srand(time(NULL)) � um jeitinho huehueBRBR para os n�meros aleat�rios nunca se repetirem
	//rand() % tamanhoDaSequencia � um jeito que vai me garantir que o n�mero aleat�rio n�o passe de um determinado valor
	//Ex.: se o tamanho do dna � 13, ent�o o tamanho da sequ�ncia do dna � 13, logo, por causa do % tamanho.. o n�mero random vai ficar entre 0 e 13
	//se o tamanho do dna � 20, o random vai ficar entre 0 e 20..
	//isso � uma garantia de que sempre voc�s v�o conseguir acessar uma posi��o v�lida no vetor
	srand(time(NULL));
	numeroAuxiliar = rand() % tamanhoDaSequencia;
	printf("\n");
	
	//nesse printf eu coloquei numeroAuxiliar + 1 para vcs n�o cometerem o mesmo engano que eu tive, pensar que a base trocada tava na posicao 6, enquanto a posicao era 5
	//lembrem-se que o vetor come�a no zero
	//resumindo, numeroAuxiliar + 1 � para s� pra facilitar a visualiza��o 
	printf("POSICAO: %d", numeroAuxiliar + 1);
}

void gerarMutacao(char *dna, char baseDesejada){
	
	for(numeroAuxiliar; numeroAuxiliar < 5; numeroAuxiliar++){
		printf("GERANDO MUTACAO...\n");
	}
	
	//esses dois m�todos voc�s j� sabem o que eles fazem
	zerarNumeroAuxiliar();	
	criarNumeroRandomico();
	
	
	//esse for vai tentar encontrar no DNA a posi��o aleat�ria e vai trocar a base
	int auxiliar = 0;
	for(auxiliar; auxiliar < tamanhoDaSequencia; auxiliar++){
		if(auxiliar == numeroAuxiliar){
			dna[auxiliar] = baseDesejada;
		}
	}
	
	//olhem depois o m�todo imprimirResultados e vejam o que o n�mero 2 imprime.. :)
	imprimirResultados(2);
}

void zerarNumeroAuxiliar(){
	numeroAuxiliar = 0;
}

void gerarCruzamento(){
	
	//m�todo que vai deixar pronto os vetores cromossomo/descendencias
	gerarCromossomosDescendecias();
	
	//esse m�todo s� consegue ser sucesso, ou seja, o cromossomo1/2 s� conseguem ser utilizados
	//porque no m�todo gerarCromossomos...() eles foram "criados".
	obterCromossomo(urlCromossomo1, cromossomo1);
	obterCromossomo(urlCromossomo2, cromossomo2);
	
	criarNumeroRandomico();	
	int auxiliar = 0;
	
	//� interessante voc�s olharem o arquivo sobre cruzamento que t� no sigaa
	//com a leitura do arquivo, voc�s v�o se ligar porque no else eu fa�o a troca
	
	//neste m�todo -> numeroAuxiliar == ponto do cruzamento
	//if == copiando os primeiros numeros antes do ponto de cruzamento
	//else == copiando os n�meros ap�s o ponto de cruzamento
	for(auxiliar; auxiliar < tamanhoDaSequencia; auxiliar++){
		if(auxiliar < numeroAuxiliar){
			descendencia1[auxiliar] = cromossomo1[auxiliar];
			descendencia2[auxiliar] = cromossomo2[auxiliar];
		}else{
			descendencia1[auxiliar] = cromossomo2[auxiliar];
			descendencia2[auxiliar] = cromossomo1[auxiliar];
		}
	}
	printf(" | EFEITO DO CRUZAMENTO");
	printf("\nDESCENDENCIA 01 - %s \n", descendencia1);
	printf("DESCENDENCIA 02 - %s \n", descendencia2);
	
	salvarArquivo(urlCromossomoSaida, descendencia1);
	salvarArquivo(urlCromossomoSaida2, descendencia2);
}

//esse m�todo pede dois par�metros
//1 - a url do arquivo que tem o cromossomo
//2 - o vetor em que o cromossomo vai ser salvo
void obterCromossomo(char *url, char *cromossomo){
	zerarNumeroAuxiliar();
	lerArquivo(url,digitos,3);
	copiarVetor(cromossomo,dna);
}

//m�todo do sucesso que cria os vetores e que v�o deixar voc�s fazerem todas as manipula��es necess�rias
void gerarCromossomosDescendecias(){
	cromossomo1 = (char *) malloc(tamanhoDaSequencia * sizeof(char));
	cromossomo2 = (char *) malloc(tamanhoDaSequencia * sizeof(char));
	descendencia1 = (char *) malloc(tamanhoDaSequencia * sizeof(char));
	descendencia2 = (char *) malloc(tamanhoDaSequencia * sizeof(char));
}
