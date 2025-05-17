#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <math.h>
#include <ctype.h>
#define FILENAME "database.txt"
#define PASSWORD "password"

struct Student_Details{
    int index_number;
    char first_name[15];
    char last_name[15];
    int age;
    float cwa;
    int reference_number;
    char gender[7];

};


char * format_name(char *name){
    if (name[0]) {
        name[0] = toupper(name[0]);
    }

    for (int i = 1; name[i]; i++) {
        name[i] = tolower(name[i]);
    }
    return name;
}

void flush(void){
    int flush;
    while ((flush = getchar()) != '\n' && flush != EOF);
}

void trimNewLine(char *name){
for(int i = 0; i< strlen(name); i++){
 if (name[i] == '\t' || name[i] == '\n'){
    name[i] = '\0';
    break;
 }}}



int verify_admin_password(void){
char input_password[90];
printf("Password: ");
fgets(input_password, sizeof(input_password), stdin);
trimNewLine(input_password);
 if (strcmp(input_password, PASSWORD) == 0){
        return 1;
 } else{
     printf("Password is Incorrect. Try again\n");
     printf("Password: ");
     fgets(input_password, sizeof(input_password), stdin);
     trimNewLine(input_password);
    if(strcmp(input_password, PASSWORD)== 0){
        return 1;
    }
    else {
    printf("Password is Incorrect. Last try\n");
    printf("Password: ");
    fgets(input_password, sizeof(input_password), stdin);
    trimNewLine(input_password);
   if(strcmp(input_password, PASSWORD)== 0){
        return 1;
    }
    else {
        printf("Incorrect password. Access Denied");
 return 0;}
    }
 }}






void print_menu(void){
    printf("========MENU======\n");
    printf("1.Add Students\n");
    printf("2.View Students\n");
    printf("3.Search Student\n");
    printf("4.Update Student Information\n");
    printf("5.Delete Student Information\n");
    printf("6.Exit\n");
    printf("Enter your choice:  ");

}


void add_student(struct Student_Details new_student,struct Student_Details student, const char *filename){
    FILE *file = fopen(filename, "a+");
    if (file == NULL){
        printf("File error.\n");
        return;
    }
    rewind(file);
    printf("Enter student details\n");
    printf("First Name: \n");
    scanf("%s", new_student.first_name);
    printf("Last Name: \n");
    scanf("%s", new_student.last_name);




    while(fscanf(file, "%s %s %d %d %f %d %s", student.first_name,student.last_name, &student.index_number, &student.age, &student.cwa,
        &student.reference_number, student.gender) != EOF){
        if (strcasecmp(new_student.first_name, student.first_name)==0 && strcasecmp(new_student.last_name, student.last_name)==0){
            printf("Student already exists in our database\n");
            goto end_of_function;
        }}
    printf("Index number: \n");
    scanf("%d", &new_student.index_number);
    printf("Age: \n");
    scanf("%d", &new_student.age);
    printf("CWA: \n");
    scanf("%f", &new_student.cwa);
    printf("Reference Number: \n");
    scanf("%d", &new_student.reference_number);
    printf("Gender: \n");
    scanf("%6s", new_student.gender);
    fprintf(file,"%s %s %d %d %f %d %s \n",
    new_student.first_name, new_student.last_name, new_student.index_number, new_student.age, new_student.cwa,
    new_student.reference_number, new_student.gender);
    printf("%s has been added successfully\n\n", format_name(new_student.first_name));
end_of_function:
    fclose(file);
}


void view_students(const char *filename, struct Student_Details student){
    FILE *file = fopen(filename, "r");
    if (file == NULL){
        printf("File error. \n");
        return;
    }
    while(fscanf(file, "%s %s %d %d %f %d %s", student.first_name, student.last_name, &student.index_number, &student.age, &student.cwa,
        &student.reference_number, student.gender ) != EOF){
            printf("Name:%s %s \nIndex Number: %d\nAge: %d\nCWA: %.2f\nReference Number: %d\nGender: %s\n",
                 format_name(student.first_name), format_name(student.last_name), student.index_number, student.age, student.cwa,
                student.reference_number, format_name(student.gender));
            printf("\n\n");
        }
        fclose(file);
}



void search_student(char *search_name1, char *search_name2, const char *filename, struct Student_Details student){
    trimNewLine(search_name1);
    trimNewLine(search_name2);
    FILE *file = fopen(filename,"r");
    if (file == NULL){
        printf("File error.\n");
        return;
    }
    int found = 0;
    while(fscanf(file, "%s %s %d %d %f %d %s", student.first_name, student.last_name, &student.index_number, &student.age, &student.cwa,
        &student.reference_number, student.gender) != EOF){
        if (strcasecmp(student.first_name, search_name1)==0 && strcasecmp(student.last_name, search_name2)==0){
            printf("Name: %s %s\t", format_name(student.first_name), format_name(student.last_name));
            printf("Index Number: %d\t", student.index_number);
            printf("Age: %d\t", student.age);
            printf("CWA: %f\t",student.cwa);
            printf("Reference Number: %d\t", student.reference_number);
            printf("Gender: %s\t\n\n", format_name(student.gender));
            found = 1;
        }
    }
    if (!found){

        printf("No student found with name: %s %s found\n\n", format_name(search_name1), format_name(search_name2));
    }

    fclose(file);
}



void update_student_information(char *search_name1, char *search_name2, const char *filename, struct Student_Details student){
    trimNewLine(search_name1);
    trimNewLine(search_name2);
    FILE *file = fopen(filename, "r");
    FILE *temp = fopen("temp.txt", "w");

    if ( file == NULL || temp == NULL){
        printf("File error.\n");
        return;
    }
    int found = 0;
    while (fscanf(file, "%s %s %d %d %f %d %s", student.first_name, student.last_name, &student.index_number, &student.age, &student.cwa, &student.reference_number, student.gender)!=EOF){
        if (strcasecmp(student.first_name, search_name1)==0 && strcasecmp(student.last_name, search_name2)==0){
            found = 1;
            printf("Student found. Enter new data:\n");
            printf("First Name: \n");
            scanf("%s", student.first_name);
            printf("Last Name: \n");
            scanf("%s", student.last_name);
            printf("Index number: \n");
            scanf("%d", &student.index_number);
            printf("Age: \n");
            scanf("%d", &student.age);
            printf("CWA: \n");
            scanf("%f", &student.cwa);
            printf("Reference Number: \n");
            scanf("%d", &student.reference_number);
            printf("Gender: \n");
            scanf("%6s", student.gender);
        }
        fprintf(temp, "%s %s %d %d %f %d %s \n", student.first_name, student.last_name, student.index_number, student.age, student.cwa, student.reference_number, student.gender);

    }
    fclose(file);
    fclose(temp);
    remove(filename);
    rename("temp.txt", filename);

    found ? printf("Student record updated successfully\n\n"): printf("%s %s does not exist.\n\n", format_name(search_name1), format_name(search_name2));
}



void delete_student(const char *filename, char *search_name1, char *search_name2, struct Student_Details student){
    trimNewLine(search_name1);
    trimNewLine(search_name2);
    FILE *file = fopen(filename, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (file == NULL || temp == NULL){
        printf("File error. \n");
        return;
    }
    int found = 0;
    while( fscanf(file, "%s %s %d %d %f %d %s", student.first_name, student.last_name, &student.index_number, &student.age, &student.cwa, &student.reference_number, student.gender) != EOF){
        if (strcasecmp(student.first_name, search_name1)==0 && strcasecmp(student.last_name, search_name2)==0){
            found = 1;
            printf("%s's information has been deleted\n\n", format_name(search_name1));
            continue;
        }
        fprintf(temp, "%s %s %d %d %f %d %s \n", student.first_name,  student.last_name, student.index_number, student.age, student.cwa, student.reference_number, student.gender);

    }

    fclose(temp);
    fclose(file);
    remove(filename);
    rename("temp.txt", filename);
    if(!found){
        printf("Student could not be found.\n\n");
    }

}


int main(void){
    int choice;
    printf("Welcome to the Student Management System\n");
    FILE *file = fopen("database.txt", "r");
    if (file == NULL){
        printf("Creating database...\nDatabase created\n\n");
        file = fopen("database.txt", "w");
        if (file == NULL){
            printf("file error");
           return 1;}
        }
    fclose(file);

while(1){
    print_menu();
    scanf("%d", &choice);
    printf("\n\n");
    struct Student_Details new_student;
    struct Student_Details student;
    flush();
    char search_name1[15];
    char search_name2[15];
 switch(choice){
    case 1:
        if(verify_admin_password()){
      add_student(new_student, student, FILENAME);}
      break;
    case 2:
      view_students(FILENAME, student);
      break;
    case 3:
      printf("Enter the name of the student you're searching for\n");
      printf("First name: ");
      fgets(search_name1, sizeof(search_name1), stdin);
      printf("Last name: ");
      fgets(search_name2, sizeof(search_name2), stdin);
      search_student(search_name1, search_name2, FILENAME, student);
      break;
    case 4:
        if(verify_admin_password()){
      printf("Enter the name of the student\n");
      printf("First name: ");
      fgets(search_name1, sizeof(search_name1), stdin);
      printf("Last name: ");
      fgets(search_name2, sizeof(search_name2), stdin);
      update_student_information(search_name1,search_name2, FILENAME, student);}
      break;
    case 5:
        if(verify_admin_password()){
      printf("Enter Student name\n");
      printf("First name: ");
      fgets(search_name1, sizeof(search_name1), stdin);
      printf("Last name: ");
      fgets(search_name2, sizeof(search_name2), stdin);
      delete_student("database.txt", search_name1, search_name2, student);}
      break;
    case 6:
      printf("Program Existing...");
      exit(0);
    default:
      printf("You entered a wrong choice");
      }



}
return 0;
}


