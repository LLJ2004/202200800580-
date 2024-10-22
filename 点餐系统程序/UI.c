#pragma warning(disable : 6386) //����C6386�����ܻ�����������ѽ������ݷ�Χ�жϣ�����������
#include "Core.h"
#include "UI.h"
#include "IO.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <io.h>
extern struct SDU_Restaurant_Data SDU_Restaurant;

/*�����Ļ������*/
void clearScreenBuffer(void)
{
    char c;
    while ((c = getchar()) != EOF && c != '\n')
        ;
}

/*��¼�˵�����*/
void Loading_Menu(char* ID_input, char* password_input)
{
    printf("\t   �� �� �� �� �� \n\n");
    printf("\t   ( �� �� �� �� �� �� �� ��)\n\n");
    printf("\t   > ");
    fscanf_s(stdin, "%s", ID_input, USRID_LENGTH_MAX);
    printf("\n\n");
    printf("\t   �� �� �� �� �� \n\n");
    printf("\t   ( �� �� �� �� �� �� �� ��)\n\n");
    printf("\t   > ");

    /*��ʽ��������*/
    char ch;
    int idx = 0;
    while (1)
    {
        ch = _getch();
        if (ch == '\r')
            break;
        else if (ch == '\b' && idx > 0)
        {
            printf("\b \b");
            idx--;
        }
        else if (ch == '\b' && idx == 0)
            continue;
        else
        {
            password_input[idx++] = ch;
            printf("*");
        }
    }
    password_input[idx] = '\0';

    clearScreenBuffer();
}

/*��������Ƿ�ƥ��*/
int Check_ID_Passwd(char* ID_input, char* password_input, enum UserType* userType, int Choice)
{
    int st = 0;
    int flag = 0;
    if (Choice == 1)
    {
        st = Check_Admin(ID_input, password_input);
    }
    if (Choice == 2)
    {
        st = Check_Waiter(ID_input, password_input);
    }
    if (!st)
    {
        /*����򹤺Ų�ƥ��*/
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); //����ɫ
        printf("\n\n\n\t   �� �� �� �� �� �� �� !\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //�ָ���ɫ
        SDU_Restaurant_Sleep(1200);
        *userType = undefine;
        SDU_Restaurant.user = undefine;
    }
    else
    {
        /*�����빤�ž�ƥ��*/
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); //����ɫ
        printf("\n\n\n\t   �� ¼ �� �� !\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //�ָ���ɫ
        SDU_Restaurant_Sleep(1200);
        flag = 1;
    }
    system("cls");
    return flag;
}

/*�û�����ѡ��ҳ��*/
enum UserType SDU_Restaurant_Welcome(void)
{
    enum UserType userType = undefine;
    int Choice = 0;
    char ID_input[USRID_LENGTH_MAX + 1];
    char password_input[USRPAS_LENGTH_MAX + 1];
    system("cls");
    while (!(userType == admin || userType == waiter))
    {
        printf("\n\n\n");
        printf(" ############## �� ӭ ʹ �� ɽ �� �� �� ϵ ͳ #############\n\n\n");
        printf("\t\t   �� ѡ �� �� �� �� ��:\n\n\n");
        printf("\t\t    1) �� �� �� �� Ա.\n\n");
        printf("\t\t    2) �� �� �� �� Ա.\n\n\n");
        printf("\t�� �� �� �� �� �� �� �� �� Ӧ �� �� ��: [ ]\b\b");
        scanf_s("%d", &Choice);
        clearScreenBuffer();
        system("cls");
        if (Choice == 2)
        {
            printf("\n\n\n");
            printf(" -------- �� ӭ ʹ �� ɽ �� �� �� �� �� Ա ϵ ͳ ---------\n\n\n\n");
            Loading_Menu(ID_input, password_input);
            if (Check_ID_Passwd(ID_input, password_input, &userType, Choice))
            {
                userType = waiter;
                SDU_Restaurant.user = waiter;
            }
        }
        else if (Choice == 1)
        {
            printf("\n\n\n");
            printf(" -------- �� ӭ ʹ �� ɽ �� �� �� �� �� Ա ϵ ͳ ---------\n\n\n\n");
            Loading_Menu(ID_input, password_input);
            if (Check_ID_Passwd(ID_input, password_input, &userType, Choice))
            {
                userType = admin;
                SDU_Restaurant.user = admin;
            }
        }
    }
    return userType;
}

/*����Ա�˵�ҳ��*/
int Admin_Menu(void)
{
    system("cls");
    printf("\n\n\n");
    printf(" -------- �� ӭ ʹ �� ɽ �� �� �� �� �� Ա ϵ ͳ ---------\n\n\n");
    printf("\t\t    [1] �� λ �� Ϣ\n\n");
    printf("\t\t    [2] Ӫ ҵ �� ��\n\n");
    printf("\t\t    [3] �� �� �� Ʒ\n\n");
    printf("\t\t    [4] �� �� Ա ��\n\n");
    printf("\t\t    [5] �� �� V I P\n\n");
    printf("\t\t    [6] �� �� �� ��\n\n");
    printf("\t\t    [7] �� Ʒ �� ��\n\n");
    printf("\t\t    [8] �� �� �� ��\n\n");
    printf("\t\t    [0] �� �� �� ��\n\n");
    printf("\t Admin, �� ��!\n\n");
    printf("\t �� �� �� �� �� �� �� Ӧ �� ָ �� �� ��: [ ]\b\b");
    int Choice;
    scanf_s("%d", &Choice);
    clearScreenBuffer();
    return Choice;
}

/*����Ա�˵�ҳ��*/
int Waiter_Menu(void)
{

    system("cls");
    printf("\n\n\n");
    printf(" -------- �� ӭ ʹ �� ɽ �� �� �� �� �� Ա ϵ ͳ ---------\n\n\n");
    printf("\t\t    [1] �� λ Ԥ ��\n\n");
    printf("\t\t    [2] չ ʾ �� Ʒ\n\n");
    printf("\t\t    [3] �� �� �� ��\n\n");
    printf("\t\t    [4] �� �� �� ��\n\n");
    printf("\t\t    [5] ȡ �� Ԥ ��\n\n");
    printf("\t\t    [6] �� �� �� ��\n\n");
    printf("\t\t    [7] �� �� �� ��\n\n");
    printf("\t\t    [0] �� �� �� ��\n\n\n");
    printf("\t %s, �� ��!\n\n", SDU_Restaurant.waiter_Login->waiterNick);
    printf("\t �� �� �� �� Ӧ �� ָ �� �� ��: [ ]\b\b");
    int Choice;
    scanf_s("%d", &Choice);
    clearScreenBuffer();
    return Choice;
}

/*չʾ�˵�����*/
void Waiter_Food_Show(void)
{
    while (1)
    {
        system("cls");
        printf("\n\n\n");
        printf(" -------- �� ӭ ʹ �� ɽ �� �� �� �� �� Ա ϵ ͳ ---------\n\n\n");
        printf("    �� ��\t\t��   ��\t\t\t �� ��\n");
        printf(" ==========================================================\n\n");
        Print_LinkTable_F(SDU_Restaurant.current_foods);
        printf("\n ==========================================================\n\n");
        printf("  �� �� 0 �� �� �� һ �� �� ��...\n\n");
        int Choi = 1;
        scanf_s("%d", &Choi);
        if (!Choi)
            break;
    }
    system("cls");
}

/*��ʾ���˽���*/
double Check_VIP(void)
{
    while (1)
    {
        system("cls");
        printf("\n\n\n");
        printf(" -------- �� ӭ ʹ �� ɽ �� �� �� �� �� Ա ϵ ͳ ---------\n\n\n");
        double discount = 1;
        printf("\n\t   �� �� �� �� δ �� �� Ŷ ~\n\n\t   �� �� �� �� �� �� VIP ?  ( y / n )\n\n");
        printf("\t   > ");
        char GETCHAR = getchar();
        clearScreenBuffer();
        if (GETCHAR == 'y' || GETCHAR == 'Y')
        {
            long long int phonenumber;
            printf("\n\n\t   �� �� �� �� �� ��\n\n");
            printf("\t   > ");
            scanf_s("%lld", &phonenumber);
            clearScreenBuffer();
            discount = Judge_VIP(phonenumber) ? 0.9 : 1;
            if (Judge_VIP(phonenumber))
            {
                discount = 0.9;
                return discount;
            }
            else
            {
                printf("\n\n\t   �� �� �� �� �� VIP���� �� �� �� ��\n\n");
                SDU_Restaurant_Sleep(1000);
            }
        }
        else if (GETCHAR == 'n' || GETCHAR == 'N')
        {
            return discount;
        }
        else
        {
            printf("\n\n\t   �� �� �� �� ȷ ѡ ��\n\n");
            SDU_Restaurant_Sleep(1000);
        }
    }
}
void Waiter_Food_Check(void)
{
    while (1)
    {
        system("cls");
        printf("\n\n\n");
        printf(" -------- �� ӭ ʹ �� ɽ �� �� �� �� �� Ա ϵ ͳ ---------\n\n\n");
        printf("\t   �� �� �� �� �� �� �� \n\n");
        printf("\t   ( �� �� 0 �� �� ��  һ  �� �� ��)\n\n");
        printf("\t   > ");
        int seat;
        int col, row;
        scanf_s("%d", &seat);
        if (seat == 0)
            break;
        col = (seat - 1) % SEATINFO_WIDTH;
        row = (seat - col) / SEATINFO_WIDTH;
        clearScreenBuffer();
        if (0 == SDU_Restaurant.seatsMap[row][col].isSeated)
        {
            printf("  �� �� �� δ �� ��");
            SDU_Restaurant_Sleep(1000);
            return;
        }
        NODE_C* pr = SDU_Restaurant.current_customer;
        for (; pr != NULL; pr = pr->next)
        {
            if (seat == pr->data.Seatnum)
                break;
        }
        if (pr == NULL)
        {
            printf("\t�� �� λ �� �� �� �ͣ�\n\n");
            SDU_Restaurant_Sleep(1200);
            system("cls");
        }
        else
        {
            if (pr->data.order.isDiscount == 0) {
                double discount = Check_VIP();
                pr->data.order.ExpensesToBePaid = discount * pr->data.order.ExpensesToBePaid;
                if (discount == 0.9)
                    pr->data.order.isDiscount = 1;
            }
            Save_Customer_Inform();
            while (1)
            {
                system("cls");
                printf("\n\n\n");
                printf(" -------- �� ӭ ʹ �� ɽ �� �� �� �� �� Ա ϵ ͳ ---------\n\n\n");
                printf("\t�� �� �� �ݣ�");
                if (pr->data.order.isDiscount == 0) {
                    printf("\t�� V I P �� ��\n\n");
                }
                else if (pr->data.order.isDiscount == 1) {
                    printf("\tV I P �� ��\n\n");
                }
                printf("\n\n\t�� �� �� �� �� Ϊ��");
                printf("\t%.2fԪ\n", pr->data.order.ExpensesToBePaid);

                printf(" ==========================================================\n\n");
                printf("\t�� �� �� �� �� �� �� ( �� λ ��Ԫ )(�� �� 0 �� ��)\n\n\t>  ");
                double temp = pr->data.order.ExpensesToBePaid;
                double paid = 0;
                scanf_s("%lf", &paid);
                clearScreenBuffer();
                pr->data.order.ExpensesToBePaid -= paid; //��Ǯ

                if (paid - 0 < 0.00001)
                    break;
                if (pr->data.order.ExpensesToBePaid - 0 > 0.000001)
                {
                    printf("\n\t�� �� �� ������ �� �� �� ֧ �� %.2f Ԫ��\n\n", pr->data.order.ExpensesToBePaid);
                    SDU_Restaurant_Sleep(1000);
                    SDU_Restaurant.Day_Profit += paid;
                    SDU_Restaurant.current_date->data.profit = SDU_Restaurant.Day_Profit;
                    Save_Date_Inform();
                }

                else if (pr->data.order.ExpensesToBePaid - 0 <= 0.000001)
                {
                    if (pr->data.order.ExpensesToBePaid - 0 < 0.000001)
                        printf("\n\t�� �� �� ������ �� �� %.2f Ԫ��\n\n", -pr->data.order.ExpensesToBePaid);
                    else if (pr->data.order.ExpensesToBePaid - 0 == 0.000001)
                        printf("\n\t�� �� �� ����\n\n");
                    SDU_Restaurant_Sleep(1000);
                    pr->data.order.isDiscount = 0;
                    pr->data.order.ExpensesToBePaid = 0;
                    SDU_Restaurant.seatsMap[row][col].isSeated = 0;
                    SDU_Restaurant.Day_Profit += temp;
                    SDU_Restaurant.current_date->data.profit = SDU_Restaurant.Day_Profit;
                    Save_Date_Inform();
                    SDU_Restaurant.waiter_Login->profit += temp;
                    Save_Waiter_Inform();
                    Leave_Seat(seat);
                    SDU_Restaurant.current_customer = SDU_Delete_Customer(SDU_Restaurant.current_customer, seat);
                    Save_Customer_Inform();
                    Write_SeatMap_Inform((struct Seat*)&SDU_Restaurant.seatsMap);
                    printf(" ==========================================================\n\n");
                    printf(" �� Enter �� �� �� �� һ �� �� ��...");
                    char GET_CHAR = getchar();
                    break;
                }
            }
        }
    }
}

/*����Ա���Ĳ�Ʒ��Ϣ*/
void Admin_Food_Change(void)
{
    while (1)
    {
        system("cls");
        printf("\n\n\n");
        printf(" -------- �� ӭ ʹ �� ɽ �� �� �� �� �� Ա ϵ ͳ ---------\n\n\n");
        printf("    �� ��\t\t��   ��\t\t\t �� ��\n");
        printf(" ==========================================================\n\n");
        Print_LinkTable_F(SDU_Restaurant.current_foods);
        printf("\n ==========================================================\n\n");
        printf("  \"add [�� Ʒ ��] [�� ��] \" �� �� �� Ʒ\n\n");
        printf("  \"del [�� ��]\" ɾ �� �� Ʒ\n\n");
        printf("  \"quit\" �� �� �� һ �� �� ��\n\n");
        printf("   $ admin > ");
        char cmd[30] = { 0 };
        scanf_s("%s", cmd, sizeof(cmd));
        if (strcmp(cmd, "add") == 0)
        {
            //������Ʒ��Ϣ
            struct food newFood;
            scanf_s(" %s", newFood.name, sizeof(newFood.name));
            scanf_s(" %lf", &newFood.price);

            newFood.orderCount = 0;

            struct _finddata_t File;

            //���²�Ʒ����
            SDU_Add_Food(SDU_Restaurant.current_foods, newFood);

            //�洢���ļ�
            Save_Food_Inform();
            clearScreenBuffer(); //��add ��������������ȥ
        }
        else if (strcmp(cmd, "del") == 0)
        {
            if (!(0 == SDU_Restaurant.foodsCount)) //�жϲ�Ʒ���Ƿ�Ϊ��
            {
                int id;
                scanf_s(" %d", &id);
                SDU_Restaurant.current_foods = SDU_Delete_Food(SDU_Restaurant.current_foods, id);
                Save_Food_Inform();
            }
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); //����ɫ
                printf("\n  �� Ʒ �� Ϊ �գ��� �� �� �� ɾ ����");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //�ָ���ɫ
                SDU_Restaurant_Sleep(1000);
            }
            Order_By_ID_F(SDU_Restaurant.current_foods);
            clearScreenBuffer(); //��del ��������������ȥ
        }
        else if (strcmp(cmd, "quit") == 0)
            break;
        else
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); //����ɫ
            printf("\n  �� �� �� �� �� �� �� ʽ �� ��");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //��ɫ
            SDU_Restaurant_Sleep(500);
        }
    }
    clearScreenBuffer();
    system("cls");
}

/*����Ա���ķ���Ա��Ϣ*/
void Admin_Waiter_Change(void)
{
    while (1)
    {
        system("cls");
        printf("\n\n\n");
        printf(" -------- �� ӭ ʹ �� ɽ �� �� �� �� �� Ա ϵ ͳ ---------\n\n\n");
        printf("     �� ��\t\t ��  ��\t\t\t ӯ ��\n");
        printf(" ==========================================================\n\n");
        Print_LinkTable_W(SDU_Restaurant.current_waiters);
        printf(" ==========================================================\n\n");
        printf("  �� �� \"add [�� ��] [�� ��] \" �� �� Ա �� \n\n");
        printf("  �� ʼ �� �� ��  Ϊ 123456���� ʼ �� ӯ �� Ϊ 0 \n\n  ");
        printf("  �� �� \"del [�� ��]\" ɾ �� Ա ��\n\n");
        printf("  �� �� \"quit\" �� �� �� һ �� �� ��\n\n");
        printf("   $ admin > ");
        char cmd[30] = { 0 };
        scanf_s("%s", cmd, sizeof(cmd));
        if (strcmp(cmd, "add") == 0)
        {
            //��������Ա��Ϣ
            struct Waiter newWaiter;
            scanf_s(" %s", newWaiter.id, sizeof(newWaiter.id));
            scanf_s(" %s", newWaiter.waiterNick, sizeof(newWaiter.waiterNick));
            strcpy_s(newWaiter.passwd, sizeof(newWaiter.passwd), "123456"); //�����ʼ��
            newWaiter.profit = 0;

            //���²�Ʒ����
            SDU_Add_Waiter(SDU_Restaurant.current_waiters, newWaiter);

            //�洢���ļ�
            Save_Waiter_Inform();
            clearScreenBuffer(); //��add ��������������ȥ
        }
        else if (strcmp(cmd, "del") == 0)
        {
            if (!(0 == SDU_Restaurant.waitersCount)) //�жϷ���Ա���Ƿ�Ϊ��
            {
                char id[WAITERID_LENGTH_MAX];
                scanf_s(" %s", id, sizeof(id));
                SDU_Restaurant.current_waiters = SDU_Delete_Waiter(SDU_Restaurant.current_waiters, id);
                Save_Waiter_Inform();
            }
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); //����ɫ
                printf("\n  �� �� Ա �� �� Ϊ �գ��� �� �� �� ɾ ����");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //�ָ���ɫ
                SDU_Restaurant_Sleep(1000);
            }
            Order_By_ID_W(SDU_Restaurant.current_waiters);
            clearScreenBuffer(); //��del ��������������ȥ
        }
        else if (strcmp(cmd, "chek") == 0)
        {
            //IMAGE picture;
            NODE_W* pr = NULL;
            char id[WAITERID_LENGTH_MAX];
            scanf_s(" %s", id, sizeof(id));
            clearScreenBuffer();
            if (pr == NULL)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); //����ɫ
                printf("\n  �� �� �� Ա �� �� �ţ�");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //�ָ���ɫ
                SDU_Restaurant_Sleep(1200);
            }
        }
        else if (strcmp(cmd, "quit") == 0)
            break;
        else
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); //����ɫ
            printf("\n  �� �� �� �� �� �� �� ʽ �� ��");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //��ɫ
            SDU_Restaurant_Sleep(500);
        }
    }
    clearScreenBuffer();
    system("cls");
}

/*����Ա����VIP��Ϣ*/
void Admin_VIP_Change(void)
{
    while (1)
    {
        system("cls");
        printf("\n\n\n");
        printf(" -------- �� ӭ ʹ �� ɽ �� �� �� �� �� Ա ϵ ͳ ---------\n\n\n");
        printf("     \t�� ��\t\t�� ��\t\t  \n");
        printf(" ==========================================================\n\n");
        Print_LinkTable_V(SDU_Restaurant.current_vip);
        printf(" ==========================================================\n\n");
        printf("  �� �� \"add [�� ��] [�� ��] \" �� �� VIP �� �ͣ�\n\n");
        // printf("  �� ʼ �� �� ��  Ϊ 123456���� ʼ �� ӯ �� Ϊ 0  \n\n  �� �� �� ͼ Ƭ �� �� �� �� \"EMPTY_ADRESS\"\n\n");
        printf("  �� �� \"del [�� ��]\" ɾ �� VIP\n\n");
        printf("  �� �� \"quit\" �� �� �� һ �� �� ��\n\n");
        printf("   $ admin > ");
        char cmd[30] = { 0 };
        scanf_s("%s", cmd, sizeof(cmd));
        if (strcmp(cmd, "add") == 0)
        {
            //����VIP��Ϣ
            struct VIP newVIP;
            scanf_s(" %d", &newVIP.cardnum);
            scanf_s(" %lld", &newVIP.phonenum);

            //����VIP����
            SDU_Add_VIP(SDU_Restaurant.current_vip, newVIP);

            //�洢���ļ�
            Save_VIP_Inform();
            clearScreenBuffer(); //��add ��������������ȥ
        }
        else if (strcmp(cmd, "del") == 0)
        {
            if (!(0 == SDU_Restaurant.vipsCount)) //�ж� VIP���Ƿ�Ϊ��
            {
                int cardnum;
                scanf_s(" %d", &cardnum);
                SDU_Restaurant.current_vip = SDU_Delete_VIP(SDU_Restaurant.current_vip, cardnum);
                Save_VIP_Inform();
            }
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); //����ɫ
                printf("\n  VIP �� �� Ϊ �գ��� �� �� �� ɾ ����");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //�ָ���ɫ
                SDU_Restaurant_Sleep(1000);
            }
            //Order_By_ID(SDU_Restaurant.current_vip);
            clearScreenBuffer(); //��del ��������������ȥ
        }
        else if (strcmp(cmd, "quit") == 0)
            break;
        else
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); //����ɫ
            printf("\n  �� �� �� �� �� �� �� ʽ �� ��");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //��ɫ
            SDU_Restaurant_Sleep(500);
        }
    }
    clearScreenBuffer();
    system("cls");
}

/*�˳��������*/
void Show_Exit_Program(void)
{
    system("cls");
    printf("\n\n\n\n\n\n");
    printf("\t         �� л �� �� ʹ �ã��� �� ��            \n\n\n\n\n");
    SDU_Restaurant_Sleep(1000);
    exit(EXIT_FAILURE);
}

/*Ԥ����λҳ��*/
void Waiter_Seat_Select(void)
{
    int row, col, num;
    while (1)
    {
        system("cls");
        printf("\n\n\n");
        printf(" -------- �� ӭ ʹ �� ɽ �� �� �� �� �� Ա ϵ ͳ ---------\n\n");
        printf("    �� �� �� �� ʵ ʱ �� λ ͼ��\n");
        printSeatsMap();
        printf("    \"*\" ���� ʾ �� Ԥ Լ �� �� ��\n    \"@\" ���� ʾ �� �� �� �� �� �� ��\n");
        printf("    �� �� �� �� �� [�� �� ��] �� ѡ �� һ �� �� λ\n    �� �� 0 �� �� �� һ �� �� ��...\n\n");
        printf("    �� Ҫ ѡ �� λ ��: ");
        scanf_s("%d", &num);
        col = (num - 1) % SEATINFO_WIDTH;
        row = (num - col) / SEATINFO_WIDTH;
        if (num == 0)
            break;
        if ((col < 0 || col >= SEATINFO_WIDTH) || (row < 0 || row >= SEATINFO_HEIGHT))
        {
            printf("\n   �� �� λ �� �� �� ��~\n");
            SDU_Restaurant_Sleep(1000);
            continue;
        }
        //�ж���λ�Ƿ��ѡ��
        if (Check_Selected(num))
        {
            printf("\n   �� �� λ �� �� �� �� ռ ��~\n");
            SDU_Restaurant_Sleep(1000);
            continue;
        }
        else if (Check_Seated(num))
        {
            printf("\n   �� �� λ �� �� �� �� �� ��~\n");
            SDU_Restaurant_Sleep(1000);
            continue;
        }

        clearScreenBuffer();
        printf("    �� ѡ �� �� �� %d �� �� %d �� �� �� λ���� �� Ϊ %d\n", row + 1, col + 1, num);

        struct Customer newcustomer;
        newcustomer.Seatnum = num;              //�¹˿͵���λ
        newcustomer.order.ExpensesToBePaid = 0; //��ʼ���¹˿͵Ķ���
        newcustomer.order.foodCount = 0;
        strcpy_s(newcustomer.address, sizeof(newcustomer.address), EMPTY_ADDRESS); // ���ƿյ�ַ��Ϣ�� newcustomer.address
        SDU_Add_Customer(SDU_Restaurant.current_customer, newcustomer);
        Save_Customer_Inform();

        SDU_Restaurant.seatsMap[row][col].isSelected = 1; //ѡ���������λ
        SDU_Restaurant.seatsMap[row][col].isSeated = 0;   //ѡ���������λ
        Write_SeatMap_Inform((struct Seat*)&SDU_Restaurant.seatsMap);
        SDU_Restaurant_Sleep(1000);
    }
    system("cls");
}

/*�ǼǶ�������*/
void Waiter_Food_Order(void)
{
    int num;
    int col, row;
    NODE_C* pr = SDU_Restaurant.current_customer;
    int quit = 0;
    while (1)
    {
        system("cls");
        printf("\n\n\n");
        printf(" -------- �� ӭ ʹ �� ɽ �� �� �� �� �� Ա ϵ ͳ ---------\n\n\n");
        printf("\t   �� �� �� �� �� �� �� \n\n");
        printf("\t   ( �� �� 0 �� �� ��  һ  �� �� ��)\n\n");
        printf("\t   > ");
        scanf_s("%d", &num);
        col = (num - 1) % SEATINFO_WIDTH;
        row = (num - col) / SEATINFO_WIDTH;
        clearScreenBuffer();
        if (!num)
        {
            quit = 1;
            break;
        }
        else
        {
            for (pr = SDU_Restaurant.current_customer; pr != NULL; pr = pr->next)
            {
                if (pr->data.Seatnum == num) {
                    pr->data.order.isDiscount = 0;
                    break;
                }
            }

            if (pr == NULL)
            {
                printf("�� �� �� �� �� �ͣ�");
                SDU_Restaurant_Sleep(1200);
            }
            else
                break;
        }
    }
    if (quit == 0)
        while (1)
        {
            system("cls");
            printf("\n\n\n");
            printf(" -------- �� ӭ ʹ �� ɽ �� �� �� �� �� Ա ϵ ͳ ---------\n\n");
            printf("    �� ��\t\t��   ��\t\t\t �� ��\n");
            printf(" ==========================================================\n");
            Print_LinkTable_F(SDU_Restaurant.current_foods);
            printf(" ==========================================================\n\n");

            int i;
            if (!(pr->data.order.foodCount == 0))
            {

                printf("\t\t      �� �� �� ��\n\n");
                printf("    �� ��\t\t��   ��\t\t\t �� ��\n");
                printf(" ==========================================================\n");

                for (i = 0; i < pr->data.order.foodCount; i++)
                    printf("      %02d\t\t  %-15s\t %3.2lf Ԫ\n", pr->data.order.foods[i].id, pr->data.order.foods[i].name, pr->data.order.foods[i].price);
                printf(" ==========================================================\n");
                printf("    �� �� Ʒ ��: %2d\t\t Ӧ ֧ �� �� ��: %3.2f Ԫ\n\n", pr->data.order.foodCount, pr->data.order.ExpensesToBePaid);
            }

            printf("    �� �� �� �� Ʒ �� �� Ӧ �� �� �� �� �� �� �ͣ� \n\n    �� �� 0 �� �� �� һ �� �� ��...\n\n");
            static int addResult = -1; //��ֵ������0
            if (!addResult)            //�����һ������˷Ƿ�foodID������һ�����ʧ�ܣ����������ʾ
            {
                printf("    �� �� �� �� �� �� �� ���� �� �� �� ȷ �� �� Ʒ �� ��.\n");
            }
            int foodID;
            printf("    �� �� �� �� Ʒ �� ��: [ ]\b\b");
            addResult = scanf_s("%d", &foodID);//��ֹ���������
            clearScreenBuffer();
            system("cls");
            if (foodID == 0)
            {
                break;
            }
            else if (foodID > 0 && addResult)
            {
                addResult = Add_Food_To_Order(foodID, &pr->data.order, pr->data.order.isDiscount == 1 ? 0.9 : 1);
            }

            else if (addResult)
            {
                addResult = Delet_Food_From_Order(-foodID, &pr->data.order, pr->data.order.isDiscount == 1 ? 0.9 : 1);
            }
            Save_Customer_Inform();
        }
    if (pr != NULL && pr->data.order.foodCount)
    {
        SDU_Restaurant.seatsMap[row][col].isSelected = 0;
        SDU_Restaurant.seatsMap[row][col].isSeated = 1;
        Write_SeatMap_Inform((struct Seat*)&SDU_Restaurant.seatsMap);
    }
}

/*��ӡÿ��Ӫҵ��*/
void Print_Daily_Profit(NODE_D* pHead_d)
{
    NODE_D* pr = NULL;
    if (0 == SDU_Restaurant.dateCount)
        return;
    for (pr = pHead_d; !(pr == NULL); pr = pr->next)
        printf("       \t%04d / %02d / %02d\t\t      %10.2f Ԫ\n", pr->data.year, pr->data.month, pr->data.day, pr->data.profit);
}

/*չʾ��ǰ��λ���*/
void printSeatsMap()
{
    int row, col;
    printf("   ");
    printf("\n");
    for (row = 0; row < SEATINFO_HEIGHT; row++)
    {
        printf("   ");
        for (col = 0; col < SEATINFO_WIDTH; col++)
        {
            char ch;
            if (SDU_Restaurant.seatsMap[row][col].isSeated)
            {
                ch = '@';
            }
            else if (SDU_Restaurant.seatsMap[row][col].isSelected)
            {
                ch = '*';
            }
            else
            {
                ch = ' ';
            }
            printf(" %02d[%c]", row * SEATINFO_WIDTH + col + 1, ch);
        }
        printf("\n\n");
    }
}

/*����Ա�鿴Ӫҵ�ܶ�*/
void Admin_Daily_Profit(void)
{
    system("cls");
    printf("\n\n\n");
    printf(" -------- �� ӭ ʹ �� ɽ �� �� �� �� �� Ա ϵ ͳ ---------\n\n");
    printf("\t    �� ��\t\t\t �� ��\n");
    printf(" ==========================================================\n\n");
    Print_Daily_Profit(SDU_Restaurant.current_date);
    printf("\n ==========================================================\n");

    system("pause");
}

/*����Աչʾ��λ���*/
void Admin_Seat_Infom(void)
{
    system("cls");
    printf("\n\n\n");
    printf(" -------- �� ӭ ʹ �� ɽ �� �� �� �� �� Ա ϵ ͳ ---------\n\n");
    printf("    �� �� �� �� ʵ ʱ �� λ ͼ��\n");
    printSeatsMap();

    int customer_count = 0;
    for (int i = 0; i < SEATINFO_HEIGHT; i++)
        for (int j = 0; j < SEATINFO_WIDTH; j++)
            if (SDU_Restaurant.seatsMap[i][j].isSelected || SDU_Restaurant.seatsMap[i][j].isSeated)
                customer_count++;

    printf("============================================================\n");
    printf("     * �� ʾ �� λ �� ��\n\n");
    printf("    �� ǰ �� �� �� �� �� %d �� �� ��\n", customer_count);
    printf("============================================================\n\n");
    printf("    �� Enter �� �� �� һ �� �� �� �� ��...");
    char GETCHAR = getchar();
    system("cls");
}
void Admin_Statistics_Analysis(void)
{
    system("cls");
    printf("\n\n\n");
    printf(" -------- �� ӭ ʹ �� ɽ �� �� �� �� �� Ա ϵ ͳ ---------\n\n");
    printf("    �� ��\t  ��   ��\t   �� ��\t����\n");
    printf("============================================================\n");
    Show_LinkTable_F(SDU_Restaurant.current_foods);
    printf("============================================================\n");
    system("pause");
}

/*ȡ��Ԥ��*/
void Waiter_Seat_Cancel(void)

{
    while (1)
    {
        system("cls");
        printf("\n\n\n");
        printf(" -------- �� ӭ ʹ �� ɽ �� �� �� �� �� Ա ϵ ͳ ---------\n\n");
        printf("    �� �� �� �� ʵ ʱ �� λ ͼ��\n");
        printSeatsMap();
        printf("    �� �� �� �� �� [�� �� ��] �� ȡ �� һ �� �� λ �� Ԥ ��\n\n    �� �� 0 �� �� �� һ �� �� ��...\n\n");
        int row, col, num;
        printf("    �� Ҫ ȡ �� �� λ ��: ");
        scanf_s("%d", &num);
        col = (num - 1) % SEATINFO_WIDTH;
        row = (num - col) / SEATINFO_WIDTH;
        if (num == 0)
            break;

        //�ж���λ�Ƿ��ɾ��
        if (Check_Selected(num))
        {
            SDU_Restaurant.seatsMap[row][col].isSelected = 0;
            printf("    �� �� �� ȡ �� Ԥ �� �� �� %d �� �� %d �� �� �� λ\n", row + 1, col + 1);
            SDU_Restaurant.current_customer = SDU_Delete_Customer(SDU_Restaurant.current_customer, num);
            Save_Customer_Inform();
            Write_SeatMap_Inform((struct Seat*)&SDU_Restaurant.seatsMap);
            SDU_Restaurant_Sleep(1000);
        }
        else if (Check_Seated(num))
        {
            printf("    �� λ �� �� �� �� �ͣ��� �� ȡ �� Ԥ ��\n");
            SDU_Restaurant_Sleep(1000);
        }
        else if (!Check_Selected(num)) //û��ѡ������λ
        {
            printf("    �� λ �� �� δ Ԥ ������ �� ȡ ��\n");
            SDU_Restaurant_Sleep(1000);
        }
        else if (!(col >= 0 && col < SEATINFO_WIDTH) && (row >= 0 && row < SEATINFO_HEIGHT))
        {
            printf("    �� �� �� �� �� �ڣ��� �� ȡ ��\n");
            SDU_Restaurant_Sleep(1000);
        }
        Write_SeatMap_Inform((struct Seat*)&SDU_Restaurant.seatsMap);
        clearScreenBuffer();
    }
    system("cls");
}

/*����Ա�޸��˻�����*/
void Admin_Passwd_Change(void)
{
    system("cls");
    printf("\n\n\n");
    printf(" -------- �� ӭ ʹ �� ɽ �� �� �� �� �� Ա ϵ ͳ ---------\n\n\n");
    printf("\t   �� �� �� �� �� �� \n\n");
    printf("\t   ( �� �� �� �� �� �� �� ��)\n\n");
    printf("\t   > ");
    char oldpasswd[ADMINPAS_LENGTH_MAX];
    scanf_s("%s", oldpasswd, ADMINPAS_LENGTH_MAX);
    printf("\n\n");
    printf("\t   �� �� �� �� �� �� \n\n");
    printf("\t   ( �� �� �� �� �� �� �� ��)\n\n");
    printf("\t   > ");
    char newpasswd[ADMINPAS_LENGTH_MAX] = { 0 };
    scanf_s("%s", newpasswd, ADMINPAS_LENGTH_MAX);
    printf("\n\n");
    if (Check_Admin("admin", oldpasswd))
    {
        printf("\t   �� ȷ �� �� ��\n");
        printf("\t   ( �� �� �� �� �� �� �� ��)\n\n");
        printf("\t   > ");
        char newpasswd2[ADMINPAS_LENGTH_MAX] = { 0 };
        scanf_s("%s", newpasswd2, ADMINPAS_LENGTH_MAX);
        if (0 == strcmp(newpasswd, newpasswd2))
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); //����ɫ
            printf("\n\n\t   �� �� �� �� !");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //�ָ���ɫ
            SDU_Restaurant_Sleep(1200);
            Write_Admin_Inform("admin", newpasswd);
        }
        else
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); //����ɫ
            printf("\n\n\t   �� �� �� �� �� �� �� �� һ �� !");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //�ָ���ɫ
            SDU_Restaurant_Sleep(1000);
        }
    }
    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); //����ɫ
        printf("\n\n\t   �� �� �� �� �� !");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //�ָ���ɫ
        SDU_Restaurant_Sleep(1000);
    }
}

/*����Ա�޸��������*/
void Waiter_Passwd_Change(void)
{
    system("cls");
    printf("\n\n\n");
    printf(" -------- �� ӭ ʹ �� ɽ �� �� �� �� �� Ա ϵ ͳ ---------\n\n\n");
    printf("\t   �� �� �� �� �� �� \n\n");
    printf("\t   ( �� �� �� �� �� �� �� ��)\n\n");
    printf("\t   > ");
    char oldpasswd[WAITERPAS_LENGTH_MAX] = { 0 };
    scanf_s("%s", oldpasswd, WAITERPAS_LENGTH_MAX);
    printf("\n\n");
    printf("\t   �� �� �� �� �� �� \n\n");
    printf("\t   ( �� �� �� �� �� �� �� ��)\n\n");
    printf("\t   > ");
    char newpasswd[WAITERPAS_LENGTH_MAX] = { 0 };
    scanf_s("%s", newpasswd, WAITERPAS_LENGTH_MAX);
    printf("\n\n");
    if (0 == strcmp(oldpasswd, SDU_Restaurant.waiter_Login->passwd))
    {
        printf("\t   �� ȷ �� �� ��\n\n");
        printf("\t   ( �� �� �� �� �� �� �� ��)\n\n");
        printf("\t   > ");
        char newpasswd2[WAITERPAS_LENGTH_MAX] = { 0 };
        scanf_s("%s", newpasswd2, WAITERPAS_LENGTH_MAX);
        if (0 == strcmp(newpasswd, newpasswd2))
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); //����ɫ
            printf("\n\n\n\t   �� �� �� �� !");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //�ָ���ɫ
            SDU_Restaurant_Sleep(1200);
            const size_t passwd_size = sizeof(SDU_Restaurant.waiter_Login->passwd);
            if (strlen(newpasswd) < passwd_size) {
                strcpy_s(SDU_Restaurant.waiter_Login->passwd, passwd_size, newpasswd);
            }
            else {
                // ���������ַ������������
                printf("Error: Password string too long.\n");
            }
            Save_Waiter_Inform();
        }
        else
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); //����ɫ
            printf("\n\n\n\t   �� �� �� �� �� �� �� �� һ �� !");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //�ָ���ɫ
            SDU_Restaurant_Sleep(1000);
        }
    }
    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); //����ɫ
        printf("\n\n\n\t   �� �� �� �� �� !");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //�ָ���ɫ
        SDU_Restaurant_Sleep(1000);
    }
}
