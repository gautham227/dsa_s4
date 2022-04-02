// made by gautham on 31st mar
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>

struct edge{
    int src;
    int dest;
    int weight;
};

struct list{
    struct edge* lhead;
};

struct graph{
    int v;
    int e;
    struct list* arr;
};

struct graph* createg(int v, int e){
    struct graph* g;
    g=(struct graph*)malloc(sizeof(struct graph));
    g->v=v;
    g->e=e;
    g->arr=(struct list*)malloc(e*sizeof(struct list));
    int i;
    // for(i=0;i<e;i++){
    //     g->arr[i].lhead=NULL;
    // }
    return g;
}

void addedge(struct graph* g,int s, int dest, int w, int i){
    // struct edge* n1=g->arr[i].lhead;
    g->arr[i].lhead=(struct edge*)malloc(sizeof(struct edge));
    g->arr[i].lhead->src=s;
    g->arr[i].lhead->dest=dest;
    g->arr[i].lhead->weight=w;

    return;
}

int neg_cycle_bell(struct graph* g, int s, int* d){
    int vcnt=g->v;
    int ecnt=g->e;
    for(int i=0;i<vcnt;i++){
        d[i]=1e9+7;
    }
    d[s]=0;
    for(int i=1;i<vcnt;i++){
        for(int j=0;j<ecnt;j++){
            int u=g->arr[j].lhead->src;
            int v=g->arr[j].lhead->dest;
            int w=g->arr[j].lhead->weight;
            if(d[u]!=1e9+7 && d[u]+w<d[v]){
                d[v]=d[u]+w;
            }
        }
    }
    for(int i=0;i<ecnt;i++){
        int u=g->arr[i].lhead->src;
        int v=g->arr[i].lhead->dest;
        int w=g->arr[i].lhead->weight;
        if(d[u]!=1e9+7 && d[u]+w<d[v]){
            return 1;
        }
    }
    return 0;
}

int allnodes(struct graph* g){
    int vcnt=g->v;
    int vis[vcnt+1];
    for(int i=0;i<vcnt+1;i++){
        vis[i]=0;
    }
    int flag=0;
    int* d;
    d=(int*)malloc(vcnt*sizeof(int));
    for(int i=0;i<vcnt;i++){
        d[i]=1e9+7;
    }
    for(int i=0;i<vcnt;i++){
        if(vis[i]==0){
            int res=neg_cycle_bell(g,i,d);
            if(res==1){
                flag=1;
                return 1;
            }
        }
        for(int i=0;i<vcnt;i++){
            if(d[i]!=1e9+7){
                vis[i]=1;
            }
        }
    }
    if(flag==0){
        return 0;
    }
    return 1;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    struct graph* g;
    g=createg(n,m);
    int s,dest,w;
    for(int i=0;i<m;i++){
        scanf("%d %d %d", &s, &dest, &w);
        addedge(g,s,dest,w,i);
    }
    int ans=allnodes(g);
    if(ans){
        printf("1\n");
    }
    else{
        printf("-1\n");
    }
    return 0;
}