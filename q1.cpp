#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//variáveis globais
int tamanhoDaSequencia = 0, numeroAuxiliar = 0;
char dna[256], base = 'A';
char url[] = "C:\\Users\\Ygor Reis\\Documents\\trabalhoAuriLinda\\dna.txt", urlSaida[] = "C:\\Users\\Ygor Reis\\Documents\\trabalhoAuriLinda\\dna_saida.txt",digitos[2];

//declaração de métodos
void lerArquivo(char *url, char *digitos);
void obterTamanhoSequencia(char *digitos);
void criarCadeiaCorrespondente(char *dna);
void salvarArquivo(char *url, char *dna);
void gerarMutacao(char *dna, char baseDesejada);
void zerarNumeroAuxiliar();
void criarNumeroRandomico();
void imprimirResultados(int opcao);

int main(){
		
	lerArquivo(url,digitos);	
	criarCadeiaCorrespondente(dna);
	salvarArquivo(urlSaida,dna);
	gerarMutacao(dna,base);
    
	return 0;
}

void lerArquivo(char *url, char *digitos){
	
	FILE *arq = fopen(url, "r");
	if(arq == NULL){
		printf("ERRO NA LEITURA");
	}else{
		while((fscanf(arq,"%s\n", digitos)) != EOF){
			if(numeroAuxiliar == 0){
				obterTamanhoSequencia(digitos);
				numeroAuxiliar++;
			}else{
				strncpy(dna, digitos, tamanhoDaSequencia);
				numeroAuxiliar = 0;
			}
		}
	}
	fclose(arq);
	imprimirResultados(0);
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
		printf("DNA CORRESPONDENTE SALVO COM SUCESSO\n");
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
	}else{
		printf("DNA COM MUTACAO    - %s\n", dna);
	}
}

void criarNumeroRandomico(){
	
	//printf("Numero auxiliar era: %d\n", numeroAuxiliar);
	srand(time(NULL));
	numeroAuxiliar = rand() % tamanhoDaSequencia;
	printf("\n");
	printf("POSICAO DA BASE TROCADA: %d\n", numeroAuxiliar);
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
