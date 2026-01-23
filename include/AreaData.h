#pragma once
#include "../include/AllStruct.h"
#include <iostream>

class AreaData {
public:
	AreaData() = delete;														// 禁止实例化
	~AreaData() = delete;														// 禁止析构
	AreaData(const AreaData&) = delete;											// 禁止拷贝构造
	AreaData& operator=(const AreaData&) = delete;								// 禁止赋值操作

	// 根据省名称获取市列表
	static const std::vector<City>& get_cities_by_province(const std::string& province_name);
	// 根据省名称和市名称获取区列表
	static const std::vector<std::string>& get_districts_by_city(const std::string& province_name, const std::string& city_name);

	static const std::vector<Province>& get_area_data();						// 获取省市区数据
};