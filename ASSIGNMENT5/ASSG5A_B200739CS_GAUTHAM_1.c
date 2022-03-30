// made by gautham on 30th mar
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>

// disjoint set union

struct nods1{
    int val;
    struct nods1* represent;
};
typedef struct nods1* node1;

struct nods2{
    int key;
    int rank;
    struct nods2* represent;
};
typedef struct nods2* node2;

struct list1s{
	node1 head;
};
typedef struct list1s* list1;

struct list2s{
	node2 head;
};
typedef struct list2s* list2;

list1 set1, set2;
list2 set3, set4;

int cnt1=0, cnt2=0, cnt3=0, cnt4=0;

int MAKESET(int k){
    if(set1[k].head!=NULL){
        return -1;
    }
    node1 sna=(node1)malloc(sizeof(struct nods1));
    node1 na=(node1)malloc(sizeof(struct nods1));
    node2 snb=(node2)malloc(sizeof(struct nods2));
    node2 nb=(node2)malloc(sizeof(struct nods2));
    sna->val=k;
    sna->represent=sna;
    na->val=k;
    na->represent=na;
    set1[k].head=sna;
    set2[k].head=na;

    snb->key=k;
    snb->represent=snb;
    snb->rank=0;

    nb->key=k;
    nb->represent=nb;
    nb->rank=0;

    set3[k].head=snb;
    set4[k].head=nb;
    return k;
}

int main(){
    set1=(list1)malloc(10000*sizeof(struct list1s));
	set2=(list1)malloc(10000*sizeof(struct list1s));
	set3=(list2)malloc(10000*sizeof(struct list2s));
	set4=(list2)malloc(10000*sizeof(struct list2s));

    for(int i=0;i<10000;i++){
        set1[i].head=NULL;
        set2[i].head=NULL;
        set3[i].head=NULL;
        set4[i].head=NULL;
    }

    char c='a';
    int k, res;
    while(c!='s'){
        scanf("%c", &c);
        switch (c)
        {
        case 'm':
            scanf("%d", &k);
            res=MAKESET(k);
            printf("%d\n", res);
            break;

        case 'f':
            
            break;
        case 'u':
            
            break;
        case 's':
            printf("%d %d %d %d\n", cnt1, cnt2, cnt3, cnt4);
            break;
        }
    }
}