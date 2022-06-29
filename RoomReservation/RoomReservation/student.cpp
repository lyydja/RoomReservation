#include "student.h"
using namespace std;


Student::Student(int id, string name, string passWd) {
	//��ʼ������
	this->m_id = id;
	this->m_name = name;
	this->m_passWd = passWd;

	//��ʼ��������Ϣ
	ifstream ifs;
	ifs.open(COMPUTERROOM_FILE, ios::in);

	ComputerRoom com;
	while (ifs >> com.m_ComId && ifs >> com.m_maxNum) {
		m_comRoom.push_back(com);
	}
	ifs.close();
}

//�˵�����
void Student::OperMenu() {
	cout << endl;
	cout << "��ӭѧ������" << this->m_name << "��¼��" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          1.����ԤԼ              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          2.�鿴�ҵ�ԤԼ          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          3.�鿴����ԤԼ          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          4.ȡ��ԤԼ              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          0.ע����¼              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "��ѡ�����Ĳ����� " << endl;
}

//����ԤԼ
void Student::ApplyOrder() {
	cout << "��������ʱ��Ϊ��һ������" << endl;
	cout << "����������ԤԼ��ʱ�䣺" << endl;
	cout << "1����һ" << endl;
	cout << "2���ܶ�" << endl;
	cout << "3������" << endl;
	cout << "4������" << endl;
	cout << "5������" << endl;

	int date = 0;		//����
	int interval = 0;	//ʱ���
	int room = 0;		//�������

	while (true) {
		cin >> date;
		if (date >= 1 && date <= 5) {
			break;
		}
		//��������д���
		cout << "�����д�������������" << endl;
		//������뻺����,��ֹ�����ֵ�����д�
		cin.clear();
		cin.ignore();
	}

	cout << "����������ԤԼʱ��Σ�" << endl;
	cout << "1������" << endl;
	cout << "2������" << endl;
	while (true) {
		cin >> interval;
		if (interval >= 1 && interval <= 2) {
			break;
		}
		//��������д���
		cout << "�����д�������������" << endl;
		//������뻺����,��ֹ�����ֵ�����д�
		cin.clear();
		cin.ignore();
	}

	cout << "��ѡ�������" << endl;
	for (int i = 0; i < m_comRoom.size(); i++) {
		cout << m_comRoom[i].m_ComId << "�Ż�������Ϊ��"
			<< m_comRoom[i].m_maxNum << endl;
	}
	while (true) {
		cin >> room;
		if (room >= 1 && room <= m_comRoom.size()) {
			break;
		}
		//��������д���
		cout << "�����д�������������" << endl;
		//������뻺����,��ֹ�����ֵ�����д�
		cin.clear();
		cin.ignore();
	}

	cout << "ԤԼ�ɹ����ȴ������" << endl;

	//�������ļ���
	ofstream ofs;
	ofs.open(ORDER_FILE, ios::app);

	ofs << "date:" << date << " "
		<< "interval:" << interval << " "
		<< "stuId:" << this->m_id << " "
		<< "stuName:" << this->m_name << " "
		<< "roomId:" << room << " "
		<< "status:" << 1 << endl;		// 1 �����  2 ��ԤԼ  -1 ԤԼʧ��  0 ȡ��ԤԼ
	ofs.close();

	system("pause");
	system("cls");	
}

//��ʾ�����ԤԼ
void Student::ShowOrder() {
	OrderFile of;

	if (of.m_size == 0) {
		cout << "��ԤԼ��¼!" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < of.m_size; i++) {
		if (this->m_id == atoi(of.m_orderData[i]["stuId"].c_str())) {
			cout << "ԤԼ���ڣ���" << of.m_orderData[i]["date"];
			cout << " ʱ��Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");
			cout << " �����ţ�" << of.m_orderData[i]["roomId"];
			string status = " ״̬��";
			// 1 �����  2 ��ԤԼ  -1 ԤԼʧ��  0 ȡ��ԤԼ
			if ("1" == of.m_orderData[i]["status"]) {
				status += "�����";
			}
			else if ("2" == of.m_orderData[i]["status"]) {
				status += "ԤԼ�ɹ�";
			}
			else if("-1" == of.m_orderData[i]["status"]) {
				status += "ԤԼʧ��";
			}
			else {
				status += "ԤԼ��ȡ��";
			}
			cout << status << endl;
		}
	}

	system("pause");
	system("cls");
}

//��ʾ���е�ԤԼ
void Student::ShowAllOrder() {
	OrderFile of;

	if (of.m_size == 0) {
		cout << "��ԤԼ��¼!" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < of.m_size; i++) {
		cout << i + 1 << "�� ";
		cout << "ԤԼ���ڣ���" << of.m_orderData[i]["date"];
		cout << " ʱ��Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");
		cout << " �����ţ�" << of.m_orderData[i]["roomId"];
		string status = " ״̬��";
		// 1 �����  2 ��ԤԼ  -1 ԤԼʧ��  0 ȡ��ԤԼ
		if ("1" == of.m_orderData[i]["status"]) {
			status += "�����";
		}
		else if ("2" == of.m_orderData[i]["status"]) {
			status += "ԤԼ�ɹ�";
		}
		else if ("-1" == of.m_orderData[i]["status"]) {
			status += "ԤԼʧ��";
		}
		else {
			status += "ԤԼ��ȡ��";
		}
		cout << status << endl;
	}

	system("pause");
	system("cls");
}

//ȡ�������ԤԼ��ԤԼ�ɹ�������е�ԤԼ����ȡ��ԤԼ
void Student::CancelOrder() {
	
	//��ȡ��������л�ԤԼ�ɹ���ԤԼ��¼
	OrderFile of;
	if (of.m_size == 0) {
		cout << "��ԤԼ��¼!" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "����л�ԤԼ�ɹ��ļ�¼����ȡ��������ȡ���ļ�¼���£�" << endl;
	vector<int> v; //��ſ���ȡ����ԤԼ��¼��OrderFile�е�����
	int index = 1;
	for (int i = 0; i < of.m_size; i++) {
		//��ʾ����ԤԼ
		if (this->m_id == atoi(of.m_orderData[i]["stuId"].c_str())) {
			//��ʾԤԼ�ɹ�������е�ԤԼ
			if (("1" == of.m_orderData[i]["status"]) || ("2" == of.m_orderData[i]["status"])) {
				v.emplace_back(i);
				cout << index++ << "��";
				cout << "ԤԼ���ڣ���" << of.m_orderData[i]["date"];
				cout << " ʱ��Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");
				cout << " �����ţ�" << of.m_orderData[i]["roomId"];
				string status = " ״̬��";
				// 1 �����  2 ��ԤԼ  -1 ԤԼʧ��  0 ȡ��ԤԼ
				if ("1" == of.m_orderData[i]["status"]) {
					status += "�����";
				}
				else if ("2" == of.m_orderData[i]["status"]) {
					status += "ԤԼ�ɹ�";
				}
				cout << status << endl;
			}
		}
	}

	if (index == 1) {
		cout << "-----�޿�ȡ����¼-----" << endl;
		cout << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "������ȡ���ļ�¼��0������" << endl;
	int option = 0;
	while (true) {
		cin >> option;

		if (option >= 0 && option <= v.size()) {
			//����
			if (option == 0) {
				
				break;
			}
			else {
				of.m_orderData[v[option - 1]]["status"] = "0";
				of.UpdateOrder(); //���¼�¼
				cout << "��ȡ��ԤԼ" << endl;
				break;
			}
		}
		cout << "������������������" << endl;
		//������뻺����,��ֹ�����ֵ�����д�
		cin.clear();
		cin.ignore();
	}
	system("pause");
	system("cls");
}