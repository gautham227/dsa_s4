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

void PRINT_TREE(node n){
    if(n==NULL){
        printf("( ) ");
        return;
    };
    printf("%c ",'(');
    if(n->colour==1){
        printf("%d B ",n->key);
    }
    else{
        printf("%d R ",n->key);
    }
    PRINT_TREE(n->left);
    PRINT_TREE(n->right);
    printf("%c ",')');
    return;
}

void INSERT_RED_BLACK(tree t, int val){
    node cur=CREATE_NODE(val);
    INSERT(t, cur);
    PRINT_TREE(t->root);
    printf("\n");
    return;
}

int main(){
    char* s;
    s=(char*)malloc(sizeof(char)*19);
    tree t;
    t=(tree)malloc(sizeof(struct tre));
    while(1){
        scanf("%s",s);
        if(s[0]=='t')break;
        int val=0;
        int i=0;
        while(s[i]!='\0'){
            val=val*10+(s[i]-'0');
            i++;
        }
        INSERT_RED_BLACK(t,val);

    }
    return 0;
}