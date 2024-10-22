#pragma once

/*����Ա*/
int Waiter_Menu(void); //����Ա�˵�ҳ��

void Waiter_Food_Show(void); //����Աչʾ��Ʒ����

void Waiter_Food_Order(void); //����Աչʾ��˽���

void Waiter_Food_Check(void); //����Աչʾ���˽���

void Waiter_Seat_Select(void); //����Ա��λԤ������

void Waiter_Passwd_Change(void); //����Ա�޸��������

void Waiter_Seat_Cancel(void); //����Աȡ��Ԥ������

/*����Ա*/
int Admin_Menu(void); //����Ա�˵�ҳ��

void Admin_Food_Change(void); //����Ա���Ĳ�Ʒ��Ϣ

void Admin_Waiter_Change(void); //����Ա���ķ���Ա��Ϣ

void Admin_Seat_Infom(void);//����Աչʾ��λ���

void Admin_Daily_Profit(void);//����Աչʾÿ������

void Admin_Statistics_Analysis();//����Աչʾ��Ʒ����

void Admin_Passwd_Change();//����Ա��������

void Admin_VIP_Change(void);//����Ա����VIP��Ϣ

/*UI����*/
enum UserType SDU_Restaurant_Welcome(void); //�û�����ѡ��ҳ��

void Loading_Menu(char* ID_input, char* password_input); //��¼�˵�����

int Check_ID_Passwd(char* ID_input, char* password_input, enum UserType* userType, int Choice); //��������Ƿ�ƥ��

void Show_Exit_Program(void); //�˳�����ҳ��

void clearScreenBuffer(void); //�����Ļ������
