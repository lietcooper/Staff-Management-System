#include"employee.h"

employee::employee(int id, string name, int dID, string gender, string birth, string pstatus, string email)
{
	this->m_ID = id;
	this->m_name = name;
	this->m_depID = dID;
	this->m_gender = gender;
	this->m_birth = birth;
	this->m_pstatus = pstatus;
	this->m_email = email;
}

void employee::show_info()
{
	cout << "ID：" << this->m_ID
		<< "\tName：" << this->m_name
		<< "\tGender：" << this->m_gender
		<< "\tPosition：" << this->get_depname()
		<< "\t岗位职责：完成经理交付的任务" 
		<< "\tBirthday：" << this->m_birth
		<< "\tPolitics Status：" << this->m_pstatus
		<< "\tEmail：" << this->m_email << endl;
}

string employee::get_depname()
{
	return string ("员工");

}