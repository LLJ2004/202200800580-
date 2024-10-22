#pragma once

/*��ʼ��*/
void Create_DataBaseFiles(void); //����ȫ�µ����ݿ��ļ���ԭ�ȵ����ݽ������

/*��λ*/
void Read_SeatMap_Inform(struct Seat* pSeatsMap); //���ļ��ж�ȡ��λͼ��Ϣ

void Write_SeatMap_Inform(struct Seat* pSeatsMap); //����λͼ��Ϣд���ļ�

int Check_Seated(int num); //�жϵ�ǰ��λ�Ƿ�ռ��

int Check_Selected(int num); //�жϵ�ǰ��λ�Ƿ�Ԥ��

/*��Ʒ*/
void Read_Food_Inform(struct food* (*foods), int* num); //���ļ��ж�ȡ��Ʒ��Ϣ

void Write_Food_Inform(struct food foods[], int num); //����Ʒ��Ϣд���ļ�

/*����Ա*/
void Read_Waiter_Inform(struct Waiter* (*waiters), int* num); //���ļ��ж�ȡ����Ա��Ϣ

void Write_Waiter_Inform(struct Waiter waiters[], int num); //������Ա��Ϣд���ļ�

int Check_Waiter(char* id_input, char* ps_input); //������Ա�����Ƿ���ȷ

/*����Ա*/
void Write_Admin_Inform(const char id[], const char ps[]); //������Ա��Ϣд���ļ�

int Check_Admin(const char* id_input, char* ps_input); //������Ա�����Ƿ���ȷ

/*�˿�*/
void Read_Customer_Inform(struct Customer* (*customer), int* num); //���ļ��ж�ȡ�˿���Ϣ

void Write_Customer_Inform(struct Customer customer[], int num); //���˿���Ϣд���ļ�

/*VIP*/
void Read_VIP_Inform(struct VIP* (*vips), int* num); //���ļ��ж�ȡ�˿���Ϣ

void Write_VIP_Inform(struct VIP vips[], int num); //���˿���Ϣд���ļ�

/*������*/
void Read_Date_Inform(struct Date* (*dates), int* num); //���ļ��ж�ȡ��������Ϣ

void Write_Date_Inform(struct Date dates[], int num); //����������Ϣд���ļ�
