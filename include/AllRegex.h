//——————————————————————————————————————————————————————注释标准：27个制表符宽度
#pragma once
#include <iostream>
#include <string>
#include <regex>

class AllRegex {
public:
	AllRegex() = delete;																					// 禁止实例化
	~AllRegex() = delete;																					// 禁止析构
	AllRegex(const AllRegex&) = delete;																		// 禁止拷贝
	AllRegex& operator=(const AllRegex&) = delete;															// 禁止赋值构造

	static const std::regex& get_id_regex();																// 获取ID的正则表达式
	static const std::regex& get_name_regex();																// 获取姓名的正则表达式
	static const std::regex& get_gender_regex();															// 获取性别的正则表达式
	static const std::regex& get_age_regex();																// 获取年龄的正则表达式
	static const std::regex& get_native_place_regex();														// 获取用于读取籍贯的正则表达式
	static const std::regex& get_phone_number_regex();														// 获取电话号码的正则表达式
	static const std::regex& get_file_name_regex();															// 获取文件名的正则表达式
};