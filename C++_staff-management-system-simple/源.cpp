#include<iostream>
#include"workerManager.h"
using namespace std;
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"


int main()
{

	//worker* worker = NULL;
	//worker = new employee(1, "zhangsan", 1);
	//worker->show_info();
	//delete worker;

	//worker = new manager(2, "lisi", 2);
	//worker->show_info();
	//delete worker;

	//worker = new boss(3, "wangwu", 3);
	//worker->show_info();
	//delete worker;

	//实例化管理者对象
	workerManager wm;

	int choice = 0;//存储用户选项
	while (true)
	{
		wm.show_menu();
		cout << "请输入你的选择：" << endl;
		cin >> choice;

		switch (choice)
		{
		case 0: // exit
			wm.exitsystem();
			break;
		case 1: // add
			wm.addEmp();
			break;
		case 2: // show
			wm.show_Emp();
			break; 
		case 3: // delete
			wm.Del_Emp();
			break;
		case 4: // revise
			wm.Mod_Emp();
			break;
		case 5: // search
			wm.Find_Emp();
			break;
		case 6: // sort
			wm.sort_Emp();
			break;
		case 7: // clear
			wm.clean_file();
			break;
		default:
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}