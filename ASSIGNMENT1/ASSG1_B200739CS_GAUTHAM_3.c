// made by gautham on 6th jan
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<ctype.h>

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

int MINIMUM(node a){
    if(a==NULL)return 100000000;
    while(a->left!=NULL){
        a=a->left;
    }
    return a->key;
}

int MAXIMUM(node a){
    if(a==NULL)return -100000000;
    while(a->right!=NULL){
        a=a->right;
    }
    return a->key;
}

bool check(node n, int low, int upp){
    if(n==NULL)return true;
    if(n->key<low || n->key>upp)return false;
    bool x;
    bool y;
    x=check(n->left,low,n->key-1);
    y=check(n->right,n->key+1,upp);
    bool res=x && y;
    return res;
}

int no_of_del(tree t){
    bool t1,t2;
    int low=-100000000;
    int upp=100000000;
    t1=check(t->root->left,low,upp);
    t2=check(t->root->right,low,upp);
    int mt1,mt2;
    mt1=MAXIMUM(t->root->left);
    mt2=MINIMUM(t->root->right);
    int ans=2;
    if(t1 && mt1<t->root->key)ans--;
    if(t2 && mt2>t->root->key)ans--;
    return ans;
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
    t->root=make(str, &ind);
    int ans=no_of_del(t);
    printf("%d\n",ans);
    return 0;
}