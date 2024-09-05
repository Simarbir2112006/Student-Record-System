#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

// Defining max length for the name and branch abrivations

#define MAX_NAME 50
#define MAX_BRANCH 4
#define TABLE_SIZE 15

// Represents a student in the hash table
typedef struct node
{
    char name[MAX_NAME + 1];
    int roll_no;
    float CGPA;
    char branch[MAX_BRANCH + 1];
    // Can add other stuff related to a student
    struct node *next;
} node;

unsigned int hash (char *name);
void print_table();
bool insert(node *name);
void to_lowercase(char *str);
node *find_student(char *name);

// Hash table
node *table[TABLE_SIZE] = {NULL};

int main(int argc, char *argv[])
{
    // Check for correct number of args
    if (argc != 2)
    {
        printf("Usage: .\\a.exe [student name]\n");
        return 1;
    }

    char *student = argv[1];

    // Student details
    node students[] = {
        {.name = "Simarbir", .roll_no = 103122, .CGPA = 10.0, .branch = "AIML"},
        {.name = "Manit", .roll_no = 126451, .CGPA = 9.5, .branch = "COE"},
        {.name = "Harjot", .roll_no = 145861, .CGPA = 9.5, .branch = "MEE"},
        {.name = "Daman", .roll_no = 145616, .CGPA = 7.1, .branch = "ECE"},
        {.name = "Krish", .roll_no = 126785, .CGPA = 6.5, .branch = "MEE"},
        {.name = "Rohan", .roll_no = 149852, .CGPA = 7.2, .branch = "COPC"},
        {.name = "Jasroop", .roll_no = 118152, .CGPA = 8.7, .branch = "COPC"},
        {.name = "Harkirat", .roll_no = 113461, .CGPA = 8.3, .branch = "COE"},
        {.name = "Navjot", .roll_no = 135861, .CGPA = 6.8, .branch = "COSE"},
        {.name = "Yuvraj", .roll_no = 133824, .CGPA = 7.2, .branch = "EIC"},
        {.name = "Gurshaan", .roll_no = 119654, .CGPA = 8.6, .branch = "EEC"},
        {.name = "Urvansh", .roll_no = 115896, .CGPA = 7.7, .branch = "ENC"},
        {.name = "Aniket", .roll_no = 101192, .CGPA = 6.9, .branch = "AIML"},
        {.name = "Liza", .roll_no = 126451, .CGPA = 8.8, .branch = "COBS"},
        {.name = "Bikram", .roll_no = 115766, .CGPA = 10.0, .branch = "COE"}
    };

    // Adding students to the hash table
    for (int i = 0; i < sizeof(students)/sizeof(students[0]); i++)
    {
        insert(&students[i]);
    }

    // Printing the entire hash table
    print_table();

    // Checking if the student is in the Database
    node *found = find_student(student);
    if (find_student(student) != NULL)
    {
        printf("\n\t%s is in the system!\n", student);
        printf("\tDetails\t--->\tName: %s | Roll No: %d | CGPA: %.2f | Branch: %s\n", found->name, found->roll_no, found->CGPA, found->branch);
    }
    else
    {
        printf("%s is not in the system!\n", student);
    }
    return 0;
}

// Hashes the name to a unique number
unsigned int hash (char *name)
{
    unsigned int index = toupper(name[0]) - 'A'; 

    int len = strlen(name);
    for (int i = 1; i < len; i++)
    {
        index += name[i]; 
    }

    return (index * 2) % TABLE_SIZE;
}

// Print the whole hash table to show case the implementation
void print_table()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {

        node *current = table[i];

        if (current == NULL)
        {
            printf("\t%i\t--->\n", i + 1);
        }

        else
        {
            while(current != NULL)
            {
                printf("\t%i\t--->\t%s (Roll No: %d, CGPA: %.2f, Branch: %s)", i + 1, current->name, current->roll_no, current->CGPA, current->branch);
                current = current->next;
            }

            printf("\n");
        }
    }   
}

// Add the student in the hash table
bool insert(node *name)
{
    if (name == NULL)
    {
        return false;
    }

    int index = hash(name->name);

    // Insert at the beginning of the list for simplicity
    name->next = table[index];
    table[index] = name;

    return true;
}

// To lowercase the string
void to_lowercase(char *str)
{
    for (int i = 0; str[i]; i++)
    {
        str[i] = tolower((unsigned char)str[i]);
    }
}

// To check the presence of the student in the hash table
node *find_student(char *student_name)
{
    //creating this array to store the lowercase version of the name that has been input
    char lower_student_name[MAX_NAME + 1];
    strcpy(lower_student_name, student_name);
    to_lowercase(lower_student_name);
    
    int index = hash(student_name);

    node *current = table[index];

    while (current != NULL)
    {
        //creating this array to store the lowercase version of the name that is currently in this bucket
        char lower_current[MAX_NAME + 1];
        strcpy(lower_current, current->name);
        to_lowercase(lower_current);

        if (strcmp(lower_current, lower_student_name) == 0)
        {
            return current;
        }
        else
        {
            current = current->next;
        }
    }
    return NULL;
}
