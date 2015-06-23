#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//variáveis globais
//Ao trocar os caminhos lembrar de colocar duas barras (\\) 

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
		
	lerArquivo(url,digitos,0);	
	criarCadeiaCorrespondente(dna);
	salvarArquivo(urlSaida,dna);
	gerarMutacao(dna,base);
	gerarCruzamento();
    
	return 0;
}

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

void imprimirResultados(int opcao){
	
	if(opcao == 0){
		printf("DNA ORIGINAL       - %s\n", dna);	
	}else if(opcao == 1){
		printf("DNA CORRESPONDENTE - %s\n", dna);
	}else if(opcao == 2){
		printf("DNA COM MUTACAO    - %s\n", dna);
	}else{
		printf("\n");
		printf("CROMOSSOMO         - %s\n", dna);
	}
}

void criarNumeroRandomico(){
	
	srand(time(NULL));
	numeroAuxiliar = rand() % tamanhoDaSequencia;
	printf("\n");
	printf("POSICAO: %d\n", numeroAuxiliar + 1);
}

void gerarMutacao(char *dna, char baseDesejada){
	
	for(numeroAuxiliar; numeroAuxiliar < 5; numeroAuxiliar++){
		printf("GERANDO MUTACAO...\n");
	}
	
	zerarNumeroAuxiliar();
	
	criarNumeroRandomico();
	int auxiliar = 0;
	for(auxiliar; auxiliar < tamanhoDaSequencia; auxiliar++){
		if(auxiliar == numeroAuxiliar){
			dna[auxiliar] = baseDesejada;
		}
	}
	
	imprimirResultados(2);
}

void zerarNumeroAuxiliar(){
	numeroAuxiliar = 0;
}

void gerarCruzamento(){
	
	gerarCromossomosDescendecias();
	obterCromossomo(urlCromossomo1, cromossomo1);
	obterCromossomo(urlCromossomo2, cromossomo2);
	
	criarNumeroRandomico();	
	int auxiliar = 0;
	
	//copiando os primeiros numeros antes do ponto de cruzamento
	//numeroAuxiliar == ponto do cruzamento
	for(auxiliar; auxiliar < tamanhoDaSequencia; auxiliar++){
		if(auxiliar < numeroAuxiliar){
			descendencia1[auxiliar] = cromossomo1[auxiliar];
			descendencia2[auxiliar] = cromossomo2[auxiliar];
		}else{
			descendencia1[auxiliar] = cromossomo2[auxiliar];
			descendencia2[auxiliar] = cromossomo1[auxiliar];
		}
	}	
	printf("DESCENDENCIA 01 - %s \n", descendencia1);
	printf("DESCENDENCIA 02 - %s \n", descendencia2);
	
	salvarArquivo(urlCromossomoSaida, descendencia1);
	salvarArquivo(urlCromossomoSaida2, descendencia2);
}

void obterCromossomo(char *url, char *cromossomo){
	zerarNumeroAuxiliar();
	lerArquivo(url,digitos,3);
	copiarVetor(cromossomo,dna);
}

void gerarCromossomosDescendecias(){
	cromossomo1 = (char *) malloc(tamanhoDaSequencia * sizeof(char));
	cromossomo2 = (char *) malloc(tamanhoDaSequencia * sizeof(char));
	descendencia1 = (char *) malloc(tamanhoDaSequencia * sizeof(char));
	descendencia2 = (char *) malloc(tamanhoDaSequencia * sizeof(char));
}
