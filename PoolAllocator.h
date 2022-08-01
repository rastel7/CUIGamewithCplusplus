#pragma once
#include<vector>
#include"Character.h"
const size_t DEFAULTMAXPOOLSIZE = 64;
// class Tを最大MAXSIZE個確保可能なPoolAllocatorを実装してください
template<class T, size_t MAXSIZE = DEFAULTMAXPOOLSIZE> class PoolAllocator
{
private:
	// TODO: 実装してください
	union element_type {
		T value;
		std::uintptr_t next;
		inline element_type():value() {}
		inline ~element_type(){}
	};
	element_type* freelist;
	std::vector<element_type> buffer;
public:
	// コンストラクタ 
	PoolAllocator() :buffer(MAXSIZE) {
		freelist = &buffer[0];
		for (size_t i = 0; i < MAXSIZE; ++i) {
			if (i + 1 == MAXSIZE) {
				//最後尾の後ろにはnullptr
				buffer[i].next = reinterpret_cast<uintptr_t>(nullptr);
			}
			else {
				//次のバッファへのポインタを与える
				buffer[i].next = reinterpret_cast<uintptr_t>(&buffer[i + 1]);
			}
		}
	}

	// デストラクタ
	
	~PoolAllocator() {
		buffer.clear();
	}

	T* Alloc() {
		if (freelist == nullptr) {
			//空きがないのでnullptrを返す
			return nullptr;
		}
		T* result = &freelist->value;
		freelist = reinterpret_cast<element_type*>(freelist->next);
		return result;
	}

	// Free(nullptr)で誤動作しないようにする事。
	void Free(T* addr) {
		if (addr == nullptr) {
			//nullptrが渡されたので処理せず返す
			return;
		}
		element_type* element_ptr = reinterpret_cast<element_type*>(addr);
		if (element_ptr == nullptr) {
			//不正なポインタが渡されたので処理せず返す
			return;
		}
		element_ptr->next = reinterpret_cast<uintptr_t>(freelist);
		freelist = element_ptr;

		return;
	}
};
