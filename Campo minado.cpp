#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <time.h>

using namespace std;

//Cabeçalho de funções 
void menuInicial();

void limpaTela(){
	system("CLS");
}

void iniciaTabuleiro(char tabuleiro[10][10],char mascara[10][10]){
	
	//Popula o tabuleiro com Água
	int linha, coluna;
	
	for(linha = 0; linha < 10; linha++){
		
		for( coluna = 0; coluna < 10; coluna++){
			
			tabuleiro[linha][coluna] = 'A';
			mascara[linha][coluna] = '*';
			
		}
		
	}
	
}

void exibeMapa(){
	
	//mapa indicaddor de colunas
	
	int cont;
	for(cont = 0; cont < 10; cont++){
		if(cont == 0){
			
			cout << "     ";
			
		}
		
		cout << cont << " ";
			
	}
	cout << "\n";
	for(cont = 0; cont < 10; cont++){
		if(cont == 0){
			
			cout << "     ";
			
		}
		cout << "| ";
	}
	cout << "\n";
	
}

void exibeTabuleiro(char tabuleiro[10][10],char mascara[10][10], bool mostraGabarito){
	
	char blue[] = { 0x1b,'[','1',';','3','4','m',0};
	char green[] = { 0x1b,'[','1',';','3','2','m',0};
	char normal[] = { 0x1b,'[','1',';','3','9','m',0};
	
	
	//Exibe o tabuleiro
	int linha, coluna;
	
	for(linha = 0; linha < 10; linha++){
		
		cout << linha << " - ";
		
		for( coluna = 0; coluna < 10; coluna++){
			
			
			switch(mascara[linha][coluna]){
				
				case 'A':
					cout << blue << " " << mascara[linha][coluna] << normal;
					break;
				
				case 'P':
					cout << green << " " << mascara[linha][coluna] << normal;
					break;
					
				default:
					cout << " " << mascara[linha][coluna];
					break;
			}
			
		}
			
		cout << "\n";
	}
	
	if(mostraGabarito == true){
		
		for(linha = 0; linha < 10; linha++){
		
			for( coluna = 0; coluna < 10; coluna++){
			
				cout << " " << tabuleiro[linha][coluna];
		
			}
			
			cout << "\n";
		}
		
	}

}

void posicionaBarcos(char tabuleiro[10][10]){
	
	//colaca 10 barcos no tabuleiro 
	int cont, quantidade = 10, quantidadePosicionada = 0;
	
	//Verifica se ja posicionou todos os barcos 
	while(quantidadePosicionada < quantidade){
		
		int linhaAleatoria = rand() % 10;			//Gera numeros aleatorios de 0 9
		int colunaAleatoria = rand() % 10;			//Gera numeros aleatorios de 0 9
		
		if(tabuleiro[linhaAleatoria][colunaAleatoria] = 'A'){
			
			//posiciona 10 barcos aleatoriamente 
			tabuleiro[linhaAleatoria][colunaAleatoria] = 'P';
			
			//Aumenta o contadoor de barcos posicionados
			quantidadePosicionada++;
		}
		
	}
		
}

void vericaTiro(char tabuleiro[10][10], int linhaJogada, int colunaJogada, int *pontos, string *mensagem){
	
	//verifica quantos pontos adicionar
	switch(tabuleiro[linhaJogada][colunaJogada]){
		
			
		case 'P':
			*pontos = *pontos + 10;
			*mensagem = "Voce acertou um barco pequeno! (10 pts)";
			break;
		
		case 'A':
			*mensagem = "Voce acertou a Água";
			break;
			
	}
	
}

void jogo(string nomeDoJogador){
	
	//Variaveis Gerais
	char tabuleiro[10][10],mascara[10][10];			//Tabuleiro do jogo
	int linha, coluna;								//Auxiliar de navegação
	int linhaJogada, colunaJogada;					//Posição escolhida pelo jogador
	int estadoDeJogo = 1;							// 1 = jogo acontecendo = 0 fim de jogo
	int pontos = 0;									//Pontuação do Jogador
	int tentativas = 0, maximoDeTentativas = 5;		//tentativas do jogador
	int opcao;										//opção de fim de jogo
	string mensagem;								//Mensagem de feedback	para jogador		
	
	//inicia o tabuleiro com água
	iniciaTabuleiro(tabuleiro,mascara);
	
	//posiciona barcos aleatoriamente 
	posicionaBarcos(tabuleiro);
	
	while (tentativas < maximoDeTentativas){
		
		limpaTela();
		
		exibeMapa();
		
		//Exibe o tabuleiro
		exibeTabuleiro(tabuleiro,mascara, false);
		
		cout << "\nPontos :" << pontos << ", Tenttivas Restantes:" << maximoDeTentativas - tentativas;
		cout << "\n" << mensagem;
		
		//Verificação de dados
		linhaJogada = -1;
		colunaJogada = -1;
		
		while((linhaJogada < 0 || colunaJogada < 0) || (linhaJogada > 9 || colunaJogada > 9)){
			
			cout << "\n" << nomeDoJogador << "\nDigite uma linha:";
			cin >> linhaJogada;
			cout << "\n" << nomeDoJogador << "\nDigite uma coluna:";
			cin >> colunaJogada;
			
		}
	
		//Verifia o que aconteceu 
		vericaTiro(tabuleiro,linhaJogada,colunaJogada, &pontos, &mensagem);
	
		//Revela o que esta no tabuleiro 
		mascara[linhaJogada][colunaJogada] =	tabuleiro[linhaJogada][colunaJogada];
		
		tentativas ++;
	}
		
	cout << "Fim de jogo, o que deseja fazer?";
	cout << "\n1 - Jogar Novamente";
	cout << "\n2 - Ir para  Menu";
	cout << "\n3 - Sair";
	cin >> opcao;
	
	switch(opcao){
		
		case 1:
			
			jogo(nomeDoJogador);
			
			break;
			
		case 2:
			menuInicial();
			break;
	}
}
	
	

void menuInicial(){
	
	//opção escolhida pelo usuário
	int opcao = 0;
	
	//Nome do usuário
	string nomeDoJogador;
	//Enquanto o jogador não escolhe uma opção valida mostra o menu
	while(opcao < 1 || opcao > 3){
		
		limpaTela();
		
		cout << "BEm vindo ao Jogo de Batalha Naval";
		cout << "\n1 - Jogar";
		cout << "\n2 - Sobre";
		cout << "\n3 - Sair";
		cout << "\nEscolha uma opcao e tecla ENTER:";
		cin >> opcao;
		
		switch(opcao){
			
			case 1:
				
				//Inicia o jogo
				//cout << "Jogo iniciado";
				cout << "Qual seu nome?";
				cin >> nomeDoJogador;
				jogo(nomeDoJogador);
				break;
			
			case 2:
				
				//informação do jogo
				cout << "informacoes do jogo";
				
				break;
			
			case 3:
				
				//Sair do jogo
				cout << "Ate mais!";
				
				break;
		}
		
	}
	
}




int main(){
	//Para gerar numeros realmente aleatorios 
	srand( (unsigned)time(NULL));
	
	menuInicial();
	
	
	return 0;
} 
