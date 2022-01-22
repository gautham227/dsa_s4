// made by gautham on 31st dec
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>

struct nod{
    int key;
    struct nod* next;
};
typedef struct nod* node;
struct ll{
    node head;
    node last;
};
typedef struct ll* sll;

node CREATE_NODE(int k, sll n){
    node ne;
    ne=(node)malloc(sizeof(struct nod));
    ne->key=k;
    if(n->head==NULL){
        n->head=ne;
    }
    else{
        n->last->next=ne;
    }
    return ne;
}

int main(){
    sll list;
    list=(sll)malloc(sizeof(struct ll));
    list->head=NULL;
    list->last=NULL;
    int n=0;
    while(1){
        int k;
        char c;
        scanf("%d",&k);
        scanf("%c",&c);
        node cur=CREATE_NODE(k,list);
        list->last=cur;
        n++;
        if(c=='\n'){
            break;
        }
    }
    int l;
    scanf("%d",&l);
    if(l>n){
        printf("%d",-1);
    }
    else{
        int w=n-l;
        node present=list->head;
        while(w--){
            present=present->next;
        }
        printf("%d",present->key);
    }
    return 0;
}