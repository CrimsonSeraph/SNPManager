#pragma once
#include "../include/FileManager.h"
#include <iostream>
#include <string>
#include <vector>

// 学生体
struct Student {
	std::string id;																// 学号：10位数字，唯一标识，不能重复
	std::string name;															// 姓名：2-5个中文字符，支持复姓
	bool gender;																// 性别：true/false，男/女，单选输入
	int age;																	// 年龄：16-30岁整数，需符合大学生年龄范围
	NativePlace native_place;													// 籍贯：省、市、县三级
	std::string phone_number;													// 联系方式：11位手机号
};

// 籍贯体
struct NativePlace {
	std::string province;														// 省
	std::string city;															// 市
	std::string district;														// 区/县
};

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
	void add_id();// 添加学号
	void add_name();// 添加姓名
	void add_gender();// 添加性别
	void add_age();// 添加年龄
	void add_native_place();// 添加籍贯
	void add_phone_number();// 添加手机号

	FileManager file_manager;													// 文件管理器
	std::vector<Student> all_student;											// 存放所有的Studnet
	int index = 0;																// 指向操作的Student
	StudentManagerStatus status= kNone;											// 当前操作状态
};