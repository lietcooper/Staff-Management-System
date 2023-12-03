#pragma once//��ֹͷ�ļ��ظ�����
#include<iostream>
using namespace std; //ʹ�ñ�׼�����ռ�
#include"worker.h"
#include"employee.h"
#include"boss.h"
#include"manager.h"
#include<fstream>
#include<stdlib.h>
#define FILENAME "empFile.txt"



class workerManager
{
public:

	workerManager();//���캯��

	//չʾ�˵�
	void show_menu();

	//�˳�ϵͳ
	void exitsystem();

	~workerManager();//��������
	
	//��¼ְ������
	int m_EmpNum;

	//ְ����ָ�������ָ��
	worker** m_EmpArray;

	//���ְ��
	void addEmp();

	//�����ļ�
	void save();

	//�ж��ļ��Ƿ�Ϊ��
	bool m_FileIsEmpty;

	//ͳ���ļ�������
	int get_EmpNum();

	//��ʼ��Ա��
	void init_Emp();

	//��ʾԱ��
	void show_Emp();

	//ɾ��ְ��
	void Del_Emp();

	//�жϴ���
	int IsExist(int id);

	//�޸�ְ��
	void Mod_Emp();

	//����ְ��
	void Find_Emp();

	//��ְ���������
	void sort_Emp();

	//�������
	void clean_file();
};