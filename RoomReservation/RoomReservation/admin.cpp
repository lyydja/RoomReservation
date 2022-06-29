#include "admin.h"


Admin::Admin() {

}

//�вι���
Admin::Admin(string name, string pwd) {
	this->m_name = name;
	this->m_passWd = pwd;

	//��ʼ������
	this->InitVector();

	//��ʼ��������Ϣ
	ifstream ifs;
	ifs.open(COMPUTERROOM_FILE, ios::in);
	ComputerRoom com;
	while (ifs >> com.m_ComId && ifs >> com.m_maxNum) {
		m_vCom.emplace_back(com);
	}
	ifs.close();
}

//�˵�����
void Admin::OperMenu() {
	cout << endl;
	cout << "��ӭ����Ա��" << this->m_name << "��¼��" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          1.����˺�              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          2.�鿴�˺�              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          3.�鿴����              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          4.���ԤԼ              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          0.ע����¼              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "��ѡ�����Ĳ����� " << endl;
}

//����˺�
void Admin::AddPerson() {
	cout << "����������˺�����" << endl;
	cout << "1�����ѧ���˺�" << endl;
	cout << "2����ӽ�ʦ�˺�" << endl;

	string fileName;	//�����ļ���
	string tip;			//��ʾid��
	string errorTip;	//�ظ�������ʾ

	/****************����˺�*******************/
	ofstream ofs;

	int option = 0;
	cin >> option;
	while (cin.fail()) {
		cin.clear();
		cin.ignore();
		cout << "�����ʽ��������������" << endl;
		cin >> option;
	}
	if (option == 1) {
		fileName = STUDENT_FILE;
		tip = "������ѧ�ţ�";
		errorTip = "ѧ���ظ�������������";
	}
	else if (option == 2) {
		fileName = TEACHER_FILE;
		tip = "������ְ����ţ�";
		errorTip = "ְ�����ظ�������������";
	}

	ofs.open(fileName, ios::out | ios::app);

	int id;			//ѧ�Ż�ְ����
	string name;	//����
	string pwd;		//����

	cout << tip << endl;
	while (true) {
		cin >> id;
		//����˺��Ƿ��ظ�
		bool ret = CheckRepeat(id, option);
		//����˺��ظ�
		if (ret) {
			cout << errorTip << endl;
		}
		//����˺Ų��ظ�
		else {
			break;
		}
	}

	cout << "������������" << endl;
	cin >> name;
	cout << "���������룺" << endl;
	cin >> pwd;

	//���ļ����������
	ofs << id << " " << name << " " << pwd << endl;
	cout << "��ӳɹ�" << endl;

	ofs.close();
	/********************************************/

	system("pause");
	system("cls");

	//��������������
	this->InitVector();
}

//�鿴�˺�
void Admin::ShowPerson() {
	cout << "��ѡ��鿴����(����ѡ��Ϊ�˳�)��" << endl;
	cout << "1���鿴����ѧ��" << endl;
	cout << "2���鿴���н�ʦ" << endl;

	int option = 0;
	cin >> option;
	while (cin.fail()) {
		cin.clear();
		cin.ignore();
		cout << "�����ʽ��������������" << endl;
		cin >> option;
	}

	if (option == 1) {
		cout << "����ѧ����Ϣ���£�" << endl;
		for (vector<Student>::iterator it = m_vStu.begin(); it != m_vStu.end(); it++) {
			cout << "ѧ�ţ�" << it->m_id << "\t������" << it->m_name << "\t���룺" << it->m_passWd << endl;
		}
	}
	else if (option == 2) {
		cout << "���н�ʦ��Ϣ���£�" << endl;
		for (vector<Teacher>::iterator it = m_vTea.begin(); it != m_vTea.end(); it++) {
			cout << "ְ���ţ�" << it->m_empId << "\t������" << it->m_name << "\t���룺" << it->m_passWd << endl;
		}
	}
	
	system("pause");
	system("cls");
}

//��ʾ������Ϣ
void Admin::ShowComputerRoom() {
	cout << "������Ϣ���£�" << endl;

	for (vector<ComputerRoom>::iterator it = m_vCom.begin(); it != m_vCom.end(); it++) {
		cout << "������ţ�" << it->m_ComId << "\t���������" << it->m_maxNum << endl;
	}
	system("pause");
	system("cls");
}

//���ԤԼ
void Admin::CleanOrder() {
	ofstream ofs(ORDER_FILE, ios::trunc);
	ofs.close();

	cout << "��ճɹ���" << endl;
	system("pause");
	system("cls");
}

bool Admin::CheckRepeat(int id, int option) {

	//ѧ��
	if (option == 1) {
		for (vector<Student>::iterator it = m_vStu.begin(); it != m_vStu.end(); it++) {
			if (id == it->m_id)	return true;
		}
	}
	//��ʦ
	else if (option == 2) {
		for (vector<Teacher>::iterator it = m_vTea.begin(); it != m_vTea.end(); it++) {
			if (id == it->m_empId)	return true;
		}
	}

	//���û���ظ����˺�
	return false;
}

//��ʼ�������ӿ�
void Admin::InitVector() {
	//��վ�����
	m_vStu.clear();
	m_vTea.clear();

	/*******************��ȡ������*******************/
	//��ȡѧ������
	ifstream ifs;
	
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "�ļ���ȡʧ��" << endl;
		return;
	}

	Student s;
	while (ifs >> s.m_id && ifs >> s.m_name && ifs >> s.m_passWd) {
		m_vStu.emplace_back(s);
	}
	ifs.close();

	//��ȡ��ʦ����
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "�ļ���ȡʧ��" << endl;
		return;
	}

	Teacher t;
	while (ifs >> t.m_empId && ifs >> t.m_name && ifs >> t.m_passWd) {
		m_vTea.emplace_back(t);
	}
	ifs.close();
	/************************************************/
}