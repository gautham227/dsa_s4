// made by gautham on 8th feb
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>

int strle(char* s){
    int i=0;
    while(s[i]!='\0'){
        i++;
    }
    return i;
}

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

long long po(int k){
    long long val=1;
    for(int i=0;i<k;i++){
        val=val*3;
    }
    return val;
}

void INSERTINTO(node* ht, int len){
    char* word;
    word=(char*)malloc(1000*sizeof(char));
    scanf("%s",word);
    node ne=CREATE_NODE(word);
    long long ind=0;
    for(int i=0;i<strle(word);i++){
        int x;
        if(word[i]>96){
            x=word[i]-96;
        }
        else{
            x=word[i]-64;
        }
        ind=ind+x*po(i);
    }
    ind=ind%len;
    if(ht[ind]->next==NULL && strcmp(ht[ind]->word,"-1")==0){
        ht[ind]=ne;
        return;
    }
    // bool x=LIST_SEARCH(ht[ind], word);
    node present=ht[ind];
    while(present->next!=NULL){
        present=present->next;
    }
    present->next=ne;
    return;
}

void DELETE(node* ht, int len){
    char* word;
    word=(char*)malloc(1000*sizeof(char));
    scanf("%s",word);
    long long ind=0;
    for(int i=0;i<strlen(word);i++){
        int x;
        if(word[i]>96){
            x=word[i]-96;
        }
        else{
            x=word[i]-64;
        }
        ind=ind+x*po(i);
    }
    ind=ind%len;
    node present;
    present=ht[ind];
    node last=NULL;
    if(strcmp(word,present->word)==0){
        if(present->next==NULL){
            strcpy(ht[ind]->word,"-1");
        }
        else{
            ht[ind]=present->next;
        }
        return;}
    while(present!=NULL){
        if(strcmp(word,present->word)==0){
            last->next=present->next;
            break;}
        last=present;
        present=present->next;}
    return;
}

int CHECK(node* ht, int len){
    for(int i=0;i<len;i++){
        if(ht[i]->next!=NULL){
            return -1;}
    }
    return 1;
}

int main(){
    int len;
    scanf("%d",&len);
    char c='a';
    node ht[len];
    for(int i=0;i<len;i++){
        node ptr;
        ptr=(node)malloc(sizeof(struct nod));
        ptr->word=(char*)malloc(1000* sizeof(char));
        ptr->next=NULL;
        strcpy(ptr->word,"-1");
        ht[i]=ptr;
    }
    while(c!='t'){
        scanf("%c",&c);
        switch (c)
        {
        case 'i':
            INSERTINTO(ht,len);
            break;
        case 'd':
            DELETE(ht, len);
            break;
        case 'p':
            int ans=CHECK(ht,len);
            if(ans==1){
                printf("1\n");}
            else{
                printf("-1\n");}
            break;}
    }
    return 0;
}