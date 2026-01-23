#pragma once
#include <iostream>
#include <vector>

// 市级体
struct City {
	std::string name;															// 市名称
	std::vector<std::string> districts;											// 区/县名称列表
};

// 省级体
struct Province {
	std::string name;															// 省名称
	std::vector<City> cities;													// 市列表
};

// 籍贯体
struct NativePlace {
	std::string province;														// 省
	std::string city;															// 市
	std::string district;														// 区/县
};

// 学生体
struct Student {
	std::string id;																// 学号：10位数字，唯一标识，不能重复
	std::string name;															// 姓名：2-5个中文字符，支持复姓
	bool gender;																// 性别：true/false，男/女，单选输入
	int age;																	// 年龄：16-30岁整数，需符合大学生年龄范围
	NativePlace native_place;													// 籍贯：省、市、县三级
	std::string phone_number;													// 联系方式：11位手机号
};

// 文件信息体
struct FileInfo {
	int index;																	// 文件序号
	std::string name;															// 文件名称
};