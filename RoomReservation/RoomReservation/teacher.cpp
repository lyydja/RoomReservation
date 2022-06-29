#include "teacher.h"


Teacher::Teacher() {

}

Teacher::Teacher(int id, string name, string pwd) {
	this->m_empId = id;
	this->m_name = name;
	this->m_passWd = pwd;
}
//�˵�����
void Teacher::OperMenu() {
	cout << endl;
	cout << "��ӭ��ʦ��" << this->m_name << "��¼��" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          1.�鿴����ԤԼ          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          2.���ԤԼ              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          0.ע����¼              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "��ѡ�����Ĳ����� " << endl;
}

//��ʾ���е�ԤԼ
void Teacher::ShowAllOrder() {
	OrderFile of;
	if (of.m_size == 0) {
		cout << "��ԤԼ��¼" << endl;
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

//���ԤԼ
void Teacher::ValidOrder() {
	//��ȡ��������е�ԤԼ��¼
	OrderFile of;
	if (of.m_size == 0) {
		cout << "��ԤԼ��¼!" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "����˵ļ�¼���£�" << endl;
	vector<int> v; //��ſ���ȡ����ԤԼ��¼��OrderFile�е�����
	int index = 0;
	
	for (int i = 0; i < of.m_size; i++) {
		//��ʾ����˵�ԤԼ
		if ("1" == of.m_orderData[i]["status"]) {
			v.emplace_back(i);
			cout << ++index << "��";
			cout << "ԤԼ���ڣ���" << of.m_orderData[i]["date"];
			cout << " ʱ��Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");
			cout << " �����ţ�" << of.m_orderData[i]["roomId"];
			string status = " ״̬�������";
			cout << status << endl;
		}
	}

	cout << "��������˵ļ�¼��0������" << endl;
	int option = 0;
	int ret = 0; //����ԤԼ���
	while (true) {
		cin >> option;

		if (option >= 0 && option <= v.size()) {
			//����
			if (option == 0) {
				break;
			}
			else {
				cout << "��������˽����" << endl;
				cout << "1��ͨ��" << endl;
				cout << "2����ͨ��" << endl;
				cin >> ret;
				while (cin.fail()) {
					cin.clear();
					cin.ignore();
					cout << "�����ʽ��������������" << endl;
					cin >> ret;
				}
				//ԤԼͨ��
				if (ret == 1) {
					of.m_orderData[v[option - 1]]["status"] = "2";
				}
				//ԤԼ��ͨ��
				else {
					of.m_orderData[v[option - 1]]["status"] = "-1";
				}
				of.UpdateOrder(); //����ԤԼ��¼
				cout << "������" << endl;
				break;
			}
		}
		cout << "������������������" << endl;
	}
	system("pause");
	system("cls");
}