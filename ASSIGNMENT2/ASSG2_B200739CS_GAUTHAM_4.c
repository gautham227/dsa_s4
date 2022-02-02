// made by gautham on 1st feb
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>

typedef char* stringg;

stringg* hashtable(){
    stringg* ht;
    ht=(stringg*)malloc(1000* sizeof(stringg));
    for(int i=0;i<1000;i++){
        ht[i]=(char*)malloc(10* sizeof(char));
    }
    for(int i=0;i<1000;i++){
        ht[i][0]='0';
    }
    return ht;
}

int generateno(char* s, int len, int cd){
    int cnt=0;
    int val=0;
    for(int i=0;i<3;i++){
        if(cnt>=len)break;
        val=val+s[cnt];
        cnt+=cd;
    }
    int hval=(val%26)%10;
    return hval;
}

void INSERTDATA(stringg* ht){
    char* name;
    name=(char*)malloc(10000*sizeof(char));
    scanf("%s",name);
    int len=strlen(name);
    // printf("%d\n",len);
    char* rollno;
    rollno=(char*)malloc(10*sizeof(char));
    rollno[0]=name[0];
    int c1,c2,c3;
    c1=generateno(name, len, 1);
    c2=generateno(name, len, 2);
    c3=generateno(name, len, 4);
    rollno[1]='0'+c1;
    rollno[2]='0'+c2;
    rollno[3]='0'+c3;
    int tabval=c1*100+c2*10+c3;
    ht[tabval]=name;
    return;
}

void SEARCH(stringg* ht){
    char roll[10];
    scanf("%s",&roll);
    int hval=(roll[1]-'0')*100+(roll[2]-'0')*10+(roll[3]-'0');
    if(strcmp(ht[hval],"0")==0){
        printf("NOT FOUND\n");
    }
    else{
        printf("%s\n",ht[hval]);
    }
    return;
}

void DELETE(stringg* ht){
    char roll[10];
    scanf("%s",&roll);
    int hval=(roll[1]-'0')*100+(roll[2]-'0')*10+(roll[3]-'0');
    strcpy(ht[hval], "0");
    return;
}

int main(){
    stringg* ht=hashtable();
    char c='a';
    while(c!='t'){
        scanf("%c ",&c);
        switch (c)
        {
        case 'i':
            INSERTDATA(ht);
            break;
        case 's':
            SEARCH(ht);
            break;
        case 'd':
            DELETE(ht);
        case 't':
            break;
        }
    }
}