#pragma once
#include "attribute.h"

struct ColumnName {
	const std::string& db_name;
	const std::string& table_name;
	const std::string& column_name;
};


class CatalogManager {
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
};