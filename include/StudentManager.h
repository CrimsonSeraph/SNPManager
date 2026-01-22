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
	kSAddId,																		// 添加学号
	kSAddName,																	// 添加姓名
	kSAddGender,																	// 添加性别
	kSAddAge,																	// 添加年龄
	kSAddNativePlace,															// 添加籍贯
	kSAddPhoneNumber,															// 添加联系方式
	kSStartLoad,																// 开始加载
	kSNone,																		// 无操作
};

// 学生管理类
class StudentManager {
public:
	StudentManager();
	~StudentManager();

	void change_status();														// 默认的状态转移
	void change_to_status(StudentManagerStatus to_status);						// 自定义的状态转移

private:
	void start_load();															// 开始加载
	void add_id();																// 添加学号
	void add_name();															// 添加姓名
	void add_gender();															// 添加性别
	void add_age();																// 添加年龄
	void add_native_place();													// 添加籍贯
	void add_phone_number();													// 添加手机号
	std::string enter_as_regex(std::regex i_regex);								// 按正则输入信息

	FileManager file_manager;													// 文件管理器
	std::vector<Student> all_student;											// 存放所有的Studnet
	int index = 0;																// 指向操作的Student
	StudentManagerStatus status = kSNone;										// 当前操作状态
};