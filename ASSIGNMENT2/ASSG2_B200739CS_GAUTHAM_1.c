// made by gautham on 23rd jan
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>

int * HASHTABLE(int m){
    int * ht;
    ht=(int*)malloc(sizeof(int)* m);
    for(int i=0;i<m;i++){
        ht[i]=-1e9-10;
    }
    return ht;
}

// -1e9-10 depicts an position that has always been empty
// -1e9 depicts a position that that currently is empty but was filled earlier

int appsqrt(int k){
    int s=0,e=k,mid;
    double ans=0;
    while(s<=e){
        mid=(s+e)/2;
        if(mid*mid==k){
            ans=mid;
            break;
        }
        else if(mid*mid<k){
            ans=s;
            s=mid+1;
        }
        else{
            e=mid-1;
        }
    }
    float inc = 0.1;
	for (int i = 0; i < 5; i++) {
		while (ans * ans <= k) {
			ans=ans+inc;
		}
		ans=ans-inc;
		inc=inc/ 10;
	}
    int an=ans/1+1;
    return an;
}

int smallestprime(int k){
    if(k%2==0)k--;
    else k-=2;
    int u=0;
    for(int i=k;i>=2;k=k-2){
        if(i%2==0)continue;
        for(int j=2;j<=appsqrt(k);j++){
            if(i%j==0){
                u=1;break;
            }
        }
        if(u==0)return i;
        u=0;
    }
    return 2;
}

void INSERTQP(int* ht, int k, int m, int c1,int c2){
    int h=k%m;
    long long cnt=0;
    long long ind;
    while(true){
        ind=(h+c1*cnt+c2*cnt*cnt)%m;
        if(ht[ind]==-1e9-10 || ht[ind]==-1e9){
            ht[ind]=k;
            break;
        }
        cnt++;
        if(cnt>=m)break;
    }
}

void INSERTDH(int* ht, int k, int m, int R){
    int h1=k%m;
    int h2=R-(k%R);
    long long cnt=0;
    long long ind;
    while(true){
        ind=(h1+cnt*h2)%m;
        if(ht[ind]==-1e9-10 || ht[ind]==-1e9){
            ht[ind]=k;
            break;
        }
        cnt++;
        if(cnt>=m)break;
    }
}

bool SEARCHQP(int* ht, int k, int m, int c1,int c2){
    int h=k%m;
    long long cnt=0;
    long long ind;
    while(true){
        ind=(h+c1*cnt+c2*cnt*cnt)%m;
        if(ht[ind]==k)return true;
        if(ht[ind]==-1e9-10){
            break;
        }
        cnt++;
        if(cnt>=m)break;
    }
    return false;
}

bool SEARCHDH(int* ht, int k, int m, int R){
    int h1=k%m;
    int h2=R-(k%R);
    long long cnt=0;
    long long ind;
    while(true){
        ind=(h1+cnt*h2)%m;
        if(ht[ind]==k)return true;
        if(ht[ind]==-1e9-10){
            break;
        }
        cnt++;
        if(cnt>=m)break;
    }
    return false;
}

void DELETEQP(int* ht, int k, int m, int c1,int c2){
    int h=k%m;
    long long cnt=0;
    long long ind;
    while(true){
        ind=(h+c1*cnt+c2*cnt*cnt)%m;
        if(ht[ind]==k){
            ht[ind]=-1e9;
            break;
        }
        cnt++;
        if(cnt>=m)break;
    }
}

void DELETEDH(int* ht, int k, int m, int R){
    int h1=k%m;
    int h2=R-(k%R);
    long long cnt=0;
    long long ind;
    while(true){
        ind=(h1+cnt*h2)%m;
        if(ht[ind]==k){
            ht[ind]=-1e9;
            break;
        }
        cnt++;
        if(cnt>=m)break;
    }
}

void PRINT(int* ht, int m){
    for(int i=0;i<m;i++){
        printf("%d ",i);
        if(ht[i]==-1e9 || ht[i]==-1e9-10){
            printf("()");
        }
        else{
            printf("(%d)",ht[i]);
        }
        printf("\n");
    }
}


int main(){
    char type;
    scanf("%c",&type);
    int m;
    scanf("%d",&m);
    int* ht=HASHTABLE(m);
    int c1,c2,R;
    if(type == 'a'){
        scanf("%d %d",&c1,&c2);
    }
    else{
        R=smallestprime(m);
    }
    char c='a';
    int k;
    bool ans;
    while(c!='t'){
        scanf("%c",&c);
        switch (c)
        {
        case 'i':
            scanf(" %d",&k);
            if(type=='a'){
                INSERTQP(ht, k ,m, c1, c2);
            }
            else{
                INSERTDH(ht, k, m, R);
            }
            break;
        case 's':
            scanf(" %d",&k);
            if(type=='a'){
                ans=SEARCHQP(ht, k ,m, c1, c2);
            }
            else{
                ans=SEARCHDH(ht, k, m, R);
            }
            if(ans)printf("%d\n",1);
            else printf("%d\n",-1);
            break;
        case 'd':
            scanf(" %d",&k);
            if(type=='a'){
                DELETEQP(ht, k ,m, c1, c2);
            }
            else{
                DELETEDH(ht, k, m, R);
            }
            break;
        case 'p':
            PRINT(ht, m);
            break;
        case 't':
            break;
        }
    }
    return 0;
}