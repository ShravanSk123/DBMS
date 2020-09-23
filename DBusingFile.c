#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct student
{
	char name[30];//name can include spaces
	int id;
	char address[30];
	char dob[30];
	char mail[30];
	long phone;
	char branch[10];
	char course[30];
}stu;


//This function adds a new student to database(file)
void insert()
{
	FILE *fptr;
  	fptr = fopen("studb1","a");
  	printf("Enter the student's name:\n> ");
  	scanf(" %[^\n]s",stu.name);

  	printf("Enter the student id:\n> ");
  	scanf("%d",&stu.id);

  	printf("Enter the student's Place:\n> ");
  	scanf(" %[^\n]s",stu.address);

  	printf("Enter the student's date of birth:\n> ");
  	scanf(" %[^\n]s",stu.dob);
	
  	printf("Enter the student's EMAIL:\n> ");
  	scanf(" %[^\n]s",stu.mail);
	
  	printf("Enter the student's phone number:\n> ");
  	scanf("%ld",&stu.phone);
	
  	printf("Enter the student's branch:\n> ");
  	scanf(" %[^\n]s",stu.branch);
	
  	printf("Enter the student's course:\n> ");
  	scanf(" %[^\n]s",stu.course);
		
  	fwrite(&stu,sizeof(stu),1,fptr);
  
		
  	fclose(fptr);
}


//This function displays database(file) contents in tabular form
void display()
{
  	FILE *fp1;
  	fp1 = fopen("studb1", "r");
  	printf("----------------------------------------------------------------- STUDENT DATABASE --------------------------------------------------------------------------");
  	printf("\n\n");
  	printf("%-20s %-20s %-20s %-20s %-20s %-20s %-20s %-20s\n","Name","ID","Address","Date_of_birth","Email","Phone_number","Branch","Course");
  	printf("%-155s\n","-----------------------------------------------------------------------------------------------------------------------------------------------------------------");
  	while (fread(&stu, sizeof(stu), 1, fp1))
  	{
	  	printf("%-20s %-20d %-20s %-20s %-20s %-20ld %-20s %-20s\n",stu.name,stu.id,stu.address,stu.dob,stu.mail,stu.phone,stu.branch,stu.course);
  	}
  	fclose(fp1);
  	printf("\n");
}


//This function checks if required id is present in file or not..
int idavl(int id1)
{
  	FILE *fp;
  	fp = fopen("studb1", "r");
  	while (!feof(fp))
  	{
 	  	fread(&stu, sizeof(stu), 1, fp);
		
    		if (id1 == stu.id)
      			return 1;
  	}
 	return 0;
}


//This function deletes an entry by student ID..
void deletes()
{
  	//creates a new temporary file and copies the content(other than which is to be deleted) to new file
  	//then copies content from new file to old file by overriding existing content

	FILE *fpo;
 	FILE *fpn;
 	int sid, x;
 	printf("Enter the student id to delete:\n> ");
 	scanf("%d", &sid);
 	if (idavl(sid) == 0)
  		printf("Student with id '%d' is not listed in the databse\n", sid);
 	else
 	{
  		fpo = fopen("studb1", "r");
  		fpn = fopen("newstudb1", "w");
  		while (fread(&stu, sizeof(stu), 1, fpo))
  		{
   			x = stu.id;
   			if (x != sid)
    			fwrite(&stu, sizeof(stu), 1, fpn);
  		}
  		fclose(fpo);
  		fclose(fpn);
  		fpo = fopen("studb1", "w");
  		fpn = fopen("newstudb1", "r");
  		while (fread(&stu, sizeof(stu), 1, fpn))
      		{
   			fwrite(&stu, sizeof(stu), 1, fpo);
      		}
		printf("\nRECORD DELETED SUCCESSFULLY..........\n");
      
  		//close files
  		fclose(fpo);
  		fclose(fpn);
 	}
}


//This function searches for the required student by ID..
void search()
{
	FILE *fp2;
	
	int sid, s, avl;
 	printf("Enter studuent id to search:\n> ");
 	scanf("%d", &sid);
 	avl = idavl(sid);
 	if (avl == 0)
  		printf("Student with id '%d' is not listed in the database\n",sid);
 	else
 	{
  		fp2 = fopen("studb1", "r");
  		while (fread(&stu, sizeof(struct student), 1, fp2)!=0)
  		{
   			s = stu.id;
   			if (s == sid)
   			{
   				printf("%-20s %-20s %-20s %-20s %-20s %-20s %-20s %-20s\n","Name","ID","Address","Date_of_birth","Email","Phone_number","Branch","Course");
   				printf("%-155s\n","-----------------------------------------------------------------------------------------------------------------------------------------------------------------");
          			printf("%-20s %-20d %-20s %-20s %-20s %-20ld %-20s %-20s\n",stu.name,stu.id,stu.address,stu.dob,stu.mail,stu.phone,stu.branch,stu.course);
			}
  		}
  		fclose(fp2);
 	}
}


//This function updates any entry(one at a time) of any student by ID..
void update()
{
  	int avl;
 	FILE *fpn;
 	FILE *fpo;
 	int s, sid, ch;
 	printf("Enter student id to select student to be updated:> ");
 	scanf("%d", &sid);
 	avl = idavl(sid);
 	if (avl == 0)
 	{
  		printf("Student with id '%d' is not listed in the database", sid);
 	}
 	else
 	{
  		fpo = fopen("studb1", "r");
  		fpn = fopen("newstudb1", "w");
  		while (fread(&stu, sizeof(stu), 1, fpo))
  		{
   			s = stu.id;
   			if (s != sid)
    				fwrite(&stu, sizeof(stu), 1, fpn);
   			else
   			{
   				printf("\nWhat do u want to update?\n1:name\n2:id\n3:address\n4:DOB\n5:email\n6:phone\n7:branch\n8:course\n9: No updates..\n");
   				scanf("%d",&ch);
   				switch(ch)
   				{
   					case 1:	printf("Enter Updated Name:\n> ");
						scanf("%s", stu.name);
						break;
     					case 2:	printf("Enter Updated id:\n> ");
						scanf("%d", &stu.id);
						break;
			  		case 3: printf("Enter Updated address:\n> ");
						scanf("%s", stu.address);
						break;
            				case 4:	printf("Enter Updated DOB:\n> ");
						scanf("%s", stu.dob);
						break;
     					case 5:	printf("Enter Updated email:\n> ");
						scanf("%s", stu.mail);
						break;
     					case 6:	printf("Enter Updated phone:\n> ");
						scanf("%ld", &stu.phone);
						break;
     					case 7:	printf("Enter Updated branch:\n> ");
						scanf("%s", stu.branch);
						break;
     					case 8:	printf("Enter Updated course:\n> ");
						scanf("%s", stu.course);
						break;
     					default: printf("Invalid selection.Can't update record...\n");
                     				break;
	  			}//end of switch
          
    				fwrite(&stu, sizeof(stu), 1, fpn);
			}

		}//end of while

		fclose(fpo);
    		fclose(fpn);
    		fpo = fopen("studb1", "w");
    		fpn = fopen("newstudb1", "r");
    		while (fread(&stu, sizeof(stu), 1, fpn))
    		{
      			fwrite(&stu, sizeof(stu), 1, fpo);
    		}
    		printf("\nRECORD UPDATED SUCCESSFULLY.......\n");
    		//close files
    		fclose(fpo);
    		fclose(fpn);
 	}//end of outermost else
}


void main()
{
	int ch;
	while(1)
	{
		printf("\nWhat to do?\n1: Insert New Student Data\n2: Delete Existing Data\n3: Search for Student by ID\n4: Update(one field at a time) a field\n5: Display Data Stored in Database\n >=6: Exit\n");
		scanf("%d",&ch);
    
		switch(ch)
		{
			case 1: insert();break;
			case 2: deletes();break;
			case 3: search();break;
			case 4: update();break;
			case 5: display();break;
			default: exit(0);
		}
	}
}





