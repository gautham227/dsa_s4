// made by gautham on 27th feb
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>

// rb tree insertion

struct nod{
    int key;
    struct nod* left;
    struct nod* right;
    struct nod* parent;
    int colour; //1->black, 0->red
    bool visited;
};

typedef struct nod* node;

struct tre{
    node root;
};

typedef struct tre* tree;

node CREATE_NODE(int val){
    node ele;
    ele=(node)malloc(sizeof(struct nod));
    ele->key=val;
    ele->left=NULL;
    ele->right=NULL;
    ele->parent=NULL;
    ele->colour=0;
    ele->visited=false;
    return ele;
}

void LEFT_ROTATE(tree t, node cur){
    node pre=cur->right;
    cur->right=pre->left;
    if(pre->left!=NULL)
        pre->left->parent=cur;
        pre->parent=cur->parent;
    if(cur->parent==NULL)
        t->root=pre;
    else if(cur==cur->parent->left)
        cur->parent->left=pre;
    else
        cur->parent->right=pre;
    pre->left=cur;
    cur->parent=pre;
}

void RIGHT_ROTATE(tree t, node cur){
    node pre=cur->left;
    cur->left=pre->right;
    if(pre->right!=NULL)
        pre->right->parent=cur;
        pre->parent=cur->parent;
    if(cur->parent==NULL)
        t->root=pre;
    else if(cur==cur->parent->left)
        cur->parent->left=pre;
    else
        cur->parent->right=pre;
    pre->right=cur;
    cur->parent=pre;
}

void ADJUST(tree t, node* n){
    node* root=&(t->root);
    node par, grandpar, uncle;
    par=NULL;
    grandpar=NULL;
    while((*n)!=(t->root) && (*n)->colour==0 && (*n)->parent->colour==0){
        par=(*n)->parent;
        grandpar=(*n)->parent->parent;
        if(par==grandpar->left){
            uncle=grandpar->right;
            if(uncle!=NULL && uncle->colour==0){
                uncle->colour=1;
                par->colour=1;
                grandpar->colour=0;
                (*n)=grandpar;
            }
            else{
                if((*n)==par->right){
                    (*n)=par;
                    LEFT_ROTATE(t, (*n));
                    par=(*n)->parent;
                    grandpar=par->parent;
                }
                par->colour=1;
                grandpar->colour=0;
                RIGHT_ROTATE(t, grandpar);
            }
        }
        else{
            uncle=grandpar->left;
            if(uncle!=NULL && uncle->colour==0){
                uncle->colour=1;
                par->colour=1;
                grandpar->colour=0;
                (*n)=grandpar;
            }
            else{
                if((*n)==par->left){
                    (*n)=par;
                    RIGHT_ROTATE(t, (*n));
                    par=(*n)->parent;
                    grandpar=par->parent;
                }
                par->colour=1;
                grandpar->colour=0;
                LEFT_ROTATE(t, grandpar);
            }
        }
    }
    t->root->colour=1;
}

node INSERT(tree t, node n){
    node present=t->root; //x
    node cur=NULL; //y

    while(present!=NULL){
        cur=present;
        if(n->key<present->key){
            present=present->left;
        }
        else{
            present=present->right;
        }
    }
    n->parent=cur;
    if(cur==NULL){
        t->root=n;
    }
    else if(n->key<cur->key){
        cur->left=n;
    }
    else{
        cur->right=n;
    }
    ADJUST(t, &n);
    return t->root;
}

void INSERT_RED_BLACK(tree t, int val){
    node cur=CREATE_NODE(val);
    INSERT(t, cur);
    return;
}

void dfs(node n, int k, bool* ans){
    if(n==NULL)return;
    if(n->visited==1)return;
    n->visited=true;
    if(k==0){
        if(n->colour==1)(*ans=true);
        return;
    }
    dfs(n->left, k-1, ans);
    dfs(n->right, k-1, ans);
    dfs(n->parent, k-1, ans);
}

void reset(node s){
    if(s==NULL)
        return;
    s->visited=false;
    reset(s->left);
    reset(s->right);
}

void count(node start, node n, int k, int* ans){
    if(n==NULL)return;
    reset(start);
    bool x=false;
    dfs(n, k, &x);
    if(x){(*ans)++;}
    count(start, n->left, k, ans);
    count(start, n->right, k, ans);
}

int main(){
    char* s;
    s=(char*)malloc(sizeof(char)*19);
    tree t;
    t=(tree)malloc(sizeof(struct tre));
    int dist;
    scanf("%d",&dist);
    int no;
    scanf("%d",&no);
    for(int i=0;i<no;i++){
        int k;
        scanf("%d", &k);
        INSERT_RED_BLACK(t, k);
    }
    int ans=0;
    count(t->root,t->root, dist, &ans);
    printf("%d",ans);
    return 0;
}