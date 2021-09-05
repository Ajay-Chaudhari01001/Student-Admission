#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>       // This header file are use to date and time function
#include<process.h>   
void inputdata();   
void showdata();
void search();
void searchbyname();
void searchbyrollno();
void modifydata();
void deletdata();
FILE *fp;
struct student   // all student related information store in strure type variable
{
    char name[20];
    char branch[10];
    int rollno;
    char date[20];
}s;                 // refrence variable of structure student 

int main()
{
    int choice;
    while(1)
    {
        system("cls");
        system("COLOR 70");
        printf("\t\t\t**********************************************\n");
        printf("\t\t\t\t\tWELCOME TO MY COLLEGE");
        printf("\n\t\t\t**********************************************\n");
        printf("\n\n \t\t1 Take Admission \n");
        printf("\n\t\t 2 Display Data \n");
        printf("\n\t\t 3 Modify Data \n");
        printf("\n\t\t 4 Search Data \n");
        printf("\n\t\t 5 Delete Data \n");
        printf("\n\t\t 0 Exit \n");
        printf("\n\t\tEnter Your Choice :");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:
            inputdata();                
            break;
        case 2:
            showdata();
            break;
        case 3:
            modifydata();
            break;
        case 4:
            search();
            break;
        case 5:
            deletdata();
            break;
        case 0:
            exit(0);
        default:
            printf("\n \t\t Please Enter Correct Choice ");
            break;
        }
        printf("\n\n\t\t Press Any Key to Continue...");
        getch();
    }
    return 0;
}
void inputdata()
{
    system("cls");       // for clear screen
    system("COLOR 0e");  // for background and foreground color
    printf("\t\t Enter New Student Data \n");
    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate,"%02d/%02d/%02d", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);
    strcpy(s.date,myDate);    

    fp = fopen("Admission.txt","ab");     // create new file admission.txt
    printf("\n\t\tEnter Student Name : ");
    fflush(stdin);
    gets(s.name);
    scanf("%d",s.name);
    printf("\n\t\tEnter Student Branch : ");
    fflush(stdin);
    gets(s.branch);
    printf("\n\t\tEnter Student RollNo : ");
    scanf("%d",&s.rollno);
    fwrite(&s,sizeof(s),1,fp);
    printf("\n\t Record Save Successfully.....");
    fclose(fp);
}
void showdata()
{
    system("cls");
    system("COLOR 0f");
    printf("\t\t<== Student Info ==>\n\n");
     printf("\n-----------------------------------------------------------------------------------------\n");
    printf("%-30s %-20s %-10s %s\n" , "NAME", "BRANCH", "ROLLNO", "DATE");
    fp = fopen("Admission.txt","rb");
    while(fread(&s,sizeof(s),1,fp)==1)
    {
        printf("\n%-30s %-20s %-10d %s\n" ,s.name,s.branch,s.rollno,s.date);
    }
    fclose(fp);
}
void search()
{
    while(1)
    {
        system("cls");
        system("COLOR 0d");
        int ch;
        printf("\n \t\t 1 Search By Rollno\n");
        printf("\n\t\t 2 Search By Name \n");
        printf("\n\t\t 0 Exit\n");
        printf("\n\t\tEnter Your choice :");
        scanf("%d",&ch);
        switch (ch)
        {
        case 0:
            main();
            break;
        case 1:
            searchbyrollno();
            break;
        case 2:
            searchbyname();
            break;
        default:
            printf("\n\t\t Enter Valid Choice Number ");
            break;
        }
    }
}
void searchbyrollno()
{
    int rl,flag=0;
    printf("\n\t\t Enter Rollno You Want Search : ");
    scanf("%d",&rl);
    printf("%-30s %-20s %-10s %s\n" , "NAME", "BRANCH", "ROLLNO", "DATE");
    fp = fopen("Admission.txt","rb");
    while(fread(&s,sizeof(s),1,fp)==1)
    {
        if(rl==s.rollno)
        {
        flag=1;
        printf("\n%-30s %-20s %-10d %s\n" ,s.name,s.branch,s.rollno,s.date);
        break;
        }
    }
    fclose(fp);
    if(flag==0)
    printf("\n\t Record Not Found ");
    else
    printf("\n\t Record Found Successfully.... ");
    getch();
}
void searchbyname()
{
    char nm[20];
    int flag=0;
    printf("\n\t\t Enter Name You Want Search : ");
    fflush(stdin);
    gets(nm);
    printf("%-30s %-20s %-10s %s\n" , "NAME", "BRANCH", "ROLLNO", "DATE");
    fp = fopen("Admission.txt","rb");
    while(fread(&s,sizeof(s),1,fp)==1)
    {
        if(strcmpi(nm, s.name)==0)
        {
        flag=1;
        printf("\n%-30s %-20s %-10d %s\n" ,s.name,s.branch,s.rollno,s.date);
        break;
        }
    }
    fclose(fp);
    if(flag==0)
    printf("\n\t Record Not Found ");
    else
    printf("\n\t Record Found Successfully.... ");
    getch();
}

void modifydata()
{
    system("cls");
    system("COLOR 0f");
    int rl,flag=0;
    printf("\n\t\t Enter Rollno You Want Modify : ");
    scanf("%d",&rl);
    fp = fopen("Admission.txt","rb+");
    while(fread(&s,sizeof(s),1,fp)==1)
    {
        if(rl==s.rollno)
        {
        flag=1;
          printf("\n\t\tEnter New  Name : ");
          fflush(stdin);
          gets(s.name);
          scanf("%d",s.name);
          printf("\n\t\tEnter New Branch : ");
          fflush(stdin);
          gets(s.branch);
          printf("\n\t\tEnter New RollNo : ");
          scanf("%d",&s.rollno);
          fseek(fp,-sizeof(s),1);
          fwrite(&s,sizeof(s),1,fp);
          fclose(fp);
          break;
        }
    }
    fclose(fp);
    if(flag==0)
    printf("\n\t Record Not Found ");
    else
    printf("\n\t Record Modify Successfully.... ");
    getch();
}
void deletdata()
{
    system("cls");
    system("COLOR 0c");
    int rl,flag=0;
    FILE *tf;
    printf("\n\t\t Enter Rollno You Want to Delete : ");
    scanf("%d",&rl);
    fp = fopen("Admission.txt","rb");
    tf = fopen("temp.txt","wb");
    while(fread(&s,sizeof(s),1,fp)==1)
    {
        if(rl==s.rollno)
        flag=1;
        else
        {
            fwrite(&s,sizeof(s),1,tf);
        }
    }
    fclose(fp);
    fclose(tf);
    remove("Admission.txt");
    rename("temp.txt","Admission.txt");
    if(flag==0)
    printf("\n\t Record Not Found ");
    else
    printf("\n\t Record Delete Successfully.... ");
    getch();
}

