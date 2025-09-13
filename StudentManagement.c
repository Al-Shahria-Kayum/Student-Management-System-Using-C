//Student Management Project in DS course - Second Semester 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STUDENTS 100
#define MAX_SEMESTERS 8

typedef struct {
    int id;
    char name[50];
    char address[100];
    char fatherName[50];
    char fatherPhone[12]; // 11 digits + null terminator
    char motherName[50];
    char motherPhone[12]; // 11 digits + null terminator
    char studentPhone[12]; // 11 digits + null terminator
    float cgpa[MAX_SEMESTERS]; // Store CGPA for each semester
} Student;

Student students[MAX_STUDENTS];
int studentCount = 0;

int isPhoneNumberUnique(const char* phoneNumber) {
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].fatherPhone, phoneNumber) == 0 ||
            strcmp(students[i].motherPhone, phoneNumber) == 0 ||
            strcmp(students[i].studentPhone, phoneNumber) == 0) {
            return 0; // Phone number is not unique
        }
    }
    return 1; // Phone number is unique
}

int isStudentIdUnique(int id) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            return 0; // Student ID is not unique
        }
    }
    return 1; // Student ID is unique
}

int isValidPhoneNumber(const char* phoneNumber) {
    return strlen(phoneNumber) == 11 && phoneNumber[0] == '0' && phoneNumber[1] == '1';
}

int containsDigits(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (isdigit(str[i])) {
            return 1;
        }
    }
    return 0;
}

void insertStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf("Student limit reached!\n");
        return;
    }

    Student newStudent;

    // Ensure unique student ID
    do {
        printf("Enter Student ID: ");
        scanf("%d", &newStudent.id);
        if (!isStudentIdUnique(newStudent.id)) {
            printf("This Student ID already exists. Please enter a different ID.\n");
        }
    } while (!isStudentIdUnique(newStudent.id));

    // Ensure student name does not contain digits
    do {
        printf("Enter Student Name: ");
        scanf(" %[^\n]", newStudent.name);
        if (containsDigits(newStudent.name)) {
            printf("Digits are not allowed. Please try again.\n");
        }
    } while (containsDigits(newStudent.name));

    printf("Enter Student Address: ");
    scanf(" %[^\n]", newStudent.address);

    // Ensure unique student's phone number
    do {
        printf("Enter Student's Phone Number (11 digits, starts with 01): ");
        scanf("%s", newStudent.studentPhone);
        if (!isValidPhoneNumber(newStudent.studentPhone)) {
            printf("Invalid phone number. Please try again.\n");
        } else if (!isPhoneNumberUnique(newStudent.studentPhone)) {
            printf("This phone number already exists. Please enter a different number.\n");
        }
    } while (!isValidPhoneNumber(newStudent.studentPhone) || !isPhoneNumberUnique(newStudent.studentPhone));

    // Ensure father's name does not contain digits
    do {
        printf("Enter Father's Name: ");
        scanf(" %[^\n]", newStudent.fatherName);
        if (containsDigits(newStudent.fatherName)) {
            printf("Digits are not allowed. Please try again.\n");
        }
    } while (containsDigits(newStudent.fatherName));

    // Ensure unique father's phone number
    do {
        printf("Enter Father's Phone Number (11 digits, starts with 01): ");
        scanf("%s", newStudent.fatherPhone);
        if (!isValidPhoneNumber(newStudent.fatherPhone)) {
            printf("Invalid phone number. Please try again.\n");
        } else if (!isPhoneNumberUnique(newStudent.fatherPhone) || strcmp(newStudent.fatherPhone, newStudent.studentPhone) == 0) {
            printf("This phone number already exists or matches the student's phone number. Please enter a different number.\n");
        }
    } while (!isValidPhoneNumber(newStudent.fatherPhone) || !isPhoneNumberUnique(newStudent.fatherPhone) || strcmp(newStudent.fatherPhone, newStudent.studentPhone) == 0);

    // Ensure mother's name does not contain digits
    do {
        printf("Enter Mother's Name: ");
        scanf(" %[^\n]", newStudent.motherName);
        if (containsDigits(newStudent.motherName)) {
            printf("Digits are not allowed. Please try again.\n");
        }
    } while (containsDigits(newStudent.motherName));

    // Ensure unique mother's phone number
    do {
        printf("Enter Mother's Phone Number (11 digits, starts with 01): ");
        scanf("%s", newStudent.motherPhone);
        if (!isValidPhoneNumber(newStudent.motherPhone)) {
            printf("Invalid phone number. Please try again.\n");
        } else if (!isPhoneNumberUnique(newStudent.motherPhone) ||
                   strcmp(newStudent.motherPhone, newStudent.fatherPhone) == 0 ||
                   strcmp(newStudent.motherPhone, newStudent.studentPhone) == 0) {
            printf("This phone number already exists or matches the father's or student's phone number. Please enter a different number.\n");
        }
    } while (!isValidPhoneNumber(newStudent.motherPhone) || !isPhoneNumberUnique(newStudent.motherPhone) ||
             strcmp(newStudent.motherPhone, newStudent.fatherPhone) == 0 ||
             strcmp(newStudent.motherPhone, newStudent.studentPhone) == 0);

    // Initialize CGPA for all semesters to 0
    for (int j = 0; j < MAX_SEMESTERS; j++) {
        newStudent.cgpa[j] = 0.0;
    }

    students[studentCount++] = newStudent;
    printf("Student added successfully!\n");
    printf("-------------------------\n");
}

void addSemesterCGPA() {
    int id, semesterNumber;
    float entryCGPA;
    printf("Enter Student ID to add CGPA: ");
    scanf("%d", &id);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            // Prompt for semester number
            do {
                printf("Enter semester number (1 to 8): ");
                scanf("%d", &semesterNumber);
                if (semesterNumber < 1 || semesterNumber > 8) {
                    printf("Please enter a valid semester number.\n");
                } else if (students[i].cgpa[semesterNumber - 1] != 0.0) {
                    printf("CGPA for semester %d is already entered. Please update it instead.\n", semesterNumber);
                    return;
                } else if (semesterNumber > 1 && students[i].cgpa[semesterNumber - 2] == 0.0) {
                    printf("CGPA for semester %d is not entered. Please enter the CGPA for semester %d first.\n", semesterNumber - 1, semesterNumber);
                    semesterNumber = 0; // Reset to allow re-entry
                }
            } while (semesterNumber < 1 || semesterNumber > 8);

            // Prompt for CGPA value
            do {
                printf("Enter CGPA value (1.00 to 4.00): ");
                scanf("%f", &entryCGPA);
                if (entryCGPA < 1.00 || entryCGPA > 4.00) {
                    printf("Please enter a valid CGPA value.\n");
                }
            } while (entryCGPA < 1.00 || entryCGPA > 4.00);

            // Store the CGPA for the specified semester
            students[i].cgpa[semesterNumber - 1] = entryCGPA;
            printf("CGPA for semester %d updated successfully!\n", semesterNumber);
            return;
        }
    }
    printf("Student not found!\n");
}

void printAllStudents() {
    if (studentCount == 0) {
        printf("No students to display.\n");
        return;
    }
    for (int i = 0; i < studentCount; i++) {
        printf("Student ID: %d\n", students[i].id);
        printf("Name: %s\n", students[i].name);
        printf("Address: %s\n", students[i].address);
        printf("Father's Name: %s\n", students[i].fatherName);
        printf("Father's Phone: %s\n", students[i].fatherPhone);
        printf("Mother's Name: %s\n", students[i].motherName);
        printf("Mother's Phone: %s\n", students[i].motherPhone);
        printf("Student's Phone: %s\n", students[i].studentPhone);
        printf("CGPA: ");
        double avg = 0, cg = 0;
        int cnt = 0;
        for (int j = 0; j < MAX_SEMESTERS; j++) {
            printf("Semester %d: %.2f ", j + 1, students[i].cgpa[j]);
            if (students[i].cgpa[j] > 0) {
                cnt++;
                cg += students[i].cgpa[j];
            }
        }
        avg = cg / cnt;
        printf("\nAverage CGPA: %0.2lf\n", avg);
        printf("\n-------------------------\n");
    }
}

void deleteStudent() {
    int id;
    printf("Enter Student ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1]; // Shift students left
            }
            studentCount--;
            printf("Student deleted successfully!\n");
            return;
        }
    }
    printf("Student not found!\n");
}

void searchStudentById() {
    int id;
    printf("Enter Student ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            printf("Student ID: %d\n", students[i].id);
            printf("Name: %s\n", students[i].name);
            printf("Address: %s\n", students[i].address);
            printf("Father's Name: %s\n", students[i].fatherName);
            printf("Father's Phone: %s\n", students[i].fatherPhone);
            printf("Mother's Name: %s\n", students[i].motherName);
            printf("Mother's Phone: %s\n", students[i].motherPhone);
            printf("Student's Phone: %s\n", students[i].studentPhone);
            printf("CGPA: ");
            for (int j = 0; j < MAX_SEMESTERS; j++) {
                printf("Semester %d: %.2f ", j + 1, students[i].cgpa[j]);
            }
            printf("\n-------------------------\n");
            return;
        }
    }
    printf("Student not found!\n");
}

void searchStudentByName() {
    char name[50];
    printf("Enter Student Name to search: ");
    scanf(" %[^\n]", name);

    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].name, name) == 0) {
            printf("Student ID: %d\n", students[i].id);
            printf("Name: %s\n", students[i].name);
            printf("Address: %s\n", students[i].address);
            printf("Father's Name: %s\n", students[i].fatherName);
            printf("Father's Phone: %s\n", students[i].fatherPhone);
            printf("Mother's Name: %s\n", students[i].motherName);
            printf("Mother's Phone: %s\n", students[i].motherPhone);
            printf("Student's Phone: %s\n", students[i].studentPhone);
            printf("CGPA: ");
            for (int j = 0; j < MAX_SEMESTERS; j++) {
                printf("Semester %d: %.2f ", j + 1, students[i].cgpa[j]);
            }
            printf("\n-------------------------\n");
            return;
        }
    }
    printf("Student not found!\n");
}

void searchStudentByAddress() {
    char address[100];
    printf("Enter Student Address to search: ");
    scanf(" %[^\n]", address);

    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].address, address) == 0) {
            printf("Student ID: %d\n", students[i].id);
            printf("Name: %s\n", students[i].name);
            printf("Address: %s\n", students[i].address);
            printf("Father's Name: %s\n", students[i].fatherName);
            printf("Father's Phone: %s\n", students[i].fatherPhone);
            printf("Mother's Name: %s\n", students[i].motherName);
            printf("Mother's Phone: %s\n", students[i].motherPhone);
            printf("Student's Phone: %s\n", students[i].studentPhone);
            printf("CGPA: ");
            for (int j = 0; j < MAX_SEMESTERS; j++) {
                printf("Semester %d: %.2f ", j + 1, students[i].cgpa[j]);
            }
            printf("\n-------------------------\n");
            return;
        }
    }
    printf("Student not found!\n");
}

void updateStudentInformation() {
    int id;
    printf("Enter Student ID to update: ");
    scanf("%d", &id);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            printf("Updating information for Student ID: %d\n", id);

            // Update student name
            char newName[50];
            printf("Enter new Student Name (or press enter to keep current): ");
            scanf(" %[^\n]", newName);
            if (strlen(newName) > 0 && !containsDigits(newName)) {
                strcpy(students[i].name, newName);
            } else if (containsDigits(newName)) {
                printf("Digits are not allowed. Please try again.\n");
            }

            // Update address
            char newAddress[100];
            printf("Enter new Address (or press enter to keep current): ");
            scanf(" %[^\n]", newAddress);
            if (strlen(newAddress) > 0) {
                strcpy(students[i].address, newAddress);
            }

            // Update student's phone number
            char newStudentPhone[12];
            printf("Enter new Student's Phone Number (11 digits, starts with 01) (or press enter to keep current): ");
            scanf("%s", newStudentPhone);
            if (strlen(newStudentPhone) > 0) {
                if (!isValidPhoneNumber(newStudentPhone)) {
                    printf("Invalid phone number. Please try again.\n");
                } else if (!isPhoneNumberUnique(newStudentPhone) ||
                           strcmp(newStudentPhone, students[i].fatherPhone) == 0 ||
                           strcmp(newStudentPhone, students[i].motherPhone) == 0) {
                    printf("This phone number already exists or matches the father's or mother's phone number. Please enter a different number.\n");
                } else {
                    strcpy(students[i].studentPhone, newStudentPhone);
                }
            }

            // Update father's name
            char newFatherName[50];
            printf("Enter new Father's Name (or press enter to keep current): ");
            scanf(" %[^\n]", newFatherName);
            if (strlen(newFatherName) > 0 && !containsDigits(newFatherName)) {
                strcpy(students[i].fatherName, newFatherName);
            } else if (containsDigits(newFatherName)) {
                printf("Digits are not allowed. Please try again.\n");
            }

            // Update mother's name
            char newMotherName[50];
            printf("Enter new Mother's Name (or press enter to keep current): ");
            scanf(" %[^\n]", newMotherName);
            if (strlen(newMotherName) > 0 && !containsDigits(newMotherName)) {
                strcpy(students[i].motherName, newMotherName);
            } else if (containsDigits(newMotherName)) {
                printf("Digits are not allowed. Please try again.\n");
            }

            printf("Student information updated successfully!\n");
            return;
        }
    }
    printf("Student not found!\n");
}

int main() {
    int choice;
    do {
        printf("Student Management System\n");
        printf("1. Insert Student\n");
        printf("2. Search Student by ID\n");
        printf("3. Search Student by Name\n");
        printf("4. Search Student by Address\n");
        printf("5. Update Student Information\n");
        printf("6. Add Semester CGPA\n");
        printf("7. Print All Students\n");
        printf("8. Delete Student\n");
        printf("9. Exit\n");
        printf("-------------------------\n");

        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Alphabets are not allowed. Please try again.\n");
            while (getchar() != '\n'); // Clear the input buffer
            continue;
        }

        switch (choice) {
            case 1: insertStudent(); break;
            case 2: searchStudentById(); break;
            case 3: searchStudentByName(); break;
            case 4: searchStudentByAddress(); break;
            case 5: updateStudentInformation(); break;
            case 6: addSemesterCGPA(); break;
            case 7: printAllStudents(); break;
            case 8: deleteStudent(); break;
            case 9: printf("Exiting...\n"); break;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 9);

    return 0;
}