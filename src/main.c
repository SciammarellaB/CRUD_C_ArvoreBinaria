#define _CRT_SECURE_NO_WARNINGS 1 // UTILIZADO PARA O Visual Studio nao reclamar de 'scanf_s'
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int BRINQUEDO_CODIGO_ATUAL = 1;

//DADOS
typedef struct brinquedo {
	int Codigo;
	char Nome[125];
	char Descricao[500];
	int Quantidade;
	float Preco;
} Brinquedo;

typedef struct arvore {
	struct arvore* esquerda;
	struct arvore* direita;
	//DADO UTIL
	Brinquedo* brinquedo;
} Arvore;

//CABECALHO METODOS
int menu_principal();
void gerenciar_menu_principal(Arvore* arvore);
Arvore* inicializa_arvore();
Brinquedo* criar_Brinquedo();
int inserir_arvore_regra(char nomeA[125], char nomeB[125]);
Arvore* cria_noArvore(Brinquedo* brinquedo, Arvore* esquerda, Arvore* direita);
Arvore* inserir_arvore(Arvore* arvore, Brinquedo* brinquedo);
int arvore_vazia(Arvore* arvore);
Brinquedo* buscar_brinquedo(Arvore* arvore, char nome[125]);
Brinquedo* editar_brinquedo(Brinquedo* brinquedo);
Arvore* remover_brinquedo(Arvore* arvore, char nome[125]);
void imprimir_brinquedo(Brinquedo* brinquedo);
void imprimir_arvore_ordem_alfabetica(Arvore* arvore);
void imprimirAcimaDeX(Arvore* arvore, float valor);
void imprimirAbaixoDeX(Arvore* arvore, float valor);
void limpar();

//CARGA INICIAL
Brinquedo* gerar_Brinquedo(char nome[125], char descricao[500], int quantidade, float preco) {
	Brinquedo* b = (Brinquedo*)malloc(sizeof(Brinquedo));
	b->Codigo = BRINQUEDO_CODIGO_ATUAL;
	strcpy(b->Nome, nome);
	strcpy(b->Descricao, descricao);
	b->Quantidade = quantidade;
	b->Preco = preco;
	BRINQUEDO_CODIGO_ATUAL++;
	return b;
}

Arvore* cargaInicial(Arvore* arvore) {
	arvore = inserir_arvore(arvore, gerar_Brinquedo("Jogo de Tabuleiro 'Detetive'", "Um jogo de estrategia e misterio para divertir toda a familia.", 10, 64.99));	
	arvore = inserir_arvore(arvore, gerar_Brinquedo("Boneca de Pano", "Uma boneca de pano feita a mao, perfeita para abracar e brincar.", 15, 29.99));
	arvore = inserir_arvore(arvore, gerar_Brinquedo("Carrinho de Controle Remoto", "Um carrinho de controle remoto rapido e agil para corridas emocionantes.", 12, 50));
	arvore = inserir_arvore(arvore, gerar_Brinquedo("Quebra-Cabeca de 100 Pecas", "Um quebra-cabeca colorido com 100 pecas para desafiar a mente das criancas.", 20, 24.99));
	arvore = inserir_arvore(arvore, gerar_Brinquedo("Bola de Futebol", "Uma bola de futebol de alta qualidade, ideal para jogos no parque.", 18, 40));
	arvore = inserir_arvore(arvore, gerar_Brinquedo("Jogo de Construcao de Blocos", "Conjunto de blocos de construcao para estimular a criatividade e habilidades motoras.", 25, 34.99));
	arvore = inserir_arvore(arvore, gerar_Brinquedo("Patins Infantis", "Patins ajustaveis para criancas aprenderem a patinar com segurança.", 8, 70));
	arvore = inserir_arvore(arvore, gerar_Brinquedo("Piano de Brinquedo com Microfone", "Um piano eletronico com microfone para pequenos musicos em ascensao.", 14, 45));
	arvore = inserir_arvore(arvore, gerar_Brinquedo("Quebra-Cabeca 3D de Castelo", "Um desafio em tres dimensoes para construir um castelo impressionante.", 6, 55));
	arvore = inserir_arvore(arvore, gerar_Brinquedo("Pelucia do Personagem Favorito", "Uma pelucia fofa do personagem favorito da crianca para abracar e brincar.", 22, 20));
	return arvore;
}

//METODOS
int main(int argc, char** argv) {
	Arvore* arvore = inicializa_arvore();
	arvore = cargaInicial(arvore);

	gerenciar_menu_principal(arvore);
	return 0;
}

int menu_principal() {
	int opcao = 0;
	printf("\n#########################");
	printf("\n   LOJA DE BRINQUEDOS    ");
	printf("\n#########################\n");
	printf("\n(1) Listar Brinquedos (ORDEM ALFABETICA)");
	printf("\n(2) Consultar Brinquedo");
	printf("\n(3) Cadastrar Brinquedo");
	printf("\n(4) Listar Brinquedos com valor acima de:");
	printf("\n(5) Listar Brinquedos com valor abaixo de:");
	printf("\n(6) Editar Brinquedo");
	printf("\n(7) Remover Brinquedo");
	printf("\n(8) Sair\n");
	printf("\nSelecionar opcao: ");
	scanf("%d", &opcao);
	return opcao;
}

void gerenciar_menu_principal(Arvore* arvore) {
	int opcao;
	int sair = 0;
	do {
		limpar();
		opcao = menu_principal();
		switch (opcao)
		{
			case 1:
				limpar();
				printf("Listar Brinquedos (ORDEM ALFABETICA)\n");
				if (!arvore_vazia(arvore)) {
					imprimir_arvore_ordem_alfabetica(arvore);
					printf("\n");
					system("pause");
				}
				else {
					printf("\nNENHUM DADO A SER MOSTRADO\n\n");
					system("pause");
				}
				break;			
			case 2:
				limpar();
				printf("Consultar Brinquedo\n\n");
				char busca[125];
				printf("Digite o nome do brinquedo desejado: ");
				scanf(" %[^\n]", busca);
				getchar();
				Brinquedo* brinquedo = buscar_brinquedo(arvore, busca);
				if (brinquedo) {
					imprimir_brinquedo(brinquedo);
					printf("\n");
					system("pause");
				}
				else {
					printf("\nBRINQUEDO NAO ENCONTRADO\n\n");
					system("pause");
				}
				break;
			case 3:
				limpar();
				printf("Cadastrar Brinquedo\n\n");
				arvore = inserir_arvore(arvore, criar_Brinquedo());
				printf("\nBrinquedo Cadastrado com sucesso!\n\n");
				system("pause");
				break;
			case 4:
				limpar();
				printf("Listar Brinquedos com valor acima de:\n\n");
				float valorAcima = 0;
				printf("Digite o valor: ");
				scanf("%f", &valorAcima);
				imprimirAcimaDeX(arvore, valorAcima);
				printf("\nBusca finalizada\n\n");
				system("pause");
				break;
			case 5:
				limpar();
				printf("Listar Brinquedos com valor abaixo de:\n\n");
				float valorAbaixo = 0;
				printf("Digite o valor: ");
				scanf("%f", &valorAbaixo);
				imprimirAbaixoDeX(arvore, valorAbaixo);
				printf("\nBusca finalizada\n\n");
				system("pause");
				break;
			case 6:
				limpar();
				printf("Editar Brinquedo\n\n");
				char editar[125];
				printf("Digite o nome do brinquedo desejado: ");
				scanf(" %[^\n]", editar);
				getchar();
				Brinquedo* brinquedoEditar = buscar_brinquedo(arvore, editar);
				if (brinquedoEditar) {
					imprimir_brinquedo(brinquedoEditar);
					printf("\n");
					Brinquedo* temp = brinquedoEditar;
					int codigo = temp->Codigo;
					printf("Editar dados:\n\n");
					arvore = remover_brinquedo(arvore, brinquedoEditar->Nome);
					arvore = inserir_arvore(arvore, editar_brinquedo(codigo));
					free(temp);
					printf("\nBrinquedo Editado com sucesso!\n\n");
					system("pause");
				}
				else {
					printf("\nBRINQUEDO NAO ENCONTRADO\n\n");
					system("pause");
				}
				break;
			case 7:
				limpar();
				printf("Remover Brinquedo\n\n");
				char remocao[125];
				printf("Digite o nome do brinquedo a ser removido: ");
				scanf(" %[^\n]", remocao);
				getchar();
				arvore = remover_brinquedo(arvore, remocao);
				printf("\nBrinquedo Removido com sucesso!\n\n");
				system("pause");
				break;
			case 8:
				sair = 1;
				break;
			default:
				printf("Opcao Invalida!!!\n");
				system("pause");
				sair = 0;
		}
	} while (!sair);
}

//INICIALIZA ARVORE COMO NULO
Arvore* inicializa_arvore() {
	return NULL;
}

//CRIA O ESPACO DE MEMORIA E INPUT DE DADOS DO BRINQUEDO
Brinquedo* criar_Brinquedo() {
	Brinquedo* brinquedo = (Brinquedo*)malloc(sizeof(Brinquedo));

	printf("Digite o nome do brinquedo: ");
	scanf(" %[^\n]", brinquedo->Nome);
	getchar();

	printf("Digite uma descricao: ");
	scanf(" %[^\n]", brinquedo->Descricao);
	getchar();

	printf("Digite a quantidade em estoque: ");
	scanf("%d", &brinquedo->Quantidade);
	getchar();

	printf("Digite o preco: ");
	scanf("%f", &brinquedo->Preco);
	getchar();

	brinquedo->Codigo = BRINQUEDO_CODIGO_ATUAL;

	BRINQUEDO_CODIGO_ATUAL++;

	return brinquedo;
}

//METODO PARA VERIFICAR SE IRA ADICIONAR A ESQUERDA OU DIREITA DA ARVORE BASEADO NO NOME DO BRINQUEDO
int inserir_arvore_regra(char nomeA[125], char nomeB[125]) {
	return strcmp(nomeA, nomeB);
}

//CRIA O NO DA ARVORE COM OS DADOS RECEBIDOS POR PARAMETRO E RETORNA O PONTEIRO
Arvore* cria_noArvore(Brinquedo* brinquedo, Arvore* esquerda, Arvore* direita) {
	Arvore* item = (Arvore*)malloc(sizeof(Arvore));
	item->brinquedo = brinquedo;
	item->direita = direita;
	item->esquerda = esquerda;
	return item;
}

Arvore* inserir_arvore(Arvore* arvore, Brinquedo* brinquedo) {

	//CASO SEJA A POSICAO A SER INSERIDO
	if (!arvore)
		return cria_noArvore(brinquedo, NULL, NULL);

	//VERIFICA A ORDEM EM QUE O BRINQUEDO DEVE SER GRAVADO
	if (inserir_arvore_regra(brinquedo->Nome, arvore->brinquedo->Nome) > 0)
		arvore->direita = inserir_arvore(arvore->direita, brinquedo);
	else if (inserir_arvore_regra(brinquedo->Nome, arvore->brinquedo->Nome) < 0)
		arvore->esquerda = inserir_arvore(arvore->esquerda, brinquedo);
	//TRATATIVA PARA CASO JA EXISTA O BRINQUEDO INSERIDO - FAZ A LIMPEZA DA MEMORIA ALOCADA DO CADASTRO DO BRINQUEDO
	else {
		printf("\nBRINQUEDO JA SE ENCONTRA INSERIDO\n");
		system("pause");
		free(brinquedo);
	}

	return arvore;
}

//VERIFICA SE A ARVORE ESTA VAZIA
int arvore_vazia(Arvore* arvore) {
	return arvore == NULL;
}

Brinquedo* buscar_brinquedo(Arvore* arvore, char nome[125]) {
	//CASO NAO TENHA MAIS NO DA ARVORE RETORNAR NULO
	if (!arvore)
		return NULL;

	//QUANDO O NOME ATUAL DO NO DA ARVORE FOR O QUE PROCURA
	if (inserir_arvore_regra(nome, arvore->brinquedo->Nome) == 0) {
		return arvore->brinquedo;
	}
	//QUANDO O NOME ATUAL DO NO DA ARVORE FOR DEPOIS DO QUE PROCURA
	else if (inserir_arvore_regra(nome, arvore->brinquedo->Nome) > 0) {
		return buscar_brinquedo(arvore->direita, nome);
	}
	//QUANDO O NOME ATUAL DO NO DA ARVORE FOR ANTES DO QUE PROCURA
	return buscar_brinquedo(arvore->esquerda, nome);
}

Brinquedo* editar_brinquedo(int codigo) {
	Brinquedo* brinquedoEditado = (Brinquedo*)malloc(sizeof(Brinquedo));
	brinquedoEditado->Codigo = codigo;
	
	printf("Digite o nome do brinquedo: ");
	scanf(" %[^\n]", brinquedoEditado->Nome);
	getchar();

	printf("Digite uma descricao: ");
	scanf(" %[^\n]", brinquedoEditado->Descricao);
	getchar();

	printf("Digite a quantidade em estoque: ");
	scanf("%d", &brinquedoEditado->Quantidade);
	getchar();

	printf("Digite o preco: ");
	scanf("%f", &brinquedoEditado->Preco);
	getchar();

	return brinquedoEditado;
}

Arvore* remover_brinquedo(Arvore* arvore, char nome[125]) {
	//ARVORE VAZIA
	if (!arvore)
		return arvore;
	//CASO O NOME DE BUSCA SEJA ANTES DO NO DA ARVORE ATUAL
	if (inserir_arvore_regra(nome, arvore->brinquedo->Nome) < 0)
		arvore->esquerda = remover_brinquedo(arvore->esquerda, nome);
	//CASO O NOME DE BUSCA SEJA DEPOIS DO NO DA ARVORE ATUAL
	else if (inserir_arvore_regra(nome, arvore->brinquedo->Nome) > 0)
		arvore->direita = remover_brinquedo(arvore->direita, nome);
	//ENCONTROU O NO
	else {
		//CASO NAO POSSUA NO ESQUERDO OU DIREITO
		if (!arvore->esquerda && !arvore->direita) {			
			free(arvore);
			arvore = NULL;
		}
		//CASO POSUA NO EM UM DOS LADOS
		else if (!arvore->esquerda || !arvore->direita) {
			Arvore* temp = arvore;
			if (arvore->esquerda)
				arvore = arvore->esquerda;
			else
				arvore = arvore->direita;			
			free(temp);
		}
		//CASO POSSUA NO NOS DOIS LADOS
		else {
			Arvore* temp = arvore->esquerda;
			while (temp->direita)
				temp = temp->direita;
			Brinquedo* brinquedo = arvore->brinquedo;
			arvore->brinquedo = temp->brinquedo;
			temp->brinquedo = brinquedo;
			arvore->esquerda = remover_brinquedo(arvore->esquerda, nome);
		}
	}
	return arvore;
}

//METODO PARA RETORNAR E MOSTRAR OS DADOS DO BRINQUEDO NA TELA
void imprimir_brinquedo(Brinquedo* brinquedo) {
	printf("\nBrinquedo\n");
	printf("Codigo: %d\n", brinquedo->Codigo);
	printf("Nome: %s\n", brinquedo->Nome);
	printf("Descricao: %s\n", brinquedo->Descricao);
	printf("Quantidade Estoque: %d\n", brinquedo->Quantidade);
	printf("Preco: %.2f\n", brinquedo->Preco);
}

//FUNCAO PARA IMPRIMIR OS DADOS CADASTRADOS DE FORMA ORDENARA (NOME)
void imprimir_arvore_ordem_alfabetica(Arvore* arvore) {
	if (!arvore_vazia(arvore)) {
		imprimir_arvore_ordem_alfabetica(arvore->esquerda);
		imprimir_brinquedo(arvore->brinquedo);
		imprimir_arvore_ordem_alfabetica(arvore->direita);
	}
}

void imprimirAcimaDeX(Arvore* arvore, float valor) { 
	if (!arvore)
		return;
	imprimirAcimaDeX(arvore->esquerda, valor);
	if (arvore->brinquedo->Preco > valor)
		imprimir_brinquedo(arvore->brinquedo);
	imprimirAcimaDeX(arvore->direita, valor);
}

void imprimirAbaixoDeX(Arvore* arvore, float valor) {
	if (!arvore)
		return;
	imprimirAbaixoDeX(arvore->esquerda, valor);
	if (arvore->brinquedo->Preco < valor)
		imprimir_brinquedo(arvore->brinquedo);
	imprimirAbaixoDeX(arvore->direita, valor);
}

void limpar() {
	system("cls");
}