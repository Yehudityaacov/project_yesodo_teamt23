#include <stdio.h>

typedef struct newBorn    
{
	unsigned long babyID;
	char * babyName;

}newBorn;


typedef struct personalStatus  
{
	char * currentFamilyName;
	char * newFamilyName;
}personalStatus;

typedef struct familyChange  
{
	char currentStatus;
	char newStatus;
}familyChange;

typedef struct Request
{
	int request_ID;    // number of the request
	unsigned long int request_UserID;
	char * request_gender;
	char * request_status;
	newBorn * form1;
	personalStatus * form2;
	familyChange * form3;

}Request;

typedef struct User
{
	char * firstName;
	char * lastName;
	unsigned long int ID;
	char * gender;
	char familyStatus;
	int kids;
	char * password;
	Request ** requestList;
}User;

typedef struct Manager
{
	char * firstName;
	char * lastName;
	unsigned long int M_ID;
	char * M_password;
}Manager;

typedef struct CotentEditor
{
	char * firstName;
	char * lastName;
	unsigned long int E_ID;
	char * E_password;
}CotentEditor;

typedef struct LogIn
{
	unsigned long int ID;
	char * password;
}LogIn;