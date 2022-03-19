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
    int min=-1e9;
    while(x!=NULL){
        if(x->key<min){
            min=x->key;
            pre=x;
            m=x->rsib;
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
    else ne=head2;
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

heap UNION(node head1,node head2){
    if(head1==NULL && head2==NULL){
        return NULL;
    }
    heap hp=MAKEHEAP();
    hp->head=MERGE(head1,head2);
    if(hp->head==NULL)return hp;
    node prev=NULL;
    node curr=hp->head;
    node next=curr->rsib;
    while(next!=NULL){
        if(curr->degree!=next->degree || (next->rsib!=NULL && next->rsib->degree==curr->degree)) {
            prev=curr;
            curr=next;
        }
        else if(curr->key<=next->key){
            curr->rsib=next->rsib;
            LINK(next,curr);
        }
        else if(prev==NULL){
            hp->head=next;
            LINK(curr,next);
            curr=next;
        }
        else{
            prev->rsib=next;
            LINK(curr,next);
            curr=next;
        }
        next=curr->rsib;
    }
    return curr;
}

void INSERT(heap hp, int k){
    heap h2=MAKEHEAP();
    node ne=CREATE_NODE(k);
    h2->head=ne;
    hp=UNION(hp,h2);
}

node EXTRACTMIN(node h){
    if(h==NULL)return NULL;
    node prev=NULL,curr=h,next=curr->rsib;
    node mi=MINIMUM(h)->key;
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

void DECREASEKEY(node head, int pre, int ne){
    node x=SEARCH(head,pre);
    if(x==NULL)return;
    x->key-=ne;
    node y=x->par;
    while(y!=NULL && x->key<y->key){
        int temp=x->key;
        x->key=y->key;
        y->key=temp;
        x=y;
        y=y->par;
    }
    return;
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
            INSERT(hp,k);
            break;
        case 'd':
            scanf("%d",&k);
            DELETE(hp,k);
            break;
        case 'p':
            PRINT(hp);
            break;
        case 'm':
            ne=MINIMUM(hp);
            printf("%d\n",ne->key);
            break;
        case 'x':
            EXTRACTMIN(hp);
            break;
        case 'r':
            scanf("%d",&y);
            scanf("%d",&k);
            DECREASEKEY(hp,y,k);
            break;
        case 'e':
            break;
        }
    }
    return 0;
}