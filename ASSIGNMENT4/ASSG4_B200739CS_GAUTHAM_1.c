// made by gautham on 18th mar
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>

//binomial heap

struct nod{
    struct nod* par;
    struct nod* lchild;
    struct nod* rsib;
    int key;
    int degree;
};
typedef struct nod* node;

struct hea{
    node head;
};
typedef struct hea* heap;

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

void PRINT(heap hp){
    queue q;
    q=(queue)malloc(sizeof(struct queu));
    if(hp->head==NULL){
        printf("\n");
        return;
    }
    q->head=NULL;
    q->tail=NULL;
    ENQUEUE(q,hp->head);
    while(!QUEUE_EMPTY(q)){
        qnode cur=q->head;
        printf("%d ",cur->no->key);
        DEQUEUE(q);
        node x=cur->no;
        if(cur->no->lchild!=NULL){
            ENQUEUE(q,cur->no->lchild);
        }
        while(x->rsib!=NULL){
            printf("%d ",x->rsib->key);
            x=x->rsib;
            if(x->lchild!=NULL){
                ENQUEUE(q,x->lchild);
            }
        }
    }
    printf("\n");
    return;
}

heap MAKEHEAP(){
    heap h;
    h=(heap)malloc(sizeof(struct hea));
    h->head=NULL;
    return h;
}

node CREATE_NODE(int key){
    node x;
    x=(node)malloc(sizeof(struct nod));
    x->key=key;
    x->degree=0;
    x->par=NULL;
    x->lchild=NULL;
    x->rsib=NULL;
    return x;
}

node MINIMUM(node head){
    node x=head;
    if(x==NULL)return NULL;
    node pre=NULL;
    node m=x;
    int min=1e9;
    while(x!=NULL){
        if(x->key<min){
            min=x->key;
            pre=x;
            m=x;
        }
        x=x->rsib;
    }
    return m;
}

void LINK(node x, node y){
    x->par=y;
    x->rsib=y->lchild;
    y->lchild=x;
    y->degree++;
    return;
}

node MERGE(node head1, node head2){
    if(head1==NULL)return head2;
    if(head2==NULL)return head1;
    node ne=NULL;
    if(head2->degree>=head1->degree)ne=head1;
    else if(head2->degree<head1->degree) ne=head2;
    while(head1!=NULL && head2!=NULL){
        if(head2->degree>head1->degree){
            head1=head1->rsib;
        }
        else if(head1->degree==head2->degree){
            node s=head1->rsib;
            head1->rsib=head2;
            head1=s;
        }
        else{
            node s=head2->rsib;
            head2->rsib=head1;
            head2=s;
        }
    }
    return ne;
}

node UNION(node head1,node head2){
    if(head1==NULL && head2==NULL){
        return NULL;
    }
    heap hp=MAKEHEAP();
    hp->head=MERGE(head1,head2);
    // if(hp->head==NULL)return hp->head;
    node pres=hp->head;
    node prev=NULL;
    node curr=pres;
    node next=curr->rsib;
    while(next!=NULL){
        if((curr->degree!=next->degree) || ((next->rsib!=NULL) && (next->rsib)->degree==curr->degree)) {
            prev=curr;
            curr=next;
        }
        else{
            if(curr->key<=next->key){
                curr->rsib=next->rsib;
                LINK(next,curr);
            }
            else{
                if(prev==NULL){
                    pres=next;
                }
                else{
                    prev->rsib=next;
                }
                LINK(curr,next);
                curr=next;
            }
        }
        next=curr->rsib;
    }
    return pres;
}

node INSERT(heap hp, int k){
    heap h2=MAKEHEAP();
    node ne=CREATE_NODE(k);
    h2->head=ne;
    hp->head=UNION(hp->head,h2->head);
    return hp->head;
}

node EXTRACTMIN(node h){
    if(h==NULL)return NULL;
    node prev=NULL,curr=h,next=curr->rsib;
    node mi=MINIMUM(h);
    int min;
    if(mi!=NULL)min=mi->key;
    while(next!=NULL){
        if(curr->key==min)break;
        prev=curr;
        curr=next;
        next=next->rsib;
    }
    if(prev==NULL)h=next;
    else{prev->rsib=next;}
    curr->rsib=NULL;
    node t=curr;
    curr=curr->lchild;
    node ne=(node)malloc(sizeof(struct nod));
    ne->par=NULL;
    ne=curr;
    prev=NULL;
    next=NULL;
    while(curr!=NULL){
        next=curr->rsib;
        curr->rsib=prev;
        prev=curr;
        curr=next;
    }
    ne=prev;
    node ret=UNION(h,ne);
    return ret;
}

node SEARCH(node h, int k){
    if(h==NULL)return NULL;
    if(h->key==k)return h;
    node s1=SEARCH(h->lchild,k);
    if(s1!=NULL)return s1;
    node s2=SEARCH(h->rsib,k);
    return s2;
}

bool DECREASEKEY(node head, int pre, int ne){
    node x=SEARCH(head,pre);
    if(x==NULL)return false;
    x->key-=ne;
    node y=x->par;
    while(y!=NULL && x->key<y->key){
        int temp=x->key;
        x->key=y->key;
        y->key=temp;
        x=y;
        y=y->par;
    }
    return true;
}

node DELETE(node head, int k){
    if(head==NULL)return NULL;
    node x=SEARCH(head,k);
    if(x==NULL)return NULL;
    DECREASEKEY(head,k,1e9+7);
    node ret=EXTRACTMIN(head);
    return ret;
}

int main(){
    heap hp=MAKEHEAP();
    char c='a';
    int k,y;
    node ne;
    while(c!='e'){
        scanf("%c",&c);
        switch (c)
        {
        case 'i':
            scanf("%d",&k);
            hp->head=INSERT(hp,k);
            break;
        case 'd':
            scanf("%d",&k);
            ne=DELETE(hp->head,k);
            if(ne!=NULL)printf("%d\n",k);
            else printf("-1\n");
            break;
        case 'p':
            PRINT(hp);
            break;
        case 'm':
            ne=MINIMUM(hp->head);
            if(ne!=NULL)printf("%d\n",ne->key);
            else printf("-1\n");
            break;
        case 'x':
            ne=MINIMUM(hp->head);
            if(ne!=NULL)printf("%d\n",ne->key);
            else printf("-1\n");
            hp->head=EXTRACTMIN(hp->head);
            break;
        case 'r':
            scanf("%d",&y);
            scanf("%d",&k);
            if(DECREASEKEY(hp->head,y,k)){
                printf("%d\n",y-k);
            }
            else printf("-1\n");
            break;
        case 'e':
            break;
        }
    }
    return 0;
}