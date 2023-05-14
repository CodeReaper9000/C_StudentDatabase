/* Student management system: Create a program that manages student data including their name,roll number, marks and grades */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_NAME_LENGTH 50

typedef struct{ 
    char name[MAX_NAME_LENGTH];
    int roll;
    float marks;
    char grade;
} Student;

// Function to create new csv
void create_csv(){
    FILE *fp;
    fp = fopen("student.csv","r");
    if(fp == NULL){
        fp = fopen("student.csv","w");
        fprintf(fp,"Roll Number,Name,Marks,Grade\n");
        fclose(fp);
    }
}

// Function to display all students
void displayStudents(){
	FILE* fp;
	fp = fopen("student.csv", "r");

	if (fp==NULL){
		printf("File doesn't exist.\n");
	}
	else{
		char buffer[1024];
		int row = 0;
		int column = 0;
		
		printf("\nStudent Data\n");
    	printf("Roll Number    	Name    	Marks    	Grade\n");
    	printf("----------------------------------------------------\n");   	
		while (fgets(buffer,1024, fp)) {
			column = 0;
			row++;
			
			if (row == 1)
				continue;

			// Splitting the data
			char* value = strtok(buffer, ", ");

			while (value) {
				printf("%s\t\t", value);
				value = strtok(NULL, ", ");
				column++;
			}
			printf("\n");
		}
		fclose(fp);
	}
}

// Function to calculate grade
char get_grade(float marks){
    if (marks >= 90) {
        return 'A';
    } else if (marks >= 80) {
        return 'B';
    } else if (marks >= 70) {
        return 'C';
    } else if (marks >= 60) {
        return 'D';
    } else {
        return 'F';
    }
}

//Functino to add students
void add_student(){
    FILE *fp;
    fp = fopen("student.csv","r");
    if(fp == NULL){
        printf("Error. File doesn't exist yet.\n");
        return;
    }
    else{
    	fclose(fp);
    	fp = fopen("student.csv","a");
    	Student student;
    	printf("\nEnter details of student:\n");
    	printf("Name: ");
    	scanf("%[^\n]",student.name);      // accepts till \n is encounterd
    	printf("Roll Number: ");
    	scanf("%d",&student.roll);
    	printf("Marks: ");
    	scanf("%f",&student.marks);
    	student.grade = get_grade(student.marks);
    	fprintf(fp, "%d,%s,%.2f,%c\n",student.roll,student.name,student.marks,student.grade);
    	printf("Student added succesfully.\n");
	}
	fclose(fp);
}

// function to delete a student from the CSV file
void delete_student() {
    char roll_no[10];
    int found = 0;
    printf("Enter the roll no of the student you want to delete: ");
    scanf("%s", roll_no);
    FILE* fp1, * fp2;
    fp1 = fopen("student.csv", "r");
    fp2 = fopen("temp.csv", "w");
    if (fp1 == NULL || fp2 == NULL) {
        printf("Error opening files.\n");
        exit(1);
    }
    char name[20], marks[10];
    char grade[2];
    char g;
    char temp_roll_no[10];
    while (fscanf(fp1, "%[^,],%[^,],%[^,],%s\n", temp_roll_no, name, marks, grade) != EOF) {
        if (strcmp(temp_roll_no, roll_no) == 0) {
            found = 1;
        }
        else{
        	float m = atof(marks);
        	fprintf(fp2, "%s,%s,%.2f,%s\n", temp_roll_no, name, m, grade);
        }
    }
    if (!found) {
        printf("Student with roll no %s not found.\n", roll_no);
    }
    else
    	printf("Student with roll no %s deleted successfully.\n", roll_no);
    fclose(fp1);
    fclose(fp2);
    remove("student.csv");
    rename("temp.csv", "student.csv");
}

// Function to update student data
void update_student() {
    char roll_no[10];
    int found = 0;
    printf("Enter the roll no of the student you want to update: ");
    scanf("%s", roll_no);
    FILE* fp1, * fp2;
    fp1 = fopen("student.csv", "r");
    fp2 = fopen("temp.csv", "w");
    if (fp1 == NULL || fp2 == NULL) {
        printf("Error opening files.\n");
        exit(1);
    }
    char name[20], marks[10];
    char grade[2];
    char g;
    //float marks;
    //int marks, grade;
    char temp_roll_no[10];
    while (fscanf(fp1, "%[^,],%[^,],%[^,],%s\n", temp_roll_no, name, marks, grade) != EOF) {
        if (strcmp(temp_roll_no, roll_no) == 0) {
            found = 1;
            printf("Enter the new name of the student: ");
            scanf("%s", name);
            printf("Enter the new marks of the student: ");
            scanf("%s", marks);
            g = get_grade(atof(marks));
            char g2[2] = {g,'\0'};
            float m = atof(marks);
        	fprintf(fp2, "%s,%s,%.2f,%s\n", temp_roll_no, name, m, g2);
        }
        else{
        	float m = atof(marks);
        	fprintf(fp2, "%s,%s,%.2f,%s\n", temp_roll_no, name, m, grade);
        }
    }
    if (!found) 
        printf("Student with roll no %s not found.\n", roll_no);
    else 
    	printf("Student with roll no %s updated successfully.\n", roll_no);
    fclose(fp1);
    fclose(fp2);
    remove("student.csv");
    rename("temp.csv", "student.csv");    	
}

// Function to search for a student by roll number
void search_student() {
	int roll_no;
    FILE *fp;
    char line[100];
    char *token;
    char copy[100];
    int found = 0;
    fp = fopen("student.csv", "r");
    if (fp == NULL) {
        printf("Error: Failed to open file for reading.\n");
        return;
    }
    printf("Enter roll number to search: ");
    scanf("%d",&roll_no);
    while (fgets(line, 100, fp) != NULL) {
    	strcpy(copy,line);					// copying line into copy as strtok reduces line
        token = strtok(line, ",");
        if (atoi(token) == roll_no) {
            printf("Roll Number    	Name    	Marks    	Grade\n");
            while (token) {					// seperates each word of one line
				printf("%s\t\t", token);
				token = strtok(NULL, ", ");
			}
			found = 1;
			break;
        }
    }
    if (!found) {
        printf("Error: Student with roll no %d not found.\n", roll_no);
    }
    fclose(fp);
}

// Function to delete entire database
void delete_database(){
	char choice;
	printf("Do you really want to delete the database? (y/n)\n");
	scanf("%c",&choice);
	if(choice == 'y'){
		FILE *fp;
		fp = fopen("student.csv", "r");
		if(fp == NULL)
    		printf("Database error\n");
		else {
    		fclose(fp);
    		if(remove("student.csv")) 
				printf("Unable to delete the file\n");
    		else 
				printf("Delete successful\n");
		}
	}
	else
		printf("Database was not deleted.");
}

// Driver Function
int main(){
	int choice;
	char newline;
    while (1) {
        printf("Welcome to Student Database Management\n");
        printf("---------------------------------------\n");
        printf("0. Create new student database\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Delete Database\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("--------------------------------------\n");
        switch (choice) {
        	case 0:
        		create_csv();
        		break;
            case 1:
            	scanf("%c", &newline);    // eat trailing newline
                add_student();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                search_student();
                break;
            case 4:
                update_student();
                break;
            case 5:
                delete_student();
                break;
            case 6:
            	scanf("%c", &newline);    // eat trailing newline
            	delete_database();
            	break;
            case 7:
                printf("Exiting program...\n");
                exit(0);
            default:
                printf("Invalid choice.\n");
                break;
        }
        printf("--------------------------------------\n");
        printf("\n\n");
    }
    return 0;
}
