#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//variáveis globais
//Ao trocar os caminhos lembrar de colocar duas barras (\\) 

//Além de ser feio, tenho preguiça de ficar declarando variáveis dentro de funções
//Declarei todas as variáveis como globais. 
//Motivo 1 - não preciso ficar criando 1001 outras variáveis no projeto
//Motivo 2 - por elas serem globais, nesse caso, é muito mais fácil manipular as referências e valores delas do que ficar passando valores entre funções

//Na leitura do código vocês irão ver que eu chamo algumas vezes o método zerarNumeroAuxiliar(); 
//Daí, vocês vão conseguir entender que com uma única variável eu consigo fazer 5/6/7/n operações

int tamanhoDaSequencia = 0, numeroAuxiliar = 0;
char *dna, *cromossomo1, *cromossomo2, *descendencia1, *descendencia2;
char digitos[2], base = 'A',
url[] = "C:\\Users\\Ygor Reis\\Documents\\trabalhoAuriLinda\\dna.txt", 
urlSaida[] = "C:\\Users\\Ygor Reis\\Documents\\trabalhoAuriLinda\\dna_saida.txt",
urlCromossomo1[] = "C:\\Users\\Ygor Reis\\Documents\\trabalhoAuriLinda\\cromossomo1.txt",
urlCromossomo2[] = "C:\\Users\\Ygor Reis\\Documents\\trabalhoAuriLinda\\cromossomo2.txt",
urlCromossomoSaida[] = "C:\\Users\\Ygor Reis\\Documents\\trabalhoAuriLinda\\cromossomo_saida.txt",
urlCromossomoSaida2[] = "C:\\Users\\Ygor Reis\\Documents\\trabalhoAuriLinda\\cromossomo_saida__2.txt";

//declaração de métodos
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
	
	//vcs sabem que um laço só executa quando uma condição é verdadeira
	//qualquer linguagem de programação 1 é verdade e 0 é mentira
	//criei a variável fakeBool para que o menu fique ativo para o usuário (executar o código vai fazer vocês entenderem isso melhor)
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
				//system cls é um comando para a janela do terminal ser limpa
				//é só mais um "comando de estética"
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

//esse método tem três parâmetros, 
//1 - a url do arquivo que tem o dna, 
//2 - o vetor com a quantidade de linhas do arquivo
//3 - o código referente a impressão, esse código você vão entender ele quando vocÊs olharem o método imprimirResultados();
 
//esse método vai ver se o arquivo tá sucesso, se tiver, ele pega o dados do arquivo
//caso contrário, é porque deu shit!
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

//esse método dispensa explicação
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
	//todo arquio tem o tamanho do DNA esse método(atoi) converte a string '13' no inteiro 13
	//se falarem besteira, falem que o foco do trabalho é no manuseio de vetores, uso do malloc, manipulaçaõ de strings e arquivos. Focar nessa função é irrelevante.
	tamanhoDaSequencia = atoi(digitos);
}

void criarCadeiaCorrespondente(char *dna){
	
	//laço responsável por trocar os nucleotídeos do DNA
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

//esse método tem dois parâmetros, a url do arquivo de saída e o dna a ser escrito nele
//o método vai ver se o arquivo tá sucesso, se tiver ele escreve o dna no arquivo e salva ele
//caso contrário, é porque deu shit!
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

//esse método dispensa explicação, é um método pra deixar centralizar as impressões e deixar as coisas bonitinhas
void imprimirResultados(int opcao){
	
	if(opcao == 0){
		printf("DNA ORIGINAL       - %s\n", dna);	
	}else if(opcao == 1){
		printf("DNA CORRESPONDENTE - %s\n", dna);
	}else if(opcao == 2){
		printf(" TROCADA PELA BASE - %c\n", base);
		printf("DNA COM MUTACAO    - %s\n", dna);
		
		//esse printf pode ser apagado
		//eu coloquei ele aqui só pra vocês lembrarem que devem mostrar o arquivo, que contém o dna original, e comparar ele com o dna mostrado no terminal
		//para vocês terem a certeza que houve a troca da base
		printf("PARA MELHOR VISUALIZACAO DA TROCA DE BASE, OLHAR ARQUIVO: %s\n", urlSaida);
	}else{
		printf("\n");
		printf("CROMOSSOMO         - %s\n", dna);
	}
}

void criarNumeroRandomico(){
	
	//a """"""""dica"""""""" da questão 2 diz para usar um número random para gerar a mutação #olharRequisitoDoTrabalho
	//srand(time(NULL)) é um jeitinho huehueBRBR para os números aleatórios nunca se repetirem
	//rand() % tamanhoDaSequencia é um jeito que vai me garantir que o número aleatório não passe de um determinado valor
	//Ex.: se o tamanho do dna é 13, então o tamanho da sequência do dna é 13, logo, por causa do % tamanho.. o número random vai ficar entre 0 e 13
	//se o tamanho do dna é 20, o random vai ficar entre 0 e 20..
	//isso é uma garantia de que sempre vocês vão conseguir acessar uma posição válida no vetor
	srand(time(NULL));
	numeroAuxiliar = rand() % tamanhoDaSequencia;
	printf("\n");
	
	//nesse printf eu coloquei numeroAuxiliar + 1 para vcs não cometerem o mesmo engano que eu tive, pensar que a base trocada tava na posicao 6, enquanto a posicao era 5
	//lembrem-se que o vetor começa no zero
	//resumindo, numeroAuxiliar + 1 é para só pra facilitar a visualização 
	printf("POSICAO: %d", numeroAuxiliar + 1);
}

void gerarMutacao(char *dna, char baseDesejada){
	
	for(numeroAuxiliar; numeroAuxiliar < 5; numeroAuxiliar++){
		printf("GERANDO MUTACAO...\n");
	}
	
	//esses dois métodos vocês já sabem o que eles fazem
	zerarNumeroAuxiliar();	
	criarNumeroRandomico();
	
	
	//esse for vai tentar encontrar no DNA a posição aleatória e vai trocar a base
	int auxiliar = 0;
	for(auxiliar; auxiliar < tamanhoDaSequencia; auxiliar++){
		if(auxiliar == numeroAuxiliar){
			dna[auxiliar] = baseDesejada;
		}
	}
	
	//olhem depois o método imprimirResultados e vejam o que o número 2 imprime.. :)
	imprimirResultados(2);
}

void zerarNumeroAuxiliar(){
	numeroAuxiliar = 0;
}

void gerarCruzamento(){
	
	//método que vai deixar pronto os vetores cromossomo/descendencias
	gerarCromossomosDescendecias();
	
	//esse método só consegue ser sucesso, ou seja, o cromossomo1/2 só conseguem ser utilizados
	//porque no método gerarCromossomos...() eles foram "criados".
	obterCromossomo(urlCromossomo1, cromossomo1);
	obterCromossomo(urlCromossomo2, cromossomo2);
	
	criarNumeroRandomico();	
	int auxiliar = 0;
	
	//é interessante vocês olharem o arquivo sobre cruzamento que tá no sigaa
	//com a leitura do arquivo, vocês vão se ligar porque no else eu faço a troca
	
	//neste método -> numeroAuxiliar == ponto do cruzamento
	//if == copiando os primeiros numeros antes do ponto de cruzamento
	//else == copiando os números após o ponto de cruzamento
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

//esse método pede dois parâmetros
//1 - a url do arquivo que tem o cromossomo
//2 - o vetor em que o cromossomo vai ser salvo
void obterCromossomo(char *url, char *cromossomo){
	zerarNumeroAuxiliar();
	lerArquivo(url,digitos,3);
	copiarVetor(cromossomo,dna);
}

//método do sucesso que cria os vetores e que vão deixar vocês fazerem todas as manipulações necessárias
void gerarCromossomosDescendecias(){
	cromossomo1 = (char *) malloc(tamanhoDaSequencia * sizeof(char));
	cromossomo2 = (char *) malloc(tamanhoDaSequencia * sizeof(char));
	descendencia1 = (char *) malloc(tamanhoDaSequencia * sizeof(char));
	descendencia2 = (char *) malloc(tamanhoDaSequencia * sizeof(char));
}
