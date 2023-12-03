#include"workerManager.h"

workerManager::workerManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	
	//1、文件不存在
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		//初始化属性
		//初始化记录人数
		this->m_EmpNum = 0;
		//初始化数组指针
		this->m_EmpArray = NULL;
		//初始化文件是否为空
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	//2、文件存在 数据为空
	if (ifs.eof())
	{
		//文件为空
		cout << "文件为空" << endl;
	}

	//3、文件存在且及记录数据
	int num = this->get_EmpNum();
	cout << "职工人数为：" << num << endl;
	this->m_EmpNum = num;

	//开辟空间
	this->m_EmpArray = new worker * [this->m_EmpNum];
	//将文件中数据存到数组中
	this->init_Emp();

	//测试代码：
	/*for (int i = 0; i < this->m_EmpNum; i++)
	{
		cout << "职工编号：" << this->m_EmpArray[i]->m_ID
			<< "姓名:" << this->m_EmpArray[i]->m_name
			<< "部门编号：" << this->m_EmpArray[i]->m_depID << endl;
	}*/
}



void workerManager::show_menu()
{
	cout << "0 -- 退出" << endl;
	cout << "1 --增加职工" << endl;
	cout << "2 --显示所有职工信息" << endl;
	cout << "3 --删除职工" << endl;
	cout << "4 --修改职工信息" << endl;
	cout << "5 --查找职工" << endl;
	cout << "6 --按职工编号进行排序" << endl;
	cout << "7 --清空文档" << endl;
	cout << endl;
		
}

void workerManager::exitsystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0); //退出程序
}

void workerManager::addEmp()
{
	cout << "输入添加职工数量：" << endl;
	int addNum = 0;
	cin >> addNum;
	if (addNum > 0)
	{
		//添加
		//计算添加新空间大小
		int newSize = this->m_EmpNum + addNum;//进空间人数=原来人数+新增人数

		//开辟新空间
		worker** newSpace = new worker* [newSize];

		//将原来空间下数据拷贝到新空间
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//批量添加数据
		for (int i = 0; i < addNum; i++)
		{
			int id;    //职工编号
			string name; //职工姓名
			int dselect; //部门选择
			string gender; //性别选择
			string birth; //生日
			string pstatus; //政治面貌
			string email; //邮箱

			FLAG:
			cout << "请输入第" << i + 1 << "个新职工编号：" << endl;
			cin >> id;
			for (int idx = 0; idx < this->m_EmpNum + i; ++idx) {
				if (newSpace[idx]->m_ID == id) {
					cout << "该编号已存在，请重新输入：" << endl;
					goto FLAG;
				}
			}
			cout << "请输入第" << i + 1 << "个新职工姓名：" << endl;
			cin >> name;
			cout << "请输入第" << i + 1 << "个新职工岗位：" << endl;
			cout << "1、普通员工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> dselect;
			cout << "请输入第" << i + 1 << "个新职工性别：男 / 女" << endl;
			cin >> gender;
			cout << "请输入第" << i + 1 << "个新职工生日：yyyy-MM-dd" << endl;
			cin >> birth;
			cout << "请输入第" << i + 1 << "个新职工政治面貌：" << endl;
			cin >> pstatus;
			cout << "请输入第" << i + 1 << "个新职工邮箱：" << endl;
			cin >> email;

			worker* worker = NULL; //初始化worker类型指针，在下面根据dID指向子类对象
			switch (dselect)
			{
			case 1:
				worker = new employee(id, name, 1,gender, birth, pstatus, email);
				break;
			case 2:
				worker = new manager(id, name, 2, gender, birth, pstatus, email);
				break;
			case 3:
				worker = new boss(id, name, 3, gender, birth, pstatus, email);
				break;
			default:
				break;
			}
			//将创建职工职责，保存到数组中
			newSpace[this->m_EmpNum + i] = worker; //用指针数组记录指针
		}
		//释放原有空间
		delete[] this->m_EmpArray; //释放数组

		//更改新空间指向
		this->m_EmpArray = newSpace;

		//更新新的职工人数
		this->m_EmpNum = newSize;

		//更新职工不为空标志
		this->m_FileIsEmpty = false;
		//提示添加成功
		cout << "添加成功" << addNum << "名新职工！" << endl;

		//保存数据到文件中
		this->save();
	}
	else
	{
		cout << "添加有误。" << endl;
	}
	//按任意键后清屏回到上级目录
	system("pause");
	system("cls");
}

void workerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	//将每个人数据写入文件
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_ID << " "
			<< this->m_EmpArray[i]->m_name << " "
			<< this->m_EmpArray[i]->m_gender << " "
			<< this->m_EmpArray[i]->m_depID << " "
			<< this->m_EmpArray[i]->m_birth << " "
			<< this->m_EmpArray[i]->m_pstatus << " "
			<< this->m_EmpArray[i]->m_email<< endl;
	}
	//关闭文件
	ofs.close();
	system("python D:\\Programming\\C++\\staff-management-txt\\toExcel.py");
}

int workerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	string gender;
	int dID;
	string birth;
	string pstatus;
	string email;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> gender && ifs >> dID && ifs >> birth && ifs >> pstatus && ifs >> email)
	{
		//统计人数变量
		num++;
	}
	return num;
}

void workerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	string gender;
	int dID;
	string birth;
	string pstatus;
	string email;


	int index = 0;

	while (ifs >> id && ifs >> name && ifs >> gender && ifs >> dID && ifs >> birth && ifs >> pstatus && ifs >> email)
	{
		worker* worker = NULL;
		if (dID == 1)//普通员工
		{
			worker = new employee(id, name, dID, gender, birth, pstatus, email);
		}
		else if (dID == 2)//经理
		{
			worker = new manager(id, name, dID, gender, birth, pstatus, email);
		}
		else //老板
		{
			worker = new boss(id, name, dID, gender, birth, pstatus, email);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}

	ifs.close();
}

void workerManager::show_Emp()
{
	//判断文件是否为空
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空!" << endl;
	}
	else
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			//利用多态用程序借口
			this->m_EmpArray[i]->show_info();
		}
	}

	system("pause");
	system("cls");
}

int workerManager::IsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_ID == id)
		{
			//找到职工
			index = i;
			break;
		}
	}
	return index;
}

void workerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		//按照职工号删除
		cout << "请输入想要删除的职工编号" << endl;
		int id = 0;
		cin >> id;

		int index = this->IsExist(id);
		if (index != -1)//说明员工存在并且要删除掉index位置员工
		{
			//数据迁移
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1]; // 不能delete，数据是连续的，delete则会有一个nullptr
			}
			this->m_EmpNum--;//更新数组中记录人员个数
			//数据同步到更新文件
			this->save();

			cout << "删除成功" << endl;
		}
		else
		{
			cout << "删除失败，未找到该职工" << endl;
		}
	}
	system("pause");
	system("cls");
}

void workerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		cout << "请修改职工的编号:" << endl;
		int id;
		cin >> id;
		int ret = this->IsExist(id);
		if (ret != -1)
		{
			//找到编号的职工，并输出信息
			cout << "查到：" << id << " 号职工；请输入新职工号" << endl;
			this->m_EmpArray[ret]->show_info();

			//获取除岗位外的信息
			int id = this->m_EmpArray[ret]->m_ID;
			string name = this->m_EmpArray[ret]->m_name;
			string gender = this->m_EmpArray[ret]->m_gender;
			string birth = this->m_EmpArray[ret]->m_birth;
			string pstatus = this->m_EmpArray[ret]->m_pstatus;
			string email = this->m_EmpArray[ret]->m_email;

			cout << "请选择要更改的信息：" << endl;
			cout << "1、岗位" << endl;
			cout << "2、职工号" << endl;
			cout << "3、姓名" << endl; // 判断修改后的职工号是否存在
			cout << "4、性别" << endl;
			cout << "5、生日" << endl;
			cout << "6、政治面貌" << endl;
			cout << "7、邮箱" << endl;
			int item_select = 0;
			cin >> item_select;

			//case中定义新变量要用 {代码块} 包起来 
			switch (item_select)
			{
			case 1:
				{
					delete this->m_EmpArray[ret];
					worker* worker = NULL;
					int pos;
					cout << "请输入岗位：" << endl;
					cout << "1、普通员工" << endl;
					cout << "2、经理" << endl;
					cout << "3、老板" << endl;
					cin >> pos;
					switch (pos) {
					case 1:
						worker = new employee(id, name, 1, gender, birth, pstatus, email);
						break;
					case 2:
						worker = new manager(id, name, 2, gender, birth, pstatus, email);
						break;
					case 3:
						worker = new boss(id, name, 3, gender, birth, pstatus, email);
						break;
					default:
						break;
					}
					this->m_EmpArray[ret] = worker;
					break;
				}
			case 2:
				{
					int newId = 0;
					cout << "请输入新编号：";
					cin >> newId;
					this->m_EmpArray[ret]->m_ID = newId;
					break;
				}
			case 3:
				{
					string newName;
					cout << "请更改姓名：";
					cin >> newName;
					this->m_EmpArray[ret]->m_name = newName;
					break;
				}
			case 4:
				{
					string newGender;
					cout << "请更改性别：";
					cin >> newGender;
					this->m_EmpArray[ret]->m_gender = newGender;
					break; 
				}
			case 5:
				{
					string newBirth;
					cout << "请更改生日：";
					cin >> newBirth;
					this->m_EmpArray[ret]->m_birth = newBirth;
					break;
				}
			case 6:
				{
					string newPstatus;
					cout << "请更改政治面貌：";
					cin >> newPstatus;
					this->m_EmpArray[ret]->m_pstatus = newPstatus;
					break;
				}
			case 7:
				{
					string newEmail;
					cout << "请更改邮箱：";
					cin >> newEmail;
					this->m_EmpArray[ret]->m_email = newEmail;
					break;
				}
			default:
				break;
			}

			cout << "修改成功！" << endl;

			//保存到文件中
			this->save();
		}
		else
		{
			cout << "修改失败，查无此人" << endl;
		}
	}
	system("pause");
	system("cls");
}

void workerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入查找方式:" << endl;
		cout << "1、按职工编号查找" << endl;
		cout << "2、按职工姓名查找" << endl;

		int select = 0;
		cin >> select;

		if (select == 1)
		{
			//按编号
			int id;
			cout << "输入查找的职工编号：" << endl;
			cin >> id;

			int ret = IsExist(id);
			if (ret != -1)
			{
				//找到职工
				cout << "查找职工！该职工信息如下：" << endl;
				this->m_EmpArray[ret]->show_info();
			}
			else
			{
				cout << "查无此人" << endl;
			}
		}
		else if (select == 2)
		{
			//按姓名查找
			string name;
			cout << "请输入查找姓名" << endl;
			cin >> name;
			
			//加入判断是否查到的标志
			bool flag = false;//默认未找到职工

			for (int i = 0; i < m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_name == name)
				{
					cout << "查找成功，职工编号为：" << this->m_EmpArray[i]->m_ID 
						<< "号职工信息如下：" << endl;

					flag = true;

					//调用信息接口
					this->m_EmpArray[i]->show_info();
				}
			}
			if (flag == false)
			{
				cout << "查找失败，查无此人！" << endl;
			}
		}
		else
		{
			cout << "输入选项有误！" << endl;
		}
	}
	system("pause");
	system("cls");
}

void workerManager::sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序方式" << endl;
		cout << "1、升序" << endl;
		cout << "2、降序" << endl;

		int select = 0;
		cin >> select;
		for (int i = 0; i< m_EmpNum; i++)
		{
			int minOrMax = i;//声明 最小值 或 最大值 下标
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1) //升序
				{
					if (this->m_EmpArray[minOrMax]->m_ID > this->m_EmpArray[j]->m_ID)
					{
						minOrMax = j;
					}
				}
				else //降序
				{
					if (this->m_EmpArray[minOrMax]->m_ID < this->m_EmpArray[j]->m_ID)
					{
						minOrMax = j;
					}
				}
			}

			//判断一开始认定的最小值或最大值是不是计算的最小值或最大值
			if (i != minOrMax)
			{
				worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
				this->m_EmpArray[minOrMax] = temp;
			}
		}

		cout << "排序成功！排序后的结果为：" << endl;
		this->save();//排序后结果保存到文件
		this->show_Emp();//展示所有的职工
	}
}

void workerManager::clean_file()
{
	cout << "是否清空?" << endl;
	cout << "1、yes" << endl;
	cout << "2、no" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		//清空文件
		ofstream ofs(FILENAME, ios::trunc);//删除文件后重新创建
		ofs.close();

		if (this->m_EmpArray != NULL)
		{
			//删除堆区的每个职工对象
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}
			//删除堆区的数组指针
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "清空成功" << endl;
	}
	system("pause");
	system("cls");
}

workerManager::~workerManager()
{
	
}