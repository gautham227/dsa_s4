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

int MAKESET(int k, list1 set1, list1 set3, list2 set2, list2 set4){
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
    set3[k].head=na;

    snb->key=k;
    snb->represent=snb;
    snb->rank=0;

    nb->key=k;
    nb->represent=nb;
    nb->rank=0;

    set2[k].head=snb;
    set4[k].head=nb;
    return k;
}

node1 path_comp1(node1 nod, int* cnt3){
    (*cnt3)++;
    if(nod!=nod->represent){
        nod->represent=path_comp1(nod->represent, cnt3);
    }
    return nod->represent;
}

node2 path_comp2(node2 nod, int* cnt4){
    (*cnt4)++;
    if(nod!=nod->represent){
        nod->represent=path_comp2(nod->represent, cnt4);
    }
    return nod->represent;
}

node1 find1(int k, list1 set1, int* cnt1){
    node1 n=set1[k].head;
    if(n==NULL)return NULL;
    (*cnt1)++;
    while(n!=NULL){
        if(n->represent!=n){
            n=n->represent;
            (*cnt1)++;
        }
        else{
            break;
        }
    }
    return n;
}

node2 find2(int k, list2 set2, int* cnt2){
    node2 n=set2[k].head;
    if(n==NULL)return NULL;
    (*cnt2)++;
    while(n!=NULL){
        if(n->represent!=n){
            n=n->represent;
            (*cnt2)++;
        }
        else{
            break;
        }
    }
    return n;
}

node1 find3(int k, list1 set3, int* cnt3){
    node1 n=set3[k].head;
    if(n==NULL)return NULL;
    n=path_comp1(set3[k].head, cnt3);
    return n;
}

node2 find4(int k, list2 set4, int* cnt4){
    node2 n=set4[k].head;
    if(n==NULL)return NULL;
    n=path_comp2(set4[k].head, cnt4);
    return n;
}

int union1(int val1, int val2, list1 set1, int* cnt1){
    node1 n=(node1)malloc(sizeof(struct nods1));
    node1 n1=(node1)malloc(sizeof(struct nods1));
    n=find1(val1, set1,cnt1);
    n1=find1(val2, set1, cnt1);
    if(n==NULL || n1==NULL){
        return 0;
    }
    if(n->val==n1->val){
        return n->val;
    }
    else{
        n1->represent=n;
        return n->val;
    }
}

int union2(int val1, int val2, list2 set2, int* cnt2){
    node2 n=(node2)malloc(sizeof(struct nods2));
    node2 n1=(node2)malloc(sizeof(struct nods2));
    n->rank=0;
    n1->rank=0;
    n=find2(val1, set2, cnt2);
    n1=find2(val2, set2, cnt2);
    if(n==NULL || n1==NULL){
        return 0;
    }
    if(n->rank>n1->rank){
        n1->represent=n;
        return n->key;
    }
    else if(n->rank<n1->rank){
        n->represent=n1;
        return n1->key;
    }
    else{
        n1->represent=n;
        n->rank++;
        return n->key;
    }
}

int union3(int val1, int val2, list1 set3, int* cnt3){
    node1 n=(node1)malloc(sizeof(struct nods1));
    node1 n1=(node1)malloc(sizeof(struct nods1));
    n=find3(val1, set3, cnt3);
    n1=find3(val2, set3, cnt3);
    if(n==NULL || n1==NULL){
        return 0;
    }
    if(n->val==n1->val){
        return n->val;
    }
    else{
        n1->represent=n;
        return n->val;
    }
}

int union4(int val1, int val2, list2 set4, int* cnt4){
    node2 n=(node2)malloc(sizeof(struct nods2));
    node2 n1=(node2)malloc(sizeof(struct nods2));
    n->rank=0;
    n1->rank=0;
    n=find4(val1, set4, cnt4);
    n1=find4(val2, set4, cnt4);
    if(n==NULL || n1==NULL){
        return 0;
    }
    if(n->rank>n1->rank){
        n1->represent=n;
        return n->key;
    }
    else if(n->rank<n1->rank){
        n->represent=n1;
        return n1->key;
    }
    else{
        n1->represent=n;
        n->rank++;
        return n->key;
    }
}

int main(){

    list1 set1, set3;
    list2 set2, set4;

    set1=(list1)malloc(10001*sizeof(struct list1s));
	set3=(list1)malloc(10001*sizeof(struct list1s));
	set2=(list2)malloc(10001*sizeof(struct list2s));
	set4=(list2)malloc(10001*sizeof(struct list2s));

    for(int i=0;i<10001;i++){
        set1[i].head=NULL;
        set3[i].head=NULL;
        set2[i].head=NULL;
        set4[i].head=NULL;
    }

    int cnt1=0, cnt2=0, cnt3=0, cnt4=0;

    char c='a';
    int k, res;
    int u1, u2; // 2 vals used for union
    // to store return val of find
    node1 f1, f3; 
    node2 f2, f4;
    int val1, val2,val3, val4;
    while(c!='s'){
        scanf("%c", &c);
        switch (c)
        {
        case 'm':
            scanf("%d", &k);
            res=MAKESET(k, set1, set3, set2, set4);
            printf("%d\n", res);
            break;

        case 'f':
            scanf("%d",&k);
            f1=find1(k, set1, &cnt1);
            if(f1==NULL){
                printf("-1 -1 -1 -1\n");
            }
            else{
                f2=find2(k, set2, &cnt2);
                f3=find3(k, set3, &cnt3);
                f4=find4(k, set4, &cnt4);
                printf("%d %d %d %d\n", f1->val, f2->key, f3->val, f4->key);
            }
            break;
        case 'u':
            scanf("%d %d",&u1, &u2);
            val1=union1(u1, u2, set1, &cnt1);
            if(val1!=0){
                val2=union2(u1, u2, set2, &cnt2);
                val3=union3(u1, u2, set3, &cnt3);
                val4=union4(u1, u2, set4, &cnt4);
                printf("%d %d %d %d\n",val1, val2, val3, val4);
            }
            else{
                printf("-1 -1 -1 -1\n");
            }
            break;
        case 's':
            printf("%d %d %d %d\n", cnt1, cnt2, cnt3, cnt4);
            break;
        }
    }
}