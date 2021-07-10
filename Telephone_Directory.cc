#include<stdio.h>
#include<stdlib.h>
struct Numbers                      //defining structure which has mobile number and comment 
{                                   //both datatypes are characters
    char mobnum[15];                //character array which takes mobile number as input
    char comment[50];               //character array which stores comment related above mobile number
};
struct directory                    //Defining structure with data type character and integer
{
    char Name[50];                  //character array takes name as the input
    int numofnumbers;               //Number of numbers user want to give
    struct Numbers *numbers;        //A structure pointer point to Number stucture(which declared above)
};
struct directory_Modify                    //Defining structure with data type character and integer
{
    char Name[50];                  //character array takes name as the input
    int numofnumbers;               //inter taks number of numbers uesrwant to give
    struct Numbers numbers[15];        //A structure array 
};
/*Function description : This function takes user inputs and stores it in the form of a structures which we defined above.
Input: Name,number of numbers user want to give,comment,number
Output: Returns a structure with all user input data*/
struct directory readfromuser(char c){  
    struct directory phn;
    printf("Enter name:");
    scanf(" %[^\n]",phn.Name);			//Takes user name as input 
    printf("How many multiple numbers do u want to give :");
    scanf(" %d",&(phn.numofnumbers));		//Takes number of phone numbers as input
    phn.numbers = (struct Numbers*)calloc(phn.numofnumbers,sizeof(struct Numbers));	//creating structure array dynamically using calloc to store phone numbers and comment with resptive to that phone number
    for(int i=0;i<phn.numofnumbers;i++)	 
    {
        printf("Enter the %d number:",i+1);
        scanf(" %s",phn.numbers[i].mobnum);	//Takes mobile number as input
        printf("Enter the comment for the above num:");
        scanf(" %[^\n]",phn.numbers[i].comment);//Takes comment w.r.t above mobile number as input
    }
    return phn;
}
/*writetofile function discription: This function appends the given data into text file.*/
void writetofile(struct directory phn){
    char k[50]=", This is your data. ";				
    FILE *fp= fopen("phn.txt","a");		//This file pointer opens text file for appending data
    fprintf(fp,"%s%s\n",phn.Name,k);		//Just an extra line to indicate your individual data
    fprintf(fp,"%s\t",phn.Name);		//This appends the given name into file
    fprintf(fp,"%d\n",phn.numofnumbers);	//This appends the number of phone numbers into file and goes to the new line.
    for(int i=0;i<phn.numofnumbers;i++){		
        fprintf(fp,"%s\t%s\n",phn.numbers[i].comment,phn.numbers[i].mobnum);//In new line this appends the phone number and comment w.r.t that phone number into the file
    }
    fclose(fp);					//To close the file
}
/*Functon Description:This function reads the data in file and returns the structure pointer array
Input: File pointer takes as input*/
struct directory* readtofile(FILE *fp){
    struct directory *p=(struct directory*) calloc(1,sizeof(struct directory));	//creating structure pointer array dynamically using calloc to store each individual data  
    if (fp==NULL) return NULL;							//If there is no data in file, it returns NULL 
    fscanf(fp,"%[^\t]%d\n",p->Name,&p->numofnumbers);				//Reads Name and Number of phone numbers w.r.t that person
    p->numbers=(struct Numbers*)calloc(p->numofnumbers,sizeof(struct Numbers));	//creating structure pointer array dynamically using calloc to store phone numbers and comment with resptive to that phone number
    for(int i=0;i<p->numofnumbers;i++){
        fscanf(fp,"%[^\t]%s\n",p->numbers[i].comment,p->numbers[i].mobnum);	//This reads comment and phone number
    }
    return p;
}
/*Function Description: This function used to free the allocated memory*/
void clearmemory(struct directory phn){	
    free(phn.numbers);			//To free the memory
}
/*Function Description: This function prints details of each person.*/
void printstruct(struct directory p){
    printf("Contact Found. These are details:\n");
    printf("Name    :%s\n",p.Name);
    for(int i=0;i<p.numofnumbers;i++){
        printf("Number %d:%s    %s\n",i+1,p.numbers[i].comment,p.numbers[i].mobnum);
    }
}
/*This below function compares two strings and returns 1 if they are equal, returns 0 if they are different*/
int compare_str(char a[],char b[]){
    int index=0;
    while(a[index]!='\0' && b[index]!=0){
        if(a[index]!=b[index]) return 0;
        index++;
    }
    if(a[index]=='\0' && b[index]=='\0')  return 1;
    return 0;
}
/*Function Description: This below function reads the file with given input name and prints the details of that name if it is found
Input : Takes string name from user and file pointer
ouput: Prints the details of given person */
int search(char temp_str[],FILE *fp){
    struct directory *std=readtofile(fp);
    int strcmp=compare_str(temp_str,std->Name);	
    if (compare_str(temp_str,std->Name)==1)	//To compare the given input with the name in file
    {
        printstruct(*std);			//prints the details of person if the given input name matches with the name in file
        clearmemory(*std);			//To free the allocated memory
        return 1;
    }
    return 0;
}
/*Function Description: This function used to modify the details of a person like name or number or comment */
void modify(){
    FILE *fp1=fopen("phn.txt","r");		//opening the file to read
    char Name_M[50],ss[50],k[50];		
    int i=0,M=0,j,struct_count;
    struct directory *trail;
    struct directory_Modify people[50];
    printf("enter the name you want modify:");
    scanf(" %[^\n]",Name_M);			//Taking name as input from user to modify the details of that person
    while (fscanf(fp1,"%s %[^\n]\n",ss,k)!=EOF)	//While it is not end of the file 
    {   
        trail=readtofile(fp1);			//To read the data from file pointer fp1
        for(j=0;trail->Name[j]!='\0';j++)	//This loop used to store name of the person in structure directory_Modify people, here i have used each single character to store separately, because we cannot store stirng directly.
            people[i].Name[j]=trail->Name[j];	//storing the name  in structure directory_Modify people
        people[i].Name[j]='\0';			//To indicate end olf the string

        people[i].numofnumbers=trail->numofnumbers;//Tol store number of numbers into the people array
        for(int q=0;q<(trail->numofnumbers);q++)	//This loop used to store comments and phone numbers into structure directory_Modify people array
        {   int count_c=0,count_m=0;
            for(int k=0;trail->numbers[q].comment[k]!='\0';k++)//This loop is used to store comments into people array, here i have used each single character to store separately, because we cannot store stirng directly.
            {
                count_c++;
                people[i].numbers[q].comment[k]=trail->numbers[q].comment[k];
            }
            people[i].numbers[q].comment[count_c]='\0';
            for(int w=0;trail->numbers[q].mobnum[w]!='\0';w++)//This loop is used to store phone numbers into people array
            {
                count_m++;
                people[i].numbers[q].mobnum[w]=trail->numbers[q].mobnum[w];
            }
            people[i].numbers[q].mobnum[count_m]='\0';
        }
        if (compare_str(people[i].Name,Name_M)==1)  M=i+1;	
        i++;
    }
    fclose(fp1);	//To close the opened file
    if(M==0){		//If M is zero this implies there are no results found with respect to that given input name
        printf("No entries found with Given name %s\n",Name_M);
        return;
    }
    struct_count=i;
    FILE *fp2=fopen("phn.txt","w");	//File is opened to write
    char type[50]=", This is your data. ";
    for(i=0;i<struct_count;i++)
    {   if (i+1==M) continue;	//If user input name is same as file , then do not append the deatils of that name		
        else		//To append total data except the given input name deatils.
        {
            fprintf(fp2,"%s%s\n",people[i].Name,type);
            fprintf(fp2,"%s\t",people[i].Name);
            fprintf(fp2,"%d\n",people[i].numofnumbers);
            for(int j=0;j<people[i].numofnumbers;j++)
                fprintf(fp2,"%s\t%s\n",people[i].numbers[j].comment,people[i].numbers[j].mobnum);
        }
    }
    fclose(fp2);	//To close the opened File
        char choice,check;
        printf("what changes are you wanted to make.\nFor modifing Name choose 'N'\nFor modifing Comment choose 'C'\nFor modifing Mobile Number..etc choose 'M'\nAnd 'Q' for Quit\n");
        printf("Enter your choice here:");
        scanf(" %c",&choice);
        if(choice=='M' || choice=='m')	//This if statment is used to modify phone number 
        {   int value_number;
            printf("Enter which number(th) phone number you want to modify(Ex: 1st,2nd,3rd......) like 1st phone number or 2nd phone number etc.:");
            scanf(" %d",&value_number);		//Takes input which numbered phone number you wanted to modify as integer.
            printf("Enter the new number:");
            scanf(" %s",people[M-1].numbers[value_number-1].mobnum);//Takes input as modified number
        }
        if(choice=='C'||choice=='c')	//This if statment is used to modify comment 
        {   
            int value_number;
            printf("Enter which number(th) comment you want to modify(Ex: 1st,2nd,3rd......) like 1st comment or 2nd comment etc.:");
            scanf(" %d",&value_number);	//Takes input which numbered comment you wanted to modify as integer.
            printf("Enter the comment:");
            scanf(" %[^\n]",people[M-1].numbers[value_number-1].comment);//Takes input as modified comment
        }
        if(choice=='N'||choice=='N')	//This if statement is used to modify Name
        { 
            printf("Enter the new Name:");
            scanf(" %[^\n]",people[M-1].Name);//Takes input as modified Name
        }
        
    FILE *fp3=fopen("phn.txt","a");	//opening the file to append modified data	
    fprintf(fp3,"%s%s\n",people[M-1].Name,type);	
    fprintf(fp3,"%s\t",people[M-1].Name);		//To append modified name
    fprintf(fp3,"%d\n",people[M-1].numofnumbers);	//To append number of numbers
    for(int j=0;j<people[M-1].numofnumbers;j++)		//This for loop used to append modified comments and mobile numbers
        fprintf(fp3,"%s\t%s\n",people[M-1].numbers[j].comment,people[M-1].numbers[j].mobnum);
    fclose(fp3);	//To close the opened file
}
int main(){
    int i=0;
    printf("Welcome to Directory\n");
    char c,c_1,ss[50],k[200];
    while(1==1)	//while true
    {
        char c;
        printf("Enter a command(s-for Search, A-Add, M-Modify,Q-Quit):");
        scanf("%c",&c);	//Takes charcter as input to add or to search or to modify the data in file if it exists
        if(c=='A'||c=='a'){ //This if statement is used to add the data into the file
            struct directory phn = readfromuser(c);	//To read the input data from user
            writetofile(phn);		//To add the input data into file
            clearmemory(phn);		
        }
        if(c=='Q'||c=='q') return 0;	//This if statement is used to quit the program
        if(c=='S'||c=='s') 		//This if statement is used to search the data
        {   int q=0;
            char temp_str[50];
            scanf("%c",&c_1);		//To take enter as charcter 
            printf("Enter the Name u want to search for:");
            scanf("%[^\n]",temp_str);	//Takes the name of the person as input you want to search
            FILE *fp=fopen("phn.txt","r");//opening the file to read 
            while (fscanf(fp,"%s %[^\n]\n",ss,k)!=EOF)//while end of the file
            {     
 		int searching=search(temp_str,fp);	//It returns integer value 0 or 1. If the name is in file it returns 1 and if not it returns 0
               
                if (searching==1) { q=1; }	//This statement is used to search a person name in file
            }
            if(q==0) printf("not found\n"); //This statement is true when the given name is not there in file
            fclose(fp);	//To close the opened file
        }
        if(c=='M'||c=='m') modify();
        scanf("%c",&c);//To take enter as character
    }
}
