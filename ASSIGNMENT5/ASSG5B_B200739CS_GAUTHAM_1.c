// made by gautham on 30th mar
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>

// adj matrix to adj list

struct nod{
    int dest;
    struct nod* next;
};
typedef struct nod* node;

struct lis{
    node head;
};
typedef struct lis* list;

struct grap{
    int v;
    list* arr;
};
typedef struct grap* graph;

node CREATENODE(int k){
    node pre;
    pre=(node)malloc(sizeof(struct nod));
    pre->dest=k;
    pre->next=NULL;
    return pre;
}

node LISTSEARCH(list l, int k){
    node curr;
    curr=l->head;
    while(curr!=NULL){
        if(curr->dest==k){
            return curr;
        }
        curr=curr->next;
    }
    return NULL;
}

void LISTINSERTTAIL(list l, node k){
    node curr;
    curr=l->head;
    if(curr==NULL){
        l->head=k;
    }
    else{
        while(curr->next!=NULL){
            curr=curr->next;
        }
        curr->next=k;
    }
}

node LISTDELETE(list l, int k){
    node curr;
    node pre;
    curr=l->head;
    if(curr->dest==k){
        l->head=curr->next;
        return curr;
    }
    while(curr!=NULL){
        if(curr->dest==k){
            pre->next=curr->next;
            return curr;
        }
        pre=curr;
        curr=curr->next;
    }
    return NULL;
}

void PRINT_LIST(list l){
    node curr;
    curr=l->head;
    while(curr!=NULL){
        printf("%d ", curr->dest);
        curr=curr->next;
    }
    printf("\n");
}

int main(){
    int sz;
    scanf("%d",&sz);
    int adjmat[sz][sz];
    graph g;
    g=(graph)malloc(sizeof(struct grap));
    g->v=sz;
    g->arr=(list*)malloc(sizeof(list)*sz);
    for(int i=0;i<sz;i++){
        g->arr[i]=(list)malloc(sizeof(struct lis));
        g->arr[i]->head=NULL;
    }
    for(int i=0;i<sz;i++){     
        for(int j=0;j<sz;j++){
            scanf("%d",&adjmat[i][j]);
            if(adjmat[i][j]==1){
                node k=CREATENODE(j);
                LISTINSERTTAIL(g->arr[i],k);
            }
        }
    }
    for(int i=0;i<sz;i++){
        printf("%d ",i);
        PRINT_LIST(g->arr[i]);
    }
    return 0;
}