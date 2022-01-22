// made by gautham on 6th jan
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<ctype.h>

struct nod{
    int key;
    struct nod* par;
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
    x->par=NULL;
    x->right=NULL;
    return x;
}

node SEARCH(tree t,int k){
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

node MINIMUM(node a){
    while(a->left!=NULL){
        a=a->left;
    }
    return a;
}

node MAXIMUM(node a){
    while(a->right!=NULL){
        a=a->right;
    }
    return a;
}

void SUCCESSOR(tree t, int k){
    node present;
    present=SEARCH(t,k);
    if(present==NULL){
        printf("%d\n",-1);
        return;
    }
    if(present->right!=NULL){
        node cur1=MINIMUM(present->right);
        printf("%d\n",cur1->key);
        return;
    }
    node p;
    p=present->par;
    while(p!=NULL && present==p->right){
        present=p;
        p=p->par;
    }
    if(p==NULL){
        printf("%d\n",-1);
    }
    else{
        printf("%d\n",p->key);
    }
}

void PREDECESSOR(tree t, int k){
    node present;
    present=SEARCH(t,k);
    if(present==NULL){
        printf("%d\n",-1);
        return;
    }
    if(present->left!=NULL){
        node cur1=MAXIMUM(present->left);
        printf("%d\n",cur1->key);
    }
    else{
        node p;
        p=present->par;
        while(p!=NULL && present==p->left){
            present=p;
            p=p->par;
        }
        if(p==NULL){
            printf("%d\n",-1);
        }
        else{
            printf("%d\n",p->key);
        }
    }
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
    a->par=y;
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

void TRANSPLANT(tree t, node a, node b){
    if(a->par==NULL){
        t->root=b;
    }
    else if(a==a->par->left){
        a->par->left=b;
    }
    else{
        a->par->right=b;
    }
    if(b!=NULL){
        b->par=a->par;
    }
    return;
}

void DELETE(tree t, int k){
    node present=SEARCH(t,k);
    if(present==NULL){
        printf("%d\n",-1);
        return;
    }
    printf("%d\n",present->key);
    if(present->left==NULL){
        TRANSPLANT(t,present,present->right);
    }
    else if(present->right==NULL){
        TRANSPLANT(t,present,present->left);
    }
    else{
        node cur=MINIMUM(present->right);
        if(cur->par!=present){
            TRANSPLANT(t,cur,cur->right);
            cur->right=present->right;
            cur->right->par=cur;
        }
        TRANSPLANT(t,present,cur);
        cur->left=present->left;
        cur->left->par=cur;
    }
}

int LEVEL(tree t,int k){
    node present;
    int ans=1;
    present=t->root;
    while(present!=NULL && present->key!=k){
        ans++;
        if(present->key>k){
            present=present->left;
        }
        else{
            present=present->right;
        }
    }
    if(present!=NULL && present->key==k){
        return ans;
    }
    return -1;
}

void INORDER(node r){
    if(r!=NULL){
        INORDER(r->left);
        printf("%d ",r->key);
        INORDER(r->right);
    }
}

void PREORDER(node r){
    if(r!=NULL){
        printf("%d ",r->key);
        PREORDER(r->left);
        PREORDER(r->right);
    }
}

void POSTORDER(node r){
    if(r!=NULL){
        POSTORDER(r->left);
        POSTORDER(r->right);
        printf("%d ",r->key);
    }
}

int main(){
    tree t;
    t=(tree)malloc(sizeof(struct tre));
    char c='b';
    int k,val;
    node ptr;
    while(c!='e'){
        scanf("%c",&c);
        switch (c)
        {
        case 'a':
            scanf(" %d",&k);
            INSERT(t,k);
            break;
        case 'd':
            scanf(" %d",&k);
            DELETE(t,k);
            break;
        case 's':
            scanf(" %d",&k);
            ptr=SEARCH(t,k);
            if(ptr==NULL){
                printf("%d\n",-1);
            }
            else{
                printf("%d\n",1);
            }
            break;
        case 'l':
            scanf(" %d",&k);
            val=LEVEL(t,k);
            if(val==-1){
                printf("%d\n",-1);
            }
            else{
                printf("%d\n",val);
            }
            break;
        case 'm':
            if(t->root!=NULL){
                ptr=MINIMUM(t->root);
                printf("%d\n",ptr->key);
            }
            break;
        case 'x':
            if(t->root!=NULL){
                ptr=MAXIMUM(t->root);
                printf("%d\n",ptr->key);
            }
            break;
        case 'r':
            scanf(" %d",&k);
            PREDECESSOR(t,k);
            break;
        case 'u':
            scanf(" %d",&k);
            SUCCESSOR(t,k);
            break;
        case 'p':
            PREORDER(t->root);
            printf("\n");
            break;
        case 'i':
            INORDER(t->root);
            printf("\n");
            break;
        case 't':
            POSTORDER(t->root);
            printf("\n");
            break;
        case 'e':
            break;
        }
    }
    return 0;
}