#include"boss.h"

boss::boss(int id, string name, int dID, string gender, string birth, string pstatus, string email)
{
	this->m_ID = id;
	this->m_name = name;
	this->m_depID = dID;
	this->m_gender = gender;
	this->m_birth = birth;
	this->m_pstatus = pstatus;
	this->m_email = email;
}


void boss::show_info()//��ʾ������Ϣ
{
	cout << "ID��" << this->m_ID
		<< "\tName��" << this->m_name
		<< "\tGender��" << this->m_gender
		<< "\tPosition��" << this->get_depname()
		<< "\t��λְ�𣺹���˾" 
		<< "\tBirthday��" << this->m_birth
		<< "\tPolitics Status��" << this->m_pstatus
		<< "\tEmail��" << this->m_email << endl;
}		

string boss::get_depname()//��ȡ��λ����
{
	return string("�ϰ�");
}

