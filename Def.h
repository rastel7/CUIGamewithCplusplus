#pragma once
#include<memory>
#include <chrono>
#include <iostream>
#include <ctime>
//alias�Ȃǂ́C�S�Ẵ\�[�X�Ŏg����`�������ɏ���
//�X�}�[�g�|�C���^��alias
template<typename T>using SPtr = std::shared_ptr<T>;
template<typename T>using WPtr = std::weak_ptr<T>;
template<typename T>using UPtr = std::unique_ptr<T>;
using uint = unsigned int;

//���ݎ�������,(0,1]�̋[���I�ȗ����𐶐�����
inline float GetRandomFloat() {
	int nowtime =(int)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();;
	nowtime *= nowtime;
	int modtime = nowtime % 997;
	return (float)(modtime) / 997.0f;
}