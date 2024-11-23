#include <stdio.h>
#include <string.h>

//Creating Structure to store Driver Details
struct D
{
	int D_ID;
	char Name;
	int Phone_No;
	float x_coordinate;
	float y_coordinate;
	float Rating;
	int No_Of_Raters;
	int Type_Of_Vehicle;
};

int main()
{

printf("***DRIVER DATABASE CREATOR***\n\n");

//Opening File in Write Mode
FILE *fp;
fp=fopen("Driver_Details.txt","w");

//Creating Variables
struct D Inputter;
int i=0;
char ch='A';
int ph=987650;

//Iterating to create 24 Different Drivers
for (i=0;i<24;i++)
{
	//Getting Input for all Driver Details

	Inputter.D_ID=i+1;

	Inputter.Name=ch;

	Inputter.Phone_No=ph;

	printf("Enter X Coordinate %d: ",i+1);
	scanf("%f",&Inputter.x_coordinate);

	printf("Enter Y Coordinate %d: ",i+1);
	scanf("%f",&Inputter.y_coordinate);

	printf("Enter Type of Vehicle %d: ",i+1);
	scanf("%d",&Inputter.Type_Of_Vehicle);

	if (i!=11 || i!=12)
	{
	Inputter.Rating=0;
	Inputter.No_Of_Raters=0;
	}

	if (i==11)
	{
	Inputter.Rating=4.5;
	Inputter.No_Of_Raters=1;
	}

	if (i==12)
	{
	Inputter.Rating=4;
	Inputter.No_Of_Raters=1;
	}

	//Writing onto File
	fwrite(&Inputter,sizeof(struct D),1,fp);
	printf("\n");
	
	ph++;
	ch++;
}

//File Closing
fclose(fp);

//Opening File in Read Mode
fp=fopen("Driver_Details.txt","r");

//Creating Variables
struct D Outputter;
struct D Driver_Database[24];

//Iterating to read details of all Drivers
for (i=0;i<24;i++)
{	
	//Reading from File
	fread(&Outputter,sizeof(struct D),1,fp);

	//Appending the detials into an Array
	Driver_Database[i]=Outputter;
}

//Printing a value to verify proper writing/reading
//Below value should print "10    D    3    987650    4" as output
printf("%f    %c    %d    %d    %f",Driver_Database[1].y_coordinate,Driver_Database[3].Name,Driver_Database[4].Type_Of_Vehicle,Driver_Database[0].Phone_No,Driver_Database[12].Rating);

fclose(fp);
return 0;
}