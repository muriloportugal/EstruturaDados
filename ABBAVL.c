#include <stdio.h>
#include <stdlib.h>

#define TRUE 1;
#define FALSE 0;

struct arv {
    int info;
	int altura;
    struct arv* esq;
    struct arv* dir;
};

typedef struct arv Arv;

void limpaTela(){
	//Deixe somente a linha do seu S.O. e comente a outra.
	//system("clear");//Unix
	system("cls");//Windows
}

void Pause(){
	char ch;
	scanf("%c",&ch);
	printf("Pressione uma tecla para continuar...");
	getchar();
}

Arv* inicializa(void){
	return NULL;
}

Arv* procurar(Arv* a,int v){
	if (a == NULL){//caso a árvore esteja vazia ou (elemento não exite)
		printf("Valor nao encontrado\n\n");
		Pause();
		return NULL;
	}
	else if (a->info > v)
		a->esq = procurar(a->esq, v);
	else if (a->info < v)
		a->dir = procurar(a->dir, v);
	else { /* achou o elemento */
		printf("Valor %d encontrado\n\n",v);
		Pause();
	}
	return a;
}

void imprimePre (Arv* a){

    if (a!=NULL){
		printf(" %d ",a->info);
		//printf("(%d)",a->altura);
	    imprimePre(a->esq);
	    imprimePre(a->dir);

    }
}

void imprimeIn (Arv* a){

    if (a!=NULL){

	    imprimeIn(a->esq);
		printf(" %d ",a->info);
	    imprimeIn(a->dir);

    }
}

void imprimePos (Arv* a){
    
	if (a!=NULL){

	    imprimePos(a->esq);
	    imprimePos(a->dir);
	    printf(" %d ",a->info);

    }
}

Arv* girarDireitaSimples(Arv* a){
	
	Arv* b = a->esq;
	a->esq = NULL;
	b->dir = a;
	a = b;
	return a;
}

Arv* girarEsquerdaSimples(Arv* a){
	
	Arv* b = a->dir;
	a->dir = NULL;
	b->esq = a;
	a = b;
	return a;
}

Arv* giroDuploDierita(Arv* a){
	
	Arv* b = a->esq;
	a->esq = girarEsquerdaSimples(b);
	a = girarDireitaSimples(a);
	return a;
}

Arv* giroDuploEsquerda(Arv* a){
	
	Arv* b = a->dir;
	a->dir = girarDireitaSimples(b);
	a = girarEsquerdaSimples(a);
	return a;
}

Arv* balanceamento(Arv* a){
 // Nós vazios(NULL) recebem -1,
 //para os demais pega a altura da sub-arvore esquerda e da sub-arvore direita.
	int alturaEsquerda = -1;
	int alturaDireita = -1;


	if (a->esq)
		alturaEsquerda = a->esq->altura;
	if (a->dir)
		alturaDireita = a->dir->altura;

	//Arvores balanceadas tem seu fator de balanceamento entre 1 e -1 (1,0,-1);
	if ((alturaEsquerda - alturaDireita) >1){
		
		if (a->esq->dir){
		 //Se tiver item na sub-árvore direita da sub-árvore esqueda do nó
		 //é necessário fazer um giro duplo.
			a = giroDuploDierita(a);
		}else{
			a = girarDireitaSimples(a);
		}
		
	}else if ((alturaEsquerda - alturaDireita) <-1){

		if(a->dir->esq){
		 //Se tiver item na sub-árvore esquerda da sub-árvore direita do nó,
	     //é necessário fazer um giro duplo
			a = giroDuploEsquerda(a);
		}else{
			a = girarEsquerdaSimples(a);
		}
		
	}
	return a;
}

Arv* retira (Arv* r, int v){
	if (r == NULL){//caso a árvore esteja vazia ou (elemento não exite)
		printf("valor nao encontrado\n\n");
		Pause();
		return NULL;
	}
	else if (r->info > v)
		r->esq = retira(r->esq, v);
	else if (r->info < v)
		r->dir = retira(r->dir, v);
	else { /* achou o elemento */
		if (r->esq == NULL && r->dir == NULL) { /* elemento sem filhos */
			free (r);
			r = NULL;
		}
		else if (r->esq == NULL) { /* so tem filho a direita */
			Arv* t = r;
			r = r->dir;
			free (t);
		}
		else if (r->dir == NULL) { /* so tem filho a esquerda */
			Arv* t = r;
			r = r->esq;
			free (t);
		}
		else { /* tem os dois filhos */
			Arv* pai = r;
			Arv* f = r->esq;
			while (f->dir != NULL) {
				pai = f;
				f = f->dir;
			}
			r->info = f->info; /* troca as informações */
			f->info = v;
			r->esq = retira(r->esq,v);
		}
	}
	return r;
}

Arv* insere (Arv* a, int v){
	int novaAltura = 0;
	if (a==NULL) {
		a = (Arv*)malloc(sizeof(Arv));
		a->info = v;
		a->altura = 0;
		a->esq = a->dir = NULL;
	}
	else if (v < a->info){
		a->esq = insere(a->esq,v);
		novaAltura = a->esq->altura +1;
	}else if(v > a->info) {
		a->dir = insere(a->dir,v);
		novaAltura = a->dir->altura +1;
	}
	if (novaAltura>a->altura)
		a->altura = novaAltura;
	a = balanceamento(a);
	return a;
}

Arv* verificaAltura(Arv* a){
	//Verifica primeiro todos os nós da esqueda
	//depois da direita.
	if (a->esq)
		verificaAltura(a->esq);
	if (a->dir)
		verificaAltura(a->dir);
	//Se não tem sub-arvore então é folha e tem altura 0;
	//Se tiver sub-árvore compara qual a maior altura e adiciona 1;
	if (a->esq==NULL && a->dir==NULL){
		a->altura=0; //Folha
	}else if(a->esq && a->dir){
		//Tem as duas sub-árvores 
		if(a->esq->altura > a->dir->altura)
			a->altura = a->esq->altura + 1;
		else{
			a->altura = a->dir->altura + 1;	
		}
	}else if(a->esq){
		//Tem somente sub-árvore da esquerda
		a->altura = a->esq->altura + 1;
	}else{
		//Tem somente sub-árvore da direita
		a->altura = a->dir->altura + 1;
	}
	return a;
}

int main(){

	Arv* a = inicializa();

	int continua = 0;
	int escolha = 0;
	int numero = 0;


	while (continua==0){
		limpaTela();
		printf("Escolha uma opcao:");
		printf("\n1 - Inserir um numero da arvore;");
		printf("\n2 - Imprimir arvore;");
		printf("\n3 - Remover um numero da arvore;");
		printf("\n4 - Procurar um valor;");
		printf("\n5 - Sair;\n");
		scanf("%d",&escolha);
		switch (escolha)
		{
		case 1:
			limpaTela();
			printf("Entre com o numero: ");
			scanf("%d",&numero);
			a = insere(a,numero);
			a = verificaAltura(a);
			break;
		case 2:
			limpaTela();
			printf("Impressao pre-ordem: ");
			imprimePre(a);
			printf("\nImpressao in-ordem: ");
			imprimeIn(a);
			printf("\nImpressao pos-ordem: ");
			imprimePos(a);
			printf("\n\n");
			Pause();
			break;
		case 3:
			limpaTela();
			printf("Escolha um numero para ser removido: ");
			scanf("%d",&numero);
			a = retira(a,numero);
			verificaAltura(a);
			break;
		case 4:
			limpaTela();
			printf("Qual valor deseja procurar? ");
			scanf("%d",&numero);
			a = procurar(a,numero);
			break;
		default:
			continua =1;
			break;
		}
	}

}
