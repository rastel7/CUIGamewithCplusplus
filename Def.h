#pragma once
#include<memory>
#include <chrono>
#include <iostream>
#include <ctime>
//aliasなどの，全てのソースで使う定義をここに書く
//スマートポインタをalias
template<typename T>using SPtr = std::shared_ptr<T>;
template<typename T>using WPtr = std::weak_ptr<T>;
template<typename T>using UPtr = std::unique_ptr<T>;
using uint = unsigned int;

//現在時刻から,(0,1]の擬似的な乱数を生成する
inline float GetRandomFloat() {
	int nowtime =(int)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();;
	nowtime *= nowtime;
	int modtime = nowtime % 997;
	return (float)(modtime) / 997.0f;
}