// made by gautham on 31st dec
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>

struct queu
{
    int* arr;
    int size;
    int tail;
    int front;
};
typedef struct queu* queue;

bool ISFULL(queue q){
    if(q->tail==q->size-1 || q->size==0){
        return true;
    }
    return false;
}

bool ISEMPTY(queue q){
    if(q->front==-1 || q->front>q->tail){
        return true;
    }
    return false;
}

void ENQUEUE(queue q){
    int k;
    scanf(" %d", &k);
    if(ISFULL(q)){
        printf("1\n");
        return;
    }
    q->tail++;
    q->arr[q->tail]=k;
    if(q->front==-1){
        q->front++;
    }
}

void DEQUEUE(queue q){
    if(ISEMPTY(q)){
        printf("1\n");
        return;
    }
    printf("%d\n",q->arr[q->front]);
    q->front++;
}

int main(){
    int n;
    scanf("%d",&n);
    queue q;
    q=(queue)malloc(sizeof(struct queu));
    q->arr=(int*)malloc(n*sizeof(int));
    q->size=n;
    q->front=-1;
    q->tail=-1;
    char c='a';
    bool x;
    while(c!='t'){
        scanf("%c",&c);
        switch (c)
        {
        case 'i':
            ENQUEUE(q);
            break;
        case 'd':
            DEQUEUE(q);
            break;
        case 'e':
            x=ISEMPTY(q);
            if(x){
                printf("1\n");
            }
            else{
                printf("-1\n");
            }
            break;
        case 'f':
            x=ISFULL(q);
            if(x){
                printf("1\n");
            }
            else{
                printf("-1\n");
            }
            break;
        case 't':
            break;
        }
    }
    return 0;
}