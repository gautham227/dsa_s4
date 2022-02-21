// made by gautham on 18th feb
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
    int height;
};
typedef struct nod* node;

int max(int a, int b){
    if(a>b)return a;
    return b;
}

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
    ele->height=0;
    return ele;
}

int FINDHEIGHT(node pre){
    int lh, rh;
    if((pre)->left==NULL){
        lh=-1;
    }
    else{
        lh=(pre)->left->height;
    }
    if((pre)->right==NULL){
        rh=-1;
    }
    else{
        rh=(pre)->right->height;
    }
    return max(lh, rh)+1;
}

int GETBALANCE(node ele){
    if(ele==NULL)
        return -1;
    int lh, rh;
    if(ele->left==NULL){
        lh=-1;
    }
    else{
        lh=ele->left->height;
    }
    if(ele->right==NULL){
        rh=-1;
    }
    else{
        rh=ele->right->height;
    }
    return lh-rh;
}

void ROTATE_LEFT(node* pre){
    node ne=(*pre)->right;
    (*pre)->right=ne->left;
    ne->left=*pre;
    (*pre)->height=FINDHEIGHT(*pre);
    ne->height=FINDHEIGHT(ne);
    *pre=ne;
}

void ROTATE_RIGHT(node* pre){
    node ne=(*pre)->left;
    (*pre)->left=ne->right;
    ne->right=*pre;
    (*pre)->height=FINDHEIGHT(*pre);
    ne->height=FINDHEIGHT(ne);
    *pre=ne;
}

node SEARCH(tree t, int k){
    node present;
    present=t->root;
    while(present!=NULL && present->key!=k){
        if(present->key>k){
            present=present->left;
        }
        else{
            present=present->right;
        }
    }
    return present;
}

void INSERT(node *pre, node ele){
    if(*pre==NULL){
        *pre=ele;
        return;
    }
    if((*pre)->key==ele->key){
        return;
    }
    if((*pre)->key>ele->key){
        INSERT(&((*pre)->left),ele);
        if(GETBALANCE(*pre)==2){
            if(GETBALANCE((*pre)->left)==1){
                ROTATE_RIGHT(pre);
            }
            else{
                ROTATE_LEFT(&((*pre)->left));
                ROTATE_RIGHT(pre);
            }
        }
    }
    else{
        INSERT(&((*pre)->right),ele);
        if(GETBALANCE(*pre)==-2){
            if(GETBALANCE((*pre)->right)==-1){
                ROTATE_LEFT(pre);
            }
            else{
                ROTATE_RIGHT(&((*pre)->right));
                ROTATE_LEFT(pre);
            }
        }
    }
    (*pre)->height=FINDHEIGHT(*pre);
    return;
}

node MINIMUM(node ele){
    node req=ele;
    while(req->left!=NULL){
        req=req->left;
    }
    return req;
}

node DELETENODE(node ele, int k){
    if(ele==NULL)return ele;
    if(ele->key<k)ele->right=DELETENODE(ele->right, k);
    else if(ele->key>k)ele->left=DELETENODE(ele->left, k);
    else{
        if(ele->left==NULL || ele->right==NULL){
            node cur;
            if(ele->left){
                cur=ele->left;
            }
            else{
                cur=ele->right;
            }
            if(cur==NULL){
                cur=ele;
                ele=NULL;
            }
            else{
                *ele=*cur;
            }

        }
        else{
            node pre=MINIMUM(ele->right);
            ele->key=pre->key;
            ele->right=DELETENODE(ele->right, ele->key);
        }
    }
    if(ele==NULL)return ele;
    ele->height=FINDHEIGHT(ele);
    if(GETBALANCE(ele)>1 && GETBALANCE(ele->left)>=0){
        ROTATE_RIGHT(&ele);
    }
    if(GETBALANCE(ele)>1 && GETBALANCE(ele->left)<0){
        ROTATE_LEFT(&(ele->left));
        ROTATE_RIGHT(&ele);
        return ele;
    }
    if(GETBALANCE(ele)<-1 && GETBALANCE(ele->right)<=0){
        ROTATE_LEFT(&ele);
        return ele;
    }
    if(GETBALANCE(ele)<-1 && GETBALANCE(ele->right)>0){
        ROTATE_RIGHT(&(ele->right));
        ROTATE_LEFT(&ele);
        return ele;
    }
    return ele;
}

void INORDER(node n){
    if(n==NULL){
        printf("( ) ");
        return;
    };
    printf("%c ",'(');
    printf("%d ",n->key);
    INORDER(n->left);
    INORDER(n->right);
    printf("%c ",')');
    return;
}

void PRINTTREE(tree t){
    INORDER(t->root);
    printf("\n");
    return;
}

int main(){
    tree t;
    t=(tree)malloc(sizeof(struct tre));
    int k;
    char c='a';
    while(c!='e'){
        scanf("%c",&c);
        switch (c)
        {
        case 'i':
            {
            scanf(" %d",&k);
            node ne=CREATE_NODE(k);
            INSERT(&(t->root), ne);
            break;
            }
        case 's':
            {
            scanf(" %d",&k);
            node pre=SEARCH(t, k);
            if(pre==NULL){
                printf("FALSE\n");
            }
            else{
                printf("TRUE\n");
            }
            break;
            }
        case 'd':
        {
            scanf(" %d",&k);
            node pre=SEARCH(t, k);
            if(pre!=NULL){
                t->root=DELETENODE(t->root, k);
                printf("%d\n",k);
            }
            else{
                printf("FALSE\n");
            }
            break;
        }
        case 'b':
            {
            scanf(" %d",&k);
            node ele=SEARCH(t, k);
            if(ele==NULL){
                printf("FALSE\n");
            }
            else{
                printf("%d\n",GETBALANCE(ele));
            }
            break;
            }
        case 'p':
        {
            PRINTTREE(t);
            break;
        }
        case 'e':
            break;
        }
    }
    return 0;
}