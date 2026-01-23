#pragma once
#include "../include/AllStruct.h"
#include <iostream>

class AreaData {
public:
	AreaData() = delete;														// 禁止实例化
	~AreaData() = delete;														// 禁止析构
	AreaData(const AreaData&) = delete;											// 禁止拷贝构造
	AreaData& operator=(const AreaData&) = delete;								// 禁止赋值操作

	static const std::vector<Province>& get_province_data();					// 获取省市区数据
};