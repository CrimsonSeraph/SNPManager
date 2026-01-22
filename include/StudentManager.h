#pragma once
#include "../include/FileManager.h"
#include "../include/AllStruct.h"
#include "../include/AllRegex.h"
#include <iostream>
#include <string>
#include <regex>																// 正则匹配
#include <vector>

// 学生管理状态机
enum StudentManagerStatus {
	kAddId,																		// 添加学号
	kAddName,																	// 添加姓名
	kAddGender,																	// 添加性别
	kAddAge,																	// 添加年龄
	kAddNativePlace,															// 添加籍贯
	kAddPhoneNumber,															// 添加联系方式
	kNone,																		// 无操作
};

// 学生管理类
class StudentManager {
public:
	StudentManager();
	~StudentManager();

private:
	void change_status();														// 默认的状态转移
	void change_to_status(StudentManagerStatus to_status);						// 自定义的状态转移
	void add_id();																// 添加学号
	void add_name();															// 添加姓名
	void add_gender();															// 添加性别
	void add_age();																// 添加年龄
	void add_native_place();													// 添加籍贯
	void add_phone_number();													// 添加手机号
	std::string enter_as_regex(std::regex i_regex);								// 按正则输入信息

	// 学号正则表达式：10位数字
	std::regex id_regex = AllRegex::get_id_regex();
	// 姓名正则表达式：2-5个中文字符，支持复姓（仅支持基本汉字，含约 20,902 个汉字字符）
	std::regex name_regex = AllRegex::get_name_regex();
	// 联系方式正则表达式：11位手机号
	std::regex phone_number_regex = AllRegex::get_phone_number_regex();

	FileManager file_manager;													// 文件管理器
	std::vector<Student> all_student;											// 存放所有的Studnet
	int index = 0;																// 指向操作的Student
	StudentManagerStatus status = kNone;										// 当前操作状态
};