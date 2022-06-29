#include "admin.h"


Admin::Admin() {

}

//有参构造
Admin::Admin(string name, string pwd) {
	this->m_name = name;
	this->m_passWd = pwd;

	//初始化容器
	this->InitVector();

	//初始化机房信息
	ifstream ifs;
	ifs.open(COMPUTERROOM_FILE, ios::in);
	ComputerRoom com;
	while (ifs >> com.m_ComId && ifs >> com.m_maxNum) {
		m_vCom.emplace_back(com);
	}
	ifs.close();
}

//菜单界面
void Admin::OperMenu() {
	cout << endl;
	cout << "欢迎管理员：" << this->m_name << "登录！" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          1.添加账号              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          2.查看账号              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          3.查看机房              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          4.清空预约              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          0.注销登录              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "请选择您的操作： " << endl;
}

//添加账号
void Admin::AddPerson() {
	cout << "请输入添加账号类型" << endl;
	cout << "1、添加学生账号" << endl;
	cout << "2、添加教师账号" << endl;

	string fileName;	//操作文件名
	string tip;			//提示id号
	string errorTip;	//重复错误提示

	/****************添加账号*******************/
	ofstream ofs;

	int option = 0;
	cin >> option;
	while (cin.fail()) {
		cin.clear();
		cin.ignore();
		cout << "输入格式有误，请重新输入" << endl;
		cin >> option;
	}
	if (option == 1) {
		fileName = STUDENT_FILE;
		tip = "请输入学号：";
		errorTip = "学号重复，请重新输入";
	}
	else if (option == 2) {
		fileName = TEACHER_FILE;
		tip = "请输入职工编号：";
		errorTip = "职工号重复，请重新输入";
	}

	ofs.open(fileName, ios::out | ios::app);

	int id;			//学号或职工号
	string name;	//姓名
	string pwd;		//密码

	cout << tip << endl;
	while (true) {
		cin >> id;
		//检查账号是否重复
		bool ret = CheckRepeat(id, option);
		//如果账号重复
		if (ret) {
			cout << errorTip << endl;
		}
		//如果账号不重复
		else {
			break;
		}
	}

	cout << "请输入姓名：" << endl;
	cin >> name;
	cout << "请输入密码：" << endl;
	cin >> pwd;

	//向文件中添加数据
	ofs << id << " " << name << " " << pwd << endl;
	cout << "添加成功" << endl;

	ofs.close();
	/********************************************/

	system("pause");
	system("cls");

	//更新容器的数据
	this->InitVector();
}

//查看账号
void Admin::ShowPerson() {
	cout << "请选择查看内容(其他选项为退出)：" << endl;
	cout << "1、查看所有学生" << endl;
	cout << "2、查看所有教师" << endl;

	int option = 0;
	cin >> option;
	while (cin.fail()) {
		cin.clear();
		cin.ignore();
		cout << "输入格式有误，请重新输入" << endl;
		cin >> option;
	}

	if (option == 1) {
		cout << "所有学生信息如下：" << endl;
		for (vector<Student>::iterator it = m_vStu.begin(); it != m_vStu.end(); it++) {
			cout << "学号：" << it->m_id << "\t姓名：" << it->m_name << "\t密码：" << it->m_passWd << endl;
		}
	}
	else if (option == 2) {
		cout << "所有教师信息如下：" << endl;
		for (vector<Teacher>::iterator it = m_vTea.begin(); it != m_vTea.end(); it++) {
			cout << "职工号：" << it->m_empId << "\t姓名：" << it->m_name << "\t密码：" << it->m_passWd << endl;
		}
	}
	
	system("pause");
	system("cls");
}

//显示机房信息
void Admin::ShowComputerRoom() {
	cout << "机房信息如下：" << endl;

	for (vector<ComputerRoom>::iterator it = m_vCom.begin(); it != m_vCom.end(); it++) {
		cout << "机房编号；" << it->m_ComId << "\t最大容量：" << it->m_maxNum << endl;
	}
	system("pause");
	system("cls");
}

//清空预约
void Admin::CleanOrder() {
	ofstream ofs(ORDER_FILE, ios::trunc);
	ofs.close();

	cout << "清空成功！" << endl;
	system("pause");
	system("cls");
}

bool Admin::CheckRepeat(int id, int option) {

	//学生
	if (option == 1) {
		for (vector<Student>::iterator it = m_vStu.begin(); it != m_vStu.end(); it++) {
			if (id == it->m_id)	return true;
		}
	}
	//教师
	else if (option == 2) {
		for (vector<Teacher>::iterator it = m_vTea.begin(); it != m_vTea.end(); it++) {
			if (id == it->m_empId)	return true;
		}
	}

	//如果没有重复的账号
	return false;
}

//初始化容器接口
void Admin::InitVector() {
	//清空旧数据
	m_vStu.clear();
	m_vTea.clear();

	/*******************获取新数据*******************/
	//获取学生数据
	ifstream ifs;
	
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "文件读取失败" << endl;
		return;
	}

	Student s;
	while (ifs >> s.m_id && ifs >> s.m_name && ifs >> s.m_passWd) {
		m_vStu.emplace_back(s);
	}
	ifs.close();

	//获取教师数据
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "文件读取失败" << endl;
		return;
	}

	Teacher t;
	while (ifs >> t.m_empId && ifs >> t.m_name && ifs >> t.m_passWd) {
		m_vTea.emplace_back(t);
	}
	ifs.close();
	/************************************************/
}