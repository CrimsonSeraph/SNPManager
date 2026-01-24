//——————————————————————————————————————————————————————注释标准：27个制表符宽度
#include "../include/FileManager.h"

FileManager::FileManager() {
}

FileManager::~FileManager() {
	std::filesystem::remove(file_path + file_name);
}

void FileManager::change_to_status(const FileManagerStatus to_status) {
	switch (to_status) {
	case FileManagerStatus::kFChooseFile:
		if (file_list.size() == 0) {
			break;
		}
		while (!open_file(file_list[choose_file()].name)) {
		}
		change_to_status(kFNone);
		break;
	case FileManagerStatus::kFSaveFile:
		while (!save_file()) {
		};
		change_to_status(kFNone);
		break;
	case FileManagerStatus::kFStartLoad:
		if (!start_load()) {
			start_load();
		}
		change_to_status(kFNone);
		break;
	default:
	case FileManagerStatus::kFNone:
		break;
	}
}

bool FileManager::start_load() {
	// 启动加载：确保存在临时文件，然后搜索文件列表
	create_temp_file();
	if (!serch_file()) {
		// 搜索失败则返回 false
		return false;
	}
	return true;
}

bool FileManager::serch_file() {
	// 搜索文件：确保目录存在，清理并构建文件列表，按需删除超出备份数量的旧文件，并重命名文件
	// 确保基础目录存在
	if (!(std::filesystem::exists(file_path) && std::filesystem::is_directory(file_path))) {
		if (!std::filesystem::create_directory(file_path)) {
			// 创建目录失败
			return false;
		}
	}
	// 清空现有列表
	file_list.clear();
	// 如果存在临时文件则加入列表
	if (is_file_exist(file_path + file_name)) {
		file_list.push_back({ 0, file_name });
	}
	// 遍历目录，匹配符合命名规则的文件并解析索引
	for (const auto& o_file_name : std::filesystem::directory_iterator(file_path)) {
		if (std::regex_match(o_file_name.path().filename().string(), AllRegex::get_file_name_regex())) {
			std::string file_name = o_file_name.path().filename().string();
			// 解析下划线后到点之前的索引部分
			size_t start = file_name.find("_") + 1;
			size_t end = file_name.find(".");
			// 校验解析结果是否合法
			if (start == std::string::npos || end == std::string::npos || end <= start) {
				return false;
			}
			int index = std::stoi(file_name.substr(start, end - start));
			// 构造 FileInfo 并加入列表
			FileInfo index_name;
			index_name.index = index;
			index_name.name = o_file_name.path().filename().string();
			file_list.push_back(index_name);
		}
	}
	// 列表为空视为失败
	if (file_list.size() == 0) {
		return false;
	}
	else if (file_list.size() == 1) {
		// 只有一个文件时不需要排序或清理
		// 直接刷新文件名后返回成功
		reflash_file_name();
		return true;
	}
	// 简单的冒泡式一次性相邻比较排序（将大索引提前）
	for (size_t i = 0; i + 1 < file_list.size(); ++i) {
		if (file_list[i].index < file_list[i + 1].index) {
			FileInfo temp_file_info = file_list[i];
			file_list[i] = file_list[i + 1];
			file_list[i + 1] = temp_file_info;
		}
	}
	// 如果文件数量超过允许的备份数量则删除最旧的（尾部）文件
	if (file_list.size() > max_file_backup) {
		for (int i = static_cast<int>(file_list.size()) - 1; i >= max_file_backup; --i) {
			delete_file(file_list[i].name);
			file_list.pop_back();
		}
	}
	// 重命名文件以确保命名连续
	reflash_file_name();
	return true;
}

bool FileManager::is_file_exist(const std::string& file) {
	// 检查给定路径是否存在文件或目录
	if (!std::filesystem::exists(file)) {
		return false;
	}
	return true;
}

bool FileManager::open_file(const std::string& name) {
	// 打开指定文件：如果已是当前文件直接返回；否则检查存在性，删除当前临时文件，再复制目标为临时文件
	if (name == file_name) {
		// 要打开的文件就是当前文件，直接成功
		return true;
	}
	// 目标文件必须存在
	if (!is_file_exist(file_path + name)) {
		return false;
	}
	// 如果已有临时文件存在，先删除它
	if (is_file_exist(file_path + file_name)) {
		delete_file(file_path + file_name);
		if (is_file_exist(file_path + file_name)) {
			// 删除失败则返回 false
			return false;
		}
	}
	// 将目标文件复制为临时文件
	if (!std::filesystem::copy_file(file_path + name, file_path + file_name)) {
		return false;
	}
	return true;
}

bool FileManager::delete_file(const std::string& name) {
	// 删除指定文件（带路径），存在则删除并返回 true，否则返回 false
	if (std::filesystem::exists(file_path + name)) {
		std::filesystem::remove(file_path + name);
		return true;
	}
	return false;
}

bool FileManager::create_temp_file() {
	// 创建临时文件：存在则直接返回；否则尝试创建文件并确保目录存在
	if (is_file_exist(file_path + file_name)) {
		return true;
	}
	std::ofstream o_file;
	// 尝试在目标路径创建文件
	o_file.open(file_path + file_name);
	if (!o_file.is_open()) {
		// 如果打开失败，可能是目录不存在，先尝试创建目录
		if (!(std::filesystem::exists(file_path) && std::filesystem::is_directory(file_path))) {
			if (!std::filesystem::create_directory(file_path)) {
				// 创建目录失败
				return false;
			}
		}
		// 再次尝试打开文件
		o_file.open(file_path + file_name);
	}
	// 关闭文件句柄
	o_file.close();
	// 返回文件是否存在的检查结果
	return is_file_exist(file_path + file_name);
}

bool FileManager::save_file() {
	// 保存当前临时文件为一个新备份文件：临时文件必须存在，目标备份名不能已存在，然后复制
	if (!is_file_exist(file_path + file_name)) {
		return false;
	}
	// 目标名称如果已存在则视为冲突失败
	if (is_file_exist(get_current_file_name())) {
		return false;
	}
	// 执行复制操作
	if (!std::filesystem::copy_file(file_path + file_name, get_current_file_name())) {
		return false;
	}
	return true;
}

int FileManager::choose_file() {
	// 选择文件：如果只有一个文件并且当前有临时文件则返回 0；否则展示文件列表并从控制台读取选择序号
	if (file_list.size() == 1) {
		if (is_file_exist(file_path + file_name)) {
			// 只有一个文件且临时文件存在，直接返回索引 0
			return 0;
		}
		// 若临时文件不存在则创建并把它加入列表以便选择
		create_temp_file();
		file_list.push_back({ 0, file_name });
	}
	// 显示文件列表到控制台
	show_file_list();
	int input;
	// 循环读取用户输入，直到输入合法序号
	while (true) {
		std::cin >> input;
		if (input > 0 && input < static_cast<int>(file_list.size())) {
			// 清除提示行（宏 CLEAR_CUR_AND_PREV_LINE）并退出循环
			std::cout << CLEAR_CUR_AND_PREV_LINE;
			break;
		}
		// 输入不合法则提示并继续循环
		std::cout << "请输入正确序号!";
	}
	return input;
}

void FileManager::show_file_list() {
	// 在控制台格式化输出文件列表，超过每行最大显示数则换行
	int current_number = 0;
	for (const auto& file_info : file_list) {
		std::cout << "序号" << file_info.index << "\t";
		std::cout << "名称" << file_info.name << "\t";
		current_number++;
		if (current_number >= max_show_number) {
			std::cout << "\n";
			current_number = 0;
		}
	}
}

void FileManager::reflash_file_name() {
	// 重命名文件：根据索引生成新的规范名，索引 0 对应临时文件名
	for (auto& file_info : file_list) {
		std::string current_file_name;
		if (file_info.index == 0) {
			current_file_name = "Student_temp.txt";
		}
		else {
			current_file_name = "Student_" + std::to_string(file_info.index);
		}
		// 执行重命名操作，末尾添加perch占位避免覆盖
		std::filesystem::rename(file_path + file_info.name, file_path + current_file_name + "perch");
		// 记录新名称
		file_info.name = current_file_name;
	}
	for(const auto& file_info : file_list) {
		if (file_info.index == 0) {
			// 临时文件跳过重命名
			continue;
		}
		// 去除占位完成最终重命名
		std::filesystem::rename(file_path + file_info.name + "perch", file_path + file_info.name + ".txt");
	}
	// 更新 current_file_index
	if (is_file_exist(file_path + file_name)) {
		current_file_index = static_cast<int>(file_list.size());
	}
	else {
		current_file_index = static_cast<int>(file_list.size()) + 1;
	}
}

std::string FileManager::get_current_file_name() {
	// 返回当前要保存的备份文件名（基于 current_file_index）
	std::string current_file_name = "Student_" + std::to_string(current_file_index)+".txt";
	return current_file_name;
}

std::vector<Student> FileManager::get_student_data() {
	// 清空存储的学生数据
	all_student.clear();
	// 读取学生数据：初始化一个默认的错误对象，尝试打开临时文件并解析每行的字段
	Student student_data = {
		.id = "0000000000",
		.name = "错误",
		.gender = true,
		.age = 16,
		.native_place = {
			.province = "错误",
			.city = "错误",
			.district = "错误",
		},
		.phone_number = "00000000000",
	};
	// 如果临时文件不存在，直接返回默认数据
	if (!is_file_exist(file_path + file_name)) {
		all_student.push_back(student_data);
		return all_student;
	}
	// 打开临时文件以读取
	std::ifstream i_file;
	i_file.open(file_path + file_name);
	if (!i_file.is_open()) {
		// 打开失败则返回默认值
		all_student.push_back(student_data);
		return all_student;
	}
	std::string line;
	std::smatch match;
	// 按行依次读取数据，假定一行一名学生
	while (std::getline(i_file, line)) {
		// 若行中匹配到 id 开始新条目，将当前 student_data 推入集合并解析各字段
		if (std::regex_search(line, match, AllRegex::get_id_regex())) {
			all_student.push_back(student_data);
			student_data.id = match.str(0);
			std::regex_search(line, match, AllRegex::get_name_regex());
			student_data.name = match.str(0);
			std::regex_search(line, match, AllRegex::get_gender_regex());

			std::regex_search(line, match, AllRegex::get_age_regex());
			student_data.age = std::stoi(match.str(0));
			std::regex_search(line, match, AllRegex::get_phone_number_regex());
			student_data.phone_number = match.str(0);
		}
	}
	return all_student;
}
