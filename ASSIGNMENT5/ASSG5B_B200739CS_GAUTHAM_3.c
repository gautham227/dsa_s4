// made by gautham on 2nd apr
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>

int mdist(int* d, int* used, int v){
    int min=1e9+7;
    int min_idx=-1;
    for(int i=0;i<v;i++){
        if(used[i]==0 && d[i]<=min){
            min=d[i];
            min_idx=i;
        }
    }
    return min_idx;
}

void dijkstra(int g[1001][1001], int s, int dest, int v, int type){
    int* d;
    d=(int*)malloc(v*sizeof(int));
    int* used;
    used=(int*)malloc(v*sizeof(int));
    for(int i=0;i<v;i++){
        d[i]=1e9+7;
        used[i]=0;
    }
    d[s]=0;
    for(int i=0;i<v-1;i++){
        int u=mdist(d, used, v);
        used[u]=1;
        for(int j=0;j<v;j++){
            if(used[j]==0 && g[u][j]!=0 && d[u]!=1e9+7 && d[u]+g[u][j]<d[j]){
                d[j]=d[u]+g[u][j];
            }
        }
    }
    if(type==1){
        for(int i=0;i<v;i++){
            if(d[i]==1e9+7){
                printf("INF ");
            }
            else{
                printf("%d ", d[i]);
            }
        }
        printf("\n");
    }
    else{
        if(d[dest]==1e9+7){
            printf("UNREACHABLE\n");
        }
        else{
            printf("%d\n", d[dest]);
        }
    }
    return;
}

int main(){
    int n;
    scanf("%d",&n);
    int adjmat[1001][1001];
    for(int i=0;i<1001;i++){
        for(int j=0;j<1001;j++){
            adjmat[i][j]=0;
        }
    }
    char junk;
    scanf("%c",&junk);
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
                else{adjmat[mnode][k]=1;}
                break;
            }
            else if(c==' '){
                if(mnode==-1){
                    mnode=k;
                }
                else{
                    adjmat[mnode][k]=1;
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
            if(adjmat[val][j]==1){
                scanf("%d",&adjmat[val][j]);
            }
        }
    }
    char s[5];
    strcpy(s,"abcd");
    int ver1,ver2;
    while(strcmp(s,"stop")!=0){
        scanf("%s",&s);
        if(strcmp(s,"apsp")==0){
            scanf("%d",&ver1);
            dijkstra(adjmat, ver1, -1, n, 1);
        }
        else if(strcmp(s,"sssp")==0){
            scanf("%d",&ver1);
            scanf("%d",&ver2);
            dijkstra(adjmat, ver1, ver2, n, 2);
        }
        else{
            continue;
        }
    }
}