#include <stdio.h>

//Defining Structure Customer
struct Customer
{
	char Name[30];
	int Cancellation;
};

int main()
{
//Opening File in Write Mode
FILE *fp;
fp=fopen("Customer_Details.txt","w");

struct Customer C1;
struct Customer C2;

//Getting Input for Customer Name
printf("Enter Customer Name: ");
scanf("%[^\n]s",C1.Name);

C1.Cancellation=0;

//Writing into File
fwrite(&C1,sizeof(struct Customer),1,fp);

//Closing File
fclose(fp);

//Opening File in Read Mode
fp=fopen("Customer_Details.txt","r");
fread(&C2,sizeof(struct Customer),1,fp);

//Test Printing
printf("Hello %s!",C2.Name);

//Closing File
fclose(fp);

return 0;
}
