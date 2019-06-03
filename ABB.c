#include <stdio.h>
#include <stdlib.h>


struct arv {
    int info;
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

Arv* insere (Arv* a, int v){
	if (a==NULL) {
		a = (Arv*)malloc(sizeof(Arv));
		a->info = v;
		a->esq = a->dir = NULL;
	}
	else if (v < a->info)
		a->esq = insere(a->esq,v);
	else if (v > a->info)
		a->dir = insere(a->dir,v);
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
			r->info = f->info; /* troca as informacoes */
			f->info = v;
			r->esq = retira(r->esq,v);
		}
	}
	return r;
}

void imprimePre (Arv* a)
{
    if (a!=NULL){
		printf(" %d ",a->info);
	    imprimePre(a->esq);
	    imprimePre(a->dir);

    }
}
void imprimeIn (Arv* a)
{
    if (a!=NULL){

	    imprimeIn(a->esq);
		printf(" %d ",a->info);
	    imprimeIn(a->dir);

    }
}
void imprimePos (Arv* a)
{
    if (a!=NULL){

	    imprimePos(a->esq);
	    imprimePos(a->dir);
	    printf(" %d ",a->info);

    }
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
