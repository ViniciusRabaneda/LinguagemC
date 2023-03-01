#include <stdio.h>
#include <locale.h> //Biblioteca de Caracteres especiais
#include <time.h> //Biblioteca para trabalhar com tempo
int main(){
	
	setlocale(LC_ALL, "Portuguese"); // utilizado para indicar o idioma dos textos
	printf("*****************************************\n");
	printf("*  Bem vindo ao nosso jogo de advinhação *\n");
	printf("*****************************************\n");
	
	//EPOCH = 1 de janeiro de 1970
	//time(0) traz o numero de segundos desde 1970 até o momento
	int segundos=time(0);
	int numerogrande=srand(segundos);// srand() devolve um valor aleatorio
	int numerosecreto= numerogrande % 100; // pega o resto da divisão de um numero por 100, por se tratar de resto, ele sera algo entre 0 e 99
	int chute;
	int tentativas =1;
	double pontos=1000;
	
	int i;
	int numerodetentativas;
	int nivel;
	printf("Qual o nível de dificuldade?\n");
	printf("(1)Fácil (2)Médio (3)Difícil\n\n");
	printf("Escolha: ");
	scanf("%d",&nivel);
	
	switch(nivel){ // diferente do if else ele executa linha a linha por isso é necessário o break
		case 1:
			numerodetentativas=20;
			break; // precisa ter break
		case 2: 
			numerodetentativas=15;
			break; // precisa ter esse break
		default: // equivale ao else 
			numerodetentativas=6;
			break; // precisa ter esse break
	}
	for(i=1;i<=numerodetentativas;i++){
		printf("Tentativa %d\n\n",tentativas);
		printf("Qual é o seu chute? \n");
		scanf("%d", &chute);
		printf("Seu chute foi %d \n",chute);
		if(chute<0){
			printf("Você não pode chutar números negativos\n");
			continue; //Ele reinicia o laço *** Diferente do break ele não quebra o laço!!
		}
		if(chute == numerosecreto){
			break;
		}
		else if (chute>numerosecreto) {   // Eles if é utilizado para deixar o codigo mais otimizado. Se a condição do else if for atendida, ele nem executa o que esta abaixo para fazer a validação
			printf("O número secreto é maior do que o valor digitado\n\n");
		}
		else{
			printf("O número secreto é menor do que o valor digitado\n\n");
		}
		tentativas++; // abs pega o numero absoluto, ou seja, sem o sinal
		double pontosperdidos=abs(chute-numerosecreto)/2.0;//2.0 faz com que a conta saia como numero real, pois o compilador vai realizar a conta da forma mais precisa ou utilizar casting (double)2 que converte momentaneamnte um valor int para double
		pontos=pontos-pontosperdidos;
	}
	printf("FIM DE JOGO\n\n");	
	if(chute == numerosecreto){
		printf("Você ganhou!\n");
		printf("Você acertou em %d tentativas \n", tentativas);	
		printf("Total de pontos:%.1f",pontos);//.1f indica o numero de casas decimais que sera considerado
	}
	else{
		printf("Você perdeu! Tente de novo\n");
	}
}
	


