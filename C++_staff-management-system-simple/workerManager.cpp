#include"workerManager.h"

workerManager::workerManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	
	//1���ļ�������
	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;
		//��ʼ������
		//��ʼ����¼����
		this->m_EmpNum = 0;
		//��ʼ������ָ��
		this->m_EmpArray = NULL;
		//��ʼ���ļ��Ƿ�Ϊ��
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	//2���ļ����� ����Ϊ��
	if (ifs.eof())
	{
		//�ļ�Ϊ��
		cout << "�ļ�Ϊ��" << endl;
	}

	//3���ļ������Ҽ���¼����
	int num = this->get_EmpNum();
	cout << "ְ������Ϊ��" << num << endl;
	this->m_EmpNum = num;

	//���ٿռ�
	this->m_EmpArray = new worker * [this->m_EmpNum];
	//���ļ������ݴ浽������
	this->init_Emp();

	//���Դ��룺
	/*for (int i = 0; i < this->m_EmpNum; i++)
	{
		cout << "ְ����ţ�" << this->m_EmpArray[i]->m_ID
			<< "����:" << this->m_EmpArray[i]->m_name
			<< "���ű�ţ�" << this->m_EmpArray[i]->m_depID << endl;
	}*/
}



void workerManager::show_menu()
{
	cout << "0 -- �˳�" << endl;
	cout << "1 --����ְ��" << endl;
	cout << "2 --��ʾ����ְ����Ϣ" << endl;
	cout << "3 --ɾ��ְ��" << endl;
	cout << "4 --�޸�ְ����Ϣ" << endl;
	cout << "5 --����ְ��" << endl;
	cout << "6 --��ְ����Ž�������" << endl;
	cout << "7 --����ĵ�" << endl;
	cout << endl;
		
}

void workerManager::exitsystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0); //�˳�����
}

void workerManager::addEmp()
{
	cout << "�������ְ��������" << endl;
	int addNum = 0;
	cin >> addNum;
	if (addNum > 0)
	{
		//���
		//��������¿ռ��С
		int newSize = this->m_EmpNum + addNum;//���ռ�����=ԭ������+��������

		//�����¿ռ�
		worker** newSpace = new worker* [newSize];

		//��ԭ���ռ������ݿ������¿ռ�
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//�����������
		for (int i = 0; i < addNum; i++)
		{
			int id;    //ְ�����
			string name; //ְ������
			int dselect; //����ѡ��
			string gender; //�Ա�ѡ��
			string birth; //����
			string pstatus; //������ò
			string email; //����

			FLAG:
			cout << "�������" << i + 1 << "����ְ����ţ�" << endl;
			cin >> id;
			for (int idx = 0; idx < this->m_EmpNum + i; ++idx) {
				if (newSpace[idx]->m_ID == id) {
					cout << "�ñ���Ѵ��ڣ����������룺" << endl;
					goto FLAG;
				}
			}
			cout << "�������" << i + 1 << "����ְ��������" << endl;
			cin >> name;
			cout << "�������" << i + 1 << "����ְ����λ��" << endl;
			cout << "1����ͨԱ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			cin >> dselect;
			cout << "�������" << i + 1 << "����ְ���Ա��� / Ů" << endl;
			cin >> gender;
			cout << "�������" << i + 1 << "����ְ�����գ�yyyy-MM-dd" << endl;
			cin >> birth;
			cout << "�������" << i + 1 << "����ְ��������ò��" << endl;
			cin >> pstatus;
			cout << "�������" << i + 1 << "����ְ�����䣺" << endl;
			cin >> email;

			worker* worker = NULL; //��ʼ��worker����ָ�룬���������dIDָ���������
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
			//������ְ��ְ�𣬱��浽������
			newSpace[this->m_EmpNum + i] = worker; //��ָ�������¼ָ��
		}
		//�ͷ�ԭ�пռ�
		delete[] this->m_EmpArray; //�ͷ�����

		//�����¿ռ�ָ��
		this->m_EmpArray = newSpace;

		//�����µ�ְ������
		this->m_EmpNum = newSize;

		//����ְ����Ϊ�ձ�־
		this->m_FileIsEmpty = false;
		//��ʾ��ӳɹ�
		cout << "��ӳɹ�" << addNum << "����ְ����" << endl;

		//�������ݵ��ļ���
		this->save();
	}
	else
	{
		cout << "�������" << endl;
	}
	//��������������ص��ϼ�Ŀ¼
	system("pause");
	system("cls");
}

void workerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	//��ÿ��������д���ļ�
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
	//�ر��ļ�
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
		//ͳ����������
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
		if (dID == 1)//��ͨԱ��
		{
			worker = new employee(id, name, dID, gender, birth, pstatus, email);
		}
		else if (dID == 2)//����
		{
			worker = new manager(id, name, dID, gender, birth, pstatus, email);
		}
		else //�ϰ�
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
	//�ж��ļ��Ƿ�Ϊ��
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��!" << endl;
	}
	else
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			//���ö�̬�ó�����
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
			//�ҵ�ְ��
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
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		//����ְ����ɾ��
		cout << "��������Ҫɾ����ְ�����" << endl;
		int id = 0;
		cin >> id;

		int index = this->IsExist(id);
		if (index != -1)//˵��Ա�����ڲ���Ҫɾ����indexλ��Ա��
		{
			//����Ǩ��
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1]; // ����delete�������������ģ�delete�����һ��nullptr
			}
			this->m_EmpNum--;//���������м�¼��Ա����
			//����ͬ���������ļ�
			this->save();

			cout << "ɾ���ɹ�" << endl;
		}
		else
		{
			cout << "ɾ��ʧ�ܣ�δ�ҵ���ְ��" << endl;
		}
	}
	system("pause");
	system("cls");
}

void workerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		cout << "���޸�ְ���ı��:" << endl;
		int id;
		cin >> id;
		int ret = this->IsExist(id);
		if (ret != -1)
		{
			//�ҵ���ŵ�ְ�����������Ϣ
			cout << "�鵽��" << id << " ��ְ������������ְ����" << endl;
			this->m_EmpArray[ret]->show_info();

			//��ȡ����λ�����Ϣ
			int id = this->m_EmpArray[ret]->m_ID;
			string name = this->m_EmpArray[ret]->m_name;
			string gender = this->m_EmpArray[ret]->m_gender;
			string birth = this->m_EmpArray[ret]->m_birth;
			string pstatus = this->m_EmpArray[ret]->m_pstatus;
			string email = this->m_EmpArray[ret]->m_email;

			cout << "��ѡ��Ҫ���ĵ���Ϣ��" << endl;
			cout << "1����λ" << endl;
			cout << "2��ְ����" << endl;
			cout << "3������" << endl; // �ж��޸ĺ��ְ�����Ƿ����
			cout << "4���Ա�" << endl;
			cout << "5������" << endl;
			cout << "6��������ò" << endl;
			cout << "7������" << endl;
			int item_select = 0;
			cin >> item_select;

			//case�ж����±���Ҫ�� {�����} ������ 
			switch (item_select)
			{
			case 1:
				{
					delete this->m_EmpArray[ret];
					worker* worker = NULL;
					int pos;
					cout << "�������λ��" << endl;
					cout << "1����ͨԱ��" << endl;
					cout << "2������" << endl;
					cout << "3���ϰ�" << endl;
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
					cout << "�������±�ţ�";
					cin >> newId;
					this->m_EmpArray[ret]->m_ID = newId;
					break;
				}
			case 3:
				{
					string newName;
					cout << "�����������";
					cin >> newName;
					this->m_EmpArray[ret]->m_name = newName;
					break;
				}
			case 4:
				{
					string newGender;
					cout << "������Ա�";
					cin >> newGender;
					this->m_EmpArray[ret]->m_gender = newGender;
					break; 
				}
			case 5:
				{
					string newBirth;
					cout << "��������գ�";
					cin >> newBirth;
					this->m_EmpArray[ret]->m_birth = newBirth;
					break;
				}
			case 6:
				{
					string newPstatus;
					cout << "�����������ò��";
					cin >> newPstatus;
					this->m_EmpArray[ret]->m_pstatus = newPstatus;
					break;
				}
			case 7:
				{
					string newEmail;
					cout << "��������䣺";
					cin >> newEmail;
					this->m_EmpArray[ret]->m_email = newEmail;
					break;
				}
			default:
				break;
			}

			cout << "�޸ĳɹ���" << endl;

			//���浽�ļ���
			this->save();
		}
		else
		{
			cout << "�޸�ʧ�ܣ����޴���" << endl;
		}
	}
	system("pause");
	system("cls");
}

void workerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "��������ҷ�ʽ:" << endl;
		cout << "1����ְ����Ų���" << endl;
		cout << "2����ְ����������" << endl;

		int select = 0;
		cin >> select;

		if (select == 1)
		{
			//�����
			int id;
			cout << "������ҵ�ְ����ţ�" << endl;
			cin >> id;

			int ret = IsExist(id);
			if (ret != -1)
			{
				//�ҵ�ְ��
				cout << "����ְ������ְ����Ϣ���£�" << endl;
				this->m_EmpArray[ret]->show_info();
			}
			else
			{
				cout << "���޴���" << endl;
			}
		}
		else if (select == 2)
		{
			//����������
			string name;
			cout << "�������������" << endl;
			cin >> name;
			
			//�����ж��Ƿ�鵽�ı�־
			bool flag = false;//Ĭ��δ�ҵ�ְ��

			for (int i = 0; i < m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_name == name)
				{
					cout << "���ҳɹ���ְ�����Ϊ��" << this->m_EmpArray[i]->m_ID 
						<< "��ְ����Ϣ���£�" << endl;

					flag = true;

					//������Ϣ�ӿ�
					this->m_EmpArray[i]->show_info();
				}
			}
			if (flag == false)
			{
				cout << "����ʧ�ܣ����޴��ˣ�" << endl;
			}
		}
		else
		{
			cout << "����ѡ������" << endl;
		}
	}
	system("pause");
	system("cls");
}

void workerManager::sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ������ʽ" << endl;
		cout << "1������" << endl;
		cout << "2������" << endl;

		int select = 0;
		cin >> select;
		for (int i = 0; i< m_EmpNum; i++)
		{
			int minOrMax = i;//���� ��Сֵ �� ���ֵ �±�
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1) //����
				{
					if (this->m_EmpArray[minOrMax]->m_ID > this->m_EmpArray[j]->m_ID)
					{
						minOrMax = j;
					}
				}
				else //����
				{
					if (this->m_EmpArray[minOrMax]->m_ID < this->m_EmpArray[j]->m_ID)
					{
						minOrMax = j;
					}
				}
			}

			//�ж�һ��ʼ�϶�����Сֵ�����ֵ�ǲ��Ǽ������Сֵ�����ֵ
			if (i != minOrMax)
			{
				worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
				this->m_EmpArray[minOrMax] = temp;
			}
		}

		cout << "����ɹ��������Ľ��Ϊ��" << endl;
		this->save();//����������浽�ļ�
		this->show_Emp();//չʾ���е�ְ��
	}
}

void workerManager::clean_file()
{
	cout << "�Ƿ����?" << endl;
	cout << "1��yes" << endl;
	cout << "2��no" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		//����ļ�
		ofstream ofs(FILENAME, ios::trunc);//ɾ���ļ������´���
		ofs.close();

		if (this->m_EmpArray != NULL)
		{
			//ɾ��������ÿ��ְ������
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}
			//ɾ������������ָ��
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "��ճɹ�" << endl;
	}
	system("pause");
	system("cls");
}

workerManager::~workerManager()
{
	
}