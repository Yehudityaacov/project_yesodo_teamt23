#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>
#include <stdbool.h>


#define size 50
#define IDSIZE 20
#define NAMESIZE 30
#define GENDERSIZE 10
#define PASSWORDSIZE 10
#define stringSIZE 80
//levels constans in order to calculate the amount of alimony
#define LEVEL1 0.10
#define LEVEL2 0.15
#define LEVEL3 0.20
#define LEVEL4 0.25



// colors for hConsole
/*#define WHITE 1
#define BLUE 2
#define GREEN 3
#define RED 4
#define PINK 5
#define YELLOW 6
#define GREY 7
#define PURPLE 8
#define TURQUISE 9 */



#define D_BLUE 1
#define D_GREEN 2
#define TURQ 3
#define D_RED 4
#define PURPLE 5
#define YUCK 6
#define WHITE 7
#define GREY 8
#define BLUE 9
#define GREEN 10
#define L_BLUE 11
#define RED 12
#define PINK 13
#define YELLOW 14
#define REAL_WHITE 15
#define CYAN 16
#define MAGENTA 17
#define LIGHTMAGENTA 18

typedef enum{ UP = 'H', DOWN = 'P' }Arrow;

int requestCounter = 0;
int userCounter = 0;

typedef struct newBorn
{

	char *babyID;
	char *babyName;

}newBorn;


typedef struct personalStatus
{

	char *currentStatus;
	char *newStatus;

}personalStatus;

typedef struct familyChange
{

	char *currentFamilyName;
	char *newFamilyName;

}familyChange;

typedef struct Request
{
	int request_ID;    // number of the request
	char *request_UserID;
	newBorn *form1;
	personalStatus *form2;
	familyChange *form3;

}Request;

typedef struct User
{
	char *firstName;
	char *lastName;
	char *ID;
	char *gender;
	char *familyStatus;
	int kids;
	char *password;
	int numRequests;
	Request **requestList;
}User;

typedef struct Manager
{
	char *firstName;
	char *lastName;
	char *M_ID;
	char *M_password;
}Manager;

typedef struct CotentEditor
{
	char *firstName;
	char *lastName;
	char *E_ID;
	char *E_password;
}CotentEditor;

typedef struct LogIn
{
	char *ID;
	char *password;
}LogIn;


User *getUsersArr();///declare it 


bool checkMatch_id_password(char *id, char *password)
{
	int i = 0;
	int index = -1;
	char ch;
	char buffer[size];
	User *users = getUsersArr();
	FILE *fp = fopen("ManagersAccounts.txt", "r");

	for (i = 0; i < userCounter; i++)
	{
		if (!strcmp(users[i].ID, id))
		{
			index = i;
			break;
		}
	}

	do
	{
		ch = fscanf(fp, "%s", buffer);
		if (!strcmp(buffer, "ID:"))
		{
			ch = fscanf(fp, "%s", buffer);
			if (!strcmp(buffer, id))
			{
				ch = fscanf(fp, "%s", buffer);
				if (!strcmp(buffer, "password:"))
				{
					ch = fscanf(fp, "%s", buffer);
					if (!strcmp(buffer, password))
					{
						fclose(fp);
						return true;
					}
				}
			}
		}
	} while (ch != EOF);

	fclose(fp);

	if (index == -1)
		return false;
	if (!strcmp(users[index].password, password))
		return true;
	else
		return false;

}
bool checkID_database(char *id)
{
	char ch;
	char buffer[size];
	FILE *fp = fopen("userText.txt", "r");
	FILE *managers = fopen("ManagersAccounts.txt", "r");
	if (fp == NULL)
		printf("warning: file was NOT found!!!\n ");
	else
	{
		do
		{
			ch = fscanf(fp, "%s", buffer);
			if (!strcmp("ID:", buffer))
			{
				ch = fscanf(fp, "%s", buffer);
				if (!strcmp(id, buffer))
				{
					fclose(fp);
					return true;
				}
			}

		} while (ch != EOF);

		do
		{
			ch = fscanf(managers, "%s", buffer);
			if (!strcmp("ID:", buffer))
			{
				ch = fscanf(managers, "%s", buffer);
				if (!strcmp(id, buffer))
				{
					fclose(managers);
					return true;
				}
			}

		} while (ch != EOF);



		fclose(managers);
		fclose(fp);
		return false;
	}


}
bool checkMatch_id_personalStatus(char *id, char *status)////////check if working
{
	char ch;
	char buffer[size];
	FILE *fp = fopen("userText.txt", "r");
	if (fp == NULL)
		printf("warning: file was NOT found!!!\n");
	else
	{
		do
		{
			ch = fscanf(fp, "%s", buffer);
			if (!strcmp("ID:", buffer))
			{
				ch = fscanf(fp, "%s", buffer);
				if (!strcmp(id, buffer))
				{
					ch = fscanf(fp, "%s", buffer);
					ch = fscanf(fp, "%s", buffer);
					ch = fscanf(fp, "%s", buffer);
					ch = fscanf(fp, "%s", buffer);
					if (!strcmp(status, buffer))
					{
						fclose(fp);
						return true;
					}
				}
			}

		} while (ch != EOF);
	}
	fclose(fp);
	return false;

}
bool check_ifRequest(int Requestnum)
{
	char ch;
	char buffer[size];
	FILE *fp = fopen("requestText.txt", "r");
	if (fp == NULL)
		printf("warning: file was NOT found!!!\n");
	else
	{
		do
		{
			ch = fscanf(fp, "%s", buffer);
			if (!strcmp("request_ID:", buffer))
			{
				ch = fscanf(fp, "%s", buffer);
				if (Requestnum == atoi(buffer))
				{
					fclose(fp);
					return true;
				}
			}

		} while (ch != EOF);
		fclose(fp);
		return false;
	}
}
bool checkValid_personalStatus(char* status)
{
	if (strcmp(status, "single") && strcmp(status, "SINGLE") && strcmp(status, "Single") && strcmp(status, "married") && strcmp(status, "MARRIED") && strcmp(status, "Married"))
		return false;
	else
		return true;
}
void writeRequestToFile(Request *request)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int i = 0;
	FILE *fp = fopen("requestText.txt", "a");
	if (fp == NULL)
		printf("warning: file was NOT found!!!\n ");
	else
	{
		fprintf(fp, "~\n");
		fprintf(fp, "request_ID: %d\n", request->request_ID);
		fprintf(fp, "request_userID: %s\n", request->request_UserID);
		if (request->form1 != NULL)
			fprintf(fp, "form1: %s %s\n", request->form1[i].babyID, request->form1[i].babyName);

		if (request->form2 != NULL)
			fprintf(fp, "form2: %s %s\n", request->form2[i].currentStatus, request->form2[i].newStatus);

		if (request->form3 != NULL)
			fprintf(fp, "form3: %s %s\n", request->form3[i].currentFamilyName, request->form3[i].newFamilyName);


		fprintf(fp, "~\n");
		SetConsoleTextAttribute(hConsole, PINK);
		printf("\n\n*** request was added succesfully!!! ***\n");
		SetConsoleTextAttribute(hConsole, WHITE);
		getchar();

		fclose(fp);
	}

}


bool checkMatch_id_lastName(char *id, char *lastName)
{
	char ch;
	char buffer[size];
	FILE *fp = fopen("userText.txt", "r");
	if (fp == NULL)
		printf("warning: file was NOT found!!!\n");
	else
	{
		do
		{
			ch = fscanf(fp, "%s", buffer);
			if (!strcmp("lastName:", buffer))
			{
				ch = fscanf(fp, "%s", buffer);
				if (!strcmp(lastName, buffer))
				{
					ch = fscanf(fp, "%s", buffer);
					ch = fscanf(fp, "%s", buffer);
					if (!strcmp(id, buffer))
					{
						fclose(fp);
						return true;
					}
					else
					{
						fclose(fp);
						return false;
					}
				}
			}

		} while (ch != EOF);
		fclose(fp);
		return false;
	}


}

bool addUser_To_database(User *user)
{
	int flag = 0;
	FILE *fp = fopen("userText.txt", "a");

	fprintf(fp, "~\n");
	fprintf(fp, "firstName: %s\n", user->firstName);
	flag++;
	fprintf(fp, "lastName: %s\n", user->lastName);
	flag++;
	fprintf(fp, "ID: %s\n", user->ID);
	flag++;
	fprintf(fp, "gender: %s\n", user->gender);
	flag++;
	fprintf(fp, "familyStatus: %s\n", user->familyStatus);
	flag++;
	fprintf(fp, "kids: %d\n", user->kids);
	flag++;
	fprintf(fp, "password: %s\n", user->password);
	flag++;
	fprintf(fp, "numRequests: %d\n", user->numRequests);

	flag++;
	fprintf(fp, "~\n");

	fclose(fp);

	if (flag == 8)
		return true;
	else
		return false;


}


void changeUsers_database(User *user)
{
	int i = 0;
	int j = 0;
	FILE *fp = fopen("userText.txt", "w");

	for (i = 0; i < userCounter; i++)
	{
		fprintf(fp, "~\n");
		fprintf(fp, "firstName: %s\n", user[i].firstName);
		fprintf(fp, "lastName: %s\n", user[i].lastName);
		fprintf(fp, "ID: %s\n", user[i].ID);
		fprintf(fp, "gender: %s\n", user[i].gender);
		fprintf(fp, "familyStatus: %s\n", user[i].familyStatus);
		fprintf(fp, "kids: %d\n", user[i].kids);
		fprintf(fp, "password: %s\n", user[i].password);
		fprintf(fp, "numRequests: %d\n", user[i].numRequests);
		if (user[i].requestList != NULL)
		{
			for (j = 0; j < user[i].numRequests; j++)
			{
				if (user[i].requestList[j]->form1 != NULL)
					fprintf(fp, "form1: %d %s %s\n", user[i].requestList[j]->request_ID, user[i].requestList[j]->form1->babyID, user[i].requestList[j]->form1->babyName);

				if (user[i].requestList[j]->form2 != NULL)
					fprintf(fp, "form2: %d %s %s\n", user[i].requestList[j]->request_ID, user[i].requestList[j]->form2->currentStatus, user[i].requestList[j]->form2->newStatus);

				if (user[i].requestList[j]->form3 != NULL)
					fprintf(fp, "form3: %d %s %s\n", user[i].requestList[j]->request_ID, user[i].requestList[j]->form3->currentFamilyName, user[i].requestList[j]->form3->newFamilyName);

			}
		}fprintf(fp, "~\n");

	}
	fclose(fp);

}

Request *getRequestsArr()
{
	FILE *fp = fopen("requestText.txt", "r");
	Request *request = NULL;
	int i = 0;
	char ch;
	char buffer[size];
	char field1[size];
	char field2[size];
	requestCounter = 0;
	do
	{
		ch = fscanf(fp, "%s", buffer);
		if (!strcmp(buffer, "request_ID:"))
		{
			requestCounter++;//in order to sum num of requests
			if (request == NULL)
				request = (Request*)malloc(sizeof(Request));
			else
				request = (Request*)realloc(request, sizeof(Request)*(i + 2));
			ch = fscanf(fp, "%s", buffer);
			request[i].request_ID = atoi(buffer);
			ch = fscanf(fp, "%s", buffer); // skip "request_userID:"
			ch = fscanf(fp, "%s", buffer);
			request[i].request_UserID = strdup(buffer);///////////////need to free?????????
			ch = fscanf(fp, "%s", buffer);
			ch = fscanf(fp, "%s", field1);
			ch = fscanf(fp, "%s", field2);
			if (!strcmp(buffer, "form1:"))
			{
				request[i].form1 = (newBorn*)malloc(sizeof(newBorn));
				request[i].form1->babyID = strdup(field1);
				request[i].form1->babyName = strdup(field2);
				request[i].form2 = request[i].form3 = NULL;
			}
			if (!strcmp(buffer, "form2:"))
			{
				request[i].form2 = (personalStatus*)malloc(sizeof(personalStatus));
				request[i].form2->currentStatus = strdup(field1);
				request[i].form2->newStatus = strdup(field2);
				request[i].form1 = request[i].form3 = NULL;
			}
			if (!strcmp(buffer, "form3:"))
			{
				request[i].form3 = (familyChange*)malloc(sizeof(familyChange));
				request[i].form3->currentFamilyName = strdup(field1);
				request[i].form3->newFamilyName = strdup(field2);
				request[i].form1 = request[i].form2 = NULL;
			}
			i++;
		}
	} while (ch != EOF);
	fclose(fp);
	return request;
}
void printRequest(Request *request)
{
	int i = 0;


	while (i < requestCounter)
	{
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		printf("Request ID: %d\n", request[i].request_ID);
		printf("User ID: %s\n", request[i].request_UserID);
		if (request[i].form1)
			printf("Baby ID: %s\nBaby Name: %s\n", request[i].form1->babyID, request[i].form1->babyName);
		if (request[i].form2)
			printf("Old Status: %s\nNew Status: %s\n", request[i].form2->currentStatus, request[i].form2->newStatus);
		if (request[i].form3)
			printf("Family Current Name: %s\nFamily New Name: %s\n", request[i].form3->currentFamilyName, request[i].form3->newFamilyName);
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		i++;
	}

}


void printUsers(User *user)
{
	int i = 0;
	int j = 0;
	while (i < userCounter)
	{
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		printf("First name: %s\n", user[i].firstName);
		printf("Last name: %s\n", user[i].lastName);
		printf("ID: %s\n", user[i].ID);
		printf("Gender: %s\n", user[i].gender);
		printf("Family status: %s\n", user[i].familyStatus);
		printf("Kids: %d\n", user[i].kids);
		printf("Password: %s\n", user[i].password);
		printf("Num of requests: %d\n", user[i].numRequests);
		printf(" ~~~ User Requests: ~~~ \n");
		for (j = 0; j < user[i].numRequests; j++)
		{
			if (user[i].requestList[j]->form1)
			{
				printf("Request ID: %d\n", user[i].requestList[j]->request_ID);
				printf("Baby ID: %s\n", user[i].requestList[j]->form1->babyID);
				printf("Baby name: %s\n", user[i].requestList[j]->form1->babyName);
			}
			else if (user[i].requestList[j]->form2)
			{
				printf("Request ID: %d\n", user[i].requestList[j]->request_ID);
				printf("Current personal status: %s\n", user[i].requestList[j]->form2->currentStatus);
				printf("New personal status: %s \n", user[i].requestList[j]->form2->newStatus);
			}
			else if (user[i].requestList[j]->form3)
			{
				printf("Request ID: %d\n", user[i].requestList[j]->request_ID);
				printf("Current last name: %s\n", user[i].requestList[j]->form3->currentFamilyName);
				printf("New last name: %s\n", user[i].requestList[j]->form3->newFamilyName);
			}

		}

		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		i++;

	}

}

int getRequestID()
{
	char ch;
	char buffer[size];
	FILE *fp = fopen("requestText.txt", "r");
	int num = 0;

	fseek(fp, 0, SEEK_SET);
	do
	{
		ch = fscanf(fp, "%s", buffer);
		if (!strcmp(buffer, "request_ID:"))
			fscanf(fp, "%d", &num);

	} while (ch != EOF);
	fclose(fp);
	return num;


}

Request *fill_form_changePersonalStatus()
{
	int cnt = 0;
	int i = 0, index = 0;
	char userId[IDSIZE];
	char current_status[NAMESIZE];
	char new_status[NAMESIZE];

	Request *newRequest;
	personalStatus *newApplication;
	FILE *fp = fopen("requestText.txt", "r");
	if (fp == NULL)
		printf("warning: file was NOT found!!!\n");
	else
	{
		printf("\n\n ***** Fill a form - change personal status *****\n");
		newRequest = (Request*)malloc(sizeof(Request));
		printf("please enter your ID:\n");
		gets(userId);

		if (!checkID_database(userId))
		{
			do
			{
				printf("sorry, the ID is NOT in our database!\n");
				printf("please try again: \n");
				gets(userId);


			} while (!checkID_database(userId));

		}

		newApplication = (personalStatus*)malloc(sizeof(personalStatus));
		printf("please enter your current personal status - single/married/divorced/widoer/widow and etc :\n");
		gets(current_status);

		if (!checkMatch_id_personalStatus(userId, current_status))
		{
			do
			{
				printf("sorry, there was NOT match according ID and your current personal status you entered!\n");
				printf("please try again - enter your current personal status: \n");
				gets(current_status);


			} while (!checkMatch_id_personalStatus(userId, current_status));
		}
		printf("please enter your new personal status:\n");
		gets(new_status);
		//if (!checkValid_personalStatus(new_status))///////////improve and apply all status!
		//{
		//	printf("NOT VALID!!!\n\n");
		//}

		newApplication->currentStatus = current_status;
		newApplication->newStatus = new_status;
		newRequest->form2 = newApplication;
		newRequest->form1 = NULL;
		newRequest->form3 = NULL;
		newRequest->request_ID = getRequestID() + 1;
		newRequest->request_UserID = userId;

		User *users = getUsersArr();
		for (i = 0; i < userCounter; i++)
		{
			if (!strcmp(users[i].ID, userId))
			{
				index = i;
				break;
			}
		}


		int k = users[index].numRequests;
		if (users[index].numRequests == 0)
		{
			users[index].requestList = (Request*)malloc(sizeof(Request));
			users[index].requestList = NULL;
		}
		else
			users[index].requestList = (Request*)realloc(users[index].requestList, sizeof(Request)*(k + 2));


		users[index].numRequests++;
		users[index].requestList[k] = (Request*)malloc(sizeof(Request));
		users[index].requestList[k]->form2 = (personalStatus*)malloc(sizeof(personalStatus));
		users[index].requestList[k]->request_ID = newRequest->request_ID;
		users[index].requestList[k]->form2->currentStatus = strdup(current_status);
		users[index].requestList[k]->form2->newStatus = strdup(new_status);
		users[index].requestList[k]->form1 = users[index].requestList[k]->form3 = NULL;



		//printUsers(users); only check
		changeUsers_database(users);




	}
	fclose(fp);
	writeRequestToFile(newRequest);
}

Request *fill_form_newBorn()
{
	int i = 0, index = 0;
	int requestIndex = 0;

	char motherID[IDSIZE];
	char babyID[IDSIZE];
	char babyName[IDSIZE];

	Request *newRequest;
	newBorn *newBornApplication;
	FILE *fp = fopen("requestText.txt", "r");
	if (fp == NULL)
		printf("warning: file was NOT found!!!\n ");
	else
	{
		printf("***** Fill a form - new born registration *****\n\n");
		newRequest = (Request*)malloc(sizeof(Request));
		printf("please enter mother ID:\n");
		gets(motherID);
		if (checkID_database(motherID))
		{
			newBornApplication = (newBorn*)malloc(sizeof(newBorn));
			printf("please enter new born ID:\n");
			gets(babyID);

			if (checkID_database(babyID))
			{
				do
				{
					printf("new born ID you entered is allready exist in the database!\n");
					printf("please try again: \n");
					gets(babyID);

				} while (checkID_database(babyID));

			}

			User *users = getUsersArr();

			printf("please enter new born name:\n");
			gets(babyName);
			newBornApplication->babyID = babyID;
			newBornApplication->babyName = babyName;
			newRequest->form1 = newBornApplication;
			newRequest->form2 = NULL;
			newRequest->form3 = NULL;
			newRequest->request_ID = getRequestID() + 1;
			newRequest->request_UserID = motherID;

			for (i = 0; i < userCounter; i++)
			{
				if (!strcmp(users[i].ID, motherID))
				{
					index = i;
					break;
				}

			}

			int k = users[index].numRequests;

			if (users[index].numRequests == 0)
			{
				users[index].requestList = (Request*)malloc(sizeof(Request));
				users[index].requestList = NULL;
			}


			else
				users[index].requestList = (Request*)realloc(users[index].requestList, sizeof(Request)*(k + 2));



			users[index].numRequests++;
			users[index].requestList[k] = (Request*)malloc(sizeof(Request));
			users[index].requestList[k]->form1 = (newBorn*)malloc(sizeof(newBorn));
			users[index].requestList[k]->request_ID = newRequest->request_ID;
			users[index].requestList[k]->form1->babyID = strdup(babyID);
			users[index].requestList[k]->form1->babyName = strdup(babyName);
			users[index].requestList[k]->form2 = users[index].requestList[k]->form3 = NULL;


			//printUsers(users); //check for myself
			changeUsers_database(users);







		}
	}
	fclose(fp);
	writeRequestToFile(newRequest);

}

Request *fill_form_changeLastName()
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	int index = 0;
	int i = 0;
	char userID[IDSIZE];
	char current_lastName[NAMESIZE];
	char new_lastName[NAMESIZE];

	Request *newRequest;
	familyChange *newApplication;
	FILE *fp = fopen("requestText.txt", "r");
	if (fp == NULL)
		printf("warning: file was NOT found!!!\n");


	else
	{
		printf("\n ***** Fill a form - change last name *****\n");
		SetConsoleTextAttribute(hConsole, YELLOW);
		printf("\nFor clarification: user can apply to change his\her last name resulting changing personal status(marriage/Divorce/Widowhood and etc)\n ");
		printf("meaning you will be asked to present relevant documents Further!\n\n\n");
		SetConsoleTextAttribute(hConsole, WHITE);
		newRequest = (Request*)malloc(sizeof(Request));
		printf("please enter your ID:\n");
		gets(userID);

		if (!checkID_database(userID))
		{
			do
			{
				printf("sorry, the ID is NOT in our database!\n");
				printf("please try again: \n");
				gets(userID);

			} while (!checkID_database(userID));

		}


		newApplication = (familyChange*)malloc(sizeof(familyChange));
		printf("please enter current last name\n");
		gets(current_lastName);
		if (checkMatch_id_lastName(userID, current_lastName))
		{
			printf("please enter new last name:\n");
			gets(new_lastName);
			newApplication->currentFamilyName = current_lastName;
			newApplication->newFamilyName = new_lastName;
			newRequest->form3 = newApplication;
			newRequest->form1 = NULL;
			newRequest->form2 = NULL;
			newRequest->request_ID = getRequestID() + 1;
			newRequest->request_UserID = userID;
		}

		User *users = getUsersArr();

		for (i = 0; i < userCounter; i++)
		{
			if (!strcmp(users[i].ID, userID))
			{
				index = i;
				break;
			}

		}

		int k = users[index].numRequests;

		if (users[index].numRequests == 0)
		{
			users[index].requestList = (Request*)malloc(sizeof(Request));
			users[index].requestList = NULL;
		}


		else
			users[index].requestList = (Request*)realloc(users[index].requestList, sizeof(Request)*(k + 2));


		users[index].numRequests++;
		users[index].requestList[k] = (Request*)malloc(sizeof(Request));
		users[index].requestList[k]->form3 = (familyChange*)malloc(sizeof(familyChange));
		users[index].requestList[k]->request_ID = newRequest->request_ID;
		users[index].requestList[k]->form3->currentFamilyName = strdup(current_lastName);
		users[index].requestList[k]->form3->newFamilyName = strdup(new_lastName);
		users[index].requestList[k]->form2 = users[index].requestList[k]->form1 = NULL;


		changeUsers_database(users);

	}
	writeRequestToFile(newRequest);
}



void familyHealthCenter_information()
{
	char ch;
	FILE *fp;
	fp = fopen("Brochure2.txt", "r");
	if (fp == NULL)
		printf("warning: file was NOT found!!!\n ");
	else
	{
		printf("\n*** station list of family health center ***\n\n");
		while ((ch = getc(fp)) != EOF)
			putchar(ch);
		fclose(fp);
	}



}

void Alimony_information()//getting information to winner in alimony case- getting the information from database
{
	char ch;
	FILE *fp;
	fp = fopen("Brochure1.txt", "r");
	if (fp == NULL)//in case file couldn't be opened
		printf("warning: file was NOT found!!!\n ");
	else
	{
		printf("\n*** Information to the winner in alimony case: ***\n\n");
		while ((ch = getc(fp)) != EOF)//as long as we dont get to the end of file
			putchar(ch);
		fclose(fp);
	}

}
void Alimony_calculator()
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	float total = 0;
	int kidsAmount;
	int mother_grossIncome, father_grossIncome;
	printf("\n\n~~~~ Alimony Calculator ~~~~\n");
	printf("please enter amount of kids under 18 age:\n");

	while ((scanf("%d", &kidsAmount) != 1) || kidsAmount < 0 || kidsAmount > 15)//check input is valid
	{
		while (getchar() != '\n');//in case its not
		SetConsoleTextAttribute(hConsole, RED);
		printf("INVALID INPUT! PLEASE TRY AGAIN\n");
		SetConsoleTextAttribute(hConsole, WHITE);
	}
	printf("please enter gross income level(for mother):\n");
	while ((scanf("%d", &mother_grossIncome) != 1) || mother_grossIncome<0 || mother_grossIncome > 1000000)//check input is valid
	{
		while (getchar() != '\n');
		SetConsoleTextAttribute(hConsole, RED);
		printf("INVALID INPUT! PLEASE TRY AGAIN\n");
		SetConsoleTextAttribute(hConsole, WHITE);

	}
	printf("please enter gross income level(for father):\n");
	while ((scanf("%d", &father_grossIncome) != 1) || father_grossIncome<0 || father_grossIncome > 1000000)//check input is valid
	{
		while (getchar() != '\n');
		SetConsoleTextAttribute(hConsole, RED);
		printf("INVALID INPUT! PLEASE TRY AGAIN\n");
		SetConsoleTextAttribute(hConsole, WHITE);

	}

	if (mother_grossIncome <= father_grossIncome)//case 1 - father income level is higer then the mother
	{
		if (0 <= father_grossIncome && father_grossIncome <= 5000)
		{
			total = kidsAmount*LEVEL2*father_grossIncome;
			SetConsoleTextAttribute(hConsole, TURQ);
			printf("*** \nThe TOTAL amount of alimony you deserve according the information you entered: ***\n");
			printf("%f ILS\n", total);
			SetConsoleTextAttribute(hConsole, WHITE);


		}
		else if (5000 < father_grossIncome && father_grossIncome <= 10000)
		{
			total = kidsAmount*LEVEL3*father_grossIncome;
			SetConsoleTextAttribute(hConsole, TURQ);
			printf("*** The TOTAL amount of alimony you deserve according the information you entered: ***\n");
			printf("%f ILS\n", total);
			SetConsoleTextAttribute(hConsole, WHITE);
		}
		else if (father_grossIncome > 10000)
		{
			total = kidsAmount*LEVEL4*father_grossIncome;
			SetConsoleTextAttribute(hConsole, TURQ);
			printf("*** The TOTAL amount of alimony you deserve according the information you entered: ***\n");
			printf("%f ILS\n", total);
			SetConsoleTextAttribute(hConsole, WHITE);
		}


	}
	else if (father_grossIncome < mother_grossIncome)//case 2 - if mother's income level is higer then father
	{
		if (0 <= father_grossIncome && father_grossIncome <= 5000)
		{
			total = kidsAmount*LEVEL1*father_grossIncome;
			SetConsoleTextAttribute(hConsole, TURQ);
			printf("*** The TOTAL amount of alimony you deserve according the information you entered: ***\n");
			printf("%f ILS\n", total);
			SetConsoleTextAttribute(hConsole, WHITE);
		}
		else if (5000 < father_grossIncome && father_grossIncome <= 10000)
		{
			total = kidsAmount*LEVEL2*father_grossIncome;
			SetConsoleTextAttribute(hConsole, TURQ);
			printf("*** The TOTAL amount of alimony you deserve according the information you entered: ***\n");
			printf("%f ILS\n", total);
			SetConsoleTextAttribute(hConsole, WHITE);
		}
		else if (father_grossIncome > 10000)
		{
			total = kidsAmount* LEVEL3*father_grossIncome;
			SetConsoleTextAttribute(hConsole, TURQ);
			printf("*** The TOTAL amount of alimony you deserve according the information you entered: ***\n");
			printf("%f ILS\n", total);
			SetConsoleTextAttribute(hConsole, WHITE);
		}


	}
	else
		printf("Couldn't be calculated!\n");//needed???
}


//manager functions
void pendingRequsts_display()
{
	char ch;
	FILE *fp = fopen("requestText.txt", "r");
	if (fp == NULL)
		printf("warning: file was NOT found!!!\n ");
	else
	{
		printf("\n\n ***** Pending REQUESTS report ***** \n\n");
		while ((ch = getc(fp)) != EOF)
			putchar(ch);
		fclose(fp);
	}

}
void print_singleUser(User *user)
{
	int j = 0;
	int i = 0;
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	printf("\n\n");
	printf("=================================\n");
	SetConsoleTextAttribute(hConsole, D_GREEN);
	printf("       USER INFORMATION:         \n");
	SetConsoleTextAttribute(hConsole, WHITE);
	printf("first name: %s\n", user->firstName);
	printf("last name: %s\n", user->lastName);
	printf("ID: %s\n", user->ID);
	printf("gender: %s\n", user->gender);
	printf("family status: %s\n", user->familyStatus);
	printf("kids: %d\n", user->kids);
	printf("password: %s\n", user->password);
	printf("number of requests: %d\n", user->numRequests);
	printf("~~ user requests: ~~\n");
	for (i = 0; i < user->numRequests; i++)
	{
		if (user->requestList[i]->form1)
		{
			printf("request_ID: %d\n", user[i].requestList[j]->request_ID);
			printf("Baby ID: %s\n", user[i].requestList[j]->form1->babyID);
			printf("Baby name: %s\n", user[i].requestList[j]->form1->babyName);
		}

		else if (user->requestList[i]->form2)
		{
			printf("request_ID: %d\n", user[i].requestList[j]->request_ID);
			printf("Current personal status: %s\n", user[i].requestList[j]->form2->currentStatus);
			printf("New personal status: %s \n", user[i].requestList[j]->form2->newStatus);
		}

		else if (user->requestList[i]->form3)
		{
			printf("request_ID: %d\n", user[i].requestList[j]->request_ID);
			printf("Current last name: %s\n", user[i].requestList[j]->form3->currentFamilyName);
			printf("New last name: %s\n", user[i].requestList[j]->form3->newFamilyName);
		}
		j++;
	}
	printf("=================================\n");

}
User *userQuery()
{
	char ch;
	char userID_input[IDSIZE];
	char buffer[size];
	char firstName[NAMESIZE];
	char lastName[NAMESIZE];
	char gender[GENDERSIZE];
	char status[IDSIZE];
	char kids[IDSIZE];
	char password[PASSWORDSIZE];
	//char userID[IDSIZE]; - dont need
	bool flag = true;


	FILE *fp = fopen("userText.txt", "r");
	if (fp == NULL)
		printf("warning: file was NOT found!!!\n ");
	printf("\n\n ***** USER QUERY *****\n\n");
	printf("please enter user ID: \n");
	gets(userID_input);


	while (!checkID_database(userID_input))
	{
		printf("ID is NOT exist in our database! please try again\n");
		gets(userID_input);
	}


	do
	{
		User *user = (User*)malloc(sizeof(User));
		ch = fscanf(fp, "%s", buffer);
		ch = fscanf(fp, "%s", buffer);//skip the "firstName:"
		fscanf(fp, "%s", firstName);
		user->firstName = firstName;
		ch = fscanf(fp, "%s", buffer);//skip the "lastName:"
		fscanf(fp, "%s", lastName);
		user->lastName = lastName;
		ch = fscanf(fp, "%s", buffer);//skip the "ID:"
		fscanf(fp, "%s", buffer);
		if (strcmp(userID_input, buffer))//if doesnt match
		{
			free(user);
			break;
		}
		else
		{
			user->ID = userID_input;
			ch = fscanf(fp, "%s", buffer); //skip the "gender:"
			fscanf(fp, "%s", gender);
			user->gender = gender;
			ch = fscanf(fp, "%s", buffer);//skip the "familyStatus:"
			fscanf(fp, "%s", status);
			user->familyStatus = status;
			ch = fscanf(fp, "%s", buffer); //skip the "kids:"
			fscanf(fp, "%s", kids);
			user->kids = atoi(kids);
			ch = fscanf(fp, "%s", buffer); //skip the "password:"
			fscanf(fp, "%s", password);
			user->password = password;
			ch = fscanf(fp, "%s", buffer);//skip the "numRequests: "
			ch = fscanf(fp, "%s", buffer);
			user->numRequests = atoi(buffer);
			/////////////need to apply and print user requests - dont forget

			flag = false;
			print_singleUser(user);
		}

	} while (ch != EOF && flag != false);

}
void changeRequest_database(Request *request)
{
	FILE *fp = fopen("requestText.txt", "w");
	int i = 0;
	fputs("counter: 1250\n", fp);
	for (i = 0; i < requestCounter; i++)
	{

		if (request[i].request_ID == 0 && i == requestCounter - 1)
			break;
		if (request[i].request_ID == 0)
			i++;


		fprintf(fp, "~\n");
		fprintf(fp, "request_ID: %d\n", request[i].request_ID);
		fprintf(fp, "request_userID: %s\n", request[i].request_UserID);
		if (request[i].form1 != NULL)
			fprintf(fp, "form1: %s %s\n", request[i].form1->babyID, request[i].form1->babyName);

		if (request[i].form2 != NULL)
			fprintf(fp, "form2: %s %s\n", request[i].form2->currentStatus, request[i].form2->newStatus);

		if (request[i].form3 != NULL)
			fprintf(fp, "form3: %s %s\n", request[i].form3->currentFamilyName, request[i].form3->newFamilyName);

		fprintf(fp, "~\n");
	}
	fclose(fp);
}
Request *delete_request()
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	int requestID = 0;
	int i = 0;
	int index = 0;
	char *userID;
	int requestIndex = 0;
	printf(" ***** Delete request after treated *****\n");
	printf("please enter request ID you would like to delete: \n");
	scanf("%d", &requestID);

	if (!check_ifRequest(requestID))
	{
		do
		{
			printf("oops! request ID was NOT found in our database!\n");
			printf("please try again: \n");
			scanf("%d", &requestID);
		} while (!check_ifRequest(requestID));
	}

	Request *request = getRequestsArr();
	for (i = 0; i < requestCounter; i++)
	{
		if (request[i].request_ID == requestID)
		{
			index = i;
			break;
		}
	}



	userID = strdup(request[index].request_UserID);

	request[index].request_ID = NULL;
	request[index].request_UserID = NULL;
	if (request[index].form1 != NULL)
		request[index].form1 = NULL;
	if (request[index].form2 != NULL)
		request[index].form2 = NULL;
	if (request[index].form3 != NULL)
		request[index].form3 = NULL;



	int j = 0;

	User *users = getUsersArr();


	for (i = 0; i < userCounter; i++)
	{
		if (!strcmp(users[i].ID, userID))
		{
			index = i;
			break;
		}
	}

	int k = users[index].numRequests;

	for (i = 0; i < k; i++)
	{
		if (users[index].requestList[i]->request_ID == requestID)
		{
			requestIndex = i;
			break;
		}
	}


	j = 0;

	Request **tempList = (Request*)malloc(sizeof(Request));


	for (i = 0; i < k; i++)
	{
		tempList[i] = (Request*)malloc(sizeof(Request));
		if (users[index].requestList[j]->form1 != NULL)
		{
			tempList[i]->form1 = (newBorn*)malloc(sizeof(newBorn));
			tempList[i]->request_ID = users[index].requestList[j]->request_ID;
			tempList[i]->form1->babyID = strdup(users[index].requestList[j]->form1->babyID);
			tempList[i]->form1->babyName = strdup(users[index].requestList[j]->form1->babyName);
			tempList[i]->form2 = tempList[i]->form3 = NULL;
		}

		else if (users[index].requestList[j]->form2 != NULL)
		{
			tempList[i]->form2 = (personalStatus*)malloc(sizeof(personalStatus));
			tempList[i]->request_ID = users[index].requestList[j]->request_ID;
			tempList[i]->form2->currentStatus = strdup(users[index].requestList[j]->form2->currentStatus);
			tempList[i]->form2->newStatus = strdup(users[index].requestList[j]->form2->newStatus);
			tempList[i]->form1 = tempList[i]->form3 = NULL;
		}

		else if (users[index].requestList[j]->form3 != NULL)
		{
			tempList[i]->form3 = (familyChange*)malloc(sizeof(familyChange));
			tempList[i]->request_ID = users[index].requestList[j]->request_ID;
			tempList[i]->form3->currentFamilyName = strdup(users[index].requestList[j]->form3->currentFamilyName);
			tempList[i]->form3->newFamilyName = strdup(users[index].requestList[j]->form3->newFamilyName);
			tempList[i]->form1 = tempList[i]->form2 = NULL;
		}
		j++;

	}

	for (i = 0; i < k; i++)
	{
		free(users[index].requestList[i]);
	}
	free(users[index].requestList);



	users[index].requestList = (Request*)malloc(sizeof(Request));


	i = 0;
	for (j = 0; j < k; j++)
	{
		if (j != requestIndex)
		{
			if (i < k - 1)
			{
				users[index].requestList[i] = (Request*)malloc(sizeof(Request));

				if (tempList[j]->form1 != NULL)
				{
					users[index].requestList[i]->form1 = (newBorn*)malloc(sizeof(newBorn));
					users[index].requestList[i]->request_ID = tempList[j]->request_ID;
					users[index].requestList[i]->form1->babyID = strdup(tempList[j]->form1->babyID);
					users[index].requestList[i]->form1->babyName = strdup(tempList[j]->form1->babyName);
					users[index].requestList[i]->form2 = users[index].requestList[i]->form3 = NULL;

				}
				else if (tempList[j]->form2 != NULL)
				{
					users[index].requestList[i]->form2 = (personalStatus*)malloc(sizeof(personalStatus));
					users[index].requestList[i]->request_ID = tempList[j]->request_ID;
					users[index].requestList[i]->form2->currentStatus = strdup(tempList[j]->form2->currentStatus);
					users[index].requestList[i]->form2->newStatus = strdup(tempList[j]->form2->newStatus);
					users[index].requestList[i]->form1 = users[index].requestList[i]->form3 = NULL;


				}
				else if (tempList[j]->form3 != NULL)
				{
					users[index].requestList[i]->form3 = (familyChange*)malloc(sizeof(familyChange));
					users[index].requestList[i]->request_ID = tempList[j]->request_ID;
					users[index].requestList[i]->form3->currentFamilyName = strdup(tempList[j]->form3->currentFamilyName);
					users[index].requestList[i]->form3->newFamilyName = strdup(tempList[j]->form3->newFamilyName);
					users[index].requestList[i]->form1 = users[index].requestList[i]->form2 = NULL;

				}

				i++;
			}
		}
	}

	users[index].numRequests--;
	for (i = 0; i < k; i++)
		free(tempList[i]);
	free(tempList);



	changeUsers_database(users);

	//printUsers(users); //check for myself


	requestCounter - 1;
	SetConsoleTextAttribute(hConsole, PINK);
	printf("\n\n The request successfully DELETED from database!!!\n");
	SetConsoleTextAttribute(hConsole, WHITE);
	changeRequest_database(request);
	getchar();

}

//void changeUsers_database(User *user)
//{
//	int i = 0;
//	int j = 0;
//	FILE *fp = fopen("userText.txt", "w");
//	
//	for (i = 0; i < userCounter; i++)
//	{
//		fprintf(fp, "~\n");
//		fprintf(fp, "firstName: %s\n", user[i].firstName);
//		fprintf(fp,"lastName: %s\n",user[i].lastName);
//		fprintf(fp,"ID: %s\n",user[i].ID);
//		fprintf(fp,"gender: %s\n",user[i].gender);
//		fprintf(fp,"familyStatus: %s\n",user[i].familyStatus);
//		fprintf(fp,"kids: %d\n",user[i].kids);
//		fprintf(fp,"password: %s\n",user[i].password);
//		fprintf(fp,"numRequests: %d\n",user[i].numRequests);
//		if (user[i].requestList != NULL)
//		{
//			for (j = 0; j < user[i].numRequests; j++)
//			{
//				if (user[i].requestList[j]->form1 != NULL)
//					fprintf(fp, "form1: %s %s\n", user[i].requestList[j]->form1->babyID, user[i].requestList[j]->form1->babyName);
//				
//				if (user[i].requestList[j]->form2 != NULL)
//					fprintf(fp, "form2: %s %s\n", user[i].requestList[j]->form2->currentStatus, user[i].requestList[j]->form2->newStatus);
//
//				if (user[i].requestList[j]->form3 != NULL)
//					fprintf(fp, "form3: %s %s\n", user[i].requestList[j]->form3->currentFamilyName, user[i].requestList[j]->form3->newFamilyName);
//				
//			}
//		}fprintf(fp, "~\n");
//
//	}
//	fclose(fp);
//
//}
User *changeUser_lastName()
{
	int i = 0;
	int index = 0;
	char userID[IDSIZE];
	char new_lastName[NAMESIZE];
	printf(" ***** Change user last name *****\n");
	printf("please enter the user ID:\n");
	gets(userID);

	while (!checkID_database(userID))
	{
		printf("oops! the wanted ID was NOT found in our database!try again:\n");
		gets(userID);
	}

	User *user = getUsersArr();

	for (i = 0; i < userCounter; i++)
	{
		if (!strcmp(userID, user[i].ID))
		{
			index = i;
			break;
		}
	}


	printf("please enter user new last name: \n");
	gets(new_lastName);

	user[index].lastName = new_lastName;
	printf("\n ~~~change user last name went successfull !!! ~~~\n");

	changeUsers_database(user);

}
User *changeUser_personalStatus()
{
	int i = 0;
	int index = 0;
	char userID[IDSIZE];
	char new_personalStatus[IDSIZE];
	printf("\n ***** Change user personal status *****\n");
	printf("please enter user ID: \n");
	gets(userID);

	while (!checkID_database(userID))
	{
		printf("oops! the wanted ID was NOT found in our database!try again:\n");
		gets(userID);
	}

	User *user = getUsersArr();
	for (i = 0; i < userCounter; i++)
	{
		if (!strcmp(user[i].ID, userID))
		{
			index = i;
			break;
		}
	}
	printf("please enter new personal status for this user: \n");
	printf("one of the following: single/married/divorced/widoer/widow\n");
	gets(new_personalStatus);

	user[index].familyStatus = new_personalStatus;
	printf("\n ~~~change user personal status went successfull !!! ~~~\n");
	changeUsers_database(user);

}
User *registerUser_newBorn()
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	int i = 0;
	int index = 0;
	char userID[IDSIZE];

	printf("\n ~~~~~ Register User new born ~~~~~\n");
	printf("please enter user ID you would like to register: \n");
	gets(userID);

	while (!checkID_database(userID))
	{
		printf("oops! the wanted ID was NOT found in our database!try again:\n");
		gets(userID);
	}
	SetConsoleTextAttribute(hConsole, YELLOW);
	printf("For clarification: note that you can ONLY register one child for each registration!!!\n");
	SetConsoleTextAttribute(hConsole, WHITE);

	User *user = getUsersArr();
	for (i = 0; i < userCounter; i++)
	{
		if (!strcmp(userID, user[i].ID))
		{
			index = i;
			break;
		}
	}

	user[index].kids = user[index].kids++;
	printf("\n ~~~registration User's new born went successfull !!! ~~~\n");

	changeUsers_database(user);


}


//Manager Menu's functions
void printManagerInside4(int mark)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (mark == 1)
	{
		SetConsoleTextAttribute(hConsole, RED);
		printf("[1]  -  Change user last name\n");
		SetConsoleTextAttribute(hConsole, WHITE);
	}
	else
		printf("[1]  -  Change user last name\n");

	if (mark == 2)
	{
		SetConsoleTextAttribute(hConsole, RED);
		printf("[2]  -  Change user personal status\n");
		SetConsoleTextAttribute(hConsole, WHITE);
	}
	else
		printf("[2]  -  Change user personal status\n");

	if (mark == 3)
	{
		SetConsoleTextAttribute(hConsole, RED);
		printf("[3]  -  Register new born\n");
		SetConsoleTextAttribute(hConsole, WHITE);
	}
	else
		printf("[3]  -  Register new born\n");

	if (mark == 4)
	{
		SetConsoleTextAttribute(hConsole, RED);
		printf("[4]  -  Back to previous page\n");
		SetConsoleTextAttribute(hConsole, WHITE);
	}
	else
		printf("[4]  -  Back to previous page\n");

}
void excuteInsideManagerMenu4(int select)
{
	switch (select)
	{
	case 1:
		changeUser_lastName();
		getchar();
		break;
	case 2:
		changeUser_personalStatus();
		getchar();
		break;
	case 3:
		registerUser_newBorn();
		getchar();
		break;
	case 4:
		printf("4\n");
		break;
	default:
		printf("DEFAULT\n");
		break;

	}
}
void managerInsideMenu4()
{
	bool flag = true;
	int choice = 1;
	char ch = UP, enter;

	do
	{
		if (ch == UP || ch == DOWN)
		{
			system("cls");
			printf("----------- Change user information in database -----------\n\n");
			printManagerInside4(choice);

		}
		enter = _getch();
		if (enter != '\r')
			ch = enter;
		if ((choice == 4) && enter == '\r')
			flag = false;
		if (enter == '\r' && choice != 4)
			excuteInsideManagerMenu4(choice);

		else
		{
			if (ch == UP)
			{
				choice--;
				if (choice == 0)
					choice = 4;

			}
			if (ch == DOWN)
			{
				choice++;
				if (choice == 5)
					choice = 1;
			}
		}


	} while (flag);
}


void printManagerMenu(int mark)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (mark == 1)
	{
		SetConsoleTextAttribute(hConsole, RED);
		printf("[1]  -  Pending requests report\n");
		SetConsoleTextAttribute(hConsole, WHITE);
	}
	else
		printf("[1]  -  Pending requests report\n");

	if (mark == 2)
	{
		SetConsoleTextAttribute(hConsole, RED);
		printf("[2]  -  User Query\n");
		SetConsoleTextAttribute(hConsole, WHITE);
	}
	else
		printf("[2]  -  User Query\n");

	if (mark == 3)
	{
		SetConsoleTextAttribute(hConsole, RED);
		printf("[3]  -  Delete request after treated\n");
		SetConsoleTextAttribute(hConsole, WHITE);
	}
	else
		printf("[3]  -  Delete request after treated\n");

	if (mark == 4)
	{
		SetConsoleTextAttribute(hConsole, RED);
		printf("[4]  -  Change user information in database\n");
		SetConsoleTextAttribute(hConsole, WHITE);
	}
	else
		printf("[4]  -  Change user information in database\n");

	if (mark == 5)
	{
		SetConsoleTextAttribute(hConsole, RED);
		printf("[5]  -  Back to previous page\n");
		SetConsoleTextAttribute(hConsole, WHITE);
	}
	else
		printf("[5]  -  Back to previous page\n");

	if (mark == 6)
	{
		SetConsoleTextAttribute(hConsole, RED);
		printf("[6]  -  LOG OFF\n");
		SetConsoleTextAttribute(hConsole, WHITE);
	}
	else
		printf("[6]  -  LOG OFF\n");

}
void excuteManagerMenu(int select)
{
	switch (select)
	{
	case 1:
		pendingRequsts_display();
		getchar();
		break;
	case 2:
		userQuery();
		getchar();
		break;
	case 3:
		delete_request();
		getchar();
		break;
	case 4:
		managerInsideMenu4();
		break;
	case 5:
		exit(1);///// add goodbye msg after
		break;
	case 6:
		exit(1);///// add goodbye msg after
		break;
	default:
		printf("*** call tech support! ***\n");
		break;
	}
}
void managerMenu()
{
	bool flag = true;
	int choice = 1;
	char ch = UP, enter;

	do
	{
		if (ch == UP || ch == DOWN)
		{
			system("cls");
			printf("----------- MANAGER MENU -----------\n\n");
			printManagerMenu(choice);

		}
		enter = _getch();
		if (enter != '\r')
			ch = enter;
		if ((choice == 6 || choice == 5) && enter == '\r')
			flag = false;
		if (enter == '\r' && (choice != 6 || choice != 5))
			excuteManagerMenu(choice);
		else
		{
			if (ch == UP)
			{
				choice--;
				if (choice == 0)
					choice = 6;

			}
			if (ch == DOWN)
			{
				choice++;
				if (choice == 7)
					choice = 1;
			}
		}


	} while (flag);

}



//User Menu's functions
void stamFuncForCheck()
{
	printf("\n-----trial-------\n");
	printf("\n------------\n");
	printf("\n------------\n");
	printf("\n------------\n");
}
void excuteInsideUserMenu1(int select)
{
	switch (select)
	{
	case 1:
		Alimony_information();
		//getchar();
		break;
	case 2:
		Alimony_calculator();
		getchar();
		break;
	case 3:
		printf("case 3\n"); ///seposed to be back to prev
		break;

	default:
		printf("illegal???????\n");
		break;
	}
	getchar();
}
void printUserInside1(int mark)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (mark == 1)
	{
		SetConsoleTextAttribute(hConsole, GREEN);
		printf("[1]  -  Alimony Information\n");
		SetConsoleTextAttribute(hConsole, WHITE);
	}
	else
		printf("[1]  -  Alimony Information\n");

	if (mark == 2)
	{
		SetConsoleTextAttribute(hConsole, GREEN);
		printf("[2]  -  Alimony Calculator\n");
		SetConsoleTextAttribute(hConsole, WHITE);
	}
	else
		printf("[2]  -  Alimony Calculator\n");

	if (mark == 3)
	{
		SetConsoleTextAttribute(hConsole, GREEN);
		printf("[3]  -  Back to previous page\n");
		SetConsoleTextAttribute(hConsole, WHITE);
	}
	else
		printf("[3]  -  Back to previous page\n");

}
void userInsideMenu1()
{
	bool flag = true;
	int choice = 1;
	char ch = UP, enter;
	do
	{
		if (ch == UP || ch == DOWN)
		{
			system("cls");
			printf(" *** DIVORCE ***\n\n");
			printUserInside1(choice);
		}
		enter = _getch();
		if (enter != '\r')
			ch = enter;
		if (choice == 3 && enter == '\r')
			flag = false;
		if (enter == '\r' && choice != 3)
			excuteInsideUserMenu1(choice);
		else
		{
			if (ch == UP)
			{
				choice--;
				if (choice == 0)
					choice = 3;
			}
			if (ch == DOWN)
			{
				choice++;
				if (choice == 4)
					choice = 1;
			}
		}

	} while (flag);
}


bool checkMatchStr(char * struser, char* strtxt)    // return true if have a match of minimum 3 words 
{
	char tav, tempU[stringSIZE], tempT[stringSIZE];
	int i, j, k = 0, m = 0, cnt = 0;

	for (i = 0; i < strlen(struser) + 1; i++)
	{
		tav = struser[i];    // sperate the str of the user to one word every loop
		tempU[k] = tav;
		k++;
		if (struser[i] == ' ' || struser[i] == '\0')
		{
			if (struser[i] == ' ')
				tempU[k - 1] = '\0';   // in the last place put \0 and instade the ' ' 
			if (struser[i] == '\0')
				tempU[k] = '\0';   // in the last place put \0 and instade the ' ' 
			k = 0;   // to start a new word  for the other loop
			for (j = 0; j < strlen(strtxt) + 1; j++)
			{
				if (strtxt[j] != '>' && strtxt[j] != '\n')
				{
					tav = strtxt[j];
					tempT[m] = tav;
					m++;
				}

				if (strtxt[j] == '-' || strtxt[j] == ' ' || strtxt[j] == '\0')
				{
					tempT[m - 1] = '\0';   // in the last place put \0 and instade the '-' 
					m = 0;  // to start a new word  for the other loop
					if (strcmp(tempU, tempT) == 0) // the words are equal - word match
					{
						tempU[0] = '\0';   // tempU = NULL 
						tempT[0] = '\0';
						cnt++;
						if (cnt >= 3)
						{
							return true;
						}
						break;
					}
					tempT[0] = '\0';
				}
			}

		}
	}




	return false;   // No words match!


}
void navigate()
{
	FILE * fnavigate;
	char strUser[stringSIZE], strTxt[stringSIZE];
	fnavigate = fopen("VirtualText.txt", "r");
	if (!fnavigate)
	{
		printf("The file couldn't be found.\n");
		return false;
	}
	printf("Welcome to the virtual service representative of gov.il !!!\n");
	printf("For your convenience with site navigation");
	printf("Please write a line with small letters what you wish to search the site:\n");
	gets(strUser);
	strlwr(strUser);

	while (!feof(fnavigate))
	{
		fgets(strTxt, stringSIZE, fnavigate);  // save every line from the text to the buffer
		if (checkMatchStr(strUser, strTxt) == true)
		{
			printf("%s", strTxt);
			printf("Successsss\n");
			break;
		}

		else
			printf("false\n");
	}

	fclose(fnavigate);
}

void printUserInside2(int mark)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (mark == 1)
	{
		SetConsoleTextAttribute(hConsole, GREEN);
		printf("[1]  -  Virtual representative\n");
		SetConsoleTextAttribute(hConsole, WHITE);
	}
	else
		printf("[1]  -  Virtual representative\n");

	if (mark == 2)
	{
		SetConsoleTextAttribute(hConsole, GREEN);
		printf("[2]  -  Back to previous page\n");
		SetConsoleTextAttribute(hConsole, WHITE);
	}
	else
		printf("[2]  -  Back to previous page\n");

}
void excuteInsideUserMenu2(int select)
{
	switch (select)
	{
	case 1:
		navigate();
		getchar();
		break;
	case 3:
		printf("case 3\n"); ///seposed to be back to prev
		break;

	default:
		printf("illegal???????\n");
		break;
	}
}
void userInsideMenu2()
{
	bool flag = true;
	int choice = 1;
	char ch = UP, enter;
	do
	{
		if (ch == UP || ch == DOWN)
		{
			system("cls");
			printf(" *** Virtual Representative ***\n\n");
			printUserInside2(choice);
		}
		enter = _getch();
		if (enter != '\r')
			ch = enter;
		if (choice == 2 && enter == '\r')
			flag = false;
		if (enter == '\r' && choice != 2)
			excuteInsideUserMenu2(choice);
		else
		{
			if (ch == UP)
			{
				choice--;
				if (choice == 0)
					choice = 3;
			}
			if (ch == DOWN)
			{
				choice++;
				if (choice == 3)
					choice = 1;
			}
		}

	} while (flag);
}



void printUserInside3(int mark)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (mark == 1)
	{
		SetConsoleTextAttribute(hConsole, GREEN);
		printf("[1]  -  Information for station family health center\n");
		SetConsoleTextAttribute(hConsole, WHITE);
	}
	else
		printf("[1]  -  Information for station family health center\n");

	if (mark == 2)
	{
		SetConsoleTextAttribute(hConsole, GREEN);
		printf("[2]  -  Fill a form - new born registration\n");
		SetConsoleTextAttribute(hConsole, WHITE);
	}
	else
		printf("[2]  -  Fill a form - new born registration\n");

	if (mark == 3)
	{
		SetConsoleTextAttribute(hConsole, GREEN);
		printf("[3]  -  Back to previous page\n");
		SetConsoleTextAttribute(hConsole, WHITE);
	}
	else
		printf("[3]  -  Back to previous page\n");


}
void excuteInsideUserMenu3(int select)
{
	switch (select)
	{
	case 1:
		familyHealthCenter_information();
		getchar();
		break;
	case 2:
		fill_form_newBorn();
		break;
	case 3:
		printf("case 3\n"); ///seposed to be back to prev
		break;

	default:
		printf("illegal???????\n");
		break;
	}
}
void userInsideMenu3()
{
	bool flag = true;
	int choice = 1;
	char ch = UP, enter;
	do
	{
		if (ch == UP || ch == DOWN)
		{
			system("cls");
			printf(" *** Pregnancy & Birth ***\n\n");
			printUserInside3(choice);
		}
		enter = _getch();
		if (enter != '\r')
			ch = enter;
		if (choice == 3 && enter == '\r')
			flag = false;
		if (enter == '\r' && choice != 3)
			excuteInsideUserMenu3(choice);
		else
		{
			if (ch == UP)
			{
				choice--;
				if (choice == 0)
					choice = 3;
			}
			if (ch == DOWN)
			{
				choice++;
				if (choice == 4)
					choice = 1;
			}
		}

	} while (flag);
}

void printUserInside4(int mark)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (mark == 1)
	{
		SetConsoleTextAttribute(hConsole, GREEN);
		printf("[1]  -  Fill a form - change last name\n");
		SetConsoleTextAttribute(hConsole, WHITE);
	}
	else
		printf("[1]  -  Fill a form - change last name\n");

	if (mark == 2)
	{
		SetConsoleTextAttribute(hConsole, GREEN);
		printf("[2]  -  Fill a form - change personal status\n");
		SetConsoleTextAttribute(hConsole, WHITE);
	}
	else
		printf("[2]  -  Fill a form - change personal status\n");

	if (mark == 3)
	{
		SetConsoleTextAttribute(hConsole, GREEN);
		printf("[3]  -  Back to previous page\n");
		SetConsoleTextAttribute(hConsole, WHITE);
	}
	else
		printf("[3]  -  Back to previous page\n");

}
void excuteInsideUserMenu4(int select)
{
	switch (select)
	{
	case 1:
		fill_form_changeLastName();
		getchar();//needed????
		break;
	case 2:
		fill_form_changePersonalStatus();
		getchar();///////needed????
		break;
	case 3:
		printf("case 3\n"); ///seposed to be back to prev
		break;

	default:
		printf("illegal???????\n");
		break;

	}

}
void userInsideMenu4()
{
	bool flag = true;
	int choice = 1;
	char ch = UP, enter;
	do
	{
		if (ch == UP || ch == DOWN)
		{
			system("cls");
			printf(" *** Change personal information ***\n\n");
			printUserInside4(choice);
		}
		enter = _getch();
		if (enter != '\r')
			ch = enter;
		if (choice == 3 && enter == '\r')
			flag = false;
		if (enter == '\r' && choice != 3)
			excuteInsideUserMenu4(choice);
		else
		{
			if (ch == UP)
			{
				choice--;
				if (choice == 0)
					choice = 3;
			}
			if (ch == DOWN)
			{
				choice++;
				if (choice == 4)
					choice = 1;
			}
		}

	} while (flag);
}

void excuteUserMenu(int selction)
{

	switch (selction)
	{
	case 1:
		userInsideMenu1();
		break;
	case 2:
		userInsideMenu2();
		break;
	case 3:
		userInsideMenu3();
		break;
	case 4:
		userInsideMenu4();
		break;
	case 5:
		exit(1);
		break;
	case 6:
		exit(1);
		break;
	default:
		printf("For any help, call ----------------\n");
		break;
	}
}
void printUserMenu(int markErea)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (markErea == 1)
	{
		SetConsoleTextAttribute(hConsole, GREEN);
		printf("[1]  -  Divorce\n");
		SetConsoleTextAttribute(hConsole, WHITE);

	}
	else
		printf("[1]  -  Divorce\n");

	if (markErea == 2)
	{
		SetConsoleTextAttribute(hConsole, GREEN);
		printf("[2]  -  Virtual representaive\n");
		SetConsoleTextAttribute(hConsole, WHITE);
	}
	else
		printf("[2]  -  Virtual representaive\n");

	if (markErea == 3)
	{
		SetConsoleTextAttribute(hConsole, GREEN);
		printf("[3]  -  Pregnancy & Birth\n");
		SetConsoleTextAttribute(hConsole, WHITE);
	}
	else
		printf("[3]  -  Pregnancy & Birth\n");

	if (markErea == 4)
	{
		SetConsoleTextAttribute(hConsole, GREEN);
		printf("[4]  -  change personal information\n");
		SetConsoleTextAttribute(hConsole, WHITE);
	}
	else
		printf("[4]  -  change personal information\n");

	if (markErea == 5)
	{
		SetConsoleTextAttribute(hConsole, GREEN);
		printf("[5]  -  Back to previous page\n");
		SetConsoleTextAttribute(hConsole, WHITE);
	}
	else
		printf("[5]  -  Back to previous page\n");

	if (markErea == 6)
	{
		SetConsoleTextAttribute(hConsole, GREEN);
		printf("[6]  -  LOG OFF\n");
		SetConsoleTextAttribute(hConsole, WHITE);
	}
	else
		printf("[6]  -  LOG OFF\n");



}
void userMenu()
{
	bool flag = true;
	int choice = 1;
	char ch = UP, enter;

	do
	{
		if (ch == UP || ch == DOWN)
		{
			system("cls");
			printf("----------- USER MENU -----------\n\n");
			printUserMenu(choice);

		}
		enter = _getch();
		if (enter != '\r')
			ch = enter;
		if ((choice == 6 || choice == 5) && enter == '\r')
			flag = false;
		if (enter == '\r' && (choice != 6 || choice != 5))//  add && choice != 5
			excuteUserMenu(choice);
		else
		{
			if (ch == UP)
			{
				choice--;
				if (choice == 0)
					choice = 6;

			}
			if (ch == DOWN)
			{
				choice++;
				if (choice == 7)
					choice = 1;
			}
		}


	} while (flag);

}


//Edtior Menu's functions
void editorMenu();
void excuteInsideEditor1(int);

bool addData()
{
	char data[stringSIZE];
	FILE *falimony;
	printf("Print the data do you want to add:\n");
	gets(data);
	falimony = fopen("Brochure1.txt", "a");
	if (!falimony)
	{
		printf("The file couldn't be found.\n");
		exit(1);
	}
	else
	{
		// additional data to the text Brochure1.txt
		fputs("\n", falimony);
		fputs(data, falimony);

		fclose(falimony);
		return true;
	}

	return false;

}
bool changeData()
{
	char data[stringSIZE];
	FILE *falimony;
	printf("Print the data do you want to rewrite:\n");
	scanf("%c", data);
	gets(data);
	falimony = fopen("Brochure1.txt", "w");
	if (!falimony)
	{
		printf("The file couldn't be found.\n");
		exit(1);
	}
	else
	{
		// change the data base to the text Brochure1.txt
		fputs("\n", falimony);
		fputs(data, falimony);

		fclose(falimony);
		return true;
	}

	return false;
}
// 3 functions for change Brochure1.txt
void printSubEditorBrochure1(int mark)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (mark == 1)
	{
		SetConsoleTextAttribute(hConsole, L_BLUE);
		printf("[1]  -  To add content to Alimony information\n");
		SetConsoleTextAttribute(hConsole, WHITE);
	}
	else
		printf("[1]  -  To add content to Alimony information\n");

	if (mark == 2)
	{
		SetConsoleTextAttribute(hConsole, L_BLUE);
		printf("[2]  -  To rewrite the Alimony information\n");
		SetConsoleTextAttribute(hConsole, WHITE);
	}
	else
		printf("[2]  -  To rewrite the Alimony information\n");

	if (mark == 3)
	{
		SetConsoleTextAttribute(hConsole, L_BLUE);
		printf("[3]  -  Back to previous page\n");
		SetConsoleTextAttribute(hConsole, WHITE);
	}
	else
		printf("[3]  -  Back to previous page\n");
}
void excuteSubMenuEditorBrochure1(int select)
{
	switch (select)
	{
	case 1:
		printf("1\n");
		break;
	case 2:
		printf("2\n");
		break;
	case 3:
		printf("3\n");
		break;
	default:
		printf("DEFAULT MSG\n");
		break;
	}
}
void editorSubMenuBrochure1()
{
	bool flag = true;
	int choice = 1;
	char ch = UP, enter;

	do
	{
		if (ch == UP || ch == DOWN)
		{
			system("cls");
			printf("----------- SUB CONTENT EDITING -----------\n\n");
			printSubEditorBrochure1(choice);

		}
		enter = _getch();
		if (enter != '\r')
			ch = enter;
		if (choice == 1 && enter == '\r')
		{
			addData();
			flag = false;
		}
		if (choice == 2 && enter == '\r')
		{
			changeData();
			flag = false;
		}
		if (choice == 3 && enter == '\r')
			flag = false;
		if (enter == '\r' && choice != 3)
			excuteSubMenuEditorBrochure1(choice);
		else
		{
			if (ch == UP)
			{
				choice--;
				if (choice == 0)
					choice = 3;
			}
			if (ch == DOWN)
			{
				choice++;
				if (choice == 4)
					choice = 1;
			}
		}
	} while (flag);
}

bool checkNumber(char* tel)
{
	int i, len = strlen(tel) + 1;
	for (i = 0; i < len - 1; i++)
	{
		if (tel[i] < '0' || tel[i] >'9')
			return false;
	}
	return true;
}
bool changeList()    // rewrite the database of Brochure2.txt
{
	int size_list, i;
	char str[IDSIZE], enter;
	FILE *fstation;
	bool check;
	fstation = fopen("Brochure2.txt", "w");
	if (!fstation)
	{
		printf("The file couldn't be found.\n");
		return false;
	}
	printf("How many station do you like to insert?\n");
	scanf("%d", &size_list);
	printf("Enter the details:\n");
	for (i = 0; i < size_list; i++)
	{
		system("cls");
		fputs("~\n", fstation);
		printf("Station Name:");
		scanf("%c", &enter);
		gets(str);
		fprintf(fstation, "station: %s\n", str);
		printf("City:");
		gets(str);
		fprintf(fstation, "city: %s\n", str);
		printf("Street Name:");
		gets(str);
		fprintf(fstation, "street: %s\n", str);
		//printf("Telephone:");
		//gets(str);
		do
		{
			printf("Telephone:");
			gets(str);
			check = checkNumber(str);

		} while (check == false);
		fprintf(fstation, "telephone: %s\n", str);
	}
	return true;

}
bool addStation()    // add station to the data base of Brochure2.txt
{
	char station[IDSIZE], city[IDSIZE], street[IDSIZE], tel[IDSIZE], enter;
	FILE *fstation;
	fstation = fopen("Brochure2.txt", "a");
	if (!fstation)
	{
		printf("The file couldn't be found.\n");
		return false;
	}
	printf("Please enter a name station:");
	scanf("%c", &enter);
	gets(station);
	printf("enter a city:");
	gets(city);
	printf("enter a street:");
	gets(street);
	printf("enter a telphone of the station:");
	gets(tel);
	if (checkNumber(tel) == false)
	{
		printf("Error telphone\n");
		return false;
	}


	fputs("\n~", fstation);
	fprintf(fstation, "\nstation: %s", station);
	fprintf(fstation, "\ncity: %s", city);
	fprintf(fstation, "\ncity: %s", street);
	fprintf(fstation, "\ncity: %s", tel);

	fclose(fstation);
	return true;
}
// 3 functions for change Brochure2.txt
void printSubEditorBrochure2(int mark)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (mark == 1)
	{
		SetConsoleTextAttribute(hConsole, L_BLUE);
		printf("[1]  -  Enter the new list satations for change\n");
		SetConsoleTextAttribute(hConsole, WHITE);
	}
	else
		printf("[1]  -  Enter the new list satations for change\n");

	if (mark == 2)
	{
		SetConsoleTextAttribute(hConsole, L_BLUE);
		printf("[2]  -  To additional a station\n");
		SetConsoleTextAttribute(hConsole, WHITE);
	}
	else
		printf("[2]  -  To additional a station\n");

	if (mark == 3)
	{
		SetConsoleTextAttribute(hConsole, L_BLUE);
		printf("[3]  -  Back to previous page\n");
		SetConsoleTextAttribute(hConsole, WHITE);
	}
	else
		printf("[3]  -  Back to previous page\n");
}
void excuteSubMenuEditorBrochure2(int select)
{
	switch (select)
	{
	case 1:
		printf("1\n");
		break;
	case 2:
		printf("2\n");
		break;
	case 3:
		printf("3\n");
		break;
	default:
		printf("DEFAULT MSG\n");
		break;
	}
}
void editorSubMenuBrochure2()
{
	bool flag = true;
	int choice = 1;
	char ch = UP, enter;

	do
	{
		if (ch == UP || ch == DOWN)
		{
			system("cls");
			printf("----------- SUB CONTENT EDITING -----------\n\n");
			printSubEditorBrochure2(choice);

		}
		enter = _getch();
		if (enter != '\r')
			ch = enter;
		if (choice == 1 && enter == '\r')
		{
			if (changeList() == true)
				printf("Success\n");
			else
				printf("Failed\n");
			flag = false;
		}
		if (choice == 2 && enter == '\r')
		{
			if (addStation() == true)
				printf("Success\n");
			else
				printf("Failed\n");

			flag = false;
		}
		if (choice == 3 && enter == '\r')
			flag = false;
		if (enter == '\r' && choice != 3)
			excuteSubMenuEditorBrochure2(choice);
		else
		{
			if (ch == UP)
			{
				choice--;
				if (choice == 0)
					choice = 3;
			}
			if (ch == DOWN)
			{
				choice++;
				if (choice == 4)
					choice = 1;
			}
		}
	} while (flag);
}


bool changeVirtualText()   // function for change all the database for VirtualText.txt
{
	FILE * fvirtual;
	int flag = 0;
	char str[stringSIZE];
	int i, j, amount;
	fvirtual = fopen("VirtualText.txt", "w");
	if (!fvirtual)
	{
		printf("The file couldn't be found.\n");
		return false;
	}
	printf("How many navigation do you want to put:");
	scanf("%d", &amount);
	for (j = 0; j < amount; j++)
	{
		do
		{
			flag = 0;
			system("cls");
			printf("Insert the new navigation according this form for example : divorce->alimony information \n");
			gets(str);
			strlwr(str);
			for (i = 0; i < strlen(str); i++)
			{
				if (str[i] == '-' && str[i + 1] == '>' && i != 0)   // check input
				{
					if (str[i - 1] != NULL && str[i - 1] != '\0' && str[i + 2] != NULL && str[i + 2] != '\0' && str[i + 2] != ' ')  // check input
					{
						flag = 1;
						break;
					}
				}
			}
		} while (flag == 0);
		fprintf(fvirtual, "\n%s", str);
	}
	fclose(fvirtual);
	return true;
}
bool addVirtualQuary()   // function to add navigation for the database for VirtualText.txt
{
	FILE * fvirtual;
	int flag = 0;
	char str[stringSIZE];
	int i, j, amount;
	fvirtual = fopen("VirtualText.txt", "a");
	if (!fvirtual)
	{
		printf("The file couldn't be found.\n");
		return false;
	}
	printf("How many navigation do you want to put:");
	scanf("%d", &amount);
	for (j = 0; j < amount; j++)
	{
		do
		{
			flag = 0;
			system("cls");
			printf("Insert the navigation you want to add according this form for example : divorce->alimony information \n");
			gets(str);
			strlwr(str);
			for (i = 0; i < strlen(str); i++)
			{
				if (str[i] == '-' && str[i + 1] == '>' && i != 0)   // check input
				{
					if (str[i - 1] != NULL && str[i - 1] != '\0' && str[i + 2] != NULL && str[i + 2] != '\0' && str[i + 2] != ' ')  // check input
					{
						flag = 1;
						break;
					}
				}
			}
		} while (flag == 0);
		fprintf(fvirtual, "\n%s", str);
	}

	fclose(fvirtual);
	return true;
}
// 3 functions for change VirtualText.txt
void printSubEditorVirtualText(int mark)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (mark == 1)
	{
		SetConsoleTextAttribute(hConsole, L_BLUE);
		printf("[1]  -  Edit the all File according this form\n   *** for example : Divorce->alimony information ***\n\n");
		SetConsoleTextAttribute(hConsole, WHITE);
	}
	else
		printf("[1]  -  Edit the all File according this form\n   *** for example : Divorce->alimony information ***\n\n");

	if (mark == 2)
	{
		SetConsoleTextAttribute(hConsole, L_BLUE);
		printf("[2]  -  Additional navigation  according this form\n   *** for example : Divorce->alimony information ***\n\n");
		SetConsoleTextAttribute(hConsole, WHITE);
	}
	else
		printf("[2]  -  Additional navigation  according this form\n   *** for example : Divorce -> alimony information ***\n\n");

	if (mark == 3)
	{
		SetConsoleTextAttribute(hConsole, L_BLUE);
		printf("[3]  -  Back to previous page\n");
		SetConsoleTextAttribute(hConsole, WHITE);
	}
	else
		printf("[3]  -  Back to previous page\n");
}
void excuteSubMenuEditorVirtualText(int select)
{
	switch (select)
	{
	case 1:
		printf("1\n");
		break;
	case 2:
		printf("2\n");
		break;
	case 3:
		printf("3\n");
		break;
	default:
		printf("DEFAULT MSG\n");
		break;
	}
}
void editorSubMenuVirtualText()
{
	bool flag = true;
	int choice = 1;
	char ch = UP, enter;

	do
	{
		if (ch == UP || ch == DOWN)
		{
			system("cls");
			printf("----------- SUB CONTENT EDITING -----------\n\n");
			printSubEditorVirtualText(choice);

		}
		enter = _getch();
		if (enter != '\r')
			ch = enter;
		if (choice == 1 && enter == '\r')
		{
			if (changeVirtualText() == true)
				printf("Success\n");
			else
				printf("Failed\n");
			flag = false;
		}
		if (choice == 2 && enter == '\r')
		{
			if (addVirtualQuary() == true)
				printf("Success\n");
			else
				printf("Failed\n");

			flag = false;
		}
		if (choice == 3 && enter == '\r')
			flag = false;
		if (enter == '\r' && choice != 3)
			excuteSubMenuEditorVirtualText(choice);
		else
		{
			if (ch == UP)
			{
				choice--;
				if (choice == 0)
					choice = 3;
			}
			if (ch == DOWN)
			{
				choice++;
				if (choice == 4)
					choice = 1;
			}
		}
	} while (flag);
}

void printEditorInside1(int mark)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (mark == 1)
	{
		SetConsoleTextAttribute(hConsole, L_BLUE);
		printf("[1]  -  Virtual representative querys\n");
		SetConsoleTextAttribute(hConsole, WHITE);
	}
	else
		printf("[1]  -  Virtual representative querys\n");

	if (mark == 2)
	{
		SetConsoleTextAttribute(hConsole, L_BLUE);
		printf("[2]  -  Alimony information\n");
		SetConsoleTextAttribute(hConsole, WHITE);
	}
	else
		printf("[2]  -  Alimony information\n");

	if (mark == 3)
	{
		SetConsoleTextAttribute(hConsole, L_BLUE);
		printf("[3]  -  Information for station family health center\n");
		SetConsoleTextAttribute(hConsole, WHITE);
	}
	else
		printf("[3]  -  Information for station family health center\n");

	if (mark == 4)
	{
		SetConsoleTextAttribute(hConsole, L_BLUE);
		printf("[4]  -  Back to previous page\n");
		SetConsoleTextAttribute(hConsole, WHITE);
	}
	else
		printf("[4]  -  Back to previous page\n");
}
void excuteInsideEditor1(int select)
{
	switch (select)
	{
	case 1:
		printf("1\n");
		break;
	case 2:
		printf("2\n");
		break;
	case 3:
		printf("3\n");
		break;
	case 4:
		printf("4\n");
		break;
	default:
		printf("DEFAULT MSG\n");
		break;
	}
}
void editorInsideMenu1()
{
	bool flag = true;
	int choice = 1;
	char ch = UP, enter;

	do
	{
		if (ch == UP || ch == DOWN)
		{
			system("cls");
			printf("----------- CONTENT EDITING -----------\n\n");
			printEditorInside1(choice);

		}
		enter = _getch();
		if (enter != '\r')
			ch = enter;
		if (choice == 1 && enter == '\r')
		{
			editorSubMenuVirtualText();
			flag = false;
		}
		if (choice == 2 && enter == '\r')
		{
			editorSubMenuBrochure1();
			flag = false;
		}
		if (choice == 3 && enter == '\r')
		{
			editorSubMenuBrochure2();
			flag = false;
		}
		if (choice == 4 && enter == '\r')
			flag = false;
		if (enter == '\r' && choice != 4)
			excuteInsideEditor1(choice);
		else
		{
			if (ch == UP)
			{
				choice--;
				if (choice == 0)
					choice = 4;
			}
			if (ch == DOWN)
			{
				choice++;
				if (choice == 5)
					choice = 1;
			}
		}


	} while (flag);
}


bool createNewBrochutre()    // To create a new Brochure data base
{
	char new_name[IDSIZE];
	printf("Enter the name file include end file (example.txt): ");
	gets(new_name);
	FILE * fn;
	fn = fopen(new_name, "w");
	if (!fn)
	{
		printf("The file couldn't be found.\n");
		return false;
	}
	fclose(fn);
	return true;
}

void printEditorMenu(int markErea)//////dont forget add inside menu
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (markErea == 1)
	{
		SetConsoleTextAttribute(hConsole, L_BLUE);
		printf("[1]  -  Content Editing\n");
		SetConsoleTextAttribute(hConsole, WHITE);
	}
	else
		printf("[1]  -  Content Editing\n");

	if (markErea == 2)
	{
		SetConsoleTextAttribute(hConsole, L_BLUE);
		printf("[2]  -  Adding new brochure\n");
		SetConsoleTextAttribute(hConsole, WHITE);
	}
	else
		printf("[2]  -  Adding new brochure\n");

	if (markErea == 3)
	{
		SetConsoleTextAttribute(hConsole, L_BLUE);
		printf("[3]  -  Back to previous page\n");
		SetConsoleTextAttribute(hConsole, WHITE);
	}
	else
		printf("[3]  -  Back to previous page\n");

	if (markErea == 4)
	{
		SetConsoleTextAttribute(hConsole, L_BLUE);
		printf("[4]  -  LOG OFF\n");
		SetConsoleTextAttribute(hConsole, WHITE);
	}
	else
		printf("[4]  -  LOG OFF\n");


}
void excuteEditorMenu(int select)
{
	switch (select)
	{
	case 1:
		editorInsideMenu1();
		break;
	case 2:
		if (createNewBrochutre() == 1)
			printf("Succes\n");
		else
			printf("Failed\n");
		break;
	case 3:
		printf("3\n");
		break;
	case 4:
		printf("4\n");
		break;
	default:
		printf("DEFAULT MSG\n");
		break;
	}
}
void editorMenu()
{
	bool flag = true;
	int choice = 1;
	char ch = UP, enter;

	do
	{
		if (ch == UP || ch == DOWN)
		{
			system("cls");
			printf("----------- CONTENT EDITOR MENU -----------\n\n");
			printEditorMenu(choice);

		}
		enter = _getch();
		if (enter != '\r')
			ch = enter;
		if ((choice == 4 || choice == 3) && enter == '\r')
			flag = false;
		if (enter == '\r' && (choice != 4 || choice != 3))
			excuteEditorMenu(choice);
		else
		{
			if (ch == UP)
			{
				choice--;
				if (choice == 0)
					choice = 4;

			}
			if (ch == DOWN)
			{
				choice++;
				if (choice == 5)
					choice = 1;
			}
		}


	} while (flag);
}

User *userRegistration()
{
	char firstName[NAMESIZE];
	char lastName[NAMESIZE];
	char userID[IDSIZE];
	char gender[GENDERSIZE];
	char familyStatus[IDSIZE];
	int kids;
	char password[PASSWORDSIZE];

	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


	//SetConsoleTextAttribute(hConsole, PINK);
	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	SetConsoleTextAttribute(hConsole, PINK);
	printf("Welcome!!! ready to user registration! \n");
	SetConsoleTextAttribute(hConsole, WHITE);
	printf("please enter your firstName: \n");
	gets(firstName);///need to send to input valid for name
	printf("please enter your last name: \n");
	gets(lastName);///need to send to input valid for name
	printf("please enter your ID: \n");
	gets(userID);//need input valid

	while (checkID_database(userID))
	{
		printf("sorry! this ID is allready exist in our database. please try again: \n");
		gets(userID);
	}

	printf("please enter your gender: (male/female) \n");
	gets(gender);//need input valid
	printf("please enter your current family status from each one of the follwoing:\n");
	printf("single/married/divorced/widoer/widow \n");
	gets(familyStatus);//need input valid
	printf("please enter the amount of kids(if any): \n");
	scanf("%d", &kids);
	printf("please enter your password: \n");
	SetConsoleTextAttribute(hConsole, YELLOW);
	printf("For clarifaction! your password can contain only digits and letters(capitals or lowers)\n");
	SetConsoleTextAttribute(hConsole, WHITE);
	gets(password);//need input valid
	getchar();

	User *newUser = (User*)malloc(1 * sizeof(User));
	newUser->firstName = strdup(firstName);
	newUser->lastName = strdup(lastName);
	newUser->ID = strdup(userID);
	newUser->gender = strdup(gender);
	newUser->familyStatus = strdup(familyStatus);
	newUser->kids = kids;
	newUser->password = strdup(password);
	newUser->numRequests = 0;
	newUser->requestList = NULL;

	SetConsoleTextAttribute(hConsole, PINK);
	printf("Thank YOU! you have registred to the system SUCCESSFULLY!\n");


	addUser_To_database(newUser);

}

bool checkPassword(unsigned long int id, char *password)//function to check match between user and his password
{
	char IfEnd;
	char buffer[size];
	FILE *user = fopen("userText.txt", "r");

	do
	{
		IfEnd = fscanf(user, "%s", buffer);
		if (!strcmp("ID:", buffer))
		{
			IfEnd = fscanf(user, "%s", buffer);
			if (!strcmp(id, buffer))
			{
				fscanf(user, "%s", buffer);
				fscanf(user, "%s", buffer);
				if (!strcmp(password, buffer))
				{
					fclose(user);
					return true;
				}
				else
				{
					fclose(user);
					return false;
				}
			}
		}

	} while (IfEnd != EOF);
	fclose(user);
	return false;
}

void hidePassword(char *oldPassword)
{
	char ch;
	int i = 0;
	char password[size];
	fflush(stdout);
	while ((ch = _getch()) != EOF && ch != '\n' && ch != '\r' && i < sizeof(password) - 1)
	{
		if (ch == 'b' && i > 0)
		{
			printf("\b \b");
			fflush(stdout);
			i--;
			password[i] = '\0';
		}
		else if (isalnum(ch))
		{
			putchar('*');
			password[i++] = (char)ch;
		}
	}
	password[i] = '\0';
	strcpy(oldPassword, password);
}



bool check_ifManager(char *id)
{
	//char ch;
	//char buffer[size];
	char ManagerIdOnly[IDSIZE] = "201483302";

	if (!strcmp(ManagerIdOnly, id))
		return true;
	else
		return false;

}
bool check_ifEditor(char *id)
{
	char EditorIdOnly[IDSIZE] = "201874328";
	if (!strcmp(EditorIdOnly, id))
		return true;
	else
		return false;
}
bool check_ifUser(char *id)
{
	int i = 0;
	User *users = getUsersArr();

	for (i = 0; i < userCounter; i++)
	{
		if (!strcmp(users[i].ID, id))
		{
			////maybe also free users???????????
			return true;
		}
	}
	//////////maybe also free users in here???????????
	return false;

}


void printGovTitle()
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, PINK);
	printf("\n\n\n");
	printf("         # # #        ###########      #           #         ###         #                    \n");
	printf("      #               #         #       #         #           #          #                     \n");
	printf("     #                #         #        #       #            #          #                     \n");
	printf("    #    #####        #         #         #     #             #          #                      \n");
	printf("     #       #        #         #          #   #              #          #                      \n");
	printf("      #      #        #         #           # #               #          #                      \n");
	printf("         # # #        ###########            #         #     ###         # # # # # #             \n\n");
	SetConsoleTextAttribute(hConsole, WHITE);



}

void startTheProgram()
{
	while (loginScreen() != 7);

}

int loginScreen()
{
	int cnt = 0;
	int exitFlag = 0;
	bool flag;
	char input[NAMESIZE];
	char password[PASSWORDSIZE];

	system("cls");
	printGovTitle();
	printf("\n\n~~~~~~~~~ LOG IN screen ~~~~~~~~~~~\n\n");
	do
	{
		printf("Enter your ID and the system will recognized which permission you own :\n");
		printf("If you want to sign in please type 'sign in'\n");
		printf("If you wish to Exit type 'exit'\n");
		gets(input);
		if (!strcmp(input, "EXIT") || !strcmp(input, "Exit") || !strcmp(input, "exit"))
		{
			exitFlag = 7;
		}
		if (!strcmp(input, "sign in") || !strcmp(input, "SIGN IN") || !strcmp(input, "Sign in") || !strcmp(input, "Sign In"))
		{
			userRegistration();
		}
		flag = checkID_database(input);

	} while (!flag && exitFlag != 7);

	if (exitFlag == 7)
		return 7;

	do
	{
		printf("Please enter your password: \n");
		//gets(password);
		hidePassword(password);
		if (!checkMatch_id_password(input, password))
		{
			printf("WRONG password! \n");
			printf("%d more attempts left!\n", 2 - cnt);
			flag = false;
		}
		else
		{
			printf("password match!!! \n");
			flag = true;
		}
		cnt++;

	} while (cnt < 3 && !checkMatch_id_password(input, password));

	if (flag)
	{

		if (check_ifEditor(input))
		{
			editorMenu();
			return 1;
		}
		if (check_ifManager(input))
		{
			managerMenu();
			return 1;
		}
		if (check_ifUser(input))
		{
			userMenu();
			return 1;
		}
	}

	else if (!flag)
	{
		printf("Log in FAILED !!! please try again later.\n");
		getchar();
		return 0;
	}
	return 0;

}


int main()
{



	startTheProgram();
	return 0;
	///need to realese??????????????

}


User *getUsersArr()
{
	char ch;
	char buffer[size];
	char field1[size];
	char field2[size];
	char field3[size];
	int i = -1;
	int j = 0;

	FILE *fp = fopen("userText.txt", "r");
	User *user = NULL;
	userCounter = 0;
	do
	{
		ch = fscanf(fp, "%s", buffer);
		if (!strcmp(buffer, "firstName:"))
		{
			i++;
			userCounter++;
			if (user == NULL)
				user = (User*)malloc(sizeof(User));
			else
				user = (User*)realloc(user, sizeof(User)*(i + 2));
			ch = fscanf(fp, "%s", buffer);//skip the "firstName:"
			user[i].firstName = strdup(buffer);
			ch = fscanf(fp, "%s", buffer);//skip "lastName:"
			ch = fscanf(fp, "%s", buffer);
			user[i].lastName = strdup(buffer);
			ch = fscanf(fp, "%s", buffer);//skip the "ID:"
			ch = fscanf(fp, "%s", buffer);
			user[i].ID = strdup(buffer);
			ch = fscanf(fp, "%s", buffer);//skip the "gender:"
			ch = fscanf(fp, "%s", buffer);
			user[i].gender = strdup(buffer);
			ch = fscanf(fp, "%s", buffer);//skip the "familyStatus:"
			ch = fscanf(fp, "%s", buffer);
			user[i].familyStatus = strdup(buffer);
			ch = fscanf(fp, "%s", buffer);//skip the ""kids:"
			ch = fscanf(fp, "%s", buffer);
			user[i].kids = atoi(buffer);
			ch = fscanf(fp, "%s", buffer);//skip the "password:"
			ch = fscanf(fp, "%s", buffer);
			user[i].password = strdup(buffer);
			ch = fscanf(fp, "%s", buffer);//skip the "numRequests:"
			ch = fscanf(fp, "%s", buffer);
			user[i].numRequests = atoi(buffer);


			if (user[i].numRequests == 0)
			{
				user[i].requestList = NULL;
				continue;
			}

			user[i].requestList = (Request**)malloc(user[i].numRequests*sizeof(Request*));

			for (j = 0; j < user[i].numRequests; j++)
			{
				user[i].requestList[j] = (Request*)malloc(sizeof(Request));

				ch = fscanf(fp, "%s", buffer);
				ch = fscanf(fp, "%s", field3);
				ch = fscanf(fp, "%s", field1);
				ch = fscanf(fp, "%s", field2);



				if (!strcmp(buffer, "form1:"))
				{
					user[i].requestList[j]->form1 = (newBorn*)malloc(sizeof(newBorn));
					user[i].requestList[j]->form1->babyID = strdup(field1);
					user[i].requestList[j]->form1->babyName = strdup(field2);
					user[i].requestList[j]->form2 = user[i].requestList[j]->form3 = NULL;
					user[i].requestList[j]->request_ID = atoi(field3);

				}
				else if (!strcmp(buffer, "form2:"))
				{
					user[i].requestList[j]->form2 = (personalStatus*)malloc(sizeof(personalStatus));
					user[i].requestList[j]->form2->currentStatus = strdup(field1);
					user[i].requestList[j]->form2->newStatus = strdup(field2);
					user[i].requestList[j]->form1 = user[i].requestList[j]->form3 = NULL;
					user[i].requestList[j]->request_ID = atoi(field3);
				}
				else if (!strcmp(buffer, "form3:"))
				{

					user[i].requestList[j]->form3 = (familyChange*)malloc(sizeof(familyChange));
					user[i].requestList[j]->form3->currentFamilyName = strdup(field1);
					user[i].requestList[j]->form3->newFamilyName = strdup(field2);
					user[i].requestList[j]->form1 = user[i].requestList[j]->form2 = NULL;
					user[i].requestList[j]->request_ID = atoi(field3);
				}
			}

		}

	} while (ch != EOF);
	fclose(fp);
	return user;
}
