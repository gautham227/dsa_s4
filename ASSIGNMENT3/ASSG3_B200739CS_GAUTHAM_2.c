// made by gautham on 9th feb
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>

struct nod{
    int key;
    struct nod* left;
    struct nod* right;
};
typedef struct nod* node;

struct tre{
    node root;
};
typedef struct tre* tree;

node CREATE_NODE(int k){
    node x;
    x=(node)malloc(sizeof(struct nod));
    x->key=k;
    x->left=NULL;
    x->right=NULL;
    return x;
}

int max2(int a, int b){
    if(a>b)return a;
    return b;
}

int min2(int a, int b){
    if(a<b)return a;
    return b;
}

void INSERT(tree t, int k){
    node a;
    a=CREATE_NODE(k);
    node x,y;
    y=NULL;
    x=t->root;
    while(x!=NULL){
        y=x;
        if(x->key<=a->key){
            x=x->right;
        }
        else{
            x=x->left;
        }
    }
    if(y==NULL){
        t->root=a;
    }
    else if(a->key<y->key){
        y->left=a;
    }
    else{
        y->right=a;
    }
}

bool CHECK(node ele, int* ht){
    int lh; int rh; // ht of l and r respt
    bool l,r;
    if(ele==NULL){
        *(ht)=0;
        return true;;
    }
    l=CHECK(ele->left, &lh);
    r=CHECK(ele->right, &rh);
    *(ht)=max2(lh, rh)+1;
    int abs_bf=max2(lh,rh)-min2(lh,rh);
    if(abs_bf>=2)return false;
    if(l==true && r==true)return true;
    return false; 
}

bool ISAVL(node ele){
    int x=0;
    bool ans=CHECK(ele,&x);
    return ans;
}

int main(){
    tree t;
    t=(tree)malloc(sizeof(struct tre));
    int k;
    char c='a';
    while(c!='t'){
        scanf("%c",&c);
        switch (c)
        {
        case 'i':{
            scanf(" %d", &k);
            INSERT(t, k);
            break;
        }
        case 'c':{
            if(ISAVL(t->root)){
                printf("%d\n",1);
            }
            else{
                printf("%d\n",0);
            }
            break;
        }
        case 't':{
            break;
        }
        }
    }
    return 0;
}