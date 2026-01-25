//—————————————————————————————————————————————————————— 注释标准：27个制表符宽度
#pragma once
#include "../include/FileManager.h"
#include "../include/AllStruct.h"
#include "../include/AllRegex.h"
#include "../include/AreaData.h"
#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <iomanip>

// 学生管理状态机
enum StudentManagerStatus {
	kSAddId,																								// 添加学号
	kSAddName,																								// 添加姓名
	kSAddGender,																							// 添加性别
	kSAddAge,																								// 添加年龄
	kSAddProvince,																							// 添加省份
	kSAddCity,																								// 添加城市
	kSAddDistrict,																							// 添加区/县
	kSAddPhoneNumber,																						// 添加联系方式
	kSGetStudentData,																						// 获取学生数据
	kSStartLoad,																							// 开始加载
	kSNone,																									// 无操作
};

// 学生管理类
class StudentManager {
public:
	StudentManager();
	~StudentManager();

	void change_status();																					// 默认的状态转移
	void change_to_status(const StudentManagerStatus to_status);											// 自定义状态转移

private:
	void start_load();																						// 开始加载
	void add_id();																							// 添加学号
	void add_name();																						// 添加姓名
	void add_gender();																						// 添加性别
	void add_age();																							// 添加年龄
	void add_province();																					// 添加省份
	void add_city();																						// 添加城市
	void add_district();																					// 添加区/县
	void add_phone_number();																				// 添加手机号
	void print_province();																					// 打印省份列表
	void print_city(const std::string& province_name);														// 打印城市列表
	void print_district(const std::string& province_name, const std::string& city_name);					// 打印区/县列表
	void reload_index();																					// 刷新学生序号
	std::string choose_from_vector(const std::vector<std::string>& all_string);								// 返回从容器中选择的string
	std::string enter_as_regex(std::regex i_regex);															// 按正则输入信息

	FileManager file_manager;																				// 文件管理器
	std::vector<Student> all_student;																		// 存放所有的Student
	int index = 0;																							// 指向操作的Studnet
	StudentManagerStatus s_status = kSNone;																	// 当前操作状态
	std::string current_province;																			// 当前选择的省份
	std::string current_city;																				// 当前选择的城市
	int currect_number = 0;																					// 当前列表显示数量
	int prince_field_width = 20;																			// 省份列宽
	int city_field_width = 20;																				// 城市列宽
	int district_field_width = 20;																			// 区/县列宽
	int max_province_show_number = 5;																		// 每行显示的省份数量
	int max_city_show_number = 5;																			// 每行显示的城市数量
	int max_district_show_number = 5;																		// 每行显示的区/县数量
};