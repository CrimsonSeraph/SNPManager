#pragma once
#include <iostream>
#include <regex>

class AllRegex {
public:
	AllRegex() = delete;														// 禁止实例化
	~AllRegex() = delete;														// 禁止析构
	AllRegex(const AllRegex&) = delete;											// 禁止拷贝构造
	AllRegex& operator=(const AllRegex&) = delete;								// 禁止赋值操作

	static const std::regex& get_id_regex();									// 获取学号正则表达式
	static const std::regex& get_name_regex();									// 获取姓名正则表达式
	static const std::regex& get_gender_regex();								// 获取性别正则表达式
	static const std::regex& get_age_regex();									// 获取年龄正则表达式
	static const std::regex& get_native_place_regex();							// 获取籍贯正则表达式
	static const std::regex& get_phone_number_regex();							// 获取电话正则表达式
	static const std::regex& get_file_name_regex();								// 获取文件名正则表达式
};