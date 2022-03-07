//������ ��� : ������ �޴� ���� ���
enum MAIN_MENU {END, READ, PRINT, EDIT, WRITE};
enum MAIN_MENU main_select;

//������ ��� : �������� �� �޴� ���� ���
enum EDIT_MENU {EXIT, PREV, NEXT, INSERT, MODIFY, DELETE, SEARCH};
enum EDIT_MENU edit_select;

#include "student_dll.h"

void read_student_data();   //student_data.txt ������ �о����
void write_student_data();  //student_data.txt ������ �����ϱ�

char student_file_name[] = "student_data.txt";

int main()
{
    int flag = 0;
    initialize_student();   //���Ḯ��Ʈ head ����

    while(!flag && head != NULL){
        system("cls");
        puts("================================");
        puts("\t ���� ���� ���α׷� \t");
        puts("================================");
        puts("1.�������α׷� ���Ͽ��� ��������");
        puts("2.�������α׷� ��Ȳ����");
        puts("3.�������α׷� �����ϱ�");
        puts("4.�������α׷� ���Ͽ� �����ϱ�");
        puts("0.����");
        printf(">> ");
        scanf_s("%d",&main_select);
        getchar();

        switch(main_select){
            case READ:
                read_student_data();
                getchar();
                break;
            case PRINT:
                print_student_data();
                getchar();
                break;
            case EDIT:
                edit_student_data();
                break;
            case WRITE:
                write_student_data();
                getchar();
                break;
            case END:
                flag = 1;
                break;
            default:
                puts("�ٽü��� �ϼ���.~");
                getchar();
                break;
        }//end of switch

    }//end of while

    return 0;
}

void read_student_data(){
    STUDENT_t* data = NULL;
    FILE* file = NULL;
    int flag = 0;
    int count = 0;

    printf("�о�� �л� ���� �����̸� �Է� >> ");
    scanf_s("%s",student_file_name, sizeof(student_file_name));
    getchar();

    file = fopen(student_file_name, "rt");

    if(file == NULL){
        printf("%s ������ ���� ���߽��ϴ�. \n",student_file_name);
        return;
    }

    while(!flag){
        data = (STUDENT_t *)calloc(1,sizeof(STUDENT_t));
        int result = fscanf(file,"%s %d %s %d %d %d %d %d %d %lf %c",
               data->name,&data->id,data->gender,&data->java,&data->android,
               &data->kotlin,&data->react_native,&data->javascript,&data->total,
               &data->avr,&data->grade);

        if(result == EOF){
           flag = 1;
           continue;
        }

        append_node(data);  //���߿��Ḯ��Ʈ data ����ü �߰�����
        count++;

        printf("%s %d %s %d %d %d %d %d %d %5.2lf %c\n",
           data->name,data->id,data->gender,data->java,data->android,
           data->kotlin,data->react_native,data->javascript,data->total,
           data->avr,data->grade);
    }

    printf("%d ���� �����͸� �о����ϴ�. ",count);
    fclose(file);
    getchar();

    return;
}


void write_student_data(){
    STUDENT_t* p = head;
    FILE* file = NULL;
    int count = 0;

    file = fopen(student_file_name, "wt");

    if(file == NULL){
        printf("%s ������ �������� ���߽��ϴ�. \n",student_file_name);
        return;
    }

    while(p->next != NULL){
        p = p->next;
        int result = fprintf(file,"%s %d %s %d %d %d %d %d %d %lf %c\n",
               p->name,p->id,p->gender,p->java,p->android,
               p->kotlin,p->react_native,p->javascript,p->total,
               p->avr,p->grade);

        if(result == EOF){
            printf("%s ������ ���嵵�߿� ������ �߻��߽��ϴ�. ",student_file_name);
            break;
        }
        count++;
    }

    printf("%d ���� �����͸� �����߽��ϴ�. ",count);
    fclose(file);
    getchar();

return;
}

//��������,��������,�������,��������,��������,�����˻�
void edit_student_data(){
   STUDENT_t* data = NULL;
   current = head->next;     //���� ����Ÿ�� ����� �����ġ ����
   int flag = 0;

   while(!flag && head != NULL){
        system("cls");
        puts("================================");
        puts("\t ���� ���� \t");
        puts("================================");

        if(current != NULL){
            print_one_student_data(current);
        }

        puts("1.��������");
        puts("2.��������");
        puts("3.�������");
        puts("4.��������");
        puts("5.��������");
        puts("6.�����˻�");
        puts("0.���ư���");
        printf(">> ");
        scanf_s("%d",&edit_select);
        getchar();

        //������ node�� ���, ����, ����, ����, ����, �˻���� ���㰡
        //���, ���ư��� ��� �㰡
        if(current == NULL){
            switch(edit_select){
                case PREV:
                case NEXT:
                case MODIFY:
                case DELETE:
                case SEARCH:
                    continue;
            }
        }

        switch(edit_select){
            case PREV:
                if(current->prev != NULL){
                    current = current->prev;
                }
                break;
            case NEXT:
                if(current->next != NULL){
                    current = current->next;
                }
                break;
            case INSERT:
                data = new_student_data();
                //1,2,3,4 ���� ���� 1:head ����, 2:��������� ����, 3: ó����� ����, 4:�߰�������
                insert_student_data(data);
                getchar();
                break;
            case MODIFY:
                update_student_data(current);
                getchar();
                break;
            case DELETE:
                delete_student_data();
                break;
           case SEARCH:
                data = search_student_data();
                if(data != NULL){
                    current = data;
                }
                break;
           case EXIT:
                flag = 1;
                break;
            default:
                puts("�ٽü��� �ϼ���.~");
                getchar();
                break;
        }//end of switch

   }//end of while

return;
}
