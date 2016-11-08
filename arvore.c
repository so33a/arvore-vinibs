#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"
#include "fila.h"

ARVORE novaArvore() {
  ARVORE a = malloc(sizeof(struct arvore));
  a->z = malloc(sizeof(struct node));
  a->raiz = a->z;
  a->raiz->left = a->raiz->right = a->z;
  a->z->left = a->z->right = a->z;
  return a;
}

void imprimePreOrdemR(ARVORE a, link h) {
  if (h != a->z) {
    printf ("%d ", h->key);
    imprimePreOrdemR(a, h->left);
    imprimePreOrdemR(a, h->right);
  }
}

int contaNosR (ARVORE a, link h) {
  if(h == a->z) return 0;
  return 1 + contaNosR(a, h->left) + contaNosR(a, h->right);
}

int contaParesR (ARVORE a, link h) {
  if(h == a->z)
    return 0;
  if (h->key %2 == 0)
    return 1 + contaParesR(a, h->left) + contaParesR(a, h->right);
  else
    return  contaParesR(a, h->left) + contaParesR(a, h->right);
}

void imprimePreOrdem (ARVORE a) {
  imprimePreOrdemR(a, a->raiz);
}
void imprimePosOrdemR(ARVORE a, link h) {
  if (h != a->z) {
    imprimePosOrdemR(a, h->left);
    imprimePosOrdemR(a, h->right);
    printf ("%d ", h->key);
  }
}

void imprimePosOrdem (ARVORE a) {
  imprimePosOrdemR(a, a->raiz);
}


void imprimeEmOrdemR (ARVORE a, link h) {
   if (h != a->z) {
     imprimeEmOrdemR(a, h->left);
     printf("%d ", h->key);
     imprimeEmOrdemR(a, h->right);
   }
}

void imprimeEmOrdem (ARVORE a) {
   imprimeEmOrdemR(a, a->raiz);
}

link buscaR (ARVORE a, link h, int key) {
  if(h == a->z) return h;
  if(h->key == key) return h;
  if( h->key < key)
    return buscaR(a, h->right, key);
  return buscaR(a, h->left, key);
}
link buscaRP (ARVORE a, link h, int key){
  link atual = h;
  link pai;

  if(atual == a->z){
    // Árvore vazia
    return a->z;

  } else{
    if(atual->key == key){
    	// Valor buscado é a raiz atual
      return atual;

    } else{
    	if(atual->key > key){
	  		// Valor buscado à esquerda da raiz atual
	  		if(atual->left->key == key){
	  			pai = atual;
	  			return pai;

	  		} else{
	  			atual = atual->left;
	  			buscaRP(a, atual, key);
	  		}
      } else{
        if(atual->right->key == key){
	  			pai = atual;
	  			return pai;

	  		} else{
	  			atual = atual->right;
	  			buscaRP(a, atual, key);
	  		}
      }
  	}
  }
}
link buscaPai (ARVORE a, int key){
    buscaRP(a,a->raiz,key);
}


link busca (ARVORE a, int key){
  return buscaR(a, a->raiz, key);
}

link novoNo(int key, link l, link r) {
  link x = malloc(sizeof(struct node));
  x->key = key;
  x->left = l;
  x->right = r;
  return x;
}
link inserirR (ARVORE a, link h, int key) {
  if(h == a->z)
    return novoNo(key, a->z, a->z);
  if(h->key == key) return h;
  if(h->key < key)
    h->right = inserirR(a, h->right, key);
  else
    h->left = inserirR(a, h->left, key);
  return h;
}
link inserirT (ARVORE a, link h, int key) {
  if(h == a->z)
    return novoNo(key, a->z, a->z);
  if(h->key == key) return h;
  if(h->key < key)  {
    h->right = inserirT(a, h->right, key);
    h =     (a, h);
  }
  else {
    h->left = inserirT(a, h->left, key);
    h = rotR(a, h);
  }
  return h;
}

void inserirNaRaiz(ARVORE a, int key) {
  a->raiz = inserirT(a, a->raiz, key);
}

void inserir (ARVORE a, int key){
  a->raiz = inserirR(a, a->raiz, key);
}

void imprimeEmLargura (ARVORE a) {
  link aux;
  FILA f = novaFila();
  enfilar(f, a->raiz);
  while (f->primeiro != NULL) {
    aux = desenfilar(f);
    printf ("%d ", aux->key);

    if (aux->left != a->z)  {
      enfilar (f,aux->left);
    }
    if (aux->right != a->z) {
      enfilar (f,aux->right);
    }
  }
  destroiFila(f);
}

link rotL(ARVORE a, link h) {
  link x = h->right;
  h->right = x->left;
  x->left = h;
  return x;
}
link rotR(ARVORE a, link h) {
  link x = h->left;
  h->left = x->right;
  x->right = h;
  return x;
}


void remover (ARVORE a, int key){
  link atual;
  link pai = buscaPai(a, key);
  link filho = busca(a, key);
  if(pai == a->z){
  	printf("O valor buscado nao existe na arvore\n");
  } else{
	  printf("\nPai %d\nFilho %d\n\n", pai->key, filho->key);

	  if(filho->left != a->z && filho->right != a->z){ 	
	  	// Tem dois filhos, o filho.
	  	atual = filho->right;
	  	if(atual->left != a->z){
		  	while(atual->left != a->z){
		  		atual = atual->left;
		  	}

		  	link pai2 = buscaPai(a, atual->key);
		  	if(filho->right != a->z){
		  		pai2->left = atual->right;
		  	} else{
		  		pai2->left = a->z;	  		
		  	}

		  	filho->key = atual->key;
		  	free(atual);

		  } else{
		  	link aux = filho->right;
		  	filho->key = aux->key;
		  	filho->right = aux->right;
		  	free(aux);
		  }		
	  } else if(filho->left != a->z){
	  	// Filho está à esquerda
	  	if(filho->key < pai->key){
	  		pai->left = filho->left;
	  	} else{
	  		pai->right = filho->left;
	  	}
	  } else if(filho->right != a->z){
	  	// Filho à direita
	  	if(filho->key < pai->key){
	  		pai->left = filho->right;
	  	} else{
	  		pai->right = filho->right;
	  	}
	  } else{
	  	// Nó folha
			if(filho->key < pai->key){
				pai->left = a->z;
			} else{
				pai->right = a->z;
			}
	  }
	}
}


#if 0
void destroiArvore(ARVORE a){
    link aux = a->head;
    if(a->head->left =! a->z){
        while(   
    }
}

void removerNo (ARVORE a, link pai);
void destroiArvore(ARVORE a);
#endif
