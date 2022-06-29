#include "roomreserv.h"

void RoomReserv::Init() {
	//��ʼ������Ա���˺ź�����
	//�ȶ�ȡ
	ifstream ifs;
	ifs.open(ADMIN_FILE, ios::in);
	//���û�и��ļ����������ļ���������Ĭ�Ϲ���Ա�˺�����
	if (!ifs.is_open()) {
		ifs.close();
		ofstream ofs;
		ofs.open(ADMIN_FILE, ios::out | ios::app);
		ofs << "admin" << " " << "admin" << endl;
		ofs.close();
	}
	//����и��ļ�
	else {
		//����Ƿ����˺�����
		string name;
		string pwd;
		int size = 0;
		while (ifs >> name && ifs >> pwd) {
			size++;
		}
		//���û���˺�����
		if (size == 0) {
			ifs.close();
			ofstream ofs;
			ofs.open(ADMIN_FILE, ios::out | ios::app);
			ofs << "admin" << " " << "admin" << endl;
			ofs.close();
		}
		//������˺�����
		else {
			ifs.close();
		}
	}
	
}
//������
void RoomReserv::ShowMainMenu() {
	cout << endl;
	cout << "====================  ��ӭ��������ԤԼϵͳ  ====================="
		<< endl;
	cout << endl << "�������������" << endl;
	cout << "\t\t -------------------------------\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|          1.ѧ������           |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|          2.��    ʦ           |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|          3.�� �� Ա           |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|          0.��    ��           |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t -------------------------------\n";
	cout << "��������ѡ��: ";
}

//ѧ���Ӳ˵�����
void RoomReserv::StudentMenu(Identity*& student) {
	while (true) {
		student->OperMenu();

		Student* stu = (Student*)student;
		int option = 0;
		cin >> option;

		if (option == 1) { //1.����ԤԼ
			stu->ApplyOrder();
		}
		else if(option == 2) { //2.�鿴�ҵ�ԤԼ
			stu->ShowOrder();
		}
		else if(option == 3) { //3.�鿴����ԤԼ
			stu->ShowAllOrder();
		}
		else if(option == 4) { //4.ȡ��ԤԼ
			stu->CancelOrder();
		}
		else { //0.ע����¼
			delete student;
			//������뻺����,��ֹ�����ֵ�����д�
			cin.clear();
			cin.ignore();
			cout << "ע���ɹ�" << endl;
			/*system("pause");
			system("cls");*/
			return;
		}
	}
}

//��ʦ�Ӳ˵�����
void RoomReserv::TeacherMenu(Identity*& teacher) {
	while (true) {
		teacher->OperMenu();

		Teacher* tea = (Teacher*)teacher;
		int option = 0;
		cin >> option;

		if (option == 1) { //1.�鿴����ԤԼ
			tea->ShowAllOrder();
		}
		else if (option == 2) { //2.���ԤԼ
			tea->ValidOrder();
		}
		else { //0.ע����¼
			delete teacher;
			//������뻺����,��ֹ�����ֵ�����д�
			cin.clear();
			cin.ignore();
			cout << "ע���ɹ�" << endl;
			/*system("pause");
			system("cls");*/
			return;
		}
	}
}

//����Ա�Ӳ˵�����
void RoomReserv::AdminMenu(Identity*& admin) {
	while (true) {
		admin->OperMenu();

		Admin* adm = (Admin*)admin;
		int option = 0;
		cin >> option;

		if (option == 1) { //1.����˺�
			adm->AddPerson();
		}
		else if (option == 2) { //2.�鿴�˺�
			adm->ShowPerson();
		}
		else if (option == 3) { //3.�鿴������Ϣ
			adm->ShowComputerRoom();
		}
		else if (option == 4) { //4.���ԤԼ
			adm->CleanOrder();
		}
		else { //0.ע����¼
			delete admin;
			//������뻺����,��ֹ�����ֵ�����д�
			cin.clear();
			cin.ignore();
			cout << "ע���ɹ�" << endl;
			/*system("pause");
			system("cls");*/
			return;
		}
	}
}

//��½����
void RoomReserv::LoginIn(string fileName, int type) {
	//����ָ�룬����ָ���������
	Identity* person = NULL;

	//���ļ�
	ifstream ifs;
	ifs.open(fileName, ios::in);

	if (!ifs.is_open()) {
		cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}

	//׼�������û�����Ϣ
	int id = 0;
	string name;
	string pwd;

	//���������Ϣ
	if (type == 1) { //ѧ��
		cout << "����������ѧ�ţ�" << endl;
		cin >> id;
		while (cin.fail()) {
			cin.clear();
			cin.ignore();
			cout << "�����ʽ��������������" << endl;
			cin >> id;
		}
	}
	else if (type == 2) { //��ʦ
		cout << "����������ְ���ţ�" << endl;
		cin >> id;
		while (cin.fail()) {
			cin.clear();
			cin.ignore();
			cout << "�����ʽ��������������" << endl;
			cin >> id;
		}
	}
	cout << "�������û�����" << endl;
	cin >> name;
	cout << "���������룺" << endl;
	cin >> pwd;

	//��֤���
	if (type == 1) { //ѧ�������֤
		int fId;		//���ļ��ж�ȡ��id��
		string fName;	//���ļ��ж�ȡ������
		string fPwd;	//���ļ��ж�ȡ������

		//���ļ���һ��һ�еĲ��ҶԱ�
		while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
			//���û��������Ϣ���Ա�
			if (fId == id && fName == name && fPwd == pwd) {
				cout << "ѧ����֤��½�ɹ���" << endl;
				system("pause");
				system("cls");
				person = new Student(id, name, pwd);
				StudentMenu(person); //����ѧ�����Ӳ˵�
				return;
			}
		}
	}
	else if (type == 2) { //��ʦ�����֤
		int fId;		//���ļ��ж�ȡ��id��
		string fName;	//���ļ��ж�ȡ������
		string fPwd;	//���ļ��ж�ȡ������

		//���ļ���һ��һ�еĲ��ҶԱ�
		while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
			//���û��������Ϣ���Ա�
			if (fId == id && fName == name && fPwd == pwd) {
				cout << "��ʦ��֤��½�ɹ���" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name, pwd);
				TeacherMenu(person); //����ѧ�����Ӳ˵�
				return;
			}
		}
	}
	else if (type == 3) { //����Ա�����֤
		string fName;	//���ļ��ж�ȡ������
		string fPwd;	//���ļ��ж�ȡ������

		//���ļ���һ��һ�еĲ��ҶԱ�
		while (ifs >> fName && ifs >> fPwd) {
			//���û��������Ϣ���Ա�
			if (fName == name && fPwd == pwd) {
				cout << "����Ա��֤��½�ɹ���" << endl;
				system("pause");
				system("cls");
				person = new Admin(name, pwd);
				AdminMenu(person); //����ѧ�����Ӳ˵�
				return;
			}
		}
	}

	//����ļ���û�ж�Ӧ���˺��������Ϣ
	cout << "��֤��½ʧ�ܣ�" << endl;
	/*system("pause");
	system("cls");*/

	return;
}

//������
void RoomReserv::Loop() {
	while (true) {
		ShowMainMenu();
		int option;

		cin >> option;

		switch (option) {
		case 0: { //�˳�
			cout << "��ӭʹ�ã��´��ټ���" << endl;
			system("pause");
			system("cls");
			exit(0);
			break;
		}
		case 1: { //ѧ��
			LoginIn(STUDENT_FILE, 1);
			break;
		}
		case 2: { //��ʦ
			LoginIn(TEACHER_FILE, 2);
			break;
		}
		case 3: {
			LoginIn(ADMIN_FILE, 3);
			break;
		}
		default:
			cout << "��������������ѡ��" << endl;
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