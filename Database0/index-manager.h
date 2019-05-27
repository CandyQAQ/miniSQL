#pragma once
#include "attribute.h"

/////////////////////////////////////
////// Index Manager            /////
/////////////////////////////////////
class IndexManager {
public:


	// http://www.cplusplus.com/reference/cstring/memcmp/ <-- memcmp
	//������ int/double ���������� memcpy((char*) rhs, (char*) lhs, key_size_by_bytes) �Ƚ�
	//ע�� IndexManager �ܴ� Cat Manager ֪��Key�ǲ��Ǳ߳��ģ���ʱ��Ӧ����strcmp
	BufferManager::Iterator<char> LookUp(Attribute&,
		const char* key,
		int key_size_by_bytes);
	bool IsIndexed(Attribute&);

	void BuildIndex(Attribute&);

	void DropIndex(Attribute&);

	void Insert(ItemPayload payload);

	void Delete(ItemPayload payload);

	void Update(ItemPayload payload);

};