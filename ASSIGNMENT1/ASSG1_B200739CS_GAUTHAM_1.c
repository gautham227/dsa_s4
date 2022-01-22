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

struct qnod{
    node no;
    struct qnod* next;
};
typedef struct qnod* qnode;

struct queu{
    qnode head;
    qnode tail;
};
typedef struct queu* queue;

qnode CREATE_QUEUE_NODE(node k){
    qnode pre;
    pre=(qnode)malloc(sizeof(struct qnod));
    pre->no=k;
    pre->next=NULL;
    return pre;
}

bool QUEUE_EMPTY(queue q){
    if(q->head==NULL){
        return true;
    }
    return false;
}

void ENQUEUE(queue q, node k){
    qnode ne=CREATE_QUEUE_NODE(k);
    if(q->head==NULL){
        q->head=ne;
        q->tail=ne;
    }
    else{
        q->tail->next=ne;
        q->tail=ne;
    }
    return;
}

int DEQUEUE(queue q){
    bool b=QUEUE_EMPTY(q);
    if(b)return 0;
    if(q->head->next==NULL){
        q->head=NULL;
        q->tail=NULL;
    }
    else{
        q->head=q->head->next;
    }
    return 1;
}

node CREATE_NODE(int k){
    node ele;
    ele=(node)malloc(sizeof(struct nod));
    ele->key=k;
    ele->par=NULL;
    ele->right=NULL;
    ele->left=NULL;
    return ele;
}

node bfs(tree t){
    queue q;
    q=(queue)malloc(sizeof(struct queu));
    ENQUEUE(q,t->root);
    while(!QUEUE_EMPTY(q)){
        qnode cur=q->head;
        DEQUEUE(q);
        if(cur->no->left==NULL){
            return cur->no;
        }
        ENQUEUE(q,cur->no->left);
        if(cur->no->right==NULL){
            return cur->no;
        }
        ENQUEUE(q,cur->no->right);
    }
}

void INSERT(tree t, int k){
    node pre=CREATE_NODE(k);
    if(t->root==NULL){
        t->root=pre;
    }
    else{
        node ne=bfs(t);
        if(ne->left==NULL){
            ne->left=pre;
        }
        else if(ne->right==NULL){
            ne->right=pre;
        }
    }
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

void PRINT(tree t){
    INORDER(t->root);
    return;
}

int main(){
    tree t;
    t=(tree)malloc(sizeof(struct tre));
    char c='a';
    int k;
    while(c!='e'){
        scanf("%c",&c);
        switch (c)
        {
        case 'i':
            scanf("%d",&k);
            INSERT(t,k);
            break;
        case 'p':
            PRINT(t);
            printf("\n");
            break;
        case 'e':
            break;
        }
    }
    return 0;
}