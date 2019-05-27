#pragma once
#include "attribute.h"

struct ColumnName {
	const std::string& db_name;
	const std::string& table_name;
	const std::string& column_name;
};


class CatalogManager {
public:
	// ���ִ�������ظ�������table������һ��std::exception �ͺ���
	// https://en.cppreference.com/w/cpp/error/exception <-- exception ���б�
	const MetaData& FetchTable(const std::string& db_name,
		const std::string& table_name);

	const Attribute& FetchColumn(ColumnName col_name);


	void NewTable(const MetaData& meta);

	void DropTable(const std::string& db_name,
		const std::string& table_name);

	void NewColumn(ColumnName col_name);

	void DropColumn(ColumnName col_name);

	void SerializeOneTable(BufferManager::Iterator<char*>& itr, const MetaData& meta) {
		itr.AutoInsert(meta.db_name); // �����һҳ���ݲ����ˣ�auto insert ���Զ���һҳ
		itr.AutoInsert(meta.table_name);
		itr.AutoInsert(&meta.file, sizeof(FileId));

		size_t num_attribs = meta.attributes.size();

		itr.AutoInsert(&num_attribs, sizeof(num_attribs));
		for (auto& attrib : meta.attributes) {
			itr.AutoInsert(attrib.first); //map �ȴ�key���ٴ�value
			SerializeOneAttrib(itr, attrib.second);
		}
		
		// ע�͵�Ϊ�˲�����
		// size_t num_primkeys = meta.primary_keys.size();
		// itr.AutoInsert(&num_primkeys, sizeof(num_primkeys));
		// for (auto pk : meta.primary_keys) {
		// 	itr.AutoInsert(&pk, sizeof(pk));
		// }
	}

	void SerializeOneAttrib(BufferManager::Iterator<char*>& itr, const Attribute& attrib) {
		itr.AutoInsert(&attrib.id, 2 * sizeof(int)); // ����͵��ֱ�Ӱ�����int����ȥ��
		// itr.AutoInsert(attrib.column_name); ���ﲻ��Ҫ����Ϊmap��key����colname
		itr.AutoInsert(attrib.comment);
			
		// ....
	}


	void DeserializeMeta(BufferManager::Iterator<char*>& itr, MetaData& meta) {
		meta.db_name = itr.Read<std::string>();
		meta.table_name = itr.Read<std::string>();

		meta.file = itr.Read<FileId>(); 

		size_t num_attribs = itr.Read<size_t>();

		for (size_t i = 0; i < num_attribs; ++i) {
			std::string col_name = itr.Read<std::string>();
			DeserializeOneAttribute(itr, meta.attributes[col_name], col_name);
		}

		// ...

	}

	void DeserializeOneAttribute(BufferManager::Iterator<char*>& itr, Attribute& attrib, const std::string& column_name) {
		int* data = reinterpret_cast<int*>(*itr);
		attrib.id = *data;
		attrib.type = *(++data);

		// �Ե���������int
		itr.Read<int64_t>();

		attrib.column_name = column_name;
		attrib.comment = itr.Read<std::string>();

		// ...
	}
};