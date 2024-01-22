#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 1000

//structure definition
 typedef struct{
	char name[30];
	char id[20];
	char designation[20];
	char department[20];
	int salary;
} employee;

//function prototypes
void enter_em( int i, employee *e[]); //function to add employees
void display_all(employee *e[], int a); //function to display all employees
void edit_em(employee *e[], int a); //function to edit employees
void cal_payment(employee *e[], int a); //function to calculate payment
int delet_em(employee *e[], int a); //function to delete an employee
void table();

int main(void){
	employee *e[SIZE];
	printf("----------------------------\n");
	printf("Employee Management System\n");
	printf("----------------------------\n");
	printf("1. Add employee \n");
	printf("2. Display all employees\n");
	printf("3. Edit employee\n");
	printf("4. Calculate employee payment\n");
	printf("5. Delete employee\n");
	printf("0. Exit\n");
	printf("----------------------------\n");
	//declaration
	int i=0; //number of employee (in array, it starts from 0)
	int ans; //choose option
	char m; // choose enter more or not
	//processing data
	do{
	fflush(stdin);
	printf("Enter Your Choice: ");
	scanf("%d", &ans);
	printf("\n");
		switch(ans){
			case 1:{
				do{
					int flag = 0; //state of searching ID ( flag = 1 while the searched ID already found/exist)
					e[i] = (employee *)malloc(sizeof(employee)); //create a pointer for each employee
					enter_em(i, e); //call function to enter employee data
					if ( i > 0){
						for (int l = 1; l <= i; l++){                       // searching ID
							fflush(stdin);
							if (strcmp((e[i]->id), (e[i-l]->id)) == 0) {
   								flag = 1;
								break;
							}
						}
					}
					//checking state of searching ID
					if (flag != 0){
						printf ("THE EMPLOYEE ID ALREADY EXIST!!! CANNOT ADD\n");
						// if ID already found/exist, the data will be not received, the number of employees will stay the same
					}
					else {
						table();
						printf("%-15s(%-5s)     %-24s%-24s\n",e[i]->name,e[i]->id,e[i]->designation,e[i]->department);
						i++; // if ID not found/exist, the data will be received, the number of employees will increase
					}
					fflush(stdin);
					printf("\nPress [Y] to enter more: ");
					scanf("%c", &m);
					printf("\n");
				} while (m != 'N');
		 		printf("\n");
				break;
			}
			case 2:{
				display_all(e,i); //call function to display all employees
				printf("\n");
				break;
			}
			case 3:{
				edit_em(e,i); //call function to display edit employee's data
				printf("\n");
				break;
			}
			case 4:{
				char n;
				printf("Please note that the salary in 1 year over $15000 will be charged 10%c for the tax. In case of the salary in 1 year over $25000, the extra charge of 5%c for the redundant amount\n", '%', '%');
				printf("\n");
				do{
					cal_payment(e,i); //call function to display calculate payment
					fflush(stdin);
					printf("Press [Y] to enter more: ");
					scanf("%c", &n);
					printf("\n");
				} while ( n != 'N');
				break;
			}
			case 5:{
				i = delet_em(e,i); //call function to delete and updating the total numebr of employees
				break;
			}
			default:{
				printf("Invalid option\n");
				break;
			}
			case 0:{
				printf("Exit the program...");
				break;
			}
		}
	}while( ans != 0);
	return 0;
}

//function definition

void enter_em(const int  i, employee *e[]){
	fflush(stdin);
	printf("Enter employee name: ");
	gets( e[i] -> name);
	printf("Enter employee ID: ");
	gets(e[i]->id);
	printf("Enter employee designation: ");
	gets(e[i] -> designation);
	printf("Enter employee department: ");
	gets(e[i] -> department);
	printf("Enter employee salary: $");
	scanf(" %d", &e[i] -> salary);
}

void display_all(employee *e[], int a){
	int i; //counter
	printf("Here is the list of employees");
	printf("\n\n");
	table();
	//output processing
	for (i = 0; i < a; i++){
		printf("%-15s(%-5s)     %-24s%-24s\n",e[i]->name,e[i]->id,e[i]->designation,e[i]->department);
	}
}

void edit_em(employee *e[], int a){
	//declaration
	int i, pos, flag; 
	char id1[20];
	//input processing
	printf("Enter employee ID for editing: ");
	scanf("%s", &id1);
	printf("\n");
	//seacrhing the ID that needs to edit data
	for (i = 0; i < a; i++){
		flag = 0;
		if (strcmp( e[i]->id, id1) == 0 ){ 
			pos = i;
			flag = 1;
			break;
		}
	}
	//checking if ID is found or not
	if (flag != 0){
		// enter the data of that employee again
		fflush(stdin);
		printf("Enter employee name: ");
		gets( e[pos] -> name);
		printf("Enter employee designation: ");
		gets(e[pos] -> designation);
		printf("Enter employee department: ");
		gets(e[pos] -> department);
		printf("Enter employee salary: $");
		scanf(" %d", &e[pos] -> salary);
		table();
		printf("%-15s(%-5s)     %-24s%-24s\n",e[i]->name,e[i]->id,e[i]->designation,e[i]->department);
	}
	//if ID is not found  then notify the user
  	else {
		printf("ID is not found");
	}
}

void cal_payment(employee *e[], int a){
	//declaration
	int i, pos, flag;
	int payment;
	char id2[20];
	fflush(stdin);
	//input processing
	printf("Enter employee ID for payment: ");
	scanf("%s", &id2);
	//seacrhing the ID that need to edit data
	for (i = 0; i < a; i++){
		flag = 0; //initialize flag = 0 with every new "for loop"
		if (strcmp( e[i]->id, id2) == 0 ){ 
			pos = i;
			flag = 1;
			break;
		}
	}
	//if the ID is found then calculate the payment
	if (flag != 0){
		// for the salary > $25000
			if (((e[pos] -> salary)*12) > 25000) payment = ((e[i] -> salary)*12)*0.9 - (((e[i] -> salary)*12)-25000)*0.05;
		// for the salary > $15000
			else if (((e[pos] -> salary)*12) > 15000 ) payment = ((e[i] -> salary)*12)*0.9;
		// for the salary < $15000
			else  payment = (e[pos] -> salary)*12;
	printf("The after-tax payment: $ %d\n", payment);
	printf("\n");
	}
	//if the ID is not found then notify the user
	else {
		printf("ID is not found\n\n");
	}
}

int delet_em(employee *e[], int a){
	//declaration
	char id3[20];
	int c,pos, flag; 
	int i; //counter
	fflush(stdin);
	printf("Enter employee ID for deleting: ");
	scanf("%s", &id3);
	//searching ID needs to be deleted
	for (i = 0; i < a; i++){
		flag = 0;
		if (strcmp( e[i]->id, id3) == 0 ) {
			flag = 1;
			pos = i;
			break;
		}
	}
	//checking if ID is found then delete
	if (flag != 0){
	printf("%s - %s already deleted\n\n", e[pos] -> name, id3);
		for (c = pos; c < a-1; c++){
			strcpy(e[c]->name , e[c+1]->name);
			strcpy(e[c]->id , e[c+1]->id);
			strcpy(e[c]->designation , e[c+1]->designation);
			strcpy(e[c]->department , e[c+1]->department);
			e[c]->salary = e[c+1]->salary;
		}
	a--; //reduce the number of employee by 1 after deleting
	}
	// if ID is not found then notify the user
	else {
		printf("ID is not found\n\n");
		//keep the number of employee if ID is  not found
	}
	return a;
}

void table(){
	printf("\n%-27s%-24s%-24s\n","Name","Designation","Department");
	printf("======================================================================\n");
}
