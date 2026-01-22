#pragma once
#include "../include/AllStruct.h"
#include "../include/AllRegex.h"
#include <iostream>
#include <fstream>																// 文件读写
#include <filesystem>															// 文件系统操作
#include <string>
#include <regex>																// 正则匹配
#include <vector>

#define CLEAR_LINE "\r\033[K"													// 回车到行首，然后清除到行尾

// 文件管理状态机
enum FileManagerStatus {
	kChooseFile,																// 选择目标文件
	kSaveFile,																	// 保存文件
	kGetStudentData,															// 获取学生数据
	kNone,																		// 无操作
};

// 文件管理类
class FileManager {
public:
	FileManager();
	~FileManager();

	void change_to_status(FileManagerStatus to_status);							// 自定义的状态转移

private:
	bool serch_file();															// 搜索当前路径下的目标文件，返回是否成功
	bool is_file_exist(std::string file);										// 检查当前目标文件是否存在
	bool open_file(const std::string name);										// 打开目标文件，返回是否成功
	bool delete_file(const std::string& name);									// 删除指定的文件，返回是否成功
	bool creat_temp_file();														// 创建临时文件，返回是否成功
	bool save_file();															// 保存临时文件，返回是否成功
	int choose_file();															// 选择目标文件, 返回文件序号
	void show_file_list();														// 显示搜索到的目标文件列表
	void reflash_file_name();													// 根据文件列表序号刷新文件名称
	std::string get_current_file_name();										// 获取当前操作的文件名
	Student get_student_data();													// 从临时文件中获取学生数据

	// 目标文件名正则表达式(示例：Student_1.txt)
	std::regex file_name_regex = AllRegex::get_file_name_regex();
	// 学号正则表达式：10位数字
	std::regex id_regex = AllRegex::get_id_regex();
	// 姓名正则表达式：2-5个中文字符，支持复姓（仅支持基本汉字，含约 20,902 个汉字字符）
	std::regex name_regex = AllRegex::get_name_regex();
	// 性别正则表达式：女 | 男
	std::regex gender_regex = AllRegex::get_gender_regex();
	// 年龄正则表达式：16-30岁整数
	std::regex age_regex = AllRegex::get_age_regex();
	// 籍贯正则表达式：省、市、县三级
	std::regex native_place_regex = AllRegex::get_native_place_regex();
	// 联系方式正则表达式：11位手机号
	std::regex phone_number_regex = AllRegex::get_phone_number_regex();

	std::vector<FileInfo> file_list;											// 存放搜索到的目标文件序号和名称
	std::vector<Student> all_student;											// 存放从文件中获取的一行Student
	std::string file_path = "../resrc/";										// 当前操作的文件路径
	std::string file_name = "Students_temp.txt";								// 临时文件名
	int max_file_backup = 5;													// 最大备份文件数量
	int current_file_index = 1;													// 临时文件序号，默认从1开始
	int max_show_number = 3;													// 每行显示的文件数量
};