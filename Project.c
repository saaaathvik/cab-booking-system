#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/*-------------------------------------------------------------------------------------------*/

//Defining Structure for Driver Database
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

//Defining Structure for Customer Details
struct C
{
	char Name[30];
	int Cancellation;
};

/*-------------------------------------------------------------------------------------------*/

//Function for using Distance Formula
float DistanceFormula(float X1, float Y1, float X2, float Y2)
{
	float d=sqrt(pow(X2-X1,2)+pow(Y2-Y1,2));
	return d;
}

/*-------------------------------------------------------------------------------------------*/

//Global declaration of variables required to compute shortest distance
float TreeArr[10]={0,0,0,0,0,0,0,0,0,0};
int CheckArr[10];
int CA_len=0;

//Function for calculating shortest distance using DIJKSTRA's ALGORITHM
void DCalc(int P, float RoadArr[10][10], float TreeArr[10], int CheckArr[10], int *CA_len)
{
	//Creating dummy variables
	int k,l,m,check1,check2;
	int min_index=-1;
	float min=1000;

	//Iterating to find all possible roads that exist from Pickup Location
	for (k=0;k<10;k++)
	{
		check1=1;
		
		//Flag used to check if k exists in CheckArr to prevent Infinite Recursion
		if (*CA_len>0)
		{
			for (l=0;l<*CA_len;l++)
			{
				if (k==CheckArr[l])
				{
					check1=0;
					break;
				}
			}	
		}

		if (RoadArr[P-1][k]!=0 && check1==1)
		{
			//Storing the distance of the road if either there previously was no road or if a shorter path is found
			if (TreeArr[k]==0 || TreeArr[k]>(RoadArr[P-1][k]+TreeArr[P-1]))
				TreeArr[k]=TreeArr[P-1]+RoadArr[P-1][k];
		}
	}

	//Adding variable to CheckArr to keep track of variables and to prevent Infinite Recursion
	CheckArr[*CA_len]=P-1;			
	*CA_len+=1;

	//Finding the shortest path that wasn't already explored and using it as the next reference for recursing
	for (l=0;l<10;l++)
	{
		check2=1;
		for (m=0;m<*CA_len;m++)
		{
			if (l==CheckArr[m])
			{
				check2=0;
				break;
			}
		}

		if (TreeArr[l]<min && TreeArr[l]!=0 && check2==1)
		{
			min=TreeArr[l];
			min_index=l;
		}
	}
	
	//Printing the distances computed for each iteration
	/*printf("\nMinimum Index for this Recursion: %d\n",min_index);
	printf("Tree Array for this Recursion:\n");
	for (m=0;m<10;m++)
		printf("%f ",TreeArr[m]);
	printf("\n");s*/

	//Recursing until the shortest distance to all points from the Pickup Location is found
	if (*CA_len<10)
		DCalc(min_index+1, RoadArr, TreeArr, CheckArr, &*CA_len);
}	

/*-------------------------------------------------------------------------------------------*/

//Global defined Array used to store the two nodes between which the Driver is present
int Road_Of_Driver[10]={0,0,0,0,0,0,0,0,0,0};

//Function to find on which road the Driver is present
void Driver_Road_Finder(float X, float Y, int Road_Of_Driver[10])
{
	//Using Line Equation of the Roads to find in which the Driver is in currently
	if (X==2)
	{
		Road_Of_Driver[0]=1;
		Road_Of_Driver[1]=1;
	}	
	else if (4*X+3*Y==56)
	{
		Road_Of_Driver[0]=1;
		Road_Of_Driver[8]=1;
	}	
	else if (5*Y-3*X==45)
	{
		Road_Of_Driver[3]=1;
		Road_Of_Driver[8]=1;
	}	
	else if (5*X-6*Y==-40)
	{
		Road_Of_Driver[3]=1;
		Road_Of_Driver[4]=1;
	}	
	else if (6*X+2*Y==136)
	{
		Road_Of_Driver[4]=1;
		Road_Of_Driver[5]=1;
	}	
	else if (5*X+Y==104)
	{
		Road_Of_Driver[5]=1;
		Road_Of_Driver[7]=1;
	}	
	else if (8*X-5*Y==107)
	{
		Road_Of_Driver[6]=1;
		Road_Of_Driver[7]=1;
	}	
	else if (5*X+7*Y==77)
	{
		Road_Of_Driver[2]=1;
		Road_Of_Driver[6]=1;
	}	
	else if (5*Y-4*X==2)
	{
		Road_Of_Driver[1]=1;
		Road_Of_Driver[2]=1;
	}	
	else if (6*X+2*Y==90)
	{
		Road_Of_Driver[3]=1;
		Road_Of_Driver[9]=1;
	}	
	else if (3*X-5*Y==-9)
	{
		Road_Of_Driver[2]=1;
		Road_Of_Driver[9]=1;
	}	
	else if (Y==9)
	{
		Road_Of_Driver[7]=1;
		Road_Of_Driver[9]=1;
	}	
}

/*-------------------------------------------------------------------------------------------*/

int main()
{

//Generating random seed for every run
srand(time(0));

printf("\n******CAB BOOKING SYSTEM******\n\n");

/*-------------------------------------------------------------------------------------------*/

//Reading Customer Details from File and Printing Name
struct C Customer;
FILE *cfp;
cfp=fopen("Customer_Details.txt","r");
fread(&Customer,sizeof(struct C),1,cfp);
printf("Welcome %s!\n\n",Customer.Name);
fclose(cfp);

/*-------------------------------------------------------------------------------------------*/

//Dummy variable i,j
int i,j;

//Storing "Location Array"
int LocationArr[30]={1, 2, 16, 2, 2, 2, 3, 7, 6, 4, 10, 15, 5, 16, 20, 6, 18, 14, 7, 14, 1, 8, 19, 9, 9, 5, 12, 10, 12, 9};

//Road Mapping Array
float RoadArr[10][10]={{0,1,0,0,0,0,0,0,1,0},{1,0,1,0,0,0,0,0,0,0},{0,1,0,0,0,0,1,0,0,1},{0,0,0,0,1,0,0,0,1,1},{0,0,0,1,0,1,0,0,0,0},{0,0,0,0,1,0,0,1,0,0},{0,0,1,0,0,0,0,1,0,0},{0,0,0,0,0,1,1,0,0,1},{1,0,0,1,0,0,0,0,0,0},{0,0,1,1,0,0,0,1,0,0}};

//Location Name Array
char AreaArr[10][20]={"Avadi","Tambaram","Chrompet","Koyambedu","Vyasarpadi","Royapettah","Sholinganallur","Adyar","Porur","T Nagar"};
printf("LOCATIONS\n");
for (i=0;i<9;i++)
{
	printf("%d.  %s\n",i+1,AreaArr[i]);
}
printf("10. T Nagar\n\n");

//Changing existing road booleans to distances
for (i=0;i<10;i++)
{
	for (j=0;j<10;j++)
	{
		//Checking if road exists
		if (RoadArr[i][j]==1)
		{
			int x_1=LocationArr[(3*i)+1];
			int y_1=LocationArr[(3*i)+2];
			int x_2=LocationArr[(3*j)+1];
			int y_2=LocationArr[(3*j)+2];
			RoadArr[i][j]=DistanceFormula(x_1,y_1,x_2,y_2);
		}
	}
}

//Printing example distance
//printf("%f",RoadCheck[0][1]);

/*-------------------------------------------------------------------------------------------*/

int Pickup_Loc,Drop_Loc,Type_Of_Vehicle;

//Getting pickup location, drop location and type of vehicle as input from user

//Case where invalid pickup location is entered
while (1)
{
	printf("Enter Pickup Location [1-10]: ");
	scanf("%d",&Pickup_Loc);
	
	if (Pickup_Loc>10 || Pickup_Loc<1)
		printf("Error! Enter a Valid Location!\n\n");
	else
		break;
}

//Case where invalid drop location is entered or pickup location is same as drop location
while (1)
{
	printf("\nEnter  Drop  Location [1-10]: ");
	scanf("%d",&Drop_Loc);

	if (Drop_Loc>10 || Drop_Loc<1)
		printf("Error! Enter a Valid Location!\n");

	else if (Pickup_Loc==Drop_Loc)
		printf("Error! Enter a Different Location!\n");
	
	else
		break;
}

printf("\n");

/*-------------------------------------------------------------------------------------------*/

DCalc(Pickup_Loc, RoadArr, TreeArr, CheckArr, &CA_len);
float Distance=TreeArr[Drop_Loc-1];

//Printing TreeArr for verification
/*printf("Tree Array:\n");
for (i=0;i<10;i++)
	printf("%f ",TreeArr[i]);
printf("\n");*/

/*-------------------------------------------------------------------------------------------*/

//Storing Fare Details
float Base_Fare[4]={40,50,60,70};
float Per_KM_Fare[4]={10,11,12,13};
float Cancellation_Charge=20;
char VArr[4][10]={"Auto","Mini","Sedan","SUV"};
int Cab_Choice;

//Getting input for type of vehicle
printf("TYPE OF VEHICLE\n1. Auto  (Suitable for 2-3 Passengers, Economical!)		       [1]\n2. Mini  (Suitable for 3-4 Passengers, AC Ride!) 		       [2]\n3. Sedan (Suitable for 3-4 Passengers, Luxurious!) 		       [3]\n4. SUV   (Suitable for 5-6 Passengers, Comfortable for Larger Groups!) [4]\n");

while (1)
{
	printf("\nEnter Type of Vehicle [1-4]: ");
	scanf("%d",&Cab_Choice);
	
	if (Cab_Choice>0 && Cab_Choice<5)
		break;

	else
		printf("Invalid Choice! Enter a Valid Type of Vehicle!\n");
}

//Printing details
printf("\nRIDE DETAILS");
printf("\nPickup Location : %s",AreaArr[Pickup_Loc-1]);	
printf("\nDrop Location   : %s",AreaArr[Drop_Loc-1]);
printf("\nType of Vehicle : %s",VArr[Cab_Choice-1]);
printf("\nDistance        : %.2f KM",Distance);

/*-------------------------------------------------------------------------------------------*/

//Getting System Time to Compute Surge Fee
time_t T = time(NULL);
struct tm tm = *localtime(&T);
int curtime=tm.tm_hour;

//Estimated Fare Calculation - taking 30% of Base Fare as the amount required to reach the location
float Estimated_Fare;
if (Distance>4)
	Estimated_Fare=Base_Fare[Cab_Choice-1]+((Distance-4)*Per_KM_Fare[Cab_Choice-1])+(Base_Fare[Cab_Choice-1]*0.3)+(Customer.Cancellation*20);
else
	Estimated_Fare=Base_Fare[Cab_Choice-1]*1.3+(Customer.Cancellation*20);

//Computing Surge Fee
float Surge=0;
if ((curtime>19 && curtime<21) || (curtime>8 && curtime<10))
{
	Surge=Estimated_Fare*0.1;
	Estimated_Fare+=Surge;
}	

//Printing Estimated Fare
printf("\n\nESTIMATED BILL");
printf("\nBase Fare               : Rs. %.2f",Base_Fare[Cab_Choice-1]);
printf("\nPer KM Fare [Rs. %.2f] : Rs. %.2f",Per_KM_Fare[Cab_Choice-1],((Distance-4)*Per_KM_Fare[Cab_Choice-1]));
printf("\nAdditional Charges      : Rs. %.2f",(Base_Fare[Cab_Choice-1]*0.3));
printf("\nCancellation Charges    : Rs. %.2f",(float) (Customer.Cancellation*20));
printf("\nSurge Fee               : Rs. %.2f",Surge);
printf("\nTOTAL ESTIMATED FARE    : Rs. %.2f\n\n",Estimated_Fare);

/*-------------------------------------------------------------------------------------------*/

//Getting Booking Confirmation
int Confirmation;
while (1)
{
	printf("Confirm Ride? [Yes/1][No/0]: ");
	scanf("%d",&Confirmation);

	if (Confirmation==0 || Confirmation==1)
		break;
	else
		printf("Error! Enter a Valid Response!\n\n");
}
printf("\n");

/*-------------------------------------------------------------------------------------------*/

//Opening File in Read Mode
FILE *fp;
fp=fopen("Driver_Details.txt","r");

//Defining Structures
struct D Outputter;
struct D Driver_Database[24];

for (i=0;i<24;i++)
{
	fread(&Outputter,sizeof(struct D),1,fp);
	Driver_Database[i]=Outputter;
}

//Printing a random data for verification
//printf("%d\n",Driver_Database[11].Type_Of_Vehicle);

//Closing File
fclose(fp);

/*-------------------------------------------------------------------------------------------*/

if (Confirmation==1)
{
	//Storing location coordinates by retrieving from Location Array
	int x1,y1,x2,y2;
	x1=LocationArr[((Pickup_Loc-1)*3)+1];
	y1=LocationArr[((Pickup_Loc-1)*3)+2];
	x2=LocationArr[((Drop_Loc-1)*3)+1];
	y2=LocationArr[((Drop_Loc-1)*3)+2];

	//Defining Variables
	int Rating=-1;
	int Assigned_Driver_ID=0;
	int check3=0; 
	float Driver_Distances[24];
	int Nearest_Node_X, Nearest_Node_Y,N1,N2;
	float D1,D2;
	float Dist_Check=5000;

	//Iterating through all Drivers
	for (i=0;i<24;i++)
	{
		D1=0;
		D2=0;

		//Checking if Driver is already at Pickup Location
		if (Driver_Database[i].x_coordinate==x1 && Driver_Database[i].y_coordinate==y1 && Driver_Database[i].Rating>Rating && Driver_Database[i].Type_Of_Vehicle==Cab_Choice)
		{
			Rating=Driver_Database[i].Rating;
			Assigned_Driver_ID=Driver_Database[i].D_ID;
			check3=1;
			Dist_Check=0;
		}

		else if (Driver_Database[i].Type_Of_Vehicle==Cab_Choice)
		{
			//Resetting the values of Road_Of_Driver Array for every iteration
			for (j=0;j<10;j++)
				Road_Of_Driver[j]=0;
	
			Driver_Road_Finder(Driver_Database[i].x_coordinate,Driver_Database[i].y_coordinate, Road_Of_Driver);

			for (j=0;j<10;j++)
			{
				if (Road_Of_Driver[j]==1)
				{
					//Finding the x and y coordinates of the Nodes connecting the road of the Driver
					Nearest_Node_X=LocationArr[((j)*3)+1];
					Nearest_Node_Y=LocationArr[((j)*3)+2];

					//Since there are two nodes that are at the ends of a road (line segment), we consider both the distances and the compute shortest distance for the Driver to reach the Pickup Location 
					if (D1==0)
					{
						D1=DistanceFormula(Driver_Database[i].x_coordinate,Driver_Database[i].y_coordinate,Nearest_Node_X,Nearest_Node_Y);
						N1=j;
					}

					else
					{
						D2=DistanceFormula(Driver_Database[i].x_coordinate,Driver_Database[i].y_coordinate,Nearest_Node_X,Nearest_Node_Y);
						N2=j;
						break;
					}
				}
			}

			//Storing the shortest distances to be travelled by the Driver to reach the Pickup Location
			if ((D1+TreeArr[N1])<(D2+TreeArr[N2]))
				Driver_Distances[i]=D1+TreeArr[N1];
			else
				Driver_Distances[i]=D2+TreeArr[N2];
		}

		else
			Driver_Distances[i]=5001;
	}

	for (i=0;i<24;i++)
	{
		//Checks if Driver has already been assigned in the previous iteration and stops the iteration if yes
		if (check3==1)
			break;

		else
		{
			//Assigns the closest Driver with the highest Rating who is within the 8km radius
			if (((Driver_Distances[i]<Dist_Check)||(Driver_Distances[i]==Dist_Check && Driver_Database[i].Rating>Rating))&&(Driver_Distances[i]<8))
			{
				Dist_Check=Driver_Distances[i];
				Rating=Driver_Database[i].Rating;
				Assigned_Driver_ID=Driver_Database[i].D_ID;
			}
		}
	}

	//Case if no driver is assigned
	if (Assigned_Driver_ID!=0)
	{
		//Printing Driver details
		printf("RIDE CONFIRMED");
		printf("\nAssigned Driver ID  : %d",Assigned_Driver_ID);
		printf("\nDriver Name         : %c",Driver_Database[Assigned_Driver_ID-1].Name);
		printf("\nDriver Phone Number : %d",Driver_Database[Assigned_Driver_ID-1].Phone_No);
		printf("\nDriver Rating       : %.2f\n\n",Driver_Database[Assigned_Driver_ID-1].Rating);

/*-------------------------------------------------------------------------------------------*/

		//Checking if Ride needs to be cancelled
		int Cancel;
		while (1)
		{
			printf("Cancel Ride? [Yes/1][No/0]: ");
			scanf("%d",&Cancel);

			if (Cancel==0 || Cancel==1)
				break;
			else
				printf("Error! Enter a Valid Response!\n\n");
		}
		printf("\n");
	
/*-------------------------------------------------------------------------------------------*/

		if (Cancel==1)
		{
			printf("NOTE: Cancellation Charge will be added to your Next Ride\n\n");
			//Increments number of Cancellations the Customer has done and stores it
			Customer.Cancellation+=1;
		}
	
		else
		{
			//Checks if the Ride has been completed
			int Complete;
			while (1)
			{
				printf("Ride Completed? [Yes/1][No/0]: ");
				scanf("%d",&Complete);

				if (Complete==1)
					break;
	
				else if (Complete!=0)
					printf("Error! Enter a Valid Response!\n\n");
		
				else
					printf("\n");
			}
			printf("\n");
	
/*-------------------------------------------------------------------------------------------*/

			//Bill is generated using the Formula Fare=Base + Per_KM + Cancellation
			float Bill;
			if (Distance>4)
				Bill=Base_Fare[Cab_Choice-1]+((Distance-4)*Per_KM_Fare[Cab_Choice-1])+((Dist_Check*Per_KM_Fare[Cab_Choice-1])/2)+(Customer.Cancellation*20);
		
			else
				Bill=Base_Fare[Cab_Choice-1]+(Customer.Cancellation*20)+((Dist_Check*Per_KM_Fare[Cab_Choice-1])/2);
		
			//Calculating Surge Fee
			if ((curtime>19 && curtime<21) || (curtime>8 && curtime<10))
				Bill*=1.1;

			//Printing Bill
			printf("FINAL BILL");
			printf("\nBase Fare               : Rs. %.2f",Base_Fare[Cab_Choice-1]);
			printf("\nPer KM Fare [Rs. %.2f] : Rs. %.2f",Per_KM_Fare[Cab_Choice-1],((Distance-4)*Per_KM_Fare[Cab_Choice-1]));
			printf("\nAdditional Charges      : Rs. %.2f",((Dist_Check*Per_KM_Fare[Cab_Choice-1])/2));
			printf("\nCancellation Charges    : Rs. %.2f",(float) (Customer.Cancellation*20));
			printf("\nSurge Fee               : Rs. %.2f",Surge);
			printf("\nTOTAL FARE              : Rs. %.2f\n\n",Bill);

			//Resets Customer Cancellation
			Customer.Cancellation=0;

/*-------------------------------------------------------------------------------------------*/

			//Input Rating from User
			float New_Rating;
			while (1)
			{
				printf("Enter Rating [1-5]: ");
				scanf("%f",&New_Rating);

				if (New_Rating>0 && New_Rating<=5)
					break;
				else
					printf("Error! Enter a Valid Response!\n\n");
			}
			printf("\n");

			//Change Driver Rating
			Driver_Database[Assigned_Driver_ID-1].Rating*=Driver_Database[Assigned_Driver_ID-1].No_Of_Raters;
			Driver_Database[Assigned_Driver_ID-1].No_Of_Raters+=1;
			Driver_Database[Assigned_Driver_ID-1].Rating+=New_Rating;
			Driver_Database[Assigned_Driver_ID-1].Rating/=Driver_Database[Assigned_Driver_ID-1].No_Of_Raters;

/*-------------------------------------------------------------------------------------------*/

			//Change Driver Location to Drop Location
			Driver_Database[Assigned_Driver_ID-1].x_coordinate=x2;
			Driver_Database[Assigned_Driver_ID-1].y_coordinate=y2;	
		}
	}

	else
		printf("Apologies. NO DRIVERS FOUND NEARBY.\n\n");
}

/*-------------------------------------------------------------------------------------------*/

//Update Driver Details in File
fp=fopen("Driver_Details.txt","w");
for (i=0;i<24;i++)
{
	fwrite(&Driver_Database[i],sizeof(struct D),1,fp);
}
fclose(fp);

//Update Customer Details in File
cfp=fopen("Customer_Details.txt","w");
fwrite(&Customer,sizeof(struct C),1,cfp);
fclose(cfp);

//Checking if it was upoaded properly
/*cfp=fopen("Customer_Details.txt","r");
fread(&Customer,sizeof(struct C),1,cfp);
printf("%d\n",Customer.Cancellation);
fclose(cfp);*/

/*struct D Test[24];
struct D test;
fp=fopen("Driver_Details.txt","r");
for (i=0;i<24;i++)
{
	fread(&test,sizeof(struct D),1,fp);
	Test[i]=test;
}
printf("%f\n",Test[1].x_coordinate);
fclose(fp);*/

/*-------------------------------------------------------------------------------------------*/

printf("THANK YOU FOR USING OUR APPLICATION!");

return 0;
}