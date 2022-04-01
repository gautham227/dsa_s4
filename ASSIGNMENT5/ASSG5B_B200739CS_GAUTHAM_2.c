// made by gautham on 31st mar
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>

// prim and kruskal

// struct knod{
//     int dest;
//     int weight;
//     struct knod* next;
// };

struct nnode{
    int dest;
    int weight;
    struct nnode* next;
};

struct nlist{
    struct nnode* lhead;
};

struct ngraph{
    int v;
    struct nlist* arr;
};

struct heapn{
    int vertex;
    int key;
};

struct heap{
    int size;
    int capacity;
    int* position;
    struct heapn** arr;
};

struct nnode* CREATENODE_N(int k, int w){
    struct nnode* pre;
    pre=(struct nnode*)malloc(sizeof(struct nnode));
    pre->next=NULL;
    pre->dest=k;
    pre->weight=w;
    return pre;
}

struct ngraph* CREATEGRAPH_N(int v){
    struct ngraph* g;
    g=(struct ngraph*)malloc(sizeof(struct ngraph));
    g->v=v;
    g->arr=(struct nlist*)malloc(v*sizeof(struct nlist));
    int i;
    for(i=0;i<v;i++){
        g->arr[i].lhead=NULL;
    }
    return g;
}

void NEWEDGE_N(struct ngraph* g, int src, int dest, int w){
    struct nnode* curr;
    curr=g->arr[src].lhead;
    if(curr==NULL){
        g->arr[src].lhead=CREATENODE_N(dest,w);
    }
    else{
        while(curr->next!=NULL){
            curr=curr->next;
        }
        curr->next=CREATENODE_N(dest,w);
    }
}

struct heapn* newheapnode(int v, int k){
    struct heapn* pre;
    pre=(struct heapn*)malloc(sizeof(struct heapn));
    pre->vertex=v;
    pre->key=k;
    return pre;
}

struct heap* createheap(int cap){
    struct heap* h;
    h=(struct heap*)malloc(sizeof(struct heap));
    h->size=0;
    h->capacity=cap;
    h->arr=(struct heapn**)malloc(cap*sizeof(struct heapn*));
    h->position=(int*)malloc(cap*sizeof(int));
    return h;
}

void HEAPIFY(struct heap* h, int i){
    int lc, rc, mi;
    lc=2*i+1;
    rc=2*i+2;
    if(lc<h->size && h->arr[lc]->key<h->arr[i]->key){
        mi=lc;
    }
    else{
        mi=i;
    }
    if(rc<h->size && h->arr[rc]->key<h->arr[mi]->key){
        mi=rc;
    }
    if(mi!=i){
        struct heapn* temp;
        temp=h->arr[i];
        h->arr[i]=h->arr[mi];
        h->arr[mi]=temp;
        h->position[h->arr[i]->vertex]=i;
        h->position[h->arr[mi]->vertex]=mi;
        HEAPIFY(h,mi);
    }
}

struct heapn* EXTRACTMIN(struct heap* h){
    if(h->size<=0){
        return NULL;
    }
    struct heapn* mi;
    mi=h->arr[0];
    struct heapn* last;
    last=h->arr[h->size-1];
    h->arr[0]=last;
    h->position[mi->vertex]=h->size-1;
    h->position[last->vertex]=0;
    h->size--;
    HEAPIFY(h,0);
    return mi;
}

void DECREASEKEY(struct heap* h, int v, int k){
    int i;
    i=h->position[v];
    h->arr[i]->key=k;
    while(i>0 && h->arr[i]->key<h->arr[(i-1)/2]->key){
        struct heapn* temp;
        temp=h->arr[i];
        h->arr[i]=h->arr[(i-1)/2];
        h->arr[(i-1)/2]=temp;
        h->position[h->arr[i]->vertex]=i;
        h->position[h->arr[(i-1)/2]->vertex]=(i-1)/2;
        i=(i-1)/2;
    }
}

bool isinheap(struct heap* h, int v){
    if(h->position[v]<h->size){
        return true;
    }
    return false;
}

void MST_PRIM(struct ngraph* g){
    int v=g->v;
    int par[v];
    int key[v];
    struct heap* h;
    h=createheap(v);

    for(int i=0;i<v;i++){
        par[i]=-1;
        key[i]=1e9+7;
        h->arr[i]=newheapnode(i,key[i]);
        h->position[i]=i;
    }
    key[0]=0;
    h->arr[0]=newheapnode(0,key[0]);
    h->size=v;
    h->position[0]=0;
    while(h->size>0){
        struct heapn* min;
        min=EXTRACTMIN(h);
        int u=min->vertex;
        struct nnode* curr;
        curr=g->arr[u].lhead;
        while(curr!=NULL){
            int v=curr->dest;
            if(isinheap(h,v) && curr->weight<key[v]){
                key[v]=curr->weight;
                par[v]=u;
                DECREASEKEY(h,v,key[v]);
            }
            curr=curr->next;
        }
    }
    int ans=0;
    for(int i=0;i<v;i++){
        if(par[i]!=-1){
            ans+=key[i];
        }
    }
    printf("%d\n",ans);
}

int main(){
    char d;
    scanf("%c",&d);
    int n;
    scanf("%d",&n);
    // if(d=='b'){
    //     for(int i=0;i<n;i++){
    //         int val;
    //         scanf("%d",&val);
    //         char c='a';
    //         int key;
    //         while(1){
    //             scanf("%c",&c);
    //             if(c=='\n'){
    //                 break;
    //             }
    //             scanf("%d",&key);
                
    //         }
    //     }
    // }
    if(d=='b'){
        struct ngraph* g;
        g=CREATEGRAPH_N(n);
        int src,dest,w;
        int adj[n][n];
        char junk;
        scanf("%c",&junk);
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                adj[i][j]=0;
            }
        }
        for(int i=0;i<n;i++){
            int k=0;
            int mnode=-1;
            char c;
            while(1){
                scanf("%c",&c);
                if(c=='\n'){
                    if(mnode==-1){
                        mnode=k;
                    }
                    else{adj[mnode][k]=1;}
                    break;
                }
                else if(c==' '){
                    if(mnode==-1){
                        mnode=k;
                    }
                    else{
                        adj[mnode][k]=1;
                    }
                    k=0;
                }
                else{
                    k=k*10+(c-'0');
                }
            }
        }
        for(int i=0;i<n;i++){
            int val;
            scanf("%d",&val);
            for(int j=0;j<n;j++){
                if(adj[val][j]==1){
                    scanf("%d",&adj[val][j]);
                    NEWEDGE_N(g,i,j,adj[val][j]);
                }
            }
        }
        MST_PRIM(g);
    }
    return 0;
}