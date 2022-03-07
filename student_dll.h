#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUBJECT_SU 5    //과목수



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

    struct STUDENT* prev; //struct STUDENT 가르키는 포인터변수(앞에 있는 구조체)
    struct STUDENT* next; //struct STUDENT 가르키느 포인터변수(뒤에 있는 구조체)
}STUDENT_t;

STUDENT_t* head = NULL;     //이중연결리스트 시작노드저장
STUDENT_t* current = NULL;  //현재화면에 표시되는 노드저장

char make_grade(double avr);
int check_id(int id);

//패턴 1 head 생성하기
void initialize_student(){
    head = (STUDENT_t *)calloc(1,sizeof(STUDENT_t));
    if(head == NULL){
        puts("힙영역에 STUDENT 구조체 생성 실패");
        getchar();
    }
return;
}

//패턴 2 노드 추가하기(처음 추가하기 , 마지막추가하기)
void append_node(STUDENT_t* data){
    STUDENT_t* p = head;

    //next NULL 인 마지막 노드로 이동
    while(p->next != NULL){
        p = p->next;
    }
    p->next = data;

    //추가된 node에서 바로 앞 node 가르킴.
    if(p != head){
        data->prev = p;
    }
return;
}

//패턴 3 노드 출력하기
void print_student_data(){
    STUDENT_t* p = head;

    if(p == NULL){
        puts("출력할 데이타가 없습니다.");
        return;
    }

    puts("=====================================================================");
    puts("이름\t학번\t성별\t\t성적\t\t총점\t평균\t등급");
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
        puts("출력할 STUDENT 구조체 없습니다. ");
        getchar();
        return;
    }

    printf("%14s [%s] \n","이름",current->name);
    printf("%14s [%4d] \n","학번",current->id);
    printf("%14s [%s] \n","성별",current->gender);
    printf("%14s [%3d] \n","자바",current->java);
    printf("%14s [%3d] \n","안드로이드",current->android);
    printf("%14s [%3d] \n","코틀린",current->kotlin);
    printf("%14s [%3d] \n","리액트네이티브",current->react_native);
    printf("%14s [%3d] \n","자바스크립트",current->javascript);
    printf("%14s [%3d] \n","총점",current->total);
    printf("%14s [%5.2lf] \n","평균",current->avr);
    printf("%14s [%3c] \n","등급",current->grade);
    puts("================================");

return;
}

STUDENT_t* new_student_data(){
    STUDENT_t* data = (STUDENT_t *)calloc(1,sizeof(STUDENT_t));
    int flag_id = 0;

    if(data == NULL){
        puts("힙영역에 STUDENT 구조체 입력 실패");
        getchar();
        return NULL;
    }

    printf("%14s : ","이름");
    scanf_s("%s",data->name,sizeof(data->name));

    //id 중복 체크 기능
    while(!flag_id){
        printf("%14s : ","학번(1000~9999)");
        scanf_s("%d",&data->id,sizeof(data->id));

        if(check_id(data->id) != 0){
            puts("기존 학번이 존재합니다.");
            continue;
        }
        flag_id = 1;
    }

    printf("%14s :","성별");
    scanf_s("%s",data->gender,sizeof(data->gender));
    data->java          = input_score("자바");
    data->android       = input_score("안드로이드");
    data->kotlin        = input_score("코틀린");
    data->react_native  = input_score("리액트네이티브");
    data->javascript    = input_score("자바스크립트");
    data->total = data->java + data->android + data->kotlin + data->react_native + data->javascript;
    data->avr = data->total / (double)SUBJECT_SU;
    data->grade = make_grade(data->avr);

return data;
}

void update_student_data(STUDENT_t* current){

    if(current == NULL){
        puts("수정할 STUDENT 구조체 존재하지 않습니다.");
        getchar();
        return;
    }

    current->java          = input_score("수정 자바");
    current->android       = input_score("수정 안드로이드");
    current->kotlin        = input_score("수정 코틀린");
    current->react_native  = input_score("수정 리액트네이티브");
    current->javascript    = input_score("수정 자바스크립트");
    current->total = current->java + current->android + current->kotlin + current->react_native + current->javascript;
    current->avr = current->total / (double)SUBJECT_SU;
    current->grade = make_grade(current->avr);

return;
}

STUDENT_t* search_student_data(){
    STUDENT_t* p = head;
    STUDENT_t* data = NULL;
    int id = 0;

    printf(" 검색할 학생 id(1000~9999): ");
    scanf("%d",&id);

       //next NULL 인 마지막 노드로 이동
    while(p->next != NULL){
        p = p->next;
        if(p->id == id){
            data = p;
            break;
        }
    }

    if(data == NULL){
        printf("학생 id[%4d] 는 없는 id입니다. \n",id);
        getchar();
        getchar();
    }

return data;
}

void insert_student_data(STUDENT_t* data){
    //1:head->next null 처음 위치 삽입
    if(head->next == NULL){
        head->next = data;
        return;
    }

    if(current->prev == NULL){            //3 처음노드 삽입
        data->next = head->next;
        data->next->prev = data;
        head->next = data;
    }else if(current->next == NULL){      //2.마지막 노드 삽입
        data->prev = current;
        current->next = data;
    }else if(current->next != NULL && current->prev != NULL){  //4.중간노드 삽입
        data->next = current->next;
        data->next->prev = data;
        current->next = data;
        data->prev = current;
    }else{
        puts("삽입에 문제 발생햇습니다.");
        getchar();
        getchar();
    }

return;
}

void delete_student_data(){
  STUDENT_t* p = current;

  //current 노드가 삭제되기 때문 current 이전노드, 다음노드, NULL변경
  if(current->next != NULL){
    current = current->next;
  }else if(current->next == NULL && current->prev != NULL){
    current = current->prev;
  }else{
    current = NULL;
  }

  if(p->next != NULL && p->prev == NULL){        //처음노드
    p->next->prev = NULL;
    head->next = p->next;
  }else if(p->next != NULL && p->prev != NULL){  //중간노드
    p->next->prev = p->prev;
    p->prev->next = p->next;
  }else if(p->next == NULL && p->prev != NULL){  //마지막 노드
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
            printf("%s 점수는(0~100) 입력하세요.\n",subject);
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

    //next NULL 인 마지막 노드로 이동
    while(p->next != NULL){
        p = p->next;
        if(p->id == id){
            find_id = p->id;
            break;
        }
    }

return find_id;
}

