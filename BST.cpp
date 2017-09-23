#include <stdlib.h>
#include <stdio.h>
#define MAX 10

struct node{
	int key;  					//chave de identificação do nodo	
	node * left, * right;		//ponteiros para os filhos
};

typedef struct _pilha{
	node *info[MAX];
	int topo;
}_pilha;

//busca por uma chave k na árvore com raiz r
//caso a chave não estiver na árvore retorna NULL

node * search (node * r, int key){
	if(!r || r->key == key ) return r;				//n encontrou a chave

	if(key <= r->key) return search (r->left, key);
	
	return search (r->right, key); 	
}


//mostra todas as chaves da árvore

void print (node * r){
	_pilha *p;
	int loop=1;

	p=(_pilha*)malloc(10*sizeof(node));
	p->topo=-1;
	while(loop!=0){
		if(!r){
			if(p->topo==-1)loop=0;
			else{
				r=p->info[p->topo];
				p->info[p->topo]=NULL;		//várias gambiarras
				p->topo--;
				printf("%i - ",r->key);
				r=r->right;
			}
		}
		else{
			p->topo++;
			p->info[p->topo]=r;
			r=r->left;
		}
	}
	printf("\n\n");
}

//insere um nodo com chave key na árvore com raiz r
//retorna um ponteiro para a raiz da árvore

node * insert (node * r, int key){
	node * n = (node *)malloc(sizeof(node));		//cria um novo nodo
	n->left = n->right = NULL;
	n->key = key;
			
	if(!r) return n;			// se a arvore estiver vazia

	node * it = r;	

	while(1){
		if(key < it->key){
			if(!it->left){
				it->left = n; 		//atualiza o filho da esquerda de r	
				break;		
			}
			it = it->left;	
		}else{
			if(!it->right){
				it->right = n;
				break;			
			}
			it = it->right;
		}		
	}

	return r;
}

//remove o nodo da árvore com raiz r que possui chave igual a key
node * remove (node * r, int k){

	if(!r) return r;

	else if(k < r->key)	r->left = remove(r->left, k); //verifica se é menor que o nó

	else if(k > r->key) r->right = remove(r->right, k); // verifica se é maior que o nó

	else{ //encontrou 
		if(!r->left && !r->right){ // os dois lados com null do nó
			free(r);
			r = NULL;
		}else if(!r->left){ //lado esquerdo é null
			node * aux = r;
			r = r->right;
			free(aux);
		}else if(!r->right){ //lado direito é null
			node * aux = r;
			r = r->left;
			free(aux);
		}else{ //os dois lados possuem outros nós
			node * aux = r->left;

			while(aux->right) aux = aux->right;	//percorre até encontrar o maior nó que irá substituir

			r->key = aux->key; //faz a troca
			aux->key = k;
			r->left = remove(r->left, k); //percorre para deletar o nó que foi trocado
		}
	}


	return r;
}


int main ( void ){
	int n,k,op=1;
	
	node * root = NULL;

	while(op!=0){
		printf("1 - Insert\n");
		printf("2 - Remove\n");
		printf("3 - Search\n");
		printf("4 - Print\n");		//menu
		printf("0 - Exit\n");
		scanf("%d",&op);

		switch(op){
			case 1:
				scanf("%d",&n);
				root = insert(root, n);		//insere valores 
			break;

			case 2:
				scanf("%i",&k);
				root=remove(root,k);		//deleta valor
			break;

			case 3:
				scanf("%d",&n);
				if(search(root, n)) printf("achouUU!\n");		//busca valor
				else printf("nao achooou :(\n");
			break;

			case 4:
				print(root);		//imprime arvore em ordem
			break;

			case 0:
			break;

			default:
				op=10;
			break;
		}
	}
	
	return 0;
}