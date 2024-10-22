#include "Core.h"
#include "IO.h"
#include "UI.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct SDU_Restaurant_Data SDU_Restaurant;
int EXIT;

int main(int argc, char const* argv[])
{

    /*�����ļ���ȡ��ȫ�ֱ�����ʼ��*/
    SDU_Restaurant_Init(argc, argv);

    while (1)
    {
        EXIT = 0;

        /*�û�ѡ�����(����ԱOR����Ա)*/
         /*����Ա*/
        enum userType user1;
        user1 = SDU_Restaurant_Welcome();
       
        int user = (int)user1;
        if (user == 1) {
            while (1)
            {
                if (EXIT == 1)
                    break;
                int choice = Admin_Menu();
                switch (choice)
                {
                case 1: //�鿴��λ��Ϣ.
                    Admin_Seat_Infom();
                    break;
                case 2: //�鿴Ӫҵ�ܶ�
                    Admin_Daily_Profit();
                    break;
                case 3: //���Ĳ�Ʒ��Ϣ
                    Admin_Food_Change();
                    break;
                case 4: //���ķ���Ա��Ϣ
                    Admin_Waiter_Change();
                    break;
                case 5://����VIP��Ϣ
                    Admin_VIP_Change();
                    break;
                case 6: //�޸Ĺ���Ա����
                    Admin_Passwd_Change();
                    break;
                case 7:  //��Ʒ��������.
                    Admin_Statistics_Analysis();
                    break;
                case 8: //����Ա�˺ŵǳ�
                    EXIT = 1;
                    break;
                case 0: //�˳�����
                    Show_Exit_Program();
                    break;
                }
            }
        }

        /*����Ա*/
        else if (user == 2)
        {
            while (1)
            {
                if (EXIT == 1)
                    break;
                int choice = Waiter_Menu();
                switch (choice)
                {
                case 1: //ѡ����λ
                    Waiter_Seat_Select();
                    break;
                case 2: //չʾ�˵�
                    Waiter_Food_Show();
                    break;
                case 3: //�Ǽǵ��
                    Waiter_Food_Order();
                    break;
                case 4: //�����˵�
                    Waiter_Food_Check();
                    break;
                case 5: //ȡ������Ԥ��
                    Waiter_Seat_Cancel();
                    break;
                case 6: //�޸ķ���Ա����
                    Waiter_Passwd_Change();
                    break;
                case 7: //����Ա�˺ŵǳ�
                    EXIT = 1;
                    break;
                case 0: //�˳�����
                    Show_Exit_Program();
                    break;
                }
            }
        }
    }
    return 0;
}
