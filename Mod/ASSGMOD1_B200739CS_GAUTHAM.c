// made by gautham on 11th jan
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>

struct nod{
    int key;
    int vis;
    struct nod* left;
    struct nod* right;
    struct nod* par;
};
typedef struct nod* node;

struct tre{
    node root;
};
typedef struct tre* tree;

node pls;

node CREATE_NODE(int k){
    node ele;
    ele=(node)malloc(sizeof(struct nod));
    ele->key=k;
    ele->par=NULL;
    ele->right=NULL;
    ele->left=NULL;
    ele->vis=0;
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
        if(n->left!=NULL){
            n->left->par=n;
        }
    }
    if(*ind<len && s[*ind]==')')(*ind)+=1;

    if(*ind<len && s[*ind]=='('){
        (*ind)+=1;
        n->right=make(s, ind);
        if(n->right!=NULL){
            n->right->par=n;
        }
    }
    if(*ind<len && s[*ind]==')')(*ind)+=1;
    return n;
}

// node x;

node find(node n, int k){
    if(n->left==NULL)return NULL;
    if(n->key==k)return n;
    node l=find(n->left,k);
    node r=find(n->right,k);
    if(l!=NULL)return l;
    return r;
}

int dfs(node n, int k){
    if(n==NULL)return 0;
    if(n->vis==1)return 0;
    n->vis=1;
    if(k==0)return n->key;
    if(k>0){
        return n->key+dfs(n->left,k-1)+dfs(n->right,k-1)+dfs(n->par,k-1);
    }
}

int main(){
    tree t;
    node x;
    x=(node)malloc(sizeof(struct nod));
    t=(tree)malloc(sizeof(struct tre));
    char* str1;
    str1=(char*)malloc(100000*sizeof(char));
    char* str;
    str=(char*)malloc(100000*sizeof(char));
    fgets(str1,100000,stdin);
    str= req(str1,str);
    int ind=0;
    t->root=make(str,&ind);
    int s,k;
    scanf("%d %d",&s, &k);
    x=find(t->root,s);
    int ans=dfs(x,k);
    printf("%d",ans);
}
