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
	static const std::regex& get_phone_number_regex();							// 获取电话正则表达式
	static const std::regex& get_file_name_regex();								// 获取文件名正则表达式
};