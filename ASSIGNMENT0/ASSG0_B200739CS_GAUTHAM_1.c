// made by gautham on 31st dec
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>

struct stac{
    int* arr;
    int top;
    int size;
};
typedef struct stac* stack;

bool ISEMPTY(stack s){
    if(s->top==-1){
        return true;
    }
    return false;
}

bool ISFULL(stack s){
    if(s->top==s->size-1){
        return true;
    }
    return false;
}

void PUSH(stack s){
    if(ISFULL(s)){
        printf("1\n");
        int * list;
        list=(int*)malloc(2*(s->size));
        for(int i=0;i<s->size;i++){
            list[i]=s->arr[i];
        }
        s->arr=list;
        s->size=2*(s->size);
    }
    int k;
    scanf("%d",&k);
    s->arr[s->top+1]=k;
    s->top++;
}

void POP(stack s){
    if(ISEMPTY(s)){
        printf("-1\n");
        return;
    }
    printf("%d\n",s->arr[s->top]);
    s->top--;
}

int main(){
    int n;
    scanf("%d",&n);
    stack s;
    s=(stack)malloc(sizeof(struct stac));
    s->arr=(int*)malloc(n*sizeof(int));
    s->size=n;
    s->top=-1;
    char c='a';
    while(c!='t'){
        scanf("%c",&c);
        switch (c)
        {
        case 'i':
            PUSH(s);
            break;
        case 'd':
            POP(s);
            break;
        case 't':
            break;
        }
    }
    return 0;
}