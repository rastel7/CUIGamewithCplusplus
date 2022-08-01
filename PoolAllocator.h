#pragma once
#include<vector>
#include"Character.h"
const size_t DEFAULTMAXPOOLSIZE = 64;
// class T���ő�MAXSIZE�m�ۉ\��PoolAllocator���������Ă�������
template<class T, size_t MAXSIZE = DEFAULTMAXPOOLSIZE> class PoolAllocator
{
private:
	// TODO: �������Ă�������
	union element_type {
		T value;
		std::uintptr_t next;
		inline element_type():value() {}
		inline ~element_type(){}
	};
	element_type* freelist;
	std::vector<element_type> buffer;
public:
	// �R���X�g���N�^ 
	PoolAllocator() :buffer(MAXSIZE) {
		freelist = &buffer[0];
		for (size_t i = 0; i < MAXSIZE; ++i) {
			if (i + 1 == MAXSIZE) {
				//�Ō���̌��ɂ�nullptr
				buffer[i].next = reinterpret_cast<uintptr_t>(nullptr);
			}
			else {
				//���̃o�b�t�@�ւ̃|�C���^��^����
				buffer[i].next = reinterpret_cast<uintptr_t>(&buffer[i + 1]);
			}
		}
	}

	// �f�X�g���N�^
	
	~PoolAllocator() {
		buffer.clear();
	}

	T* Alloc() {
		if (freelist == nullptr) {
			//�󂫂��Ȃ��̂�nullptr��Ԃ�
			return nullptr;
		}
		T* result = &freelist->value;
		freelist = reinterpret_cast<element_type*>(freelist->next);
		return result;
	}

	// Free(nullptr)�Ō듮�삵�Ȃ��悤�ɂ��鎖�B
	void Free(T* addr) {
		if (addr == nullptr) {
			//nullptr���n���ꂽ�̂ŏ��������Ԃ�
			return;
		}
		element_type* element_ptr = reinterpret_cast<element_type*>(addr);
		if (element_ptr == nullptr) {
			//�s���ȃ|�C���^���n���ꂽ�̂ŏ��������Ԃ�
			return;
		}
		element_ptr->next = reinterpret_cast<uintptr_t>(freelist);
		freelist = element_ptr;

		return;
	}
};
