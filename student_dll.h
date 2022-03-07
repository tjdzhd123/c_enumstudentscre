#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUBJECT_SU 5    //�����



typedef struct STUDENT{
    char name[20];
    int id;
    char gender[5];
    int java;
    int android;
    int kotlin;
    int react_native;
    int javascript;
    int total;
    double avr;
    char grade;

    struct STUDENT* prev; //struct STUDENT ����Ű�� �����ͺ���(�տ� �ִ� ����ü)
    struct STUDENT* next; //struct STUDENT ����Ű�� �����ͺ���(�ڿ� �ִ� ����ü)
}STUDENT_t;

STUDENT_t* head = NULL;     //���߿��Ḯ��Ʈ ���۳������
STUDENT_t* current = NULL;  //����ȭ�鿡 ǥ�õǴ� �������

char make_grade(double avr);
int check_id(int id);

//���� 1 head �����ϱ�
void initialize_student(){
    head = (STUDENT_t *)calloc(1,sizeof(STUDENT_t));
    if(head == NULL){
        puts("�������� STUDENT ����ü ���� ����");
        getchar();
    }
return;
}

//���� 2 ��� �߰��ϱ�(ó�� �߰��ϱ� , �������߰��ϱ�)
void append_node(STUDENT_t* data){
    STUDENT_t* p = head;

    //next NULL �� ������ ���� �̵�
    while(p->next != NULL){
        p = p->next;
    }
    p->next = data;

    //�߰��� node���� �ٷ� �� node ����Ŵ.
    if(p != head){
        data->prev = p;
    }
return;
}

//���� 3 ��� ����ϱ�
void print_student_data(){
    STUDENT_t* p = head;

    if(p == NULL){
        puts("����� ����Ÿ�� �����ϴ�.");
        return;
    }

    puts("=====================================================================");
    puts("�̸�\t�й�\t����\t\t����\t\t����\t���\t���");
    puts("=====================================================================");

    while(p->next != NULL){
        p = p->next;
        printf("%s\t%d\t%s\t%3d %3d %3d %3d %3d\t%3d\t%5.2lf\t%3c\n",
           p->name,p->id,p->gender,p->java,p->android,
           p->kotlin,p->react_native,p->javascript,p->total,
           p->avr,p->grade);
    }
return;
}

void print_one_student_data(STUDENT_t* current){
    if(current == NULL){
        puts("����� STUDENT ����ü �����ϴ�. ");
        getchar();
        return;
    }

    printf("%14s [%s] \n","�̸�",current->name);
    printf("%14s [%4d] \n","�й�",current->id);
    printf("%14s [%s] \n","����",current->gender);
    printf("%14s [%3d] \n","�ڹ�",current->java);
    printf("%14s [%3d] \n","�ȵ���̵�",current->android);
    printf("%14s [%3d] \n","��Ʋ��",current->kotlin);
    printf("%14s [%3d] \n","����Ʈ����Ƽ��",current->react_native);
    printf("%14s [%3d] \n","�ڹٽ�ũ��Ʈ",current->javascript);
    printf("%14s [%3d] \n","����",current->total);
    printf("%14s [%5.2lf] \n","���",current->avr);
    printf("%14s [%3c] \n","���",current->grade);
    puts("================================");

return;
}

STUDENT_t* new_student_data(){
    STUDENT_t* data = (STUDENT_t *)calloc(1,sizeof(STUDENT_t));
    int flag_id = 0;

    if(data == NULL){
        puts("�������� STUDENT ����ü �Է� ����");
        getchar();
        return NULL;
    }

    printf("%14s : ","�̸�");
    scanf_s("%s",data->name,sizeof(data->name));

    //id �ߺ� üũ ���
    while(!flag_id){
        printf("%14s : ","�й�(1000~9999)");
        scanf_s("%d",&data->id,sizeof(data->id));

        if(check_id(data->id) != 0){
            puts("���� �й��� �����մϴ�.");
            continue;
        }
        flag_id = 1;
    }

    printf("%14s :","����");
    scanf_s("%s",data->gender,sizeof(data->gender));
    data->java          = input_score("�ڹ�");
    data->android       = input_score("�ȵ���̵�");
    data->kotlin        = input_score("��Ʋ��");
    data->react_native  = input_score("����Ʈ����Ƽ��");
    data->javascript    = input_score("�ڹٽ�ũ��Ʈ");
    data->total = data->java + data->android + data->kotlin + data->react_native + data->javascript;
    data->avr = data->total / (double)SUBJECT_SU;
    data->grade = make_grade(data->avr);

return data;
}

void update_student_data(STUDENT_t* current){

    if(current == NULL){
        puts("������ STUDENT ����ü �������� �ʽ��ϴ�.");
        getchar();
        return;
    }

    current->java          = input_score("���� �ڹ�");
    current->android       = input_score("���� �ȵ���̵�");
    current->kotlin        = input_score("���� ��Ʋ��");
    current->react_native  = input_score("���� ����Ʈ����Ƽ��");
    current->javascript    = input_score("���� �ڹٽ�ũ��Ʈ");
    current->total = current->java + current->android + current->kotlin + current->react_native + current->javascript;
    current->avr = current->total / (double)SUBJECT_SU;
    current->grade = make_grade(current->avr);

return;
}

STUDENT_t* search_student_data(){
    STUDENT_t* p = head;
    STUDENT_t* data = NULL;
    int id = 0;

    printf(" �˻��� �л� id(1000~9999): ");
    scanf("%d",&id);

       //next NULL �� ������ ���� �̵�
    while(p->next != NULL){
        p = p->next;
        if(p->id == id){
            data = p;
            break;
        }
    }

    if(data == NULL){
        printf("�л� id[%4d] �� ���� id�Դϴ�. \n",id);
        getchar();
        getchar();
    }

return data;
}

void insert_student_data(STUDENT_t* data){
    //1:head->next null ó�� ��ġ ����
    if(head->next == NULL){
        head->next = data;
        return;
    }

    if(current->prev == NULL){            //3 ó����� ����
        data->next = head->next;
        data->next->prev = data;
        head->next = data;
    }else if(current->next == NULL){      //2.������ ��� ����
        data->prev = current;
        current->next = data;
    }else if(current->next != NULL && current->prev != NULL){  //4.�߰���� ����
        data->next = current->next;
        data->next->prev = data;
        current->next = data;
        data->prev = current;
    }else{
        puts("���Կ� ���� �߻��޽��ϴ�.");
        getchar();
        getchar();
    }

return;
}

void delete_student_data(){
  STUDENT_t* p = current;

  //current ��尡 �����Ǳ� ���� current �������, �������, NULL����
  if(current->next != NULL){
    current = current->next;
  }else if(current->next == NULL && current->prev != NULL){
    current = current->prev;
  }else{
    current = NULL;
  }

  if(p->next != NULL && p->prev == NULL){        //ó�����
    p->next->prev = NULL;
    head->next = p->next;
  }else if(p->next != NULL && p->prev != NULL){  //�߰����
    p->next->prev = p->prev;
    p->prev->next = p->next;
  }else if(p->next == NULL && p->prev != NULL){  //������ ���
    p->prev->next = NULL;
  }else{
    head->next = NULL;
  }

  free(p);
return;
}


int input_score(char *subject){
    int score = 0;
    int flag = 0;
    while(!flag){
        printf("%14s :",subject);
        scanf_s("%d",&score);
        if(score < 0 || score > 100){
            printf("%s ������(0~100) �Է��ϼ���.\n",subject);
            continue;
        }
        flag = 1;
    }//end of while

return score;
}

char make_grade(double avr){
    char grade = 0;

    if(avr >= 90.0){
        grade = 'A';
    }else if(avr >= 80.0){
        grade = 'B';
    }else if(avr >= 70.0){
        grade = 'C';
    }else if(avr >= 60.0){
        grade = 'D';
    }else{
        grade = 'F';
    }

return grade;
}

int check_id(int id){
    int find_id = 0;
    STUDENT_t* p = head;

    //next NULL �� ������ ���� �̵�
    while(p->next != NULL){
        p = p->next;
        if(p->id == id){
            find_id = p->id;
            break;
        }
    }

return find_id;
}

