#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<conio.h>
#include <time.h>
#include<ctype.h>
#include<io.h>
#include<malloc.h>

char stations[34][16]={"Ariyalur","Chengalpattu","Chennai\t","Coimbatore","Cuddalore","Dharmapuri","Dindigul","Erode\t","Kanchipuram","Kanyakumari","Karur\t","Krishnagiri","Madurai\t","Mayiladuthurai","Nagapattinam","Namakkal","Nilgiris","Pudukkottai","Ramanathapuram","Salem\t","Sivaganga","Tenkasi\t","Thanjavur","Theni\t","Thiruvannamalai","Thiruvarur","Thoothukudi","Tiruchirappalli","Tirunelveli","Tiruppur","Tiruvallur","Vellore\t","Viluppuram","Virudhunagar"};
long long int  cPNR;
int check=0;

struct passenger{
    long long int PNR;
    int train_no;
    int cmpt;
    int frto[2];
    char status;
    int seatno;
};

struct route{
    int data;
    int time[2];
    struct route *next;
};

struct waitlist{
    char p_user[20];
    long long int PNR;
    struct waitlist *next;
};

struct train{
    struct route *rt;
    char name[50];
    int train_no;
    int frto[2];
    int noac1,noac2,nnac1,nnac2,nw;
    struct waitlist *wt;
}trains[12];

void login();
void mainmenu(char user[20],char pw[20]);
void signup();
void shutdown();
void startup();
int* search(char user[20],char pw[20],int c);
void database();
void new_waitlist(struct passenger);
void cancelbooking(char user[20],char pw[20]);
void newbooking(char user[20],char pw[20]);
void check_upcoming(char user[20],char pw[20]);
void check_waitlist(char user[20],char pw[20]);

void delay(int number_of_seconds){
    int milli_seconds = 1000 * number_of_seconds;
    clock_t start_time = clock();
    while(clock() < start_time + milli_seconds) ;
}

int cfileexists(const char * filename){
    /* try to open file to read */
    FILE *file;
    if (file = fopen(filename, "r")){
        fclose(file);
        return 1;
    }
    return 0;
}

void newdir(){
    int check;
    char* dirname = "railway dbs";
    system("cls");
    check = mkdir(dirname);
    // check if directory is created or not
    if (!check){
        FILE *file;
        mkdir("./railway dbs/trains");
        file = fopen("./railway dbs/trains/PNRdata.txt","w");
        cPNR=1000000000;
        fprintf(file,"%lld",cPNR);
        fclose(file);
        file = fopen("./railway dbs/trains/t0.txt","w");
        fprintf(file,"%d %d %d %d %d\n",trains[0].noac1,trains[0].noac2,trains[0].nnac1,trains[0].nnac2,trains[0].nw);
        fclose(file);
        file = fopen("./railway dbs/trains/t1.txt","w");
        fprintf(file,"%d %d %d %d %d\n",trains[1].noac1,trains[1].noac2,trains[1].nnac1,trains[1].nnac2,trains[1].nw);
        fclose(file);
        file = fopen("./railway dbs/trains/t2.txt","w");
        fprintf(file,"%d %d %d %d %d\n",trains[2].noac1,trains[2].noac2,trains[2].nnac1,trains[2].nnac2,trains[2].nw);
        fclose(file);
        file = fopen("./railway dbs/trains/t3.txt","w");
        fprintf(file,"%d %d %d %d %d\n",trains[3].noac1,trains[3].noac2,trains[3].nnac1,trains[3].nnac2,trains[3].nw);
        fclose(file);
        file = fopen("./railway dbs/trains/t4.txt","w");
        fprintf(file,"%d %d %d %d %d\n",trains[4].noac1,trains[4].noac2,trains[4].nnac1,trains[4].nnac2,trains[4].nw);
        fclose(file);
        file = fopen("./railway dbs/trains/t5.txt","w");
        fprintf(file,"%d %d %d %d %d\n",trains[5].noac1,trains[5].noac2,trains[5].nnac1,trains[5].nnac2,trains[5].nw);
        fclose(file);
        file = fopen("./railway dbs/trains/t6.txt","w");
        fprintf(file,"%d %d %d %d %d\n",trains[6].noac1,trains[6].noac2,trains[6].nnac1,trains[6].nnac2,trains[6].nw);
        fclose(file);
        file = fopen("./railway dbs/trains/t7.txt","w");
        fprintf(file,"%d %d %d %d %d\n",trains[7].noac1,trains[7].noac2,trains[7].nnac1,trains[7].nnac2,trains[7].nw);
        fclose(file);
        file = fopen("./railway dbs/trains/t8.txt","w");
        fprintf(file,"%d %d %d %d %d\n",trains[8].noac1,trains[8].noac2,trains[8].nnac1,trains[8].nnac2,trains[8].nw);
        fclose(file);
        file = fopen("./railway dbs/trains/t9.txt","w");
        fprintf(file,"%d %d %d %d %d\n",trains[9].noac1,trains[9].noac2,trains[9].nnac1,trains[9].nnac2,trains[9].nw);
        fclose(file);
        file = fopen("./railway dbs/trains/t10.txt","w");
        fprintf(file,"%d %d %d %d %d\n",trains[10].noac1,trains[10].noac2,trains[10].nnac1,trains[10].nnac2,trains[10].nw);
        fclose(file);
        file = fopen("./railway dbs/trains/t11.txt","w");
        fprintf(file,"%d %d %d %d %d\n",trains[11].noac1,trains[11].noac2,trains[11].nnac1,trains[11].nnac2,trains[11].nw);
        fclose(file);
        printf("Directory created\n");
    }
    else{
        FILE *file;
        struct waitlist *t1,*t2;
        int k=0;
        file = fopen("./railway dbs/trains/PNRdata.txt","r");
        fscanf(file,"%lld",&cPNR);
        fclose(file);
        file = fopen("./railway dbs/trains/t0.txt","r");
        fscanf(file,"%d %d %d %d %d",&trains[0].noac1,&trains[0].noac2,&trains[0].nnac1,&trains[0].nnac2,&trains[0].nw);
        k=0;
        while(k<trains[0].nw)
        {
            t1=(struct waitlist*)malloc(sizeof(struct waitlist));
            fscanf(file,"%s %lld",&t1->p_user,&t1->PNR);
            if(k==0)
                trains[0].wt=t1;
            else
                t2->next=t1;
            t2=t1;
            k++;
        }
        t2->next=NULL;
        fclose(file);
        file = fopen("./railway dbs/trains/t1.txt","r");
        fscanf(file,"%d %d %d %d %d",&trains[1].noac1,&trains[1].noac2,&trains[1].nnac1,&trains[1].nnac2,&trains[1].nw);
        k=0;
        while(k<trains[1].nw)
        {
            t1=(struct waitlist*)malloc(sizeof(struct waitlist));
            fscanf(file,"%s %lld",&t1->p_user,&t1->PNR);
            if(k==0)
                trains[1].wt=t1;
            else
                t2->next=t1;
            t2=t1;
            k++;
        }
        t2->next=NULL;
        fclose(file);
        file = fopen("./railway dbs/trains/t2.txt","r");
        fscanf(file,"%d %d %d %d %d",&trains[2].noac1,&trains[2].noac2,&trains[2].nnac1,&trains[2].nnac2,&trains[2].nw);
        k=0;
        while(k<trains[2].nw)
        {
            t1=(struct waitlist*)malloc(sizeof(struct waitlist));
            fscanf(file,"%s %lld",&t1->p_user,&t1->PNR);
            if(k==0)
                trains[2].wt=t1;
            else
                t2->next=t1;
            t2=t1;
            k++;
        }
        t2->next=NULL;
        fclose(file);
        file = fopen("./railway dbs/trains/t3.txt","r");
        fscanf(file,"%d %d %d %d %d",&trains[3].noac1,&trains[3].noac2,&trains[3].nnac1,&trains[3].nnac2,&trains[3].nw);
        k=0;
        while(k<trains[3].nw)
        {
            t1=(struct waitlist*)malloc(sizeof(struct waitlist));
            fscanf(file,"%s %lld",&t1->p_user,&t1->PNR);
            if(k==0)
                trains[3].wt=t1;
            else
                t2->next=t1;
            t2=t1;
            k++;
        }
        t2->next=NULL;
        fclose(file);
        file = fopen("./railway dbs/trains/t4.txt","r");
        fscanf(file,"%d %d %d %d %d",&trains[4].noac1,&trains[4].noac2,&trains[4].nnac1,&trains[4].nnac2,&trains[4].nw);
        k=0;
        while(k<trains[4].nw)
        {
            t1=(struct waitlist*)malloc(sizeof(struct waitlist));
            fscanf(file,"%s %lld",&t1->p_user,&t1->PNR);
            if(k==0)
                trains[4].wt=t1;
            else
                t2->next=t1;
            t2=t1;
            k++;
        }
        t2->next=NULL;
        fclose(file);
        file = fopen("./railway dbs/trains/t5.txt","r");
        fscanf(file,"%d %d %d %d %d",&trains[5].noac1,&trains[5].noac2,&trains[5].nnac1,&trains[5].nnac2,&trains[5].nw);
        k=0;
        while(k<trains[5].nw)
        {
            t1=(struct waitlist*)malloc(sizeof(struct waitlist));
            fscanf(file,"%s %lld",&t1->p_user,&t1->PNR);
            if(k==0)
                trains[5].wt=t1;
            else
                t2->next=t1;
            t2=t1;
            k++;
        }
        t2->next=NULL;
        fclose(file);
        file = fopen("./railway dbs/trains/t6.txt","r");
        fscanf(file,"%d %d %d %d %d",&trains[6].noac1,&trains[6].noac2,&trains[6].nnac1,&trains[6].nnac2,&trains[6].nw);
        k=0;
        while(k<trains[6].nw)
        {
            t1=(struct waitlist*)malloc(sizeof(struct waitlist));
            fscanf(file,"%s %lld",&t1->p_user,&t1->PNR);
            if(k==0)
                trains[6].wt=t1;
            else
                t2->next=t1;
            t2=t1;
            k++;
        }
        t2->next=NULL;
        fclose(file);
        file = fopen("./railway dbs/trains/t7.txt","r");
        fscanf(file,"%d %d %d %d %d",&trains[7].noac1,&trains[7].noac2,&trains[7].nnac1,&trains[7].nnac2,&trains[7].nw);
        k=0;
        while(k<trains[7].nw)
        {
            t1=(struct waitlist*)malloc(sizeof(struct waitlist));
            fscanf(file,"%s %lld",&t1->p_user,&t1->PNR);
            if(k==0)
                trains[7].wt=t1;
            else
                t2->next=t1;
            t2=t1;
            k++;
        }
        t2->next=NULL;
        fclose(file);
        file = fopen("./railway dbs/trains/t8.txt","r");
        fscanf(file,"%d %d %d %d %d",&trains[8].noac1,&trains[8].noac2,&trains[8].nnac1,&trains[8].nnac2,&trains[8].nw);
        k=0;
        while(k<trains[8].nw)
        {
            t1=(struct waitlist*)malloc(sizeof(struct waitlist));
            fscanf(file,"%s %lld",&t1->p_user,&t1->PNR);
            if(k==0)
                trains[8].wt=t1;
            else
                t2->next=t1;
            t2=t1;
            k++;
        }
        t2->next=NULL;
        fclose(file);
        file = fopen("./railway dbs/trains/t9.txt","r");
        fscanf(file,"%d %d %d %d %d",&trains[9].noac1,&trains[9].noac2,&trains[9].nnac1,&trains[9].nnac2,&trains[9].nw);
        k=0;
        while(k<trains[9].nw)
        {
            t1=(struct waitlist*)malloc(sizeof(struct waitlist));
            fscanf(file,"%s %lld",&t1->p_user,&t1->PNR);
            if(k==0)
                trains[9].wt=t1;
            else
                t2->next=t1;
            t2=t1;
            k++;
        }
        t2->next=NULL;
        fclose(file);
        file = fopen("./railway dbs/trains/t10.txt","r");
        fscanf(file,"%d %d %d %d %d",&trains[10].noac1,&trains[10].noac2,&trains[10].nnac1,&trains[10].nnac2,&trains[10].nw);
        k=0;
        while(k<trains[10].nw)
        {
            t1=(struct waitlist*)malloc(sizeof(struct waitlist));
            fscanf(file,"%s %lld",&t1->p_user,&t1->PNR);
            if(k==0)
                trains[10].wt=t1;
            else
                t2->next=t1;
            t2=t1;
            k++;
        }
        t2->next=NULL;
        fclose(file);
        file = fopen("./railway dbs/trains/t11.txt","r");
        fscanf(file,"%d %d %d %d %d",&trains[11].noac1,&trains[11].noac2,&trains[11].nnac1,&trains[11].nnac2,&trains[11].nw);
        k=0;
        while(k<trains[11].nw)
        {
            t1=(struct waitlist*)malloc(sizeof(struct waitlist));
            fscanf(file,"%s %lld",&t1->p_user,&t1->PNR);
            if(k==0)
                trains[11].wt=t1;
            else
                t2->next=t1;
            t2=t1;
            k++;
        }
        t2->next=NULL;
        fclose(file);
    }
    system("dir/p");
}

void display_stations(){
    printf("\n\t\t 1.Ariyalur\t\t18.Pudukkottai");
    printf("\n\t\t 2.Chengalpattu\t\t19.Ramanathapuram");
    printf("\n\t\t 3.Chennai\t\t20.Salem");
    printf("\n\t\t 4.Coimbatore\t\t21.Sivaganga");
    printf("\n\t\t 5.Cuddalore\t\t22.Tenkasi");
    printf("\n\t\t 6.Dharmapuri\t\t23.Thanjavur");
    printf("\n\t\t 7.Dindigul\t\t24.Theni");
    printf("\n\t\t 8.Erode\t\t25.Thiruvannamalai");
    printf("\n\t\t 9.Kanchipuram\t\t26.Thiruvarur");
    printf("\n\t\t 10.Kanyakumari\t\t27.Thoothukudi");
    printf("\n\t\t 11.Karur\t\t28.Tiruchirappalli");
    printf("\n\t\t 12.Krishnagiri\t\t29.Tirunelveli");
    printf("\n\t\t 13.Madurai\t\t30.Tiruppur");
    printf("\n\t\t 14.Mayiladuthurai\t31.Tiruvallur");
    printf("\n\t\t 15.Nagapattinam\t32.Vellore");
    printf("\n\t\t 16.Namakkal\t\t33.Viluppuram");
    printf("\n\t\t 17.Nilgiris\t\t34.Virudhunagar\n");
}

int* search_trains(int origin,int dest,int *n){
    int i,chk,j=0;
    int *lst=malloc(12*sizeof(int));
    struct route *t;
    for(i=0;i<12;i++){
        chk=0;
        t=trains[i].rt;
        while(t!=NULL){
            if(t->data==origin)
              chk++;
            else if(t->data==dest && chk==1){
                chk++;
                *(lst+j)=i;
                j++;
                break;
            }
            t=t->next;
        }
    }
    *n=j;
    return lst;
}

void display_route(int n){
    struct route *t=trains[n].rt;
    while(t!=NULL){
        printf("\n\t\t%s\t\t%d:%d",stations[t->data],t->time[0],t->time[1]);
        t=t->next;
    }
}

void display_train(int n){
    printf("%s",trains[n].name);
    printf("\n\t\t     Train No : %d",trains[n].train_no);
    printf("\n\t\t     From : %s",stations[trains[n].frto[0]]);
    printf("\n\t\t     To   : %s",stations[trains[n].frto[1]]);
}

int main(){
    database();
    newdir();
    startup();
}

void login(){
    char user[20],pw[20],c,num[20];
    char dir[100]="./railway dbs/";
    int len,ch,i;
    FILE *fptr;
    redouser:
    strcpy(dir,"./railway dbs/");
    ch=0;
    system("cls");
    printf("\n\t\t __________________________");
    printf("\n\t\t|\t\t\t   |");
    printf("\n\t\t|\t LOGIN\t    \t   |");
    printf("\n\t\t|__________________________|");
    printf("\n\n\t\tUSERNAME : ");
    scanf("\n");
    scanf("%[^\n]%*c",user);
    len=strlen(user);
    if(len>16 || len<6)
    {
        printf("\n\t\tWARNING : Username does not follow conditions. Retry.");
        delay(1);
        goto redouser;
    }
    for(i=0;i<len;i++)
    {
        if(isalnum(user[i])==0)
            ch++;
    }
    if(ch!=0)
    {
        printf("\n\t\tWARNING : Username does not follow conditions. Retry.");
        delay(1);
        goto redouser;
    }
    strcat(dir,user);
    strcat(dir,".txt");
    if(cfileexists(dir)==0)
    {
        printf("\n\t\tWARNING : Username does not exists. Retry.");
        delay(1);
        goto redouser;
    }
    printf("\t\tPASSWORD : ");
    i=0;
    do{
        pw[i]=getch();
        if(pw[i]!='\r' && pw[i]!='\b'){
            printf("*");
        }
        if(pw[i]=='\b' &&  i>0)
        {
            printf("\b \b");
            i--;
        }
        else
         i++;
        if(i>16)
        {
            printf("\n\t\tWARNING : Exceeded 16 characters. Retry.");
            delay(1);
            goto redouser;
        }
        else if(i==1 && pw[i-1]=='\r')
        {
            printf("\n\t\tWARNING : Enter minimum of 8 characters. Retry.");
            delay(1);
            goto redouser;
        }
        if(pw[i-1]==' ')
        {
            printf("\n\t\tWARNING : Password should not contain <space>. Retry.");
            delay(1);
            goto redouser;
        }
    }while(pw[i-1]!='\r');
    pw[i-1]='\0';
    if(strlen(pw)<8)
    {
        printf("\n\t\tWARNING : Enter minimum of 8 characters. Retry.");
        delay(1);
        goto redouser;
    }
    printf("\n\n\t\tCONFIRM USERNAME & PASSWORD? (press Y to confirm. any other key to exit.) ");
    c=getch();
    if(c!='Y' && c!='y'){
        printf("\n\t\tMESSAGE : Returning to MENU.");
        delay(1);
        startup();
    }
    else
    {
        fptr = fopen(dir, "r");
        if(fptr == NULL)
        {
            printf("\n\n\t\tUnable to Login. Returning to Homepage");
            startup();
        }
        fscanf(fptr,"%s", &num);
        delay(1);
        if(strcmp(num,pw)!=0)
        {
            printf("\n\t\tWARNING : Wrong password. Retry.");
            delay(1);
            goto redouser;
        }
        fclose(fptr);
        system("cls");
        printf("\n\t\t ____________________________");
        printf("\n\t\t|\t\t\t     |");
        printf("\n\t\t|\t LOGGING IN\t     |");
        printf("\n\t\t|____________________________|");
        delay(1);
        mainmenu(user,pw);
    }
}

void mainmenu(char user[20],char pw[20]){
    char choice;
    check=0;
    retry:
    system("cls");
    printf("\n\t\t WELCOME, %s.\n",user);
    printf("\n\t\t ________________________________________________");
    printf("\n\t\t|\t\t\t\t\t\t |");
    printf("\n\t\t|\t\t\t\t\t\t |");
    printf("\n\t\t|\t CHOOSE WHAT TO DO\t\t\t |");
    printf("\n\t\t|\t _______________________________\t |");
    printf("\n\t\t|\t|\t\t\t\t|\t |");
    printf("\n\t\t|\t| 1. Book new tickets\t\t|\t |");
    printf("\n\t\t|\t| 2. Cancel booked trips\t|\t |");
    printf("\n\t\t|\t| 3. Check upcoming travels\t|\t |");
    printf("\n\t\t|\t| 4. Check waitlist\t\t|\t |");
    printf("\n\t\t|\t| 5. Logout\t\t        |\t |");
    printf("\n\t\t|\t|_______________________________|\t |");
    printf("\n\t\t|\t\t\t\t\t\t |");
    printf("\n\t\t|________________________________________________|");
    choice=getch();
    switch(choice)
    {
        case '1':
            newbooking(user,pw);
            break;
        case '2':
            cancelbooking(user,pw);
            break;
        case '3':
            check_upcoming(user,pw);
            break;
        case '4':
            check_waitlist(user,pw);
            break;
        case '5':
            startup();
            break;
        default:
            printf("\n\n\t\tWARNING : INVALID INPUT. TRY AGAIN.");
            delay(1);
            goto retry;
            break;
    }
}

void signup(){
    char user[20],pw[20],c;
    char dir[100]="./railway dbs/";
    int len,ch,i;
    FILE *fptr;
    redouser:
    strcpy(dir,"./railway dbs/");
    ch=0;
    system("cls");
    printf("\n\t\t __________________________");
    printf("\n\t\t|\t\t\t   |");
    printf("\n\t\t|\t SIGN UP\t   |");
    printf("\n\t\t|__________________________|");
    printf("\n\n\t\tNOTE : Username should consist of 6-16 characters\n\t\t [Only numbers and alphabets without space]");
    printf("\n\n\t\tUSERNAME : ");
    scanf("\n");
    scanf("%[^\n]%*c",user);
    len=strlen(user);
    if(len>16 || len<6)
    {
        printf("\n\t\tWARNING : Username does not follow conditions. Retry.");
        delay(1);
        goto redouser;
    }
    for(i=0;i<len;i++)
    {
        if(isalnum(user[i])==0)
            ch++;
    }
    if(ch!=0)
    {
        printf("\n\t\tWARNING : Username does not follow conditions. Retry.");
        delay(1);
        goto redouser;
    }
    strcat(dir,user);
    strcat(dir,".txt");
    if(cfileexists(dir)==1)
    {
        printf("\n\t\tWARNING : Username already exists. Retry.");
        delay(1);
        goto redouser;
    }
    printf("\t\tPASSWORD : ");
    i=0;
    do{
        pw[i]=getch();
        if(pw[i]!='\r' && pw[i]!='\b'){
            printf("*");
        }
        if(pw[i]=='\b' &&  i>0)
        {
            printf("\b \b");
            i--;
        }
        else
         i++;
        if(i>16)
        {
            printf("\n\t\tWARNING : Exceeded 16 characters. Retry.");
            delay(1);
            goto redouser;
        }
        else if(i==1 && pw[i-1]=='\r')
        {
            printf("\n\t\tWARNING : Enter minimum of 8 characters. Retry.");
            delay(1);
            goto redouser;
        }
        if(pw[i-1]==' ')
        {
            printf("\n\t\tWARNING : Password should not contain <space>. Retry.");
            delay(1);
            goto redouser;
        }
    }while(pw[i-1]!='\r');
    pw[i-1]='\0';
    if(strlen(pw)<8)
    {
        printf("\n\t\tWARNING : Enter minimum of 8 characters. Retry.");
        delay(1);
        goto redouser;
    }
    printf("\n\n\t\tCONFIRM USERNAME & PASSWORD? (press Y to confirm. any other key to exit.) ");
    c=getch();
    if(c!='Y' && c!='y'){
        printf("\n\t\tMESSAGE : Returning to MENU.");
        delay(1);
        startup();
    }
    else
    {
        fptr = fopen(dir, "w");
        if(fptr == NULL)
        {
            printf("\n\n\t\tUnable to create account. Returning to Homepage");
            startup();
        }
        fputs(pw, fptr);
        fclose(fptr);
        system("cls");
        printf("\n\t\t ____________________________");
        printf("\n\t\t|\t\t\t     |");
        printf("\n\t\t|\t THANK YOU FOR\t     |");
        printf("\n\t\t|\t  SIGNING UP\t     |");
        printf("\n\t\t|____________________________|");
        delay(1);
        mainmenu(user,pw);
    }
}

void shutdown(){
    FILE *file;
    struct waitlist *t;
    file = fopen("./railway dbs/trains/PNRdata.txt","w");
    fprintf(file,"%lld",cPNR);
    fclose(file);
    file = fopen("./railway dbs/trains/t0.txt","w");
    fprintf(file,"%d %d %d %d %d\n",trains[0].noac1,trains[0].noac2,trains[0].nnac1,trains[0].nnac2,trains[0].nw);
    t=trains[0].wt;
    while(t!=NULL)
    {
        fprintf(file,"%s %lld\n",t->p_user,t->PNR);
        t=t->next;
    }
    fclose(file);
    file = fopen("./railway dbs/trains/t1.txt","w");
    fprintf(file,"%d %d %d %d %d\n",trains[1].noac1,trains[1].noac2,trains[1].nnac1,trains[1].nnac2,trains[1].nw);
    t=trains[1].wt;
    while(t!=NULL)
    {
        fprintf(file,"%s %lld\n",t->p_user,t->PNR);
        t=t->next;
    }
    fclose(file);
    file = fopen("./railway dbs/trains/t2.txt","w");
    fprintf(file,"%d %d %d %d %d\n",trains[2].noac1,trains[2].noac2,trains[2].nnac1,trains[2].nnac2,trains[2].nw);
    t=trains[2].wt;
    while(t!=NULL)
    {
        fprintf(file,"%s %lld\n",t->p_user,t->PNR);
        t=t->next;
    }
    fclose(file);
    file = fopen("./railway dbs/trains/t3.txt","w");
    fprintf(file,"%d %d %d %d %d\n",trains[3].noac1,trains[3].noac2,trains[3].nnac1,trains[3].nnac2,trains[3].nw);
    t=trains[3].wt;
    while(t!=NULL)
    {
        fprintf(file,"%s %lld\n",t->p_user,t->PNR);
        t=t->next;
    }
    fclose(file);
    file = fopen("./railway dbs/trains/t4.txt","w");
    fprintf(file,"%d %d %d %d %d\n",trains[4].noac1,trains[4].noac2,trains[4].nnac1,trains[4].nnac2,trains[4].nw);
    t=trains[4].wt;
    while(t!=NULL)
    {
        fprintf(file,"%s %lld\n",t->p_user,t->PNR);
        t=t->next;
    }
    fclose(file);
    file = fopen("./railway dbs/trains/t5.txt","w");
    fprintf(file,"%d %d %d %d %d\n",trains[5].noac1,trains[5].noac2,trains[5].nnac1,trains[5].nnac2,trains[5].nw);
    t=trains[5].wt;
    while(t!=NULL)
    {
        fprintf(file,"%s %lld\n",t->p_user,t->PNR);
        t=t->next;
    }
    fclose(file);
    file = fopen("./railway dbs/trains/t6.txt","w");
    fprintf(file,"%d %d %d %d %d\n",trains[6].noac1,trains[6].noac2,trains[6].nnac1,trains[6].nnac2,trains[6].nw);
    t=trains[6].wt;
    while(t!=NULL)
    {
        fprintf(file,"%s %lld\n",t->p_user,t->PNR);
        t=t->next;
    }
    fclose(file);
    file = fopen("./railway dbs/trains/t7.txt","w");
    fprintf(file,"%d %d %d %d %d\n",trains[7].noac1,trains[7].noac2,trains[7].nnac1,trains[7].nnac2,trains[7].nw);
    t=trains[7].wt;
    while(t!=NULL)
    {
        fprintf(file,"%s %lld\n",t->p_user,t->PNR);
        t=t->next;
    }
    fclose(file);
    file = fopen("./railway dbs/trains/t8.txt","w");
    fprintf(file,"%d %d %d %d %d\n",trains[8].noac1,trains[8].noac2,trains[8].nnac1,trains[8].nnac2,trains[8].nw);
    t=trains[8].wt;
    while(t!=NULL)
    {
        fprintf(file,"%s %lld\n",t->p_user,t->PNR);
        t=t->next;
    }
    fclose(file);
    file = fopen("./railway dbs/trains/t9.txt","w");
    fprintf(file,"%d %d %d %d %d\n",trains[9].noac1,trains[9].noac2,trains[9].nnac1,trains[9].nnac2,trains[9].nw);
    t=trains[9].wt;
    while(t!=NULL)
    {
        fprintf(file,"%s %lld\n",t->p_user,t->PNR);
        t=t->next;
    }
    fclose(file);
    file = fopen("./railway dbs/trains/t10.txt","w");
    fprintf(file,"%d %d %d %d %d\n",trains[10].noac1,trains[10].noac2,trains[10].nnac1,trains[10].nnac2,trains[10].nw);
    t=trains[10].wt;
    while(t!=NULL)
    {
        fprintf(file,"%s %lld\n",t->p_user,t->PNR);
        t=t->next;
    }
    fclose(file);
    file = fopen("./railway dbs/trains/t11.txt","w");
    fprintf(file,"%d %d %d %d %d\n",trains[11].noac1,trains[11].noac2,trains[11].nnac1,trains[11].nnac2,trains[11].nw);
    t=trains[11].wt;
    while(t!=NULL)
    {
        fprintf(file,"%s %lld\n",t->p_user,t->PNR);
        t=t->next;
    }
    fclose(file);
    system("cls");
    printf("\n\t\t ____________________________");
    printf("\n\t\t|\t\t\t     |");
    printf("\n\t\t|\t THANK YOU FOR\t     |");
    printf("\n\t\t|\tUSING OUR SERVICE    |");
    printf("\n\t\t|____________________________|");
}

void startup(){
    char choice;
    system("cls");
    system("color F0");
    printf("\n\t\t ________________________________________________");
    printf("\n\t\t|\t\t\t\t\t\t |");
    printf("\n\t\t|\t\t\t\t\t\t |");
    printf("\n\t\t|\t\t\t\t\t\t |");
    printf("\n\t\t|\t\t\t\t\t\t |");
    printf("\n\t\t|\t   WELCOME TO TN RAILWAY SERVICE\t |");
    printf("\n\t\t|\t\t\t\t\t\t |");
    printf("\n\t\t|\t\t\t\t\t\t |");
    printf("\n\t\t|\t\t\t\t\t\t |");
    printf("\n\t\t|\t Here, you can book tickets for your\t |");
    printf("\n\t\t|\t next journey without worrying about     |");
    printf("\n\t\t|\t safety and security. The data about     |");
    printf("\n\t\t|\t your travels are secured in your        |");
    printf("\n\t\t|\t personal Railway Passenger account      |");
    printf("\n\t\t|\t\t\t\t\t\t |");
    printf("\n\t\t|\t\t\t\t\t\t |");
    printf("\n\t\t|\t\t\t\t\t\t |");
    printf("\n\t\t|________________________________________________|");
    printf("\n\n\t\tPress any to continue...... "); getch();
    redo:
    system("cls");
    printf("\n\t\t ________________________________________________");
    printf("\n\t\t|\t\t\t\t\t\t |");
    printf("\n\t\t|\t\t\t\t\t\t |");
    printf("\n\t\t|\t CHOOSE YOUR OPTION\t\t\t |");
    printf("\n\t\t|\t _______________________________\t |");
    printf("\n\t\t|\t|\t\t\t\t|\t |");
    printf("\n\t\t|\t| 1. Login to Existing Account\t|\t |");
    printf("\n\t\t|\t| 2. Create New Account\t        |\t |");
    printf("\n\t\t|\t| 3. Exit\t                |\t |");
    printf("\n\t\t|\t|_______________________________|\t |");
    printf("\n\t\t|\t\t\t\t\t\t |");
    printf("\n\t\t|________________________________________________|");
    choice=getch();
    if(choice!='1'&&choice!='2'&&choice!='3')
    {
        printf("\n\t\tWarning : INVALID INPUT. TRY AGAIN\n");
        delay(1);
        goto redo;
    }
    else
    {
        if(choice=='1')
            login();
        else if(choice=='2')
            signup();
        else if(choice=='3')
            shutdown();
    }
}

int* search(char user[20],char pw[20],int c){
    int choice,origin,dest,n_trains,i,*lst,*index=malloc(3*sizeof(int));
    char option,ch;
    if(c==0){
        redo_origin :
        system("cls");
        printf("\n\t\t __________________________");
        printf("\n\t\t|\t\t\t   |");
        printf("\n\t\t|\t NEW BOOKING\t   |");
        printf("\n\t\t|__________________________|");
        printf("\n\n\t\t NOTE : Choose Where you wish to travel from.\n");
        display_stations();
        printf("\n\t\t CHOICE : ");
        scanf("%d",&choice);
        if(choice<=0 || choice>34){
            printf("\n\t\t WARNING : INVALID OPTION. RETRY.");
            delay(1);
            goto redo_origin;
        }
        origin=choice-1;
        redo_dest :
        system("cls");
        printf("\n\t\t __________________________");
        printf("\n\t\t|\t\t\t   |");
        printf("\n\t\t|\t NEW BOOKING\t   |");
        printf("\n\t\t|__________________________|");
        printf("\n\n\t\t NOTE : Choose Destination.\n");
        display_stations();
        printf("\n\t\t CHOICE : ");
        scanf("%d",&choice);
        if(choice<=0 || choice>34){
            printf("\n\t\t WARNING : INVALID OPTION. RETRY.");
            delay(1);
            goto redo_dest;
        }
        dest=choice-1;
        lst=search_trains(origin,dest,&n_trains);
        system("cls");
        printf("\n\t\t __________________________");
        printf("\n\t\t|\t\t\t   |");
        printf("\n\t\t|\t NEW BOOKING\t   |");
        printf("\n\t\t|__________________________|");
        if(n_trains==0){
            printf("\n\t\t NOTE : NO DIRECT TRAINS FOUND");
            printf("\n\t\t NOTE : PRESS Y TO VIEW TRAINS. ANY OTHER TO EXIT ");
            option=getch();
            if(option=='Y' || option=='y')
                search(user,pw,1);
            else{
                check=1;}
        }
        else{
            printf("\n");
            for(i=0;i<n_trains;i++){
                printf("\n\t\t %d. ",i+1);
                display_train(*(lst+i));
            }
            printf("\n");
        printf("\n\t\t NOTE : CHOOSE WHICH TRAIN TO BOOK. ANY OTHER KEY TO EXIT.");
        option=getch();
        choice=option-'0';
        if(option<'1' || option>'9' || choice>n_trains || choice<0){
            printf("\n\t\t\t WARNING : INVALID INPUT. RETURNING TO MENU");
            check=1;
            delay(1);
        }
        else{
            choice=option-'0';
        system("cls");
        printf("\n\t\t __________________________");
        printf("\n\t\t|\t\t\t   |");
        printf("\n\t\t|\tCONFIRM BOOKING\t   |");
        printf("\n\t\t|__________________________|");
        printf("\n\n\t\tROUTE:");
        printf("\n\t\t------");
        printf("\n\t\tSTATIONS\t\tTIME");
        printf("\n\t\t--------\t\t----");
        display_route(*(lst+choice-1));
        printf("\n\n\t\t NOTE : PRESS Y TO CONFIRM BOOKING. ANY OTHER TO EXIT.");
        option=getch();
        if(option=='Y' || option=='y'){
            *index=origin;
            *(index+1)=dest;
            *(index+2)=*(lst+choice-1);
            return index;
        }
        else{
            check=1;
        }
    }}}
    else if(c==1){
        redoview:
        system("cls");
        printf("\n\t\t WELCOME, %s.\n",user);
        system("cls");
        printf("\n\t\t __________________________");
        printf("\n\t\t|\t\t\t   |");
        printf("\n\t\t|\t NEW BOOKING\t   |");
        printf("\n\t\t|__________________________|");
        printf("\n");
        for(i=0;i<12;i++){
            printf("\n\t\t%d. ",i+1);
            display_train(i);
            printf("\n");
        }
        printf("\n\n\t\t CHOOSE TRAIN : ");
        scanf("%d",&choice);
        if(choice<1 || choice>12){
            printf("\n\t\t NOTE : INVALID INPUT. RETRY.");
            goto redoview;
        }
        choice-=1;
        printf("\n\t\t NOTE : PRESS 1 TO VIEW ROUTE. 0 TO BOOK.");
        option=getch();
        if(option!='1' && option!='0'){
            printf("\n\t\t NOTE : INVALID INPUT. RETRY.");
            goto redoview;
        }
        else if(option=='1'){
            system("cls");
            printf("\n\t\t __________________________");
            printf("\n\t\t|\t\t\t   |");
            printf("\n\t\t|\tVIEW ROUTE\t   |");
            printf("\n\t\t|__________________________|");
            printf("\n\n\t\tSTATIONS\t\tTIME");
            printf("\n\t\t--------\t\t----");
            display_route(choice);
            printf("\n\n\t\t NOTE : PRESS 1 TO BOOK. 0 TO GO BACK. ANY OTHER TO EXIT. ");
            ch=getch();
            if(ch=='1'){
                *index=trains[choice].frto[0];
                *(index+1)=trains[choice].frto[1];
                *(index+2)=choice;
                return index;
            }
            else if(ch=='0')
                goto redoview;
            else{
                check=1;}
        }
        else if(option=='0'){
            *index=trains[choice].frto[0];
            *(index+1)=trains[choice].frto[1];
            *(index+2)=choice;
            return index;
        }
    }
}

void database(){
    struct route *t1,*t2;
    //train 1 - Chennai to Kanyakumari
    strcpy(trains[0].name,"Kanyakumari Superfast Express");
    trains[0].frto[0]=2;trains[0].frto[1]=9;
    trains[0].train_no=12674;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=2;
    trains[0].rt=t1;
    t1->time[0]=17;t1->time[1]=15;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=1;
    t1->next=t2;
    t2->time[0]=18;t2->time[1]=15;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=8;
    t2->next=t1;
    t1->time[0]=19;t1->time[1]=0;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=32;
    t1->next=t2;
    t2->time[0]=19;t2->time[1]=50;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=27;
    t2->next=t1;
    t1->time[0]=22;t1->time[1]=20;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=6;
    t1->next=t2;
    t2->time[0]=23;t2->time[1]=55;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=12;
    t2->next=t1;
    t1->time[0]=1;t1->time[1]=0;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=33;
    t1->next=t2;
    t2->time[0]=2;t2->time[1]=0;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=26;
    t2->next=t1;
    t1->time[0]=2;t1->time[1]=45;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=28;
    t1->next=t2;
    t2->time[0]=4;t2->time[1]=0;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=9;
    t2->next=t1;
    t1->time[0]=6;t1->time[1]=20;
    t1->next=NULL;
    trains[0].noac1=0;trains[0].noac2=0;trains[0].nnac1=0;trains[0].nnac2=0;trains[0].nw=0;
    trains[0].wt=NULL;

    //train 2 - Chennai to Coimbatore
    strcpy(trains[1].name,"Kovai Superfast Express");
    trains[1].frto[0]=2;trains[1].frto[1]=3;
    trains[1].train_no=12676;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=2;
    trains[1].rt=t1;
    t1->time[0]=6;t1->time[1]=10;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=30;
    t1->next=t2;
    t2->time[0]=7;t2->time[1]=0;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=31;
    t2->next=t1;
    t1->time[0]=8;t1->time[1]=0;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=11;
    t1->next=t2;
    t2->time[0]=8;t2->time[1]=50;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=5;
    t2->next=t1;
    t1->time[0]=9;t1->time[1]=40;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=19;
    t1->next=t2;
    t2->time[0]=11;t2->time[1]=10;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=7;
    t2->next=t1;
    t1->time[0]=12;t1->time[1]=10;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=29;
    t1->next=t2;
    t2->time[0]=12;t2->time[1]=50;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=3;
    t2->next=t1;
    t1->time[0]=14;t1->time[1]=10;
    t1->next=NULL;
    trains[1].noac1=0;trains[1].noac2=0;trains[1].nnac1=0;trains[1].nnac2=0;trains[1].nw=0;
    trains[1].wt=NULL;

    //train 3 - Nilgiris to Nagapattinam
    strcpy(trains[2].name,"Nagapattinam Express");
    trains[2].frto[0]=16;trains[2].frto[1]=14;
    trains[2].train_no=12678;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=16;
    trains[2].rt=t1;
    t1->time[0]=7;t1->time[1]=0;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=7;
    t1->next=t2;
    t2->time[0]=7;t2->time[1]=40;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=10;
    t2->next=t1;
    t1->time[0]=8;t1->time[1]=40;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=15;
    t1->next=t2;
    t2->time[0]=9;t2->time[1]=50;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=27;
    t2->next=t1;
    t1->time[0]=12;t1->time[1]=20;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=22;
    t1->next=t2;
    t2->time[0]=13;t2->time[1]=50;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=25;
    t2->next=t1;
    t1->time[0]=15;t1->time[1]=20;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=14;
    t1->next=t2;
    t2->time[0]=16;t2->time[1]=0;
    t2->next=NULL;
    trains[2].noac1=0;trains[2].noac2=0;trains[2].nnac1=0;trains[2].nnac2=0;trains[2].nw=0;
    trains[2].wt=NULL;

    //train 4 - Kanyakumari to Chennai
    strcpy(trains[3].name,"Chennai Express via Thoothukudi");
    trains[3].frto[0]=9;trains[3].frto[1]=2;
    trains[3].train_no=12680;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=9;
    trains[3].rt=t1;
    t1->time[0]=6;t1->time[1]=30;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=28;
    t1->next=t2;
    t2->time[0]=9;t2->time[1]=0;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=26;
    t2->next=t1;
    t1->time[0]=10;t1->time[1]=50;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=18;
    t1->next=t2;
    t2->time[0]=13;t2->time[1]=50;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=20;
    t2->next=t1;
    t1->time[0]=15;t1->time[1]=10;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=17;
    t1->next=t2;
    t2->time[0]=16;t2->time[1]=40;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=22;
    t2->next=t1;
    t1->time[0]=18;t1->time[1]=10;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=0;
    t1->next=t2;
    t2->time[0]=19;t2->time[1]=15;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=4;
    t2->next=t1;
    t1->time[0]=21;t1->time[1]=45;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=32;
    t1->next=t2;
    t2->time[0]=22;t2->time[1]=30;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=24;
    t2->next=t1;
    t1->time[0]=0;t1->time[1]=10;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=8;
    t1->next=t2;
    t2->time[0]=1;t2->time[1]=30;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=2;
    t2->next=t1;
    t1->time[0]=2;t1->time[1]=40;
    t1->next=NULL;
    trains[3].noac1=0;trains[3].noac2=0;trains[3].nnac1=0;trains[3].nnac2=0;trains[3].nw=0;
    trains[3].wt=NULL;

    //trains 5 - Kanyakumari to Nilgiris
    strcpy(trains[4].name,"Nilgiris Express via Theni");
    trains[4].frto[0]=9;trains[4].frto[1]=16;
    trains[4].train_no=12682;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=9;
    trains[4].rt=t1;
    t1->time[0]=5;t1->time[1]=30;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=28;
    t1->next=t2;
    t2->time[0]=7;t2->time[1]=10;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=33;
    t2->next=t1;
    t1->time[0]=8;t1->time[1]=50;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=23;
    t1->next=t2;
    t2->time[0]=10;t2->time[1]=20;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=6;
    t2->next=t1;
    t1->time[0]=12;t1->time[1]=0;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=29;
    t1->next=t2;
    t2->time[0]=13;t2->time[1]=50;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=3;
    t2->next=t1;
    t1->time[0]=14;t1->time[1]=50;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=16;
    t1->next=t2;
    t2->time[0]=16;t2->time[1]=10;
    t2->next=NULL;
    trains[4].noac1=0;trains[4].noac2=0;trains[4].nnac1=0;trains[4].nnac2=0;trains[4].nw=0;
    trains[4].wt=NULL;

    //train 6 - Coimbatore to Nagapattinam
    strcpy(trains[5].name,"Nagapattinam Express via Dindigul");
    trains[5].frto[0]=3;trains[5].frto[1]=14;
    trains[5].train_no=12684;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=3;
    trains[5].rt=t1;
    t1->time[0]=6;t1->time[1]=40;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=29;
    t1->next=t2;
    t2->time[0]=7;t2->time[1]=50;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=6;
    t2->next=t1;
    t1->time[0]=10;t1->time[1]=0;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=17;
    t1->next=t2;
    t2->time[0]=12;t2->time[1]=20;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=22;
    t2->next=t1;
    t1->time[0]=13;t1->time[1]=40;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=25;
    t1->next=t2;
    t2->time[0]=14;t2->time[1]=50;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=14;
    t2->next=t1;
    t1->time[0]=15;t1->time[1]=30;
    t1->next=NULL;
    trains[5].noac1=0;trains[5].noac2=0;trains[5].nnac1=0;trains[5].nnac2=0;trains[5].nw=0;
    trains[5].wt=NULL;

    //train 7 - Kanyakumari to Chennai
    strcpy(trains[6].name,"Chennai Superfast Express");
    trains[6].frto[0]=9;trains[6].frto[1]=2;
    trains[6].train_no=12686;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=9;
    trains[6].rt=t1;
    t1->time[0]=6;t1->time[1]=50;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=28;
    t1->next=t2;
    t2->time[0]=9;t2->time[1]=10;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=26;
    t2->next=t1;
    t1->time[0]=10;t1->time[1]=25;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=33;
    t1->next=t2;
    t2->time[0]=11;t2->time[1]=0;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=12;
    t2->next=t1;
    t1->time[0]=12;t1->time[1]=0;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=6;
    t1->next=t2;
    t2->time[0]=13;t2->time[1]=5;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=27;
    t2->next=t1;
    t1->time[0]=14;t1->time[1]=40;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=32;
    t1->next=t2;
    t2->time[0]=17;t2->time[1]=10;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=8;
    t2->next=t1;
    t1->time[0]=18;t1->time[1]=0;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=1;
    t1->next=t2;
    t2->time[0]=18;t2->time[1]=45;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=2;
    t2->next=t1;
    t1->time[0]=19;t1->time[1]=45;
    t1->next=NULL;
    trains[6].noac1=0;trains[6].noac2=0;trains[6].nnac1=0;trains[6].nnac2=0;trains[6].nw=0;
    trains[6].wt=NULL;

    //train 8 - Coimbatore to Chennai
    strcpy(trains[7].name,"Chennai - kovai Express");
    trains[7].frto[0]=3;trains[7].frto[1]=2;
    trains[7].train_no=12688;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=3;
    trains[7].rt=t1;
    t1->time[0]=14;t1->time[1]=30;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=29;
    t1->next=t2;
    t2->time[0]=15;t2->time[1]=50;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=7;
    t2->next=t1;
    t1->time[0]=16;t1->time[1]=30;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=19;
    t1->next=t2;
    t2->time[0]=17;t2->time[1]=30;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=5;
    t2->next=t1;
    t1->time[0]=19;t1->time[1]=0;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=11;
    t1->next=t2;
    t2->time[0]=19;t2->time[1]=50;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=31;
    t2->next=t1;
    t1->time[0]=20;t1->time[1]=40;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=30;
    t1->next=t2;
    t2->time[0]=21;t2->time[1]=40;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=2;
    t2->next=t1;
    t1->time[0]=22;t1->time[1]=20;
    t1->next=NULL;
    trains[7].noac1=0;trains[7].noac2=0;trains[7].nnac1=0;trains[7].nnac2=0;trains[7].nw=0;
    trains[7].wt=NULL;

    //train 9 - Nagapattinam to Nilgiris
    strcpy(trains[8].name,"Nilgiris Superfast Express");
    trains[8].frto[0]=14;trains[8].frto[1]=16;
    trains[8].train_no=12690;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=14;
    trains[8].rt=t1;
    t1->time[0]=16;t1->time[1]=30;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=25;
    t1->next=t2;
    t2->time[0]=17;t2->time[1]=10;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=22;
    t2->next=t1;
    t1->time[0]=18;t1->time[1]=40;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=27;
    t1->next=t2;
    t2->time[0]=20;t2->time[1]=10;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=15;
    t2->next=t1;
    t1->time[0]=22;t1->time[1]=40;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=10;
    t1->next=t2;
    t2->time[0]=23;t2->time[1]=50;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=7;
    t2->next=t1;
    t1->time[0]=0;t1->time[1]=50;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=16;
    t1->next=t2;
    t2->time[0]=1;t2->time[1]=30;
    t2->next=NULL;
    trains[8].noac1=0;trains[8].noac2=0;trains[8].nnac1=0;trains[8].nnac2=0;trains[8].nw=0;
    trains[8].wt=NULL;

    //train 10 - Chennai to Kanyakumari
    strcpy(trains[9].name,"Kanyakumari Express via Tenkasi");
    trains[9].frto[0]=2;trains[9].frto[1]=9;
    trains[9].train_no=12692;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=2;
    trains[9].rt=t1;
    t1->time[0]=3;t1->time[1]=10;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=8;
    t1->next=t2;
    t2->time[0]=4;t2->time[1]=20;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=24;
    t2->next=t1;
    t1->time[0]=5;t1->time[1]=40;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=32;
    t1->next=t2;
    t2->time[0]=7;t2->time[1]=20;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=4;
    t2->next=t1;
    t1->time[0]=8;t1->time[1]=5;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=0;
    t1->next=t2;
    t2->time[0]=10;t2->time[1]=35;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=22;
    t2->next=t1;
    t1->time[0]=11;t1->time[1]=40;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=17;
    t1->next=t2;
    t2->time[0]=13;t2->time[1]=10;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=20;
    t2->next=t1;
    t1->time[0]=14;t1->time[1]=40;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=18;
    t1->next=t2;
    t2->time[0]=16;t2->time[1]=40;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=26;
    t2->next=t1;
    t1->time[0]=19;t1->time[1]=40;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=21;
    t1->next=t2;
    t2->time[0]=21;t2->time[1]=10;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=28;
    t2->next=t1;
    t1->time[0]=22;t1->time[1]=30;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=9;
    t1->next=t2;
    t2->time[0]=1;t2->time[1]=0;
    t2->next=NULL;
    trains[9].noac1=0;trains[9].noac2=0;trains[9].nnac1=0;trains[9].nnac2=0;trains[9].nw=0;
    trains[9].wt=NULL;

    //train 11 - Nilgiris to Kanyakumari
    strcpy(trains[10].name,"Nilgiris - Kanyakumari Express");
    trains[10].frto[0]=16;trains[10].frto[1]=9;
    trains[10].train_no=12694;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=16;
    trains[10].rt=t1;
    t1->time[0]=15;t1->time[1]=30;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=3;
    t1->next=t2;
    t2->time[0]=17;t2->time[1]=30;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=29;
    t2->next=t1;
    t1->time[0]=18;t1->time[1]=30;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=6;
    t1->next=t2;
    t2->time[0]=20;t2->time[1]=20;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=23;
    t2->next=t1;
    t1->time[0]=22;t1->time[1]=0;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=33;
    t1->next=t2;
    t2->time[0]=23;t2->time[1]=30;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=21;
    t2->next=t1;
    t1->time[0]=1;t1->time[1]=0;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=28;
    t1->next=t2;
    t2->time[0]=1;t2->time[1]=50;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=9;
    t2->next=t1;
    t1->time[0]=3;t1->time[1]=30;
    t1->next=NULL;
    trains[10].noac1=0;trains[10].noac2=0;trains[10].nnac1=0;trains[10].nnac2=0;trains[10].nw=0;
    trains[10].wt=NULL;

    //train 12 - Nagapattinam to Coimbatore
    strcpy(trains[11].name,"Coimbatore Express");
    trains[11].frto[0]=14;trains[11].frto[1]=3;
    trains[11].train_no=12696;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=14;
    trains[11].rt=t1;
    t1->time[0]=16;t1->time[1]=10;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=25;
    t1->next=t2;
    t2->time[0]=17;t2->time[1]=30;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=22;
    t2->next=t1;
    t1->time[0]=18;t1->time[1]=40;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=17;
    t1->next=t2;
    t2->time[0]=20;t2->time[1]=0;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=6;
    t2->next=t1;
    t1->time[0]=22;t1->time[1]=20;
    t2=(struct route*)malloc(sizeof(struct route));
    t2->data=29;
    t1->next=t2;
    t2->time[0]=0;t2->time[1]=30;
    t1=(struct route*)malloc(sizeof(struct route));
    t1->data=3;
    t2->next=t1;
    t1->time[0]=1;t1->time[1]=40;
    t1->next=NULL;
    trains[11].noac1=0;trains[11].noac2=0;trains[11].nnac1=0;trains[11].nnac2=0;trains[11].nw=0;
    trains[11].wt=NULL;
}

void cancelbooking(char user[20],char pw[20]){
    FILE *in,*out;
    char dir[100]="./railway dbs/",ps[20],c,dir2[100];
    struct passenger p,r;
    struct waitlist *t,*s;
    int i=0,n,index;
    strcat(dir,user);strcat(dir,".txt");
    redoview:
    i=0;
    in = fopen(dir,"r");
    system("cls");
    printf("\n\t\t __________________________");
    printf("\n\t\t|\t\t\t   |");
    printf("\n\t\t|\tCANCEL BOOKING\t   |");
    printf("\n\t\t|__________________________|");
    fscanf(in,"%s",&ps);
    while(!feof(in)){
        fscanf(in,"%lld %d %d %d %d %d %c",&p.PNR,&p.train_no,&p.frto[0],&p.frto[1],&p.cmpt,&p.seatno,&p.status);
        printf("\n\n\t\t%d. ",i+1);i++;
        printf("PNR         : %lld",p.PNR);
        printf("\n\t\t   Train no    : %d ",p.train_no);
        printf("\n\t\t   From        : %s",stations[p.frto[0]]);
        printf("\n\t\t   To          : %s",stations[p.frto[1]]);
        if(p.cmpt==1)
            printf("\n\t\t   Compartment : 1st AC");
        else if(p.cmpt==2)
            printf("\n\t\t   Compartment : 2nd AC");
        else if(p.cmpt==3)
            printf("\n\t\t   Compartment : 1st NON AC");
        else if(p.cmpt==4)
            printf("\n\t\t   Compartment : 2nd NON AC");
        printf("\n\t\t   Seat no     : %d",p.seatno);
        if(p.status=='c')
            printf("\n\t\t   Status      : Confirmed");
        else if(p.status=='w')
            printf("\n\t\t   Status      : Waiting List");
        if(getc(in)==EOF)
            break;
    }
    fclose(in);
    if(i==0){
        printf("\n\n\t\t NOTE : NO BOOKING DONE. RETURNING TO MENU.");
        delay(1);
        mainmenu(user,pw);
    }
    else{
    printf("\n\n\t\t ENTER THE BOOKING THAT NEEDS TO BE CANCELLED : ");
    scanf("%d",&n);
    if(n>i || n<1){
        printf("\n\t\t NOTE : INVALID OPTION. RETRY.");
        delay(1);
        goto redoview;
    }
    else{
    printf("\n\t\t NOTE : PRESS Y TO CONFIRM. ANY OTHER TO EXIT.");
    c=getch();
    if(c!='y' && c!='Y')
        mainmenu(user,pw);
    else{
    strcpy(dir,"./railway dbs/");strcat(dir,"temp.txt");
    out = fopen(dir,"w");
    strcpy(dir,"./railway dbs/");strcat(dir,user);strcat(dir,".txt");
    in = fopen(dir,"r");
    fscanf(in,"%s",&ps);
    fprintf(out,"%s",ps);
    i=0;
    while(!feof(in)){
        fscanf(in,"%lld %d %d %d %d %d %c",&p.PNR,&p.train_no,&p.frto[0],&p.frto[1],&p.cmpt,&p.seatno,&p.status);
        i++;
        if(i!=n){
            fprintf(out,"\n%lld %d %d %d %d %d %c",p.PNR,p.train_no,p.frto[0],p.frto[1],p.cmpt,p.seatno,p.status);
        }
        else if(i==n){
            index=(p.train_no-12674)/2;
            if(p.status=='c'){
                if(p.cmpt==1)
                    trains[index].noac1-=1;
                else if(p.cmpt==2)
                    trains[index].noac2-=1;
                else if(p.cmpt==3)
                    trains[index].nnac1-=1;
                else if(p.cmpt==4)
                    trains[index].nnac2-=1;
                r=p;
            }
            else if(p.status=='w'){
                trains[index].nw-=1;
                t=trains[index].wt;
                s=NULL;
                while(t!=NULL){
                    if(strcmp(t->p_user,user)==0 && s==NULL){
                        trains[index].wt=t->next;
                        break;
                    }
                    else if(strcmp(t->p_user,user)==0){
                        s->next=t->next;
                        break;
                    }
                    s=t;
                    t=t->next;
                }
            }
        }
        if(getc(in)==EOF)
            break;
    }
    fclose(in);
    fclose(out);
    strcpy(dir,"./railway dbs/");strcat(dir,"temp.txt");
    strcpy(dir2,"./railway dbs/");strcat(dir2,user);strcat(dir2,".txt");
    remove(dir2);
    rename(dir,dir2);

    printf("\n\t\t NOTE : SUCCESSFULLY CANCELLED BOOKING.");
    if(trains[index].nw!=0 && r.status=='c')
        new_waitlist(r);
    delay(1);
    mainmenu(user,pw);
    }}}
}

void newbooking(char user[20],char pw[20]){
    char c,ch,dir[100]="./railway dbs/";
    struct passenger newp;
    struct waitlist *neww,*t;
    int *index;
    FILE *file;
    retry:
    system("cls");
    printf("\n\t\t WELCOME, %s.\n",user);
    printf("\n\t\t ________________________________________________");
    printf("\n\t\t|\t\t\t\t\t\t |");
    printf("\n\t\t|\t\t\t\t\t\t |");
    printf("\n\t\t|\t NEW BOOKING\t\t\t\t |");
    printf("\n\t\t|\t _______________________________\t |");
    printf("\n\t\t|\t|\t\t\t\t|\t |");
    printf("\n\t\t|\t| 1. Search by stations\t\t|\t |");
    printf("\n\t\t|\t| 2. Search by trains\t\t|\t |");
    printf("\n\t\t|\t| 3. Back to Menu\t\t|\t |");
    printf("\n\t\t|\t|_______________________________|\t |");
    printf("\n\t\t|\t\t\t\t\t\t |");
    printf("\n\t\t|________________________________________________|");
    c=getch();
    switch(c)
    {
        case '1':
            index=search(user,pw,0);
            break;
        case '2':
            index=search(user,pw,1);
            break;
        case '3':
            mainmenu(user,pw);
            break;
        default:
            printf("\n\n\t\tWARNING : INVALID INPUT. TRY AGAIN.");
            delay(1);
            goto retry;
            break;
    }
    if(check==0){
    redocpt:
    system("cls");
    printf("\n\t\t WELCOME, %s.\n",user);
    printf("\n\t\t ________________________________________________");
    printf("\n\t\t|\t\t\t\t\t\t |");
    printf("\n\t\t|\t\t\t\t\t\t |");
    printf("\n\t\t|\t CHOOSE COMPARTMENT\t\t\t |");
    printf("\n\t\t|\t _______________________________\t |");
    printf("\n\t\t|\t|\t\t\t\t|\t |");
    printf("\n\t\t|\t| 1. 1st AC\t\t\t|\t |");
    printf("\n\t\t|\t| 2. 2nd AC\t\t\t|\t |");
    printf("\n\t\t|\t| 3. 1st NON AC\t\t\t|\t |");
    printf("\n\t\t|\t| 4. 2nd NON AC\t\t\t|\t |");
    printf("\n\t\t|\t|_______________________________|\t |");
    printf("\n\t\t|\t\t\t\t\t\t |");
    printf("\n\t\t|________________________________________________|");
    c=getch();
    switch(c)
    {
        case '1':
            if(trains[*(index+2)].noac1<60){
                newp.cmpt=1;
                newp.seatno=trains[*(index+2)].noac1+1;
                trains[*(index+2)].noac1+=1;
                newp.status='c';
            }
            else{
                printf("\n\t\t NOTE : PREFERRED COMPARTMENT NOT AVAILABLE.\n\t\t PRESS Y TO RETRY OR ANY OTHER TO REMAIN IN WAITLIST. ");
                ch=getch();
                if(ch=='Y' || ch=='y')
                    goto redocpt;
                else{
                    newp.cmpt=1;
                    newp.status='w';
                }
            }
            break;
        case '2':
            if(trains[*(index+2)].noac2<60){
                newp.cmpt=2;
                newp.seatno=trains[*(index+2)].noac2+1;
                trains[*(index+2)].noac2+=1;
                newp.status='c';
            }
            else{
                printf("\n\t\t NOTE : PREFERRED COMPARTMENT NOT AVAILABLE.\n\t\t PRESS Y TO RETRY OR ANY OTHER TO REMAIN IN WAITLIST. ");
                ch=getch();
                if(ch=='Y' || ch=='y')
                    goto redocpt;
                else{
                    newp.cmpt=1;
                    newp.status='w';
                }
            }
            break;
        case '3':
            if(trains[*(index+2)].nnac1<60){
                newp.cmpt=3;
                newp.seatno=trains[*(index+2)].nnac1+1;
                trains[*(index+2)].nnac1+=1;
                newp.status='c';
            }
            else{
                printf("\n\t\t NOTE : PREFERRED COMPARTMENT NOT AVAILABLE.\n\t\t PRESS Y TO RETRY OR ANY OTHER TO REMAIN IN WAITLIST. ");
                ch=getch();
                if(ch=='Y' || ch=='y')
                    goto redocpt;
                else{
                    newp.cmpt=1;
                    newp.status='w';
                }
            }
            break;
        case '4':
            if(trains[*(index+2)].nnac2<60){
                newp.cmpt=4;
                newp.seatno=trains[*(index+2)].nnac2+1;
                trains[*(index+2)].nnac2+=1;
                newp.status='c';
            }
            else{
                printf("\n\t\t NOTE : PREFERRED COMPARTMENT NOT AVAILABLE.\n\t\t PRESS Y TO RETRY OR ANY OTHER TO REMAIN IN WAITLIST. ");
                ch=getch();
                if(ch=='Y' || ch=='y')
                    goto redocpt;
                else{
                    newp.cmpt=1;
                    newp.status='w';
                }
            }
            break;
        default:
            printf("\n\n\t\tWARNING : INVALID INPUT. TRY AGAIN.");
            delay(1);
            goto redocpt;
            break;
    }
    newp.frto[0]=*index;newp.frto[1]=*(index+1);
    newp.PNR=cPNR++;
    newp.train_no=trains[*(index+2)].train_no;
    if(newp.status=='w'){
        newp.seatno=0;
        trains[*(index+2)].nw+=1;
        neww=(struct waitlist*)malloc(sizeof(struct waitlist));
        neww->PNR=newp.PNR;
        strcpy(neww->p_user,user);
        neww->next=NULL;
        if(trains[*(index+2)].wt==NULL)
            trains[*(index+2)].wt=neww;
        else{
            t=trains[*(index+2)].wt;
            while(t->next!=NULL){
                t=t->next;
            }
            t->next=neww;
        }
    }
    strcat(dir,user);strcat(dir,".txt");
    file = fopen(dir,"a");
    fprintf(file,"\n%lld %d %d %d %d %d %c",newp.PNR,newp.train_no,newp.frto[0],newp.frto[1],newp.cmpt,newp.seatno,newp.status);
    fclose(file);

    printf("\n\t\tNOTE : SUCCESSFULLY BOOKED.");
    check=0;
    delay(1);
    }
    mainmenu(user,pw);
}

void check_upcoming(char user[20],char pw[20]){
    FILE *in;
    char dir[100]="./railway dbs/",ps[20];
    struct passenger p;
    int i=0;
    strcat(dir,user);strcat(dir,".txt");
    in = fopen(dir,"r");
    system("cls");
    printf("\n\t\t __________________________");
    printf("\n\t\t|\t\t\t   |");
    printf("\n\t\t|   UPCOMING TRAVELS\t   |");
    printf("\n\t\t|__________________________|");
    fscanf(in,"%s ",&ps);
    while(!feof(in)){
        fscanf(in,"%lld %d %d %d %d %d %c",&p.PNR,&p.train_no,&p.frto[0],&p.frto[1],&p.cmpt,&p.seatno,&p.status);
        printf("\n\n\t\t%d. ",i+1);i++;
        printf("PNR         : %lld",p.PNR);
        printf("\n\t\t   Train no    : %d ",p.train_no);
        printf("\n\t\t   From        : %s",stations[p.frto[0]]);
        printf("\n\t\t   To          : %s",stations[p.frto[1]]);
        if(p.cmpt==1)
            printf("\n\t\t   Compartment : 1st AC");
        else if(p.cmpt==2)
            printf("\n\t\t   Compartment : 2nd AC");
        else if(p.cmpt==3)
            printf("\n\t\t   Compartment : 1st NON AC");
        else if(p.cmpt==4)
            printf("\n\t\t   Compartment : 2nd NON AC");
        printf("\n\t\t   Seat no     : %d",p.seatno);
        if(p.status=='c')
            printf("\n\t\t   Status      : Confirmed");
        else if(p.status=='w')
            printf("\n\t\t   Status      : Waiting List");
        if(getc(in)==EOF)
            break;
    }
    fclose(in);
    if(i==0){
        printf("\n\n\t\t NOTE : NO BOOKING DONE. RETURNING TO MENU.");
        delay(1);
        mainmenu(user,pw);
    }
    else{
        printf("\n\n\t\t NOTE : PRESS ANY KEY TO RETURN.");
        getch();
        mainmenu(user,pw);
    }
}

void check_waitlist(char user[20],char pw[20]){
    FILE *in;
    char dir[100]="./railway dbs/",ps[20];
    struct passenger p;
    int i=0;
    strcat(dir,user);strcat(dir,".txt");
    in = fopen(dir,"r");
    system("cls");
    printf("\n\t\t __________________________");
    printf("\n\t\t|\t\t\t   |");
    printf("\n\t\t|\tWAITING LIST\t   |");
    printf("\n\t\t|__________________________|");
    fscanf(in,"%s ",&ps);
    while(!feof(in)){
        fscanf(in,"%lld %d %d %d %d %d %c",&p.PNR,&p.train_no,&p.frto[0],&p.frto[1],&p.cmpt,&p.seatno,&p.status);
        if(p.status=='w'){
            printf("\n\n\t\t%d. ",i+1);i++;
            printf("PNR         : %lld",p.PNR);
            printf("\n\t\t   Train no    : %d ",p.train_no);
            printf("\n\t\t   From        : %s",stations[p.frto[0]]);
            printf("\n\t\t   To          : %s",stations[p.frto[1]]);
            if(p.cmpt==1)
                printf("\n\t\t   Compartment : 1st AC");
            else if(p.cmpt==2)
                printf("\n\t\t   Compartment : 2nd AC");
            else if(p.cmpt==3)
                printf("\n\t\t   Compartment : 1st NON AC");
            else if(p.cmpt==4)
                printf("\n\t\t   Compartment : 2nd NON AC");
            printf("\n\t\t   Seat no     : %d",p.seatno);
            if(p.status=='c')
                printf("\n\t\t   Status      : Confirmed");
            else if(p.status=='w')
                printf("\n\t\t   Status      : Waiting List");
            if(getc(in)==EOF)
                break;
        }
    }
    fclose(in);
    if(i==0){
        printf("\n\n\t\t NOTE : NO BOOKING IN WAITING LIST. RETURNING TO MENU.");
        delay(1);
        mainmenu(user,pw);
    }
    else{
        printf("\n\n\t\t NOTE : PRESS ANY KEY TO RETURN.");
        getch();
        mainmenu(user,pw);
    }
}

void new_waitlist(struct passenger p){
    FILE *out,*in;
    char dir[100]="./railway dbs/",ps[20],dir2[100]="./railway dbs/";
    struct passenger q,r;
    struct waitlist *t,*s=NULL;
    int index,chk=0;
    index=(p.train_no-12674)/2;
    t=trains[index].wt;
    while(t!=NULL && chk==0){
        strcpy(dir,"./railway dbs/");strcat(dir,t->p_user);strcat(dir,".txt");
        in=fopen(dir,"r");
        fscanf(in,"%s ",&ps);
        while(!feof(in)){
            fscanf(in,"%lld %d %d %d %d %d %c",&q.PNR,&q.train_no,&q.frto[0],&q.frto[1],&q.cmpt,&q.seatno,&q.status);
            if(t->PNR==q.PNR && p.cmpt==q.cmpt){
                rewind(in);
                fscanf(in,"%s",&ps);
                strcpy(dir,"./railway dbs/");strcat(dir,"temp.txt");
                out=fopen(dir,"w");
                fprintf(out,"%s",ps);
                while(!feof(in)){
                    fscanf(in,"%lld %d %d %d %d %d %c",&r.PNR,&r.train_no,&r.frto[0],&r.frto[1],&r.cmpt,&r.seatno,&r.status);
                    if(t->PNR==r.PNR){
                        r.status='c';
                        r.seatno=p.seatno;
                    }
                    fprintf(out,"\n%lld %d %d %d %d %d %c",r.PNR,r.train_no,r.frto[0],r.frto[1],r.cmpt,r.seatno,r.status);
                    trains[index].nw-=1;
                    if(r.cmpt==1)
                        trains[index].noac1+=1;
                    else if(r.cmpt==2)
                        trains[index].noac2+=1;
                    else if(r.cmpt==3)
                        trains[index].nnac1+=1;
                    else if(r.cmpt==4)
                        trains[index].nnac2+=1;
                     if(getc(in)==EOF)
                        break;
                }
                fclose(in);
                fclose(out);
                strcpy(dir,"./railway dbs/");strcat(dir,"temp.txt");
                strcpy(dir2,"./railway dbs/");strcat(dir2,t->p_user);strcat(dir2,".txt");
                remove(dir2);
                rename(dir,dir2);
                if(s!=NULL){
                   s->next=t->next;
                }
                else
                    trains[index].wt=t->next;
                chk=1;
                break;
            }
            if(getc(in)==EOF || chk==1)
                break;
        }
        if(chk==1)
            break;
        fclose(in);
        s=t;
        t=t->next;
    }
}

