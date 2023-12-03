#include"manager.h"

manager::manager(int id, string name, int dID, string gender, string birth, string pstatus, string email)
{
	this->m_ID = id;
	this->m_name = name;
	this->m_depID = dID;
	this->m_gender = gender;
	this->m_birth = birth;
	this->m_pstatus = pstatus;
	this->m_email = email;
}

void manager::show_info()//显示个人信息
{
	cout << "ID：" << this->m_ID
		<< "\tName：" << this->m_name
		<< "\tGender：" << this->m_gender
		<< "\tPosition：" << this->get_depname()
		<< "\tDuty：完成老板交付的任务并下发任务"
		<< "\tBirthday：" << this->m_birth
		<< "\tPolitics Status：" << this->m_pstatus
		<< "\tEmail：" << this->m_email << endl;
}

string manager::get_depname()//获取岗位名称
{
	return string("经理");
}

