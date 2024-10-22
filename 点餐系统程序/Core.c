#pragma warning(disable:6011)//����C6011��ȡ����NULLָ������ã�����Assert_Program(void* ptr)�н����ж�
#include "Core.h"
#include "IO.h"
#include "UI.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <windows.h>
#include <time.h>
extern struct SDU_Restaurant_Data SDU_Restaurant;

/*���������������������Ժ�������������������*/

/*�ж��쳣*/
void Assert_Program(void* ptr)
{
    if (ptr == NULL)
    {
        printf("���������� !�����˳�����...\n"); //ԭ������Ƕ��ڴ����ʧ�ܣ�ϵͳ�ڴ治�㵼��
        SDU_Restaurant_Sleep(1000);
        exit(EXIT_FAILURE);
    }
}

/*������ͣ*/
void SDU_Restaurant_Sleep(unsigned long dwMilliseconds)
{
    Sleep((DWORD)dwMilliseconds); //��<window.h>�� typedef unsigned long DWORD
}



/*VIP�ж�*/
int Judge_VIP(long long int phonenum)
{
    NODE_V* pr = SDU_Restaurant.current_vip;
    for (; pr != NULL; pr = pr->next)
    {
        if (pr->data.phonenum == phonenum) {
            return 1;
        }
    }
    return 0;
}

/*�����ж�*/
void Judge_Date(NODE_D* pHead_d)
{
    struct tm flag;
    time_t now;
    time(&now);
    localtime_s(&flag, &now);

    if (pHead_d == NULL)
    {
        /*���Ӫҵ��*/
        SDU_Restaurant.Day_Profit = 0;
        /*����ʱ��*/
        struct Date Current_Date;
        Current_Date.year = flag.tm_year + 1900;
        Current_Date.month = flag.tm_mon + 1;
        Current_Date.day = flag.tm_mday;
        Current_Date.profit = 0;

        SDU_Add_Date(pHead_d, Current_Date);
        Save_Date_Inform();

        return;
    }
    else if (!(flag.tm_year + 1900 == pHead_d->data.year && flag.tm_mday == pHead_d->data.day && flag.tm_mon + 1 == pHead_d->data.month)) //����ͬһ��
    {

        /*���Ӫҵ��*/
        SDU_Restaurant.Day_Profit = 0;
        /*����ʱ��*/
        struct Date Current_Date;
        Current_Date.year = flag.tm_year + 1900;
        Current_Date.month = flag.tm_mon + 1;
        Current_Date.day = flag.tm_mday;
        Current_Date.profit = 0;

        SDU_Add_Date(pHead_d, Current_Date);
        Save_Date_Inform();
    }
}

/*�����ʼ��*/
void SDU_Restaurant_Init(int argc, char const* argv[])
{

    Create_DataBaseFiles(); //��ʼ�������ļ�����ʷ���ݽ�������

    int num; // num��Ϊѭ�����ñ�����ÿ�δ��ļ���¼����ֵʱ��������Ϊ0�������ļ����ݽ��и���

    /*��ȡ��Ʒ����*/
    struct food* Read_foods;
    Read_Food_Inform(&Read_foods, &num);
    NODE_F* pHead_f = Load_Food_Inform(Read_foods, num);
    SDU_Restaurant.current_foods = pHead_f;
    SDU_Restaurant.foodsCount = num;

    /*��ȡ����Ա����*/
    struct Waiter* Read_waiters;
    Read_Waiter_Inform(&Read_waiters, &num);
    NODE_W* pHead_w = Load_Waiter_Inform(Read_waiters, num);
    SDU_Restaurant.current_waiters = pHead_w;
    SDU_Restaurant.waitersCount = num;
    SDU_Restaurant.waiter_Login = NULL;

    /*��ȡ�˿�����*/
    struct Customer* Read_customers;
    Read_Customer_Inform(&Read_customers, &num);
    NODE_C* pHead_c = Load_Customer_Inform(Read_customers, num);
    SDU_Restaurant.current_customer = pHead_c;
    SDU_Restaurant.customerCount = num;

    /*��ȡVIP����*/
    struct VIP* Read_vips;
    Read_VIP_Inform(&Read_vips, &num);
    NODE_V* pHead_v = Load_VIP_Inform(Read_vips, num);
    SDU_Restaurant.current_vip = pHead_v;
    SDU_Restaurant.vipsCount = num;

    /*��ȡ��������*/
    struct Date* Read_dates;
    Read_Date_Inform(&Read_dates, &num);
    NODE_D* pHead_d = Load_Profit_Inform(Read_dates, num);
    SDU_Restaurant.current_date = pHead_d;
    SDU_Restaurant.dateCount = num;
    if (SDU_Restaurant.current_date != NULL)
        SDU_Restaurant.Day_Profit = SDU_Restaurant.current_date->data.profit;
    Judge_Date(SDU_Restaurant.current_date); //�ж�ϵͳ���ڣ������Ƿ���յ���Ӫҵ��

    /*��ȡ��λ��Ϣ*/
    Read_SeatMap_Inform((struct Seat*)&SDU_Restaurant.seatsMap);

    /*��ʼ��current_user�ṹ��*/
    SDU_Restaurant.user = undefine;
}

/*�������������������������������������������*/

/*����β�巨����*/
/*����Ʒ������ӵ���Ʒ����β��*/
NODE_F* Add_To_Tail_F(NODE_F* pHead_f, struct food Data)
{
    /*�����µ�����ڵ�*/
    NODE_F* pNode = (NODE_F*)malloc(sizeof(NODE_F));
    Assert_Program(pNode);
    if (pNode != NULL) {
        pNode->data = Data;
        pNode->next = NULL;
    }
    /*��ԭ����Ϊ��*/
    if (pHead_f == NULL)
    {
        if (pNode != NULL) {
            pNode->next = pHead_f;
            pHead_f = pNode;
        }
    }

    /*��ԭ����ǿ�*/
    else
    {
        NODE_F* pr = NULL;
        pr = pHead_f;
        while (!(pr->next == NULL)) //����������β��
        {
            pr = pr->next;
        }
        pr->next = pNode; //����½�㵽����β��
    }
    return pHead_f;
}

/*������Ա������ӵ�����Ա����β��*/
NODE_W* Add_To_Tail_W(NODE_W* pHead_w, struct Waiter Data)
{
    /*�����µ�����ڵ�*/
    NODE_W* pNode = (NODE_W*)malloc(sizeof(NODE_W));
    Assert_Program(pNode);
    if (pNode != NULL)
    {
        pNode->data = Data;
        pNode->next = NULL;
    }
    /*��ԭ����Ϊ��*/
    if (pHead_w == NULL)
    {
        if (pNode != NULL) {
            pNode->next = pHead_w;
            pHead_w = pNode;
        }
    }

    /*��ԭ����ǿ�*/
    else
    {
        NODE_W* pr = NULL;
        pr = pHead_w;
        while (!(pr->next == NULL)) //����������β��
        {
            pr = pr->next;
        }
        pr->next = pNode; //����½�㵽����β��
    }
    return pHead_w;
}

/*����ͷ�巨����*/
/*����Ʒ������ӵ���Ʒ����ͷ��*/
NODE_F* Add_To_Head_F(NODE_F* pHead_f, struct food data)
{
    /*�����µ�����ڵ�*/
    NODE_F* pNode = (NODE_F*)malloc(sizeof(NODE_F));
    Assert_Program(pNode);
    if (pNode != NULL)
    {
        pNode->data = data;
        pNode->next = NULL;
        pNode->next = pHead_f; //����½�㵽����ͷ��
        pHead_f = pNode;
    }
    return pHead_f;
}

/*������Ա������ӵ�����Ա����ͷ��*/
NODE_W* Add_To_Head_W(NODE_W* pHead_w, struct Waiter data)
{
    /*�����µ�����ڵ�*/
    NODE_W* pNode = (NODE_W*)malloc(sizeof(NODE_W));
    Assert_Program(pNode);
    if (pNode != NULL)
    {
        pNode->data = data;
        pNode->next = NULL;
        pNode->next = pHead_w; //����½�㵽����ͷ��
        pHead_w = pNode;
    }
    return pHead_w;
}

/*������������ӵ���������ͷ��*/
NODE_D* Add_To_Head_D(NODE_D* pHead_d, struct Date data)
{
    /*�����µ�����ڵ�*/
    NODE_D* pNode = (NODE_D*)malloc(sizeof(NODE_D));
    Assert_Program(pNode);
    if (pNode != NULL)
    {
        pNode->data = data;
        pNode->next = NULL;
        pNode->next = pHead_d; //����½�㵽����ͷ��
        pHead_d = pNode;
    }
    return pHead_d;
}

/*������������������ӡ�����������������������*/

/*�������ʳ��������Ϣ*/
void Print_LinkTable_F(NODE_F* pHead_f)
{
    NODE_F* pr = NULL;
    if (0 == SDU_Restaurant.foodsCount)
        return;
    for (pr = pHead_f; !(pr == NULL); pr = pr->next)
        printf("      %02d\t\t%-8s\t       %6.2lfԪ\n", pr->data.id, pr->data.name, pr->data.price);
}

void Show_LinkTable_F(NODE_F* pHead_f)
{
    NODE_F* pr = NULL;
    if (0 == SDU_Restaurant.foodsCount)
        return;
    for (pr = pHead_f; !(pr == NULL); pr = pr->next)
        printf("      %02d\t %-8s\t %6.2lfԪ\t%2d\n", pr->data.id, pr->data.name, pr->data.price, pr->data.orderCount);
}

/*�����������Ա������Ϣ*/
void Print_LinkTable_W(NODE_W* pHead_w)
{
    NODE_W* pr = NULL;
    if (0 == SDU_Restaurant.waitersCount)
        return;
    for (pr = pHead_w; !(pr == NULL); pr = pr->next)
        printf("    %s\t\t %-15s\t %6.2fԪ\n", pr->data.id, pr->data.waiterNick, pr->data.profit);
    printf("\n");
}

/*��������˿�������Ϣ*/
void Print_LinkTable_C(NODE_C* pHead_c)
{
    NODE_C* pr = NULL;
    if (0 == SDU_Restaurant.customerCount)
        return;
    for (pr = pHead_c; !(pr == NULL); pr = pr->next)
        printf("    %d\t\t %.2f\t \n", pr->data.Seatnum, pr->data.order.ExpensesToBePaid);
    printf("\n");
}

/*�����������������Ϣ*/
void Print_LinkTable_D(NODE_D* pHead_d)
{
    NODE_D* pr = NULL;
    if (0 == SDU_Restaurant.dateCount)
        return;
    for (pr = pHead_d; !(pr == NULL); pr = pr->next)
        printf("    %d\t\t %d\t \n", pr->data.year, pr->data.month);
    printf("\n");
}

/*��ӡVIP����*/
void Print_LinkTable_V(NODE_V* pHead_v)
{
    NODE_V* pr = NULL;
    if (0 == SDU_Restaurant.dateCount)
        return;
    for (pr = pHead_v; !(pr == NULL); pr = pr->next)
        printf("    \t%06d\t       %lld\t   \n", pr->data.cardnum, pr->data.phonenum);
    printf("\n");
}

/*�������������������ز�������������������*/

NODE_F* Load_Food_Inform(struct food* foods, int num)
{
    NODE_F* pHead_f = NULL;
    int i;
    for (i = 0; i < num; i++)
        pHead_f = Add_To_Tail_F(pHead_f, foods[i]);
    return pHead_f;
}

NODE_W* Load_Waiter_Inform(struct Waiter* waiters, int num)
{
    NODE_W* pHead_w = NULL;
    int i;
    for (i = 0; i < num; i++)
        pHead_w = Add_To_Tail_W(pHead_w, waiters[i]);
    return pHead_w;
}

NODE_C* Load_Customer_Inform(struct Customer* customers, int num)
{
    NODE_C* pHead_c = NULL;
    int i;
    for (i = 0; i < num; i++)
    {

        pHead_c = Add_To_Tail_C(pHead_c, customers[i]);
    }
    return pHead_c;
}

NODE_V* Load_VIP_Inform(struct VIP* vips, int num)
{
    NODE_V* pHead_v = NULL;
    int i;
    for (i = 0; i < num; i++)
    {

        pHead_v = Add_To_Tail_V(pHead_v, vips[i]);
    }
    return pHead_v;
}

NODE_D* Load_Profit_Inform(struct Date* dates, int num)
{
    NODE_D* pHead_d = NULL;
    int i;
    for (i = 0; i < num; i++)
    {
        pHead_d = Add_To_Tail_D(pHead_d, dates[i]);
    }
    return pHead_d;
}

/*���������������������������������������*/

/*��������Ʒ��ӵ���Ʒ����*/
void SDU_Add_Food(NODE_F* pHead_f, struct food newFood)
{
    NODE_F* pNode = (NODE_F*)malloc(sizeof(NODE_F));
    NODE_F* pr = NULL;
    if (pNode != NULL)
    {
        pNode->data = newFood;
        pNode->next = NULL;
    }
    Assert_Program(pNode);
    if (pHead_f != NULL)
    {
        for (pr = SDU_Restaurant.current_foods; !(pr == NULL); pr = pr->next) //�����Ʒ�ظ����
            if (pNode != NULL) {
                if (strcmp(pNode->data.name, pr->data.name) == 0)
                {
                    printf("  �� �� Ʒ �� �� �� ��\n");
                    SDU_Restaurant_Sleep(1300);
                    return;
                }
            }
        for (pr = SDU_Restaurant.current_foods; !(pr == NULL); pr = pr->next)
            if (pr->next == NULL) //��������Ʒ����β��
            {
                pNode->data.id = 1 + pr->data.id;
                pr->next = pNode;
                pr = pNode;
                break;
            }
    }
    else
    {
        if (pNode != NULL) {
            pNode->data.id = 1;
            pNode->next = pHead_f;
            pHead_f = pNode;
        }
    }
    SDU_Restaurant.foodsCount++;
    SDU_Restaurant.current_foods = pHead_f;
}

/*����������Ա��ӵ�����Ա����*/
void SDU_Add_Waiter(NODE_W* pHead_w, struct Waiter newWaiter)
{
    NODE_W* pNode = (NODE_W*)malloc(sizeof(NODE_W));
    NODE_W* pr = NULL;
    if (pNode != NULL)
    {
        pNode->data = newWaiter;
        pNode->next = NULL;
    }
    Assert_Program(pNode);
    if (pHead_w != NULL)
    {

        for (pr = SDU_Restaurant.current_waiters; !(pr == NULL); pr = pr->next) //�����Ʒ�ظ����
            if (pNode != NULL) {
                if (strcmp(pNode->data.id, pr->data.id) == 0)
                {
                    printf("            �� �� �� �� �� �� ��\n");
                    SDU_Restaurant_Sleep(1300);
                    return;
                }
            }

        for (pr = SDU_Restaurant.current_waiters; !(pr == NULL); pr = pr->next)
            if (pr->next == NULL) //����������Ա����β��
            {
                pNode->data.NO = 1 + pr->data.NO;
                pr->next = pNode;
                pr = pNode;
                break;
            }
    }
    else
    {
        if (pNode != NULL) {
            pNode->data.NO = 1;
            pNode->next = pHead_w;
            pHead_w = pNode;
        }
    }
    SDU_Restaurant.waitersCount++;
    SDU_Restaurant.current_waiters = pHead_w;
}

/*�������˿���ӵ��˿�����*/
void SDU_Add_Customer(NODE_C* pHead_c, struct Customer newcustomers)
{

    NODE_C* pNode = (NODE_C*)malloc(sizeof(NODE_C));
    NODE_C* pr = NULL;
    if (pNode != NULL)
    {
        pNode->data = newcustomers;
        pNode->next = NULL;
    }
    Assert_Program(pNode);

    if (pHead_c != NULL)
    {
        for (pr = SDU_Restaurant.current_customer; !(pr == NULL); pr = pr->next)
            if (pr->next == NULL) //�������˿�����β��
            {
                pr->next = pNode;
                pr = pNode;
                break;
            }
    }
    else
    {
        if (pNode != NULL) {
            pNode->next = pHead_c;
            pHead_c = pNode;
        }
    }

    SDU_Restaurant.customerCount++;
    SDU_Restaurant.current_customer = pHead_c;
}

/*������������ӵ���������*/
void SDU_Add_Date(NODE_D* pHead_d, struct Date newDate)
{
    SDU_Restaurant.current_date = Add_To_Head_D(pHead_d, newDate);
    SDU_Restaurant.dateCount++;
}
/*������VIP�˿���ӵ�VIP����*/
void SDU_Add_VIP(NODE_V* pHead_v, struct VIP newVIP)
{
    NODE_V* pNode = (NODE_V*)malloc(sizeof(NODE_V));
    NODE_V* pr = NULL;

    if (pNode != NULL)
    {
        pNode->data = newVIP;
        pNode->next = NULL;
    }

    for (pr = SDU_Restaurant.current_vip; !(pr == NULL); pr = pr->next) //�����Ʒ�ظ����
        if (pNode != NULL)
        {
            if (pNode->data.cardnum == pr->data.cardnum)
            {
                printf("            �� VIP �� �� �� �� �� ��\n");
                SDU_Restaurant_Sleep(1300);
                return;
            }
        }

    SDU_Restaurant.vipsCount++;
    SDU_Restaurant.current_vip = Add_To_Tail_V(pHead_v, newVIP);
}

/*�����������������洢��������������������*/

/*����Ʒ��Ϣ�洢���ļ�*/
void Save_Food_Inform(void)
{
    struct food* foods = NULL;
    if (SDU_Restaurant.foodsCount != 0) {
        foods = (struct food*)malloc(SDU_Restaurant.foodsCount * sizeof(struct food));
        Assert_Program(foods);
    }
    else
        foods = NULL;
    NODE_F* pr = NULL;
    int i = 0;
    for (pr = SDU_Restaurant.current_foods; !(pr == NULL); pr = pr->next)
    {
        if (foods != NULL)
            foods[i] = pr->data;
        i++;
    }
    Write_Food_Inform(foods, SDU_Restaurant.foodsCount);
}

/*������Ա��Ϣ�洢���ļ�*/
void Save_Waiter_Inform(void)
{
    struct Waiter* waiters = NULL;
    if (SDU_Restaurant.waitersCount != 0) {
        waiters = (struct Waiter*)malloc(SDU_Restaurant.waitersCount * sizeof(struct Waiter));
        Assert_Program(waiters);
    }
    else
        waiters = NULL;
    NODE_W* pr = NULL;
    int i = 0;
    for (pr = SDU_Restaurant.current_waiters; !(pr == NULL); pr = pr->next)
    {
        if (waiters != NULL)
            waiters[i] = pr->data;
        i++;
    }
    Write_Waiter_Inform(waiters, SDU_Restaurant.waitersCount);
}

/*���˿���Ϣ�洢���ļ�*/
void Save_Customer_Inform(void)
{
    struct Customer* customers = NULL;
    if (SDU_Restaurant.customerCount != 0) {
        customers = (struct Customer*)malloc(SDU_Restaurant.customerCount * sizeof(struct Customer));
        Assert_Program(customers);
    }
    else
        customers = NULL;

    NODE_C* pr = NULL;
    int i = 0;
    for (pr = SDU_Restaurant.current_customer; !(pr == NULL); pr = pr->next)
    {
        if (customers != NULL)
        {
            customers[i] = pr->data;
            i++;
        }
    }
    Write_Customer_Inform(customers, SDU_Restaurant.customerCount);
}

/*��������Ϣ�洢���ļ�*/
void Save_Date_Inform(void)
{
    struct Date* dates = NULL;
    if (SDU_Restaurant.dateCount != 0) {
        dates = (struct Date*)malloc(SDU_Restaurant.dateCount * sizeof(struct Date));
        Assert_Program(dates);
    }
    else
        dates = NULL;
    NODE_D* pr = NULL;
    int i = 0;
    if (SDU_Restaurant.current_date != NULL)
        for (pr = SDU_Restaurant.current_date; !(pr == NULL); pr = pr->next)
        {
            if (dates != NULL) {
                dates[i] = pr->data;
                i++;
            }
        }
    Write_Date_Inform(dates, SDU_Restaurant.dateCount);
}
/*��VIP��Ϣ�洢���ļ�*/
void Save_VIP_Inform(void)
{
    struct VIP* vips = NULL;
    if (SDU_Restaurant.vipsCount != 0) {
        vips = (struct VIP*)malloc(SDU_Restaurant.vipsCount * sizeof(struct VIP));
        Assert_Program(vips);
    }
    else
        vips = NULL;
    NODE_V* pr = NULL;
    int i = 0;
    if (SDU_Restaurant.current_vip != NULL)
        for (pr = SDU_Restaurant.current_vip; !(pr == NULL); pr = pr->next)
        {
            if (vips != NULL) {
                vips[i] = pr->data;
                i++;
            }
        }
    Write_VIP_Inform(vips, SDU_Restaurant.vipsCount);
}

/*����������������ɾ����������������������*/

/*�������ֵ, ɾ����Ӧ�Ĳ�Ʒ����*/
NODE_F* SDU_Delete_Food(NODE_F* pHead_f, int id)
{
    if (pHead_f == NULL) //�ж��Ƿ�Ϊ�ձ�
        return NULL;
    /*�����ڱ�ͷ���������⴦��*/
    if (id == pHead_f->data.id)
    {
        NODE_F* pDelete = pHead_f;
        pHead_f = pHead_f->next;
        SDU_Restaurant.foodsCount--;
        free(pDelete);
    }
    /*�����ڱ�ͷ������*/
    else
    {
        NODE_F* pLast = pHead_f;
        NODE_F* pNext = pHead_f->next;
        NODE_F* pDelete = NULL;
        if (pNext == NULL) //���û�ҵ�
        {
            printf("δ�ҵ���Ӧ���ֵ!\n");
            SDU_Restaurant_Sleep(1000);
            return pHead_f;
        }
        while (1)
        {
            /* ����һ��Ҫ���ж��ҵ����ݣ��ٽ�pLast��pNext�����ƶ���˳���ܷ�����������ڶ������ݾͻᱻ���Թ�ȥ*/
            if (id == pNext->data.id) //����ҵ�
            {
                pDelete = pNext;
                pLast->next = pNext->next;

                SDU_Restaurant.foodsCount--;
                free(pDelete); //��ֹ�ڴ�й©
                break;
            }
            if (pNext->next == NULL) //���û�ҵ�
            {
                printf("δ�ҵ���Ӧ���ֵ!\n");
                SDU_Restaurant_Sleep(1000);
                break;
            }
            else
            {
                pLast = pLast->next;
                pNext = pNext->next;
            }
        }
    }
    return pHead_f;
}

/*�������ֵ, ɾ����Ӧ�ķ���Ա����*/
NODE_W* SDU_Delete_Waiter(NODE_W* pHead_w, char* id)
{
    if (pHead_w == NULL) //�ж��Ƿ�Ϊ�ձ�
        return NULL;

    /*�����ڱ�ͷ���������⴦��*/
    if (0 == strcmp(pHead_w->data.id, id))
    {
        NODE_W* pDelete = pHead_w;
        pHead_w = pHead_w->next;
        SDU_Restaurant.waitersCount--;
        free(pDelete);
    }

    /*�����ڱ�ͷ������*/
    else
    {
        NODE_W* pLast = pHead_w;
        NODE_W* pNext = pHead_w->next;
        NODE_W* pDelete = NULL;
        if (pNext == NULL) //���û�ҵ�
        {
            printf("δ�ҵ���Ӧ���ֵ!\n");
            SDU_Restaurant_Sleep(1000);
            return pHead_w;
        }
        while (1)
        {
            /* ����һ��Ҫ���ж��ҵ����ݣ��ٽ�pLast��pNext�����ƶ���˳���ܷ�����������ڶ������ݾͻᱻ���Թ�ȥ*/

            if (0 == strcmp(pNext->data.id, id)) //����ҵ�
            {
                pDelete = pNext;
                pLast->next = pNext->next;

                SDU_Restaurant.waitersCount--;
                free(pDelete); //��ֹ�ڴ�й©
                break;
            }
            if (pNext->next == NULL) //���û�ҵ�
            {
                printf("δ�ҵ���Ӧ���ֵ!\n");
                SDU_Restaurant_Sleep(1000);
                break;
            }
            else
            {
                pLast = pLast->next;
                pNext = pNext->next;
            }
        }
    }
    return pHead_w;
}

/*��������, ɾ����Ӧ�Ĺ˿�����*/
NODE_C* SDU_Delete_Customer(NODE_C* pHead_c, int seatnum)
{
    if (pHead_c == NULL) //�ж��Ƿ�Ϊ�ձ�
        return NULL;

    /*�����ڱ�ͷ���������⴦��*/
    if (pHead_c->data.Seatnum == seatnum)
    {
        NODE_C* pDelete = pHead_c;
        pHead_c = pHead_c->next;
        SDU_Restaurant.customerCount--;
        free(pDelete);
    }

    /*�����ڱ�ͷ������*/
    else
    {
        NODE_C* pLast = pHead_c;
        NODE_C* pNext = pHead_c->next;
        NODE_C* pDelete = NULL;
        if (pNext == NULL) //���û�ҵ�
        {
            printf("δ�ҵ���Ӧ���ֵ!\n");
            SDU_Restaurant_Sleep(1000);
            return pHead_c;
        }
        while (1)
        {
            /* ����һ��Ҫ���ж��ҵ����ݣ��ٽ�pLast��pNext�����ƶ���˳���ܷ�����������ڶ������ݾͻᱻ���Թ�ȥ*/

            if (pNext->data.Seatnum == seatnum) //����ҵ�
            {
                pDelete = pNext;
                pLast->next = pNext->next;

                SDU_Restaurant.customerCount--;
                free(pDelete); //��ֹ�ڴ�й©
                break;
            }
            if (pNext->next == NULL) //���û�ҵ�
            {
                printf("δ�ҵ���Ӧ���ֵ!\n");
                SDU_Restaurant_Sleep(1000);
                break;
            }
            else
            {
                pLast = pLast->next;
                pNext = pNext->next;
            }
        }
    }
    return pHead_c;
}

/*�ڶ����У��������ֵ, ɾ����Ӧ���Ѷ���Ʒ����*/
int Delet_Food_From_Order(int foodID, struct Order* order, double discount)
{
    NODE_F* pHead_f = SDU_Restaurant.current_foods;
    NODE_F* pr;

    pr = pHead_f;
    int i;
    for (i = 0; i < SDU_Restaurant.foodsCount; i++)
    {
        if (foodID == pr->data.id) //�ҵ���Ӧ��Ʒ
        {
            pr->data.orderCount--; //��¼��Ʒ��ʷ����
            Save_Food_Inform();
            if (order->foodCount == 0)
            {
                printf("δ���е�ˣ��޷�ɾ����");
                SDU_Restaurant_Sleep(1000);
                return 1;
            }
            for (int i = order->foodCount - 1; i >= 0; i--)
            {
                if (order->foods[i].id == foodID)
                {
                    order->ExpensesToBePaid -= discount * order->foods[i].price;

                    for (int j = i; j < order->foodCount - 1; j++)
                        order->foods[j] = order->foods[j + 1];
                    order->foodCount--;
                    break;
                }
            }

            Assert_Program(order->foods);

            return 1;
        }
        pr = pr->next;
    }
    return 0;
}
/*���ݿ���, ɾ����Ӧ��VIP����*/
NODE_V* SDU_Delete_VIP(NODE_V* pHead_v, int cardnum)
{
    if (pHead_v == NULL) //�ж��Ƿ�Ϊ�ձ�
        return NULL;

    /*�����ڱ�ͷ���������⴦��*/
    if (pHead_v->data.cardnum == cardnum)
    {
        NODE_V* pDelete = pHead_v;
        pHead_v = pHead_v->next;
        SDU_Restaurant.vipsCount--;
        free(pDelete);
    }

    /*�����ڱ�ͷ������*/
    else
    {
        NODE_V* pLast = pHead_v;
        NODE_V* pNext = pHead_v->next;
        NODE_V* pDelete = NULL;
        if (pNext == NULL) //���û�ҵ�
        {
            printf("δ�ҵ���Ӧ���ֵ!\n");
            SDU_Restaurant_Sleep(1000);
            return pHead_v;
        }
        while (1)
        {
            /* ����һ��Ҫ���ж��ҵ����ݣ��ٽ�pLast��pNext�����ƶ���˳���ܷ�����������ڶ������ݾͻᱻ���Թ�ȥ*/

            if (pNext->data.cardnum == cardnum) //����ҵ�
            {
                pDelete = pNext;
                pLast->next = pNext->next;

                SDU_Restaurant.vipsCount--;
                free(pDelete); //��ֹ�ڴ�й©
                break;
            }
            if (pNext->next == NULL) //���û�ҵ�
            {
                printf("δ�ҵ���Ӧ���ֵ!\n");
                SDU_Restaurant_Sleep(1000);
                break;
            }
            else
            {
                pLast = pLast->next;
                pNext = pNext->next;
            }
        }
    }
    return pHead_v;
}

/*����������������������²�������������������*/

/*ʹ��Ʒ��������ˢ��Ϊ���򻯣���������ʱ��˳������*/
void Order_By_ID_F(NODE_F* pHead_f)
{
    NODE_F* pr = pHead_f;
    int idx = 1;
    while (pr != NULL)
    {
        pr->data.id = idx++;
        pr = pr->next;
    }
}

/*ʹ����Ա��������ˢ��Ϊ���򻯣���������ʱ��˳������*/
void Order_By_ID_W(NODE_W* pHead_w)
{
    NODE_W* pr = pHead_w;
    int idx = 1;
    while (pr != NULL)
    {
        pr->data.NO = idx++;
        pr = pr->next;
    }
}

/*�鲢����*/
NODE_V* Order_Merge_Sort_By_Cardnum(NODE_V* head1, NODE_V* head2)
{
    if (head1 == NULL)
        return head2;
    if (head2 == NULL)
        return head1;

    NODE_V* res, * p;
    if (head1->data.cardnum < head2->data.cardnum)
    {
        res = head1;
        head1 = head1->next;
    }
    else
    {
        res = head2;
        head2 = head2->next;
    }
    p = res;
    while (head1 != NULL && head2 != NULL)
    {
        if (head1->data.cardnum < head2->data.cardnum)
        {
            p->next = head1;
            head1 = head1->next;
        }
        else
        {
            p->next = head2;
            head2 = head2->next;
        }
        p = p->next;
    }
    if (head1 != NULL)
        p->next = head1;
    else if (head2 != NULL)
        p->next = head2;
    return res;
}

/*���˿͸�����������*/
NODE_V* Order_By_Cardnum(NODE_V* pHead_v)
{

    if (pHead_v == NULL || pHead_v->next == NULL)
        return pHead_v;
    else
    {
        NODE_V* fast = pHead_v, * slow = pHead_v;
        while (fast->next != NULL && fast->next->next != NULL)
        {
            fast = fast->next->next;
            slow = slow->next;
        }
        fast = slow;
        slow = slow->next;
        fast->next = NULL;
        fast = Order_By_Cardnum(pHead_v);
        slow = Order_By_Cardnum(slow);
        return Order_Merge_Sort_By_Cardnum(fast, slow);
    }
}

/*�鲢����*/
NODE_C* Order_Merge_Sort_By_Seatnum(NODE_C* head1, NODE_C* head2)
{
    if (head1 == NULL)
        return head2;
    if (head2 == NULL)
        return head1;

    NODE_C* res, * p;
    if (head1->data.Seatnum < head2->data.Seatnum)
    {
        res = head1;
        head1 = head1->next;
    }
    else
    {
        res = head2;
        head2 = head2->next;
    }
    p = res;
    while (head1 != NULL && head2 != NULL)
    {
        if (head1->data.Seatnum < head2->data.Seatnum)
        {
            p->next = head1;
            head1 = head1->next;
        }
        else
        {
            p->next = head2;
            head2 = head2->next;
        }
        p = p->next;
    }
    if (head1 != NULL)
        p->next = head1;
    else if (head2 != NULL)
        p->next = head2;
    return res;
}

/*���˿͸�����������*/
NODE_C* Order_By_Seatnum(NODE_C* pHead_c)
{

    if (pHead_c == NULL || pHead_c->next == NULL)
        return pHead_c;
    else
    {
        NODE_C* fast = pHead_c, * slow = pHead_c;
        while (fast->next != NULL && fast->next->next != NULL)
        {
            fast = fast->next->next;
            slow = slow->next;
        }
        fast = slow;
        slow = slow->next;
        fast->next = NULL;
        fast = Order_By_Seatnum(pHead_c);
        slow = Order_By_Seatnum(slow);
        return Order_Merge_Sort_By_Seatnum(fast, slow);
    }
}

/*������������������Ӳ�������������������*/

/*����Ʒ��Ϣ��ӵ�����*/
int Add_Food_To_Order(int foodID, struct Order* order, double discount)
{
    NODE_F* pHead_f = SDU_Restaurant.current_foods;
    NODE_F* pr;

    pr = pHead_f;
    int i;
    for (i = 0; i < SDU_Restaurant.foodsCount; i++)
    {
        if (foodID == pr->data.id) //�ҵ���Ӧ��Ʒ
        {
            pr->data.orderCount++; //��¼��Ʒ��ʷ����
            Save_Food_Inform();

            Assert_Program(order->foods);

            /*���¶���*/
            order->foods[(order->foodCount + 1) - 1] = pr->data;
            order->foodCount++;
            order->ExpensesToBePaid += discount * pr->data.price;
            return 1;
        }
        pr = pr->next;
    }
    return 0;
}

/*���˿�������ӵ��˿�����β��*/
NODE_C* Add_To_Tail_C(NODE_C* pHead_c, struct Customer Data)
{
    /*�����µ�����ڵ�*/
    NODE_C* pNode = (NODE_C*)malloc(sizeof(NODE_C));
    Assert_Program(pNode);
    if (pNode != NULL) {
        pNode->data = Data;
        pNode->next = NULL;
    }
    /*��ԭ����Ϊ��*/
    if (pHead_c == NULL)
    {
        if (pNode != NULL) {
            pNode->next = pHead_c;
            pHead_c = pNode;
        }
    }

    /*��ԭ����ǿ�*/
    else
    {
        NODE_C* pr = NULL;
        pr = pHead_c;
        while (!(pr->next == NULL)) //����������β��
        {
            pr = pr->next;
        }
        pr->next = pNode; //����½�㵽����β��
    }
    return pHead_c;
}


/*��VIP������ӵ��˿�����β��*/
NODE_V* Add_To_Tail_V(NODE_V* pHead_v, struct VIP Data)
{
    /*�����µ�����ڵ�*/
    NODE_V* pNode = (NODE_V*)malloc(sizeof(NODE_V));
    Assert_Program(pNode);
    pNode->data = Data;
    pNode->next = NULL;
    /*��ԭ����Ϊ��*/
    if (pHead_v == NULL)
    {
        if (pNode != NULL) {
            pNode->next = pHead_v;
            pHead_v = pNode;
        }
    }

    /*��ԭ����ǿ�*/
    else
    {
        NODE_V* pr = NULL;
        pr = pHead_v;
        while (!(pr->next == NULL)) //����������β��
        {
            pr = pr->next;
        }
        pr->next = pNode; //����½�㵽����β��
    }
    return pHead_v;
}

/*������������ӵ���������β��*/
NODE_D* Add_To_Tail_D(NODE_D* pHead_d, struct Date Data)
{
    /*�����µ�����ڵ�*/
    NODE_D* pNode = (NODE_D*)malloc(sizeof(NODE_D));
    Assert_Program(pNode);
    if (pNode != NULL) {
        pNode->data = Data;
        pNode->next = NULL;
    }
    /*��ԭ����Ϊ��*/
    if (pHead_d == NULL)
    {
        if (pNode != NULL) {
            pNode->next = pHead_d;
            pHead_d = pNode;
        }
    }

    /*��ԭ����ǿ�*/
    else
    {
        NODE_D* pr = NULL;
        pr = pHead_d;
        while (!(pr->next == NULL)) //����������β��
        {
            pr = pr->next;
        }
        pr->next = pNode; //����½�㵽����β��
    }
    return pHead_d;
}

/*����������������������������������������*/

/*���������λ��Ϣ*/
void Clear_Seat_Inform(void)
{
    for (int i = 0; i < SEATINFO_HEIGHT; i++)
    {
        for (int j = 0; j < SEATINFO_WIDTH; j++)
        {
            if (SDU_Restaurant.seatsMap[i][j].isSelected)
            {
                SDU_Restaurant.seatsMap[i][j].isSelected = 0;
            }
        }
    }
}

/*����ͺ��뿪��λ*/
void Leave_Seat(int num)
{
    int row, col;
    col = (num - 1) % SEATINFO_WIDTH;
    row = (num - col) / SEATINFO_WIDTH;
    SDU_Restaurant.seatsMap[row][col].isSelected = 0;
}