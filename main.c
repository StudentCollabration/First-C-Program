#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENT_NUM 100

struct student {
    char name[20];
    int age;
    char gender[10];
    char id[20];
    char phone[20];
    char email[30];
    int reward;
    int punishment;
};

struct student students[MAX_STUDENT_NUM];
int student_num = 0;

void add_student() {
    if (student_num >= MAX_STUDENT_NUM) {
        printf("Error: student list is full.\n");
        return;
    }
    struct student s;
    printf("Please input student name: ");
    scanf("%s", s.name);
    printf("Please input student age: ");
    scanf("%d", &s.age);
    printf("Please input student gender: ");
    scanf("%s", s.gender);
    printf("Please input student id: ");
    scanf("%s", s.id);
    printf("Please input student phone: ");
    scanf("%s", s.phone);
    printf("Please input student email: ");
    scanf("%s", s.email);
    s.reward = 0;
    s.punishment = 0;
    students[student_num++] = s;
    printf("Add student successfully.\n");
}

void delete_student() {
    char id[20];
    printf("Please input student id: ");
    scanf("%s", id);
    int i;
    for (i = 0; i < student_num; i++) {
        if (strcmp(students[i].id, id) == 0) {
            break;
        }
    }
    if (i == student_num) {
        printf("Error: student not found.\n");
        return;
    }
    for (; i < student_num - 1; i++) {
        students[i] = students[i + 1];
    }
    student_num--;
    printf("Delete student successfully.\n");
}

void modify_student() {
    char id[20];
    printf("Please input student id: ");
    scanf("%s", id);
    int i;
    for (i = 0; i < student_num; i++) {
        if (strcmp(students[i].id, id) == 0) {
            break;
        }
    }
    if (i == student_num) {
        printf("Error: student not found.\n");
        return;
    }
    struct student s;
    printf("Please input student name: ");
    scanf("%s", s.name);
    printf("Please input student age: ");
    scanf("%d", &s.age);
    printf("Please input student gender: ");
    scanf("%s", s.gender);
    printf("Please input student phone: ");
    scanf("%s", s.phone);
    printf("Please input student email: ");
    scanf("%s", s.email);
    students[i] = s;
    printf("Modify student successfully.\n");
}

void query_student() {
    char id[20];
    printf("Please input student id: ");
    scanf("%s", id);
    int i;
    for (i = 0; i < student_num; i++) {
        if (strcmp(students[i].id, id) == 0) {
            break;
        }
    }
    if (i == student_num) {
        printf("Error: student not found.\n");
        return;
    }
    struct student s = students[i];
    printf("Name: %s\n", s.name);
    printf("Age: %d\n", s.age);
    printf("Gender: %s\n", s.gender);
    printf("ID: %s\n", s.id);
    printf("Phone: %s\n", s.phone);
    printf("Email: %s\n", s.email);
    printf("Reward: %d\n", s.reward);
    printf("Punishment: %d\n", s.punishment);
}

void add_reward() {
    char id[20];
    printf("Please input student id: ");
    scanf("%s", id);
    int i;
    for (i = 0; i < student_num; i++) {
        if (strcmp(students[i].id, id) == 0) {
            break;
        }
    }
    if (i == student_num) {
        printf("Error: student not found.\n");
        return;
    }
    students[i].reward++;
    printf("Add reward successfully.\n");
}

void add_punishment() {
    char id[20];
    printf("Please input student id: ");
    scanf("%s", id);
    int i;
    for (i = 0; i < student_num; i++) {
        if (strcmp(students[i].id, id) == 0) {
            break;
        }
    }
    if (i == student_num) {
        printf("Error: student not found.\n");
        return;
    }
    students[i].punishment++;
    printf("Add punishment successfully.\n");
}

void print_menu() {
    printf("1. Add student\n");
    printf("2. Delete student\n");
    printf("3. Modify student\n");
    printf("4. Query student\n");
    printf("5. Add reward\n");
    printf("6. Add punishment\n");
    printf("0. Exit\n");
}

int main() {
    while (1) {
        print_menu();
        int choice;
        printf("Please input your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Error: invalid input.\n");
            // 清空输入缓冲区
            while (getchar() != '\n');
            continue;
        }
        switch (choice) {
            case 1:
                add_student();
                break;
            case 2:
                delete_student();
                break;
            case 3:
                modify_student();
                break;
            case 4:
                query_student();
                break;
            case 5:
                add_reward();
                break;
            case 6:
                add_punishment();
                break;
            case 0:
                return 0;
            default:
                printf("Error: invalid choice.\n");
                break;
        }
    }
}