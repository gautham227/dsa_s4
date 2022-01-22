// made by gautham on 6th jan
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>

struct nod{
    int key;
    struct nod* left;
    struct nod* right;
    struct nod* par;
    int no;
};
typedef struct nod* node;

struct tre{
    node root;
};
typedef struct tre* tree;


struct einf{
    int low;
    int upp;
    int maxsize;
    bool check;
};
typedef struct einf* einfo;

node CREATE_NODE(int k){
    node ele;
    ele=(node)malloc(sizeof(struct nod));
    ele->key=k;
    ele->par=NULL;
    ele->right=NULL;
    ele->left=NULL;
    ele->no=1;
    return ele;
}

char* req(char* s1, char*s2){
    int ind=0;
    int maxsz=strlen(s1);
    for(int i=1;i<maxsz-1;i++){
        if(s1[i]!=' '){
            s2[ind]=s1[i];
            ind++;
        }
        if(s1[i]==' ' && s1[i-1]=='(' && s1[i+1]==')'){
            s2[ind]=' ';
            ind++;
        }
    }
    return s2;
}

node make(char* s, int* ind){
    int len=strlen(s);
    if(len==0 || *ind>=len){
        return NULL;
    }
    int k=1;
    if(s[*ind]==' '){(*ind)+=1;return NULL;}
    int value=0;
    if(s[*ind]=='-'){
        k=-1;
        (*ind)+=1;
    }
    while(*ind<len && s[*ind]!=')' && s[*ind]!='(' ){
        value*=10;
        value+=(int)(s[*ind]-'0');
        (*ind)+=1;
    }
    value=value*k;
    node n=CREATE_NODE(value);

    if(*ind >= len)return n;
    if(*ind<len && s[*ind]=='('){
        (*ind)+=1;
        n->left=make(s, ind);
    }
    if(*ind<len && s[*ind]==')')(*ind)+=1;

    if(*ind<len && s[*ind]=='('){
        (*ind)+=1;
        n->right=make(s, ind);
    }
    if(*ind<len && s[*ind]==')')(*ind)+=1;
    return n;
}

int max(int a,int b){
    if(a>b)return a;
    return b;
}

int min(int a,int b){
    if(a<b)return a;
    return b;
}

int lbst(node n,einfo inf){
    if(n==NULL){
        inf->check=true;
        return 0;
    };
    int lsize, rsize;
    bool lf=false,rf=false;
    int mi=100000000;
    inf->upp=-100000000;
    lsize=lbst(n->left,inf);
    if(inf->check==true && n->key>inf->upp)lf=true;
    mi=inf->low;
    inf->low=100000000;
    rsize=lbst(n->right, inf);
    if(inf->check==true && n->key<inf->low)rf=true;
    inf->low=min(min(mi,inf->low),n->key);
    inf->upp=max(inf->upp,n->key);
    if(lf==true && rf==true){
        inf->maxsize=max(inf->maxsize, lsize+rsize+1);
        return lsize+rsize+1;
    }
    else{
        inf->check=false;
        return 0;
    }
}

void largest_bst(node n, int* k){
    einfo inf;
    inf=(einfo)malloc(sizeof(struct einf));
    inf->low=-100000000;
    inf->upp=100000000;
    inf->maxsize=0;
    inf->check=false;
    lbst(n,inf);
    int ans=inf->maxsize;
    *k=ans;
}

int main(){
    tree t;
    t=(tree)malloc(sizeof(struct tre));
    char* str1;
    str1=(char*)malloc(100000*sizeof(char));
    char* str;
    str=(char*)malloc(100000*sizeof(char));
    fgets(str1,100000,stdin);
    str= req(str1,str);
    int ind=0;
    t->root=make(str,&ind);
    // precomp(t->root);
    int ans=0;
    largest_bst(t->root,&ans);
    printf("%d\n",ans);
    return 0;
}