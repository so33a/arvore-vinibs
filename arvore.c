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
  if(h == a->z) return NULL;
  if(h->key == key) return h;
  if( h->key < key) 
    return buscaR(a, h->right, key);
  return buscaR(a, h->left, key);
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
    h = rotL(a, h);
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
  link l = a->raiz;
  link f;
  int pai = 0;
  while(pai != 1){
    if(l->key > key){
      if(l->left->key == key){
        pai = 1;
        f = l->left;
      } else{
          pai = 0;
          l = l->left;
      }
    } else if(l->key < key){
      if(l->right->key == key){
        pai = 1;
        f = l->right;
      } else{
          pai = 0;
          l = l->right;
      }
    }
  }
  
  removerNo(a, l, f);
}

void removerNo (ARVORE a, link node, link filho){
  while(filho->left != a->z || filho->right != a->z){    
     if(filho->left == a->z){
        node = rotL(a, filho);
        filho = node->left;
      } else if(filho->right == a->z){
        node = rotL(a, filho);
        filho = node->right;
      } else{
        filho = rotR(a, filho);
        filho = filho->right;
        filho = rotL(a, filho);
        node = filho;
        filho = filho->left;
     }
  }
  
  if(node->left->key == filho->key){
      node->left = a->z;
    } else if(node->right->key == filho->key){
      node->right = a->z 
    }
    free(filho);
}

void destroiArvore(ARVORE a){
  while(a->raiz != a->z){
    if(a->raiz->right == a->z){
      remover(a, a->raiz->left->key);
      a->raiz = a->raiz->left;
    }else if(a->raiz->left == a->z){
      remover(a, a->raiz->right->key);
      a->raiz = a->raiz->right;
    } else{
      remover(a, a->raiz->key);
      a->raiz = a->z;
    }
  }
}
