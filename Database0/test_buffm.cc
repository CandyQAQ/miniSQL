#include "buffer-manager.h"
#include <iostream>

int main()
{
	BufferManager bm;
	const char* db_file_name = "./test.db";
	FileId db_file;
	std::vector<std::string> test;
	test.push_back("This is test A .....");
	test.push_back("db_file = bm.NewFile(db_file_name);");
	test.push_back("auto v = bm.GetPage<char*>(db_file, column_Var);");
	test.push_back("for (int i = 0; i < 10; ++i) {");
	test.push_back("++itr;");
	test.push_back("itr.Insert(10.0 * i);");


	// write data
	if (!fs::exists(db_file_name)) {
		db_file = bm.NewFile(db_file_name);

		// allocate first page for column A
		PageId column_A = bm.AllocatePageAfter(db_file, 0);
		PageId column_Var = bm.AllocatePageAfter(db_file, 0);

		// get an iterator on the page
		auto itr = bm.GetPage<double>(db_file, column_A);

		// char* ��һ������ĵ���������ʾ�䳤�����ݣ��߳����������Ͽ��Դ���κ����͵����ݣ�����ռ����ռ�
		auto v = bm.GetPage<char*>(db_file, column_Var);
		for (int i = 0; i < 10; ++i) {
			itr.Insert(10.0 * i);
			++itr;
		}

		for (int i = 0; i < 10; ++i) {
			v.Insert(test[i % test.size()]);
			++v;
		}
	}
	// read data
	else {
		db_file = bm.OpenFile(db_file_name);

		// ��Ϊ֮ǰ�����column ��PageId �� 1,����͵��ֱ����1, ��Ӧ���� Catalog Manager ��¼
		// Catalog Manager ֪������ÿһ�ж�Ӧ�ĵ�һ��PageId, ��ѯ�е�ʱ��Ӧ�÷���һ��ָ���һ�еĵ�����
		// Index Manager Ӧ�ü�¼��ЩKey��Ӧ��һ��PageId, ��ѯKey��ʱ�򷵻� һ��������
		
		//TODO �ƻ��� ����Page ��ʵ�ֶ��ֲ���
		auto itr = bm.GetPage<double>(db_file, 1);
		auto v = bm.GetPage<char*>(db_file, 2);
		for (int i = 0; i < 10; ++i) {
			std::cout << "row " << i << ": " << *itr << std::endl;
			++itr;
		}

		for (int i = 0; i < 10; ++i) {
			std::cout << "row " << i << ": " << v.AsString() << std::endl;
			++v;
		}
		
		getchar();
		getchar();
	}

	

}