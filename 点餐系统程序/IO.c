#include "Core.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern struct SDU_Restaurant_Data SDU_Restaurant;

/*��ȡ��Ʒ��Ϣ*/
void Read_Food_Inform(struct food* (*foods), int* num)
{
    FILE* fp;
    errno_t err;
    if ((err = fopen_s(&fp, "DataBase_Food.txt", "rb")) == 0)
    {
        (*num) = 0;

        fread(num, sizeof(int), 1, fp);
        (*foods) = (struct food*)calloc((*num), sizeof(struct food));
        Assert_Program(*foods);

        if (*foods == NULL) //�޸������жϽ�����־���Warning C6387
            return;
        fread(*foods, sizeof(struct food), (*num), fp);
        fclose(fp);
    }
    else
    {
        printf("�ļ���ʧ�ܣ�\n");
        exit(EXIT_FAILURE);
    }
}

/*��ȡ����Ա��Ϣ*/
void Read_Waiter_Inform(struct Waiter* (*waiters), int* num)
{
    FILE* fp;
    errno_t err;
    if ((err = fopen_s(&fp, "DataBase_Waiter.txt", "rb")) == 0)
    {
        (*num) = 0;

        fread(num, sizeof(int), 1, fp);
        (*waiters) = (struct Waiter*)calloc((*num), sizeof(struct Waiter));
        Assert_Program(*waiters);

        if (*waiters == NULL) //�޸������жϽ�����־���Warning C6387
            return;
        fread(*waiters, sizeof(struct Waiter), (*num), fp);
        fclose(fp);
    }
    else
    {
        printf("�ļ���ʧ�ܣ�\n");
        exit(EXIT_FAILURE);
    }
}

/*��ȡ�˿���Ϣ*/
void Read_Customer_Inform(struct Customer* (*customers), int* num)
{
    FILE* fp;
    errno_t err;
    if ((err = fopen_s(&fp, "DataBase_Customer.txt", "rb")) == 0)
    {
        (*num) = 0;

        fread(num, sizeof(int), 1, fp);
        (*customers) = (struct Customer*)calloc((*num), sizeof(struct Customer));
        Assert_Program(*customers);

        if (*customers == NULL) //�޸������жϽ�����־���Warning C6387
            return;
        fread(*customers, sizeof(struct Customer), (*num), fp);
        fclose(fp);
    }
    else
    {
        printf("�ļ���ʧ�ܣ�\n");
        exit(EXIT_FAILURE);
    }
}

/*��ȡVIP��Ϣ*/
void Read_VIP_Inform(struct VIP* (*vips), int* num)
{
    FILE* fp;
    errno_t err;
    if ((err = fopen_s(&fp, "DataBase_VIP.txt", "rb")) == 0)
    {
        (*num) = 0;

        fread(num, sizeof(int), 1, fp);
        (*vips) = (struct VIP*)calloc((*num), sizeof(struct VIP));
        Assert_Program(*vips);

        if (*vips == NULL) //�޸������жϽ�����־���Warning C6387
            return;
        fread(*vips, sizeof(struct VIP), (*num), fp);
        fclose(fp);
    }
    else
    {
        printf("�� ��  �� �� ʧ �ܣ�\n");
        exit(EXIT_FAILURE);
    }
}

/*��ȡ��λ��Ϣ*/
void Read_SeatMap_Inform(struct Seat* pSeatsMap)
{
    FILE* fp;
    errno_t err;
    if ((err = fopen_s(&fp, "DataBase_SeatsMap.txt", "rb")) == 0)
    {
        // pSeatsMap = (struct Seat *)calloc(SEATINFO_HEIGHT*SEATINFO_WIDTH, sizeof(struct Seat));//����
        fread(pSeatsMap, sizeof(struct Seat), SEATINFO_HEIGHT * SEATINFO_WIDTH, fp);
        fclose(fp);
    }
    else
    {
        printf("�ļ���ʧ�ܣ�\n");
        exit(EXIT_FAILURE);
    }
}

/*���ļ��ж�ȡǰһ����������Ϣ*/
void Read_Date_Inform(struct Date* (*dates), int* num)
{
    FILE* fp;
    errno_t err;
    if ((err = fopen_s(&fp, "DataBase_Date.txt", "rb")) == 0)
    {
        (*num) = 0;

        fread(num, sizeof(int), 1, fp);

        if (!(num == 0))
        {
            (*dates) = (struct Date*)calloc((*num), sizeof(struct Date));
            Assert_Program(*dates);
        }
        else
        {
            (*dates) = NULL;
        }

        if (*dates == NULL) //�޸������жϽ�����־���Warning C6387
            return;
        fread(*dates, sizeof(struct Date), (*num), fp);
        fclose(fp);
    }
    else
    {
        printf("�ļ���ʧ�ܣ�\n");
        exit(EXIT_FAILURE);
    }
}

/*����Ʒ������Ϣд���ļ�*/
void Write_Food_Inform(struct food foods[], int num)
{
    FILE* fp;
    errno_t err;
    if ((err = fopen_s(&fp, "DataBase_Food.txt", "wb")) == 0)
    {
        fwrite(&num, sizeof(int), 1, fp);
        fwrite(foods, sizeof(struct food), num, fp);

        fclose(fp);
    }
    else
    {
        printf("�ļ���ʧ�ܣ�\n");
        exit(EXIT_FAILURE);
    }
}

/*������Ա������Ϣд���ļ�*/
void Write_Waiter_Inform(struct Waiter waiters[], int num)
{
    FILE* fp;
    errno_t err;
    if ((err = fopen_s(&fp, "DataBase_Waiter.txt", "wb")) == 0)
    {
        fwrite(&num, sizeof(int), 1, fp);
        fwrite(waiters, sizeof(struct Waiter), num, fp);
        fclose(fp);
    }
    else
    {
        printf("�ļ���ʧ�ܣ�\n");
        exit(EXIT_FAILURE);
    }
}

/*���˿�������Ϣд���ļ�*/
void Write_Customer_Inform(struct Customer customer[], int num)
{
    FILE* fp;
    errno_t err;

    if ((err = fopen_s(&fp, "DataBase_Customer.txt", "wb")) == 0)
    {
        fwrite(&num, sizeof(int), 1, fp);
        if (customer != NULL)
            fwrite(customer, sizeof(struct Customer), num, fp);
        else
            fwrite((struct Customer*)0, sizeof(struct Customer), 0, fp);
        fclose(fp);
    }
    else
    {
        printf("�ļ���ʧ�ܣ�\n");
        exit(EXIT_FAILURE);
    }
}

/*��VIP������Ϣд���ļ�*/
void Write_VIP_Inform(struct VIP vips[], int num)
{
    FILE* fp;
    errno_t err;

    if ((err = fopen_s(&fp, "DataBase_VIP.txt", "wb")) == 0)
    {
        fwrite(&num, sizeof(int), 1, fp);
        if (vips != NULL)
            fwrite(vips, sizeof(struct VIP), num, fp);
        else
            fwrite((struct VIP*)0, sizeof(struct VIP), 0, fp);
        fclose(fp);
    }
    else
    {
        printf("�ļ���ʧ�ܣ�\n");
        exit(EXIT_FAILURE);
    }
}

/*����������Ϣд���ļ�*/
void Write_Date_Inform(struct Date date[], int num)
{
    FILE* fp;
    errno_t err;
    if ((err = fopen_s(&fp, "DataBase_Date.txt", "wb")) == 0)
    {
        fwrite(&num, sizeof(int), 1, fp);

        fwrite(date, sizeof(struct Date), num, fp);
        fclose(fp);
    }
    else
    {
        printf("�ļ���ʧ�ܣ�\n");
        exit(EXIT_FAILURE);
    }
}

/*������Ա������Ϣд���ļ���Ŀǰֻ��һλ����Աconst char id[]����δ�����Ա���Ϊstruct Admin admin[]*/
void Write_Admin_Inform(const char id[], const char ps[])
{
    if (strlen(id) > ADMINID_LENGTH_MAX) //���ƹ��ų�������
    {
        printf("����̫���ˣ�ֻ��ǰ %d ���ַ�������.\n", ADMINID_LENGTH_MAX);
        SDU_Restaurant_Sleep(1000);
    }
    if (strlen(ps) > ADMINPAS_LENGTH_MAX) //�������볤������
    {
        printf("����̫���ˣ�ֻ��ǰ %d ���ַ�������.\n", ADMINPAS_LENGTH_MAX);
        SDU_Restaurant_Sleep(1000);
    }
    FILE* fp;
    errno_t err;
    if ((err = fopen_s(&fp, "DataBase_Admin.txt", "wb")) == 0)
    {
        fputs(id, fp);
        fputs(" ", fp);
        fputs(ps, fp);
        fclose(fp);
    }
    else
    {
        printf("�� �� �� �� ʧ �ܣ�\n");
        exit(EXIT_FAILURE);
    }
}

/*����λ��Ϣд���ļ�*/
void Write_SeatMap_Inform(struct Seat* pSeatsMap)
{
    FILE* fp;
    errno_t err;
    if ((err = fopen_s(&fp, "DataBase_SeatsMap.txt", "wb")) == 0)
    {
        fwrite(pSeatsMap, sizeof(struct Seat), SEATINFO_HEIGHT * SEATINFO_WIDTH, fp);
        fclose(fp);
    }
    else
    {
        printf("�� �� �� �� ʧ �ܣ�\n");
        exit(EXIT_FAILURE);
    }
}

extern struct VIP chushivips[3] = {
        {1001, 13888888881},
        {1002, 13888888882},
        {1003, 13888888883}
};

extern struct food chushifood[3] = {
        {01,"hslr",10,0},
        {02,"plsgm",10,0},
        {03,"dhlf",10,0}
};

extern struct Waiter chushiwaiters[3] = {
        {01,0,"100001","long","123456"},
        {02,0,"100002","zhu","123456"},
        {03,0,"100003","chang","123456"}
};

//�����ļ���ʼ��
void Create_DataBaseFiles(void)
{
    /*��ʼ��DataBase_SeatsMap����*/
    int row, col;
    for (row = 0; row < SEATINFO_HEIGHT; row++)
    {
        for (col = 0; col < SEATINFO_WIDTH; col++)
        {
            SDU_Restaurant.seatsMap[row][col].isSelected = 0;
            SDU_Restaurant.seatsMap[row][col].row = row;
            SDU_Restaurant.seatsMap[row][col].col = col;
        }
    }
    Write_SeatMap_Inform((struct Seat*)&SDU_Restaurant.seatsMap);

    /*��ʼ��DataBase_Food����*/
    Write_Food_Inform(chushifood, 3);

    /*��ʼ��DataBase_Waiter����*/
    Write_Waiter_Inform(chushiwaiters, 3);

    /*��ʼ��DataBase_Customer����*/
    Write_Customer_Inform((struct Customer*)0, 0);

    /*��ʼ��DataBase_Admin����*/
    Write_Admin_Inform("admin", "admin");

    /*��ʼ��DataBase_Date����*/
    Write_Date_Inform((struct Date*)0, 0);

    /*��ʼ��DataBase_VIP����*/
    Write_VIP_Inform(chushivips, 3);
}

/*�������Ա���*/
int Check_Admin(const char* id_input, char* ps_input)
{
    char id[ADMINID_LENGTH_MAX + 1] = { 0 };
    char ps[ADMINPAS_LENGTH_MAX + 1] = { 0 };
    FILE* fp;
    errno_t err;
    if ((err = fopen_s(&fp, "DataBase_Admin.txt", "rb")) == 0)
    {
        while (fscanf_s(fp, "%s %s", id, sizeof(id), ps, sizeof(ps)) != EOF)
        {
            if (strcmp(id, id_input) == 0 && strcmp(ps, ps_input) == 0)
            {
                fclose(fp);
                return 1;
            }
        }
        fclose(fp);
        return 0;
    }
    else
    {
        printf("�ļ���ʧ�ܣ�\n");
        exit(EXIT_FAILURE);
    }
}

/*�������Ա���*/
int Check_Waiter(char* id_input, char* ps_input)
{
    NODE_W* pr = NULL;
    if (0 == SDU_Restaurant.waitersCount)
        return 0;
    for (pr = SDU_Restaurant.current_waiters; !(pr == NULL); pr = pr->next)
    {
        if (0 == strcmp(pr->data.id, id_input) && 0 == strcmp(pr->data.passwd, ps_input))
        {

            SDU_Restaurant.waiter_Login = &pr->data;
            return 1;
        }
    }
    return 0;
}

/*�ж���λ�Ƿ�ռ��*/
int Check_Seated(int num)
{
    int row, col;
    col = (num - 1) % SEATINFO_WIDTH;
    row = (num - col) / SEATINFO_WIDTH;
    if ((col >= 0 && col < SEATINFO_WIDTH) && (row >= 0 && row < SEATINFO_HEIGHT) && SDU_Restaurant.seatsMap[row][col].isSeated)
        return 1;
    return 0;
}

int Check_Selected(int num)
{
    int row, col;
    col = (num - 1) % SEATINFO_WIDTH;
    row = (num - col) / SEATINFO_WIDTH;
    if ((col >= 0 && col < SEATINFO_WIDTH) && (row >= 0 && row < SEATINFO_HEIGHT) && SDU_Restaurant.seatsMap[row][col].isSelected)
        return 1;
    return 0;
}