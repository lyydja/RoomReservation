#include "roomreserv.h"

void RoomReserv::Init() {
	//初始化管理员的账号和密码
	//先读取
	ifstream ifs;
	ifs.open(ADMIN_FILE, ios::in);
	//如果没有该文件，创建新文件，并创建默认管理员账号密码
	if (!ifs.is_open()) {
		ifs.close();
		ofstream ofs;
		ofs.open(ADMIN_FILE, ios::out | ios::app);
		ofs << "admin" << " " << "admin" << endl;
		ofs.close();
	}
	//如果有该文件
	else {
		//检查是否有账号密码
		string name;
		string pwd;
		int size = 0;
		while (ifs >> name && ifs >> pwd) {
			size++;
		}
		//如果没有账号密码
		if (size == 0) {
			ifs.close();
			ofstream ofs;
			ofs.open(ADMIN_FILE, ios::out | ios::app);
			ofs << "admin" << " " << "admin" << endl;
			ofs.close();
		}
		//如果有账号密码
		else {
			ifs.close();
		}
	}
	
}
//主界面
void RoomReserv::ShowMainMenu() {
	cout << endl;
	cout << "====================  欢迎来到机房预约系统  ====================="
		<< endl;
	cout << endl << "请输入您的身份" << endl;
	cout << "\t\t -------------------------------\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|          1.学生代表           |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|          2.老    师           |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|          3.管 理 员           |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|          0.退    出           |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t -------------------------------\n";
	cout << "输入您的选择: ";
}

//学生子菜单界面
void RoomReserv::StudentMenu(Identity*& student) {
	while (true) {
		student->OperMenu();

		Student* stu = (Student*)student;
		int option = 0;
		cin >> option;

		if (option == 1) { //1.申请预约
			stu->ApplyOrder();
		}
		else if(option == 2) { //2.查看我的预约
			stu->ShowOrder();
		}
		else if(option == 3) { //3.查看所有预约
			stu->ShowAllOrder();
		}
		else if(option == 4) { //4.取消预约
			stu->CancelOrder();
		}
		else { //0.注销登录
			delete student;
			//清空输入缓冲区,防止非数字的输入残存
			cin.clear();
			cin.ignore();
			cout << "注销成功" << endl;
			/*system("pause");
			system("cls");*/
			return;
		}
	}
}

//教师子菜单界面
void RoomReserv::TeacherMenu(Identity*& teacher) {
	while (true) {
		teacher->OperMenu();

		Teacher* tea = (Teacher*)teacher;
		int option = 0;
		cin >> option;

		if (option == 1) { //1.查看所有预约
			tea->ShowAllOrder();
		}
		else if (option == 2) { //2.审核预约
			tea->ValidOrder();
		}
		else { //0.注销登录
			delete teacher;
			//清空输入缓冲区,防止非数字的输入残存
			cin.clear();
			cin.ignore();
			cout << "注销成功" << endl;
			/*system("pause");
			system("cls");*/
			return;
		}
	}
}

//管理员子菜单界面
void RoomReserv::AdminMenu(Identity*& admin) {
	while (true) {
		admin->OperMenu();

		Admin* adm = (Admin*)admin;
		int option = 0;
		cin >> option;

		if (option == 1) { //1.添加账号
			adm->AddPerson();
		}
		else if (option == 2) { //2.查看账号
			adm->ShowPerson();
		}
		else if (option == 3) { //3.查看机房信息
			adm->ShowComputerRoom();
		}
		else if (option == 4) { //4.清空预约
			adm->CleanOrder();
		}
		else { //0.注销登录
			delete admin;
			//清空输入缓冲区,防止非数字的输入残存
			cin.clear();
			cin.ignore();
			cout << "注销成功" << endl;
			/*system("pause");
			system("cls");*/
			return;
		}
	}
}

//登陆功能
void RoomReserv::LoginIn(string fileName, int type) {
	//父类指针，用于指向子类对象
	Identity* person = NULL;

	//读文件
	ifstream ifs;
	ifs.open(fileName, ios::in);

	if (!ifs.is_open()) {
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}

	//准备接受用户的信息
	int id = 0;
	string name;
	string pwd;

	//输入身份信息
	if (type == 1) { //学生
		cout << "请输入您的学号：" << endl;
		cin >> id;
		while (cin.fail()) {
			cin.clear();
			cin.ignore();
			cout << "输入格式有误，请重新输入" << endl;
			cin >> id;
		}
	}
	else if (type == 2) { //教师
		cout << "请输入您的职工号：" << endl;
		cin >> id;
		while (cin.fail()) {
			cin.clear();
			cin.ignore();
			cout << "输入格式有误，请重新输入" << endl;
			cin >> id;
		}
	}
	cout << "请输入用户名；" << endl;
	cin >> name;
	cout << "请输入密码：" << endl;
	cin >> pwd;

	//验证身份
	if (type == 1) { //学生身份验证
		int fId;		//从文件中读取的id号
		string fName;	//从文件中读取的姓名
		string fPwd;	//从文件中读取的密码

		//从文件中一行一行的查找对比
		while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
			//与用户输入的信息做对比
			if (fId == id && fName == name && fPwd == pwd) {
				cout << "学生验证登陆成功！" << endl;
				system("pause");
				system("cls");
				person = new Student(id, name, pwd);
				StudentMenu(person); //进入学生的子菜单
				return;
			}
		}
	}
	else if (type == 2) { //教师身份验证
		int fId;		//从文件中读取的id号
		string fName;	//从文件中读取的姓名
		string fPwd;	//从文件中读取的密码

		//从文件中一行一行的查找对比
		while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
			//与用户输入的信息做对比
			if (fId == id && fName == name && fPwd == pwd) {
				cout << "教师验证登陆成功！" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name, pwd);
				TeacherMenu(person); //进入学生的子菜单
				return;
			}
		}
	}
	else if (type == 3) { //管理员身份验证
		string fName;	//从文件中读取的姓名
		string fPwd;	//从文件中读取的密码

		//从文件中一行一行的查找对比
		while (ifs >> fName && ifs >> fPwd) {
			//与用户输入的信息做对比
			if (fName == name && fPwd == pwd) {
				cout << "管理员验证登陆成功！" << endl;
				system("pause");
				system("cls");
				person = new Admin(name, pwd);
				AdminMenu(person); //进入学生的子菜单
				return;
			}
		}
	}

	//如果文件中没有对应的账号密码等信息
	cout << "验证登陆失败！" << endl;
	/*system("pause");
	system("cls");*/

	return;
}

//主流程
void RoomReserv::Loop() {
	while (true) {
		ShowMainMenu();
		int option;

		cin >> option;

		switch (option) {
		case 0: { //退出
			cout << "欢迎使用，下次再见！" << endl;
			system("pause");
			system("cls");
			exit(0);
			break;
		}
		case 1: { //学生
			LoginIn(STUDENT_FILE, 1);
			break;
		}
		case 2: { //教师
			LoginIn(TEACHER_FILE, 2);
			break;
		}
		case 3: {
			LoginIn(ADMIN_FILE, 3);
			break;
		}
		default:
			cout << "输入有误，请重新选择！" << endl;
			/*system("pause");
			system("cls");*/
			break;
		}
		system("pause");
		system("cls");
	}
	system("pause");
	exit(0);
}