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
};
typedef struct nod* node;

struct tre{
    node root;
};
typedef struct tre* tree;

node CREATE_NODE(int k){
    node ele;
    ele=(node)malloc(sizeof(struct nod));
    ele->key=k;
    ele->par=NULL;
    ele->right=NULL;
    ele->left=NULL;
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

node lca(node n,int a, int b){
    if(n==NULL) return NULL;
    if(n->key==a || n->key==b)return n;
    node l;
    node r;
    l=lca(n->left,a,b);
    r=lca(n->right,a,b);
    if(l!=NULL && r!=NULL){
        return n;
    }
    else if(r!=NULL)return r;
    return l;
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
    node ans;
    ans=(node)malloc(sizeof(struct nod));
    int n1,n2;
    scanf("%d %d",&n1,&n2);
    ans=lca(t->root,n1,n2);
    printf("%d\n",ans->key);
    return 0;
}   