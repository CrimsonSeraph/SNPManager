//——————————————————————————————————————————————————————注释标准：27个制表符宽度
#pragma once
#include "../include/AllStruct.h"
#include "../include/AllRegex.h"
#include "../include/AreaData.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <regex>
#include <vector>

#define CLEAR_LINE "\x1b[2K\r"																				// 清除当前整行并回到行首
#define MOVE_CURSOR_UP "\x1b[1A"																			// 上移一行（光标位置相对不变）
#define CLEAR_PREV_LINE MOVE_CURSOR_UP CLEAR_LINE															// 上移一行并清除该行
#define CLEAR_CUR_AND_PREV_LINE CLEAR_LINE MOVE_CURSOR_UP CLEAR_LINE										// 清除当前行并上移清除上一行

// 文件管理状态机
enum FileManagerStatus {
	kFChooseFile,																							// 选择目标文件
	kFSaveFile,																								// 保存文件
	kFGetStudentData,																						// 获取学生数据
	kFStartLoad,																							// 开始加载
	kFNone,																									// 无操作
};

// 文件管理类
class FileManager {
public:
	FileManager();
	~FileManager();

	void change_to_status(FileManagerStatus to_status);														// 自定义状态转移

private:
	bool start_load();																						// 开始加载，返回是否成功
	bool serch_file();																						// 搜索当前路径下的目标文件，返回是否成功
	bool is_file_exist(const std::string& name);															// 检查指定文件是否存在
	bool open_file(const std::string& name);																// 打开指定文件，返回是否成功
	bool delete_file(const std::string& name);																// 删除指定文件，返回是否成功
	bool create_temp_file();																				// 创建临时文件，返回是否成功
	bool save_file();																						// 保存临时文件，返回是否成功
	int choose_file();																						// 选择目标文件，返回选择的文件序号
	void show_file_list();																					// 显示文件列表
	void reflash_file_name();																				// 根据文件列表序号刷新文件名
	std::string get_current_file_name();																	// 获取当前操作的文件名
	std::vector<Student> get_student_data();																// 从临时文件中获取学生数据

	std::vector<FileInfo> file_list;																		// 存放搜索到的目标文件序号和名称
	std::vector<Student> all_student;																		// 存放从文件中获取的一行Student
	std::string file_path = "../resrc";																		// 当前操作的文件路径
	std::string file_name = "Studnet_temp.txt";																// 临时文件名
	int max_file_backup = 5;																				// 最大备份文件数量
	int current_file_index = 0;																				// 临时文件序号，默认从0开始
	int max_show_number = 3;																				// 每行显示的文件数量
};