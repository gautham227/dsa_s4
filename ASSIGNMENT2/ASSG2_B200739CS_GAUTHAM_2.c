// made by gautham on 23rd jan
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>

struct nod{
    char* word;
    struct nod* next;
};

typedef struct nod* node;

node CREATE_NODE(char* k){
    node ne;
    ne=(node)malloc(sizeof(node));
    ne->word=k;
    ne->next=NULL;
    return ne;
}

bool LIST_SEARCH(node head,char* k){
    node present;
    present=head;
    while(present!=NULL){
        if(strcmp(k,present->word)==0){
            return true;
            break;
        }
        present=present->next;
    }
    return false;
}

void INSERT(node* ht, char* word, int len, int k){
    node ne=CREATE_NODE(word);
    int ind=(len*len)%k;
    if(ht[ind]->next==NULL && ht[ind]->word=="-1"){
        ht[ind]=ne;
        return;
    }
    bool x=LIST_SEARCH(ht[ind], word);
    if(x)return;
    node present=ht[ind];
    while(present->next!=NULL){
        present=present->next;
    }
    present->next=ne;
    return;
}

void PRINT(node* ht, int len){
    for(int i=0;i<len;i++){
        printf("%d:",i);
        if(ht[i]->word=="-1"){
            printf("null\n");
            continue;
        }
        node pre=ht[i];
        while(pre!=NULL){
            printf("%s",pre->word);
            pre=pre->next;
            if(pre!=NULL){
                printf("-");
            }
        }
        printf("\n");
    }
}

int main(){
    int len;
    scanf("%d",&len);
    char u;
    scanf("%c",&u);
    node ht[len];
    for(int i=0;i<len;i++){
        node ptr;
        ptr=(node)malloc(sizeof(struct nod));
        ptr->next=NULL;
        ptr->word="-1";
        ht[i]=ptr;
    }
    char s[510];
    fgets(s,510,stdin);
    int cnt=0;
    while(true){
        char* s1;
        s1=(char*)malloc(sizeof(char)*510);
        int ind=0;
        while(s[cnt]!=' ' && s[cnt]!='\n' && s[cnt]!='\0'){
            s1[ind]=s[cnt];
            ind++;
            cnt++;
        }
        INSERT(ht,s1,ind,len);
        if(s[cnt]=='\n' || s[cnt]=='\0'){
            break;
        }
        cnt++;
    }
    PRINT(ht,len);
    return 0;
}