//Covid-19 patient management system
//Author - Vihanga Herath (W.M.V.S.HERATH - E/18/134)
//CO253 - Mini Project 19/01/2022

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    long long int NIC;
    char fullname[50];
    int age;
    char gender[10];
    char admissionDate[20];
}patient_t;
patient_t arr[100];

void color(char col[10]){//this function is defined to use differen color in UI
    if(strcmp(col,"red")==0){
        printf("\033[1;31m");
    }else if(strcmp(col,"cyan")==0){
        printf("\033[1;36m");
    }else if(strcmp(col,"green")==0){
       printf("\033[1;32m");
    }else if(strcmp(col,"yellow")==0){
        printf("\033[0;33m");
    }
}
void color_reset(){//using this function default color can be reset
    printf("\033[0m");
}

void dash_line(){//printing dashline
    printf("\033[1;33m");
    printf("---------------------------------------------------------------------\n");
    printf("\033[0m");
}

int char_to_digit(char a){//in this function a char object will be converted to int digit - this is used to check the validity of input date
    return (int)a-48;
}

int number_of_digits(int long NIC){//count the number of digits in NIC to check the validity of the input NIC
    int counter=0;
    
    while(NIC!=0){
        NIC=NIC/10;
        counter++;
    }
    return counter;
}

void add_patient(patient_t a[],int n){//option-1 -- add new patients
    int num_digits=0;
    while(true){//checking the validity of input NIC number
        printf("Enter the patient NIC number: ");
        scanf("%lld",&a[n].NIC);
        getchar();

        num_digits=number_of_digits(a[n].NIC);
        if(num_digits==9 || num_digits==12){break;}//old NIC has 9 digits and New NIC has 12 digits
        else{
            color("yellow");
            printf("invalid NIC number, Retry!\n");
            dash_line();
            color_reset();
        }
    }

    printf("Enter the patient name: ");
    scanf("%[^\n]%*c", a[n].fullname);
    
    while(true){
        printf("Enter the patient age: ");
        scanf("%d",&a[n].age);
        getchar();

        if(a[n].age<0 || a[n].age>120){//checking validity of input age
            color("yellow");
            printf("invalid age, Retry!\n");
            dash_line();
            color_reset();
        }
        else break;
    }
    while(true){
        printf("Enter the patient gender(Input in this format 'Male' or 'Female'): ");//for futher developing, here input is stricted to pre-defined format
        scanf("%[^\n]%*c",a[n].gender);
        if(strcmp(a[n].gender,"Male")==0 || strcmp(a[n].gender,"Female")==0){break;}//checking format of input gender
        else{
            color("yellow");
            printf("Invalid format, Retry!\n");
            color_reset();
            dash_line();
        }
    }
    int month,year;
    char temp_date[20];
    while(true){
        printf("Enter the Admission Date[DD/MM/YYYY]: ");
        scanf("%[^\n]%*c",temp_date);//a[n].admissionDate);

        month = char_to_digit(temp_date[3])*10 + char_to_digit(temp_date[4]);//input month is converted to integer for checking purpose
        year = char_to_digit(temp_date[6])*1000 + char_to_digit(temp_date[7])*100 + char_to_digit(temp_date[8])*10 + char_to_digit(temp_date[9]);//same as month
        if(atoi(temp_date)<32 && 0<atoi(temp_date) && month<13 && month>0 && year>2020)break;//checking valid date(0<date<32), month(0<month<13), year(>2020)
        else{
            color("yellow");
            printf("Invalid date, Retry!\n");
            color_reset();
            dash_line();
        }
    }
    strcpy(a[n].admissionDate,temp_date);

    dash_line();
    color("yellow");
    printf("Patient record has been added successfully !\n");
    color_reset();
}

void print_patient_record(patient_t a[],int n){//option-2 -- showing information of a patient when NIC is given
    long long int temp_NIC;
    int num_digits;
    while(true){//checking the validity of input NIC number
        printf("Enter the NIC number of the patient: ");
        scanf("%lld",&temp_NIC);

        num_digits=number_of_digits(temp_NIC);
        if(num_digits==9 || num_digits==12){break;}//old NIC has 9 digits and New NIC has 12 digits
        else{
            color("yellow");
            printf("invalid NIC number, Retry!\n");
            dash_line();
            color_reset();
        }
    }

    bool flag=false;
    for(int i=0;i<n;i++){
        if(temp_NIC==a[i].NIC){//searching for given NIC
            flag=true;
            printf("\n............Patient Info.............\n");
            printf("Patient NIC             : %lld\n",a[i].NIC);
            printf("Patient full name       : %s\n",a[i].fullname);
            printf("Patient age             : %d\n",a[i].age);
            printf("Patient gender          : %s\n",a[i].gender);
            printf("Patient admission date  : %s\n",a[i].admissionDate);
            break;
        }
    }
    if(flag==false){//when given NIC is not found
        dash_line();
        color("yellow");
        printf("That NIC number is not in the system. Check and Retry!\n");
        color_reset();
    }
}

void print_all_records(patient_t a[],int n){//option 3 -- show information of all the patients in the system
    for(int i=0;i<n;i++){
        if(i!=0){putchar('\n');}
        printf("............Patient Info. %d ............\n",i+1);
        printf("Patient NIC             : %lld\n",a[i].NIC);
        printf("Patient full name       : %s\n",a[i].fullname);
        printf("Patient age             : %d\n",a[i].age);
        printf("Patient gender          : %s\n",a[i].gender);
        printf("Patient admission date  : %s\n",a[i].admissionDate);
    }
    if(n==0){
        color("yellow");
        printf("There are no patient records in the system.\n");
        color_reset();
    }
}

patient_t *delete_patient_record(patient_t a[],int *n,int max){//option-4 -- delete a patient record
    long long int temp_NIC;
    int num_digits;
    while(true){
        printf("Enter the NIC number of the patient: ");
        scanf("%lld",&temp_NIC);
        dash_line();

        num_digits=number_of_digits(temp_NIC);
        if(num_digits==9 || num_digits==12){break;}
        else{
            color("yellow");
            printf("Invalid NIC number, Retry!\n");
            color_reset();
            dash_line();
        }
    }

    patient_t *array = calloc(max,sizeof(patient_t));//creating a new array

    bool flag=false;
    for(int i=0;i<*n;i++){
        if(a[i].NIC==temp_NIC){//searching for input NIC
            int sub_option=0;
            while(true){
                color("yellow");
                printf("Are you sure you want to remove this patient record permenantly?\n");
                color_reset();
                color("red");printf("1. ");color_reset();printf("Yes, delete it!\n");
                color("red");printf("2. ");color_reset();printf("No, return the main menu!\n");
                dash_line();

                printf("Enter Option [\033[1;31m1\033[0m or \033[1;31m2\033[0m] - ");
                scanf("%d",&sub_option);
                dash_line();

                if(sub_option==1 || sub_option==2){break;}//checking for valid input

                color("yellow");
                printf("Invalid input. Retry!\n");
                color_reset();
                dash_line();
            }
            if(sub_option==1){//recreate an array without that record
                flag=true;
                for(int j=0;j<*n;j++){
                    if(j<i)array[j]=a[j];
                    if(j>i)array[j-1]=a[j];
                }
                *n=*n-1;
            }
            else if(sub_option==2){//returning main menu
                free(array);
                color("yellow");
                printf("action has been cancelled\n");
                color_reset();
                return a;
            }
        }
    }
    color("yellow");
    if(flag==false){//when the input NIC is not found
        printf("That NIC number is not in the system. Check and Retry!\n");
        color_reset();
        return a;
    }
    else{
        printf("Patient record has been removed successfully.\n");
        color_reset();
        return array;
    }
}

patient_t *delete_all_records(patient_t a[],int n,int *c){//option 5 -- delete all patinet records
    bool flag;
    while(true){
        color("yellow");
        printf("Are you sure you want to delete all patient records?\n");//take a confirmation to delete all records
        color_reset();

        color("red");printf("1. ");color_reset();printf("Yes, delete all patient records!\n");
        color("red");printf("2. ");color_reset();printf("No, return the main menu!\n");
        dash_line();
    
        int sub_option=0;
        printf("Enter Option [\033[1;31m1\033[0m or \033[1;31m2\033[0m] - ");//here, red color code is used
        scanf("%d",&sub_option);
        dash_line();

        if(sub_option==1){flag=true;break;}//checking validity of input
        if(sub_option==2){flag=false;break;}

        color("yellow");
        printf("Invalid input. Retry!\n");
        color_reset();
        dash_line();
    }

    color("yellow");
    if(flag==true){//freeing already existent array and returning an empty array
        free(a);
        patient_t *array=calloc(n,sizeof(patient_t));
        *c=0;
        printf("All records have been removed successfully.\n");
        color_reset();
        return array;
    }else if(flag==false){
        printf("Action has been cancelled.\n");
        color_reset();
        return a;
    }
}

void stats(patient_t a[],int n){//option 6 -- statics
    int male_count=0,female_count=0;
    int age_1=0,age_2=0,age_3=0,age_4=0,age_5=0;
    for(int i=0;i<n;i++){
        if(strcmp(a[i].gender,"Male")==0)male_count++;//counting male and female patients
        else if(strcmp(a[i].gender,"Female")==0)female_count++;

        if(a[i].age<12)age_1++;//counting patients in different age groups
        else if(a[i].age>=12 && a[i].age<18)age_2++;
        else if(a[i].age>=18 && a[i].age<30)age_3++;
        else if(a[i].age>=30 && a[i].age<60)age_4++;
        else if(a[i].age>60)age_5++;
    }
    color("yellow");
    printf("        ___Statics___        \n\n");//displaying informaion
    color_reset();

    printf("Number of patients in the ward: %d\n",n);
    printf("Male patients: %d  |  Female patients: %d\n\n",male_count,female_count);
    
    printf("Number of patients in different age groups......\n");
    printf("[under 12] : %d\n",age_1);
    printf("[ 12 - 17] : %d\n",age_2);
    printf("[ 18 - 29] : %d\n",age_3);
    printf("[ 30 - 59] : %d\n",age_4);
    printf("[above 60] : %d\n",age_5);
}

void find_patients(patient_t a[], int n){//option 7 -- Find patients by using date, age and gender

    int print_info(patient_t p, int count){//this fuction is defined to print information of patients
        printf("\n............Patient Info. %d ............\n",count);
        printf("Patient NIC number      : %lld\n",p.NIC);
        printf("Patient full name       : %s\n",p.fullname);
        printf("Patient age             : %d\n",p.age);
        printf("Patient gender          : %s\n",p.gender);
        printf("Patient admission date  : %s\n",p.admissionDate);
        return count+1;
    }

    int sub_option=0;
    while(true){//this is the sub-menu for this function
        color("yellow");
        printf("Select a method to find patients\n");
        color_reset();
        color("red");printf("1. ");color_reset();printf("by admission date (find all patients who were admitted on a particular date)\n");
        color("red");printf("2. ");color_reset();printf("by age (find all patients in a particular age)\n");
        color("red");printf("3. ");color_reset();printf("by gender (find Female and Male patients seperately)\n");
        color("red");printf("4. ");color_reset();printf("Cancel the action, Return main menu\n");
        dash_line();

        printf("Enter Option[\033[1;31m1\033[0m-\033[1;31m4\033[0m]: ");
        scanf("%d",&sub_option);
        getchar();

        if(sub_option==1 || sub_option==2 || sub_option==3 || sub_option==4)break;//checking for valid input
        else{
            color("yellow");
            printf("Invalid Input, Retry!\n");
            color_reset();
            dash_line();
        }
    }
    bool flag=false;
    if(sub_option==1){//find patients using a particular admission date
        char temp_date[20];
        int temp_count=1;
        int month,year;
        while(true){
            printf("Enter the date[DD/MM/YYYY]: ");
            scanf("%[^\n]%*c",temp_date);

            month = char_to_digit(temp_date[3])*10 + char_to_digit(temp_date[4]);//input month is converted to integer for checking purpose(0<month<13)
            year = char_to_digit(temp_date[6])*1000 + char_to_digit(temp_date[7])*100 + char_to_digit(temp_date[8])*10 + char_to_digit(temp_date[9]);//same as month(year>2020)
            if(atoi(temp_date)<32 && 0<atoi(temp_date) && month<13 && month>0 && year>2020)break;//checking valid date(0<date<32), month, year
            else{
                dash_line();
                color("yellow");
                printf("Invalid date, Retry!\n");
                color_reset();
            }
        }
        for(int i=0;i<n;i++){
            if(strcmp(a[i].admissionDate,temp_date)==0){
                flag=true;
                temp_count=print_info(a[i],temp_count);
            }
        }
        if(flag==false){
            dash_line();
            color("yellow");
            printf("Not Found! No patients have been admitted on that day\n");
            color_reset();
        }
    }else if(sub_option==2){//find patients using a particular age
        int temp_age=0;
        int temp_count=1;
        while(true){
            printf("Enter the age: ");
            scanf("%d",&temp_age);
            if(0<temp_age && temp_age<120)break;//checking validity of input age
            else{
                dash_line();
                color("yellow");
                printf("Invalid age, Retry!\n");
                color_reset();
            }
        }
        for(int i=0;i<n;i++){
            if(a[i].age==temp_age){
                flag=true;
                temp_count=print_info(a[i],temp_count);
            }
        }
        if(flag==false){
            dash_line();
            color("yellow");
            printf("Not Found! There are no patients with that age\n");
            color_reset();
        }
    }else if(sub_option==3){//find patients using the gender
        char gender[20];
        int temp_count=1;
        while(true){
            printf("Enter the gender[Male/Female]: ");
            scanf("%[^\n]%*c",gender);
            if(strcmp(gender,"Male")==0 || strcmp(gender,"Female")==0)break;//checking valid input
            else{
                dash_line();
                color("yellow");
                printf("Invalid input, Retry!\n");
                color_reset();
            }
        }
        for(int i=0;i<n;i++){
            if(strcmp(a[i].gender,gender)==0){
                flag=true;
                temp_count=print_info(a[i],temp_count);
            }
        }
        if(flag==false && strcmp(gender,"Male")==0){
            dash_line();
            color("yellow");
            printf("Not Found! There are no male patients.\n");
            color_reset();
        }else if(flag==false && strcmp(gender,"Female")==0){
            dash_line();
            color("yellow");
            printf("Not Found! There are no female patients.\n");
            color_reset;
        }
    }else if(sub_option==4){//return main menu
        dash_line();
        color("yellow");
        printf("Action has been cancelled!\n");
        color_reset();
    }else{//check validity of the sub-option input
        dash_line();
        color("yellow");
        printf("Invalid input, Retry!");
        color_reset();
    }
}

int main(){
    int option=1,count=0,max_cap;

    dash_line();
    color("green");
    printf("Welcome to the COVID-19 PATIENT MANAGEMENT SYSTEM !\n");
    color_reset();
    color("cyan");
    printf("-------developed by Vihanga Herath (E/18/134)------\n");
    color_reset();
    dash_line();

    printf("Enter the maximum capacity of the ward: ");
    scanf("%d",&max_cap);
    patient_t *arr = calloc(sizeof(patient_t),max_cap);

    while(option!=0){

        dash_line();
        color("cyan");
        printf("COVID-19 PATIENT MANAGEMENT SYSTEM\n");
        color_reset();
        dash_line();
        color("red");printf("0. ");color_reset();printf("Quit\n");//main menu
        color("red");printf("1. ");color_reset();printf("Add a patient Record\n");
        color("red");printf("2. ");color_reset();printf("Print a Patient Record\n");
        color("red");printf("3. ");color_reset();printf("Print all Patient Records\n");
        color("red");printf("4. ");color_reset();printf("Delet a Patient Record\n");
        color("red");printf("5. ");color_reset();printf("Delet all Patient Records\n");
        color("red");printf("6. ");color_reset();printf("Statics\n");
        color("red");printf("7. ");color_reset();printf("Find patients\n");
        dash_line();

        printf("Enter Option [\033[1;31m0\033[0m-\033[1;31m7\033[0m] - ");//here red color code is used
        scanf("%d",&option);
        dash_line();

        if(option==0){color("green");printf("Good Bye!\n");color_reset();dash_line();}
        else if(option==1){add_patient(arr,count);count++;}
        else if(option==2){print_patient_record(arr,count);}
        else if(option==3){print_all_records(arr,count);}
        else if(option==4){arr=delete_patient_record(arr,&count,max_cap);}
        else if(option==5){arr=delete_all_records(arr,max_cap,&count);}
        else if(option==6){stats(arr,count);}
        else if(option==7){find_patients(arr,count);}
        else{//when input is not in range
            color("yellow");
            printf("Invalid input. Retry!\n");
            color_reset();
        }
    }
    free(arr);
}