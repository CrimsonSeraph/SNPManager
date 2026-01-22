#include "../include/FileManager.h"

FileManager::FileManager() {
	serch_file();
}

FileManager::~FileManager() {
	std::filesystem::remove(file_path + file_name);
}

void FileManager::change_to_status(FileManagerStatus to_status) {
	switch (to_status) {
	case FileManagerStatus::kChooseFile:
		while (!open_file(file_path + file_list[choose_file() - 1].name)) {
		}
		change_to_status(kNone);
		break;
	case FileManagerStatus::kSaveFile:
		while (!save_file()) {
		};
		change_to_status(kNone);
		break;
	default:
	case FileManagerStatus::kNone:
		break;
	}
}

bool FileManager::serch_file() {
	// 检查目录是否存在，若不存在则创建
	if (!(std::filesystem::exists(file_path) && std::filesystem::is_directory(file_path))) {
		if (!std::filesystem::create_directory(file_path)) {
			return false;
		}
	}
	// 获取文件列表
	file_list.clear();
	for (const auto& o_file_name : std::filesystem::directory_iterator(file_path)) {
		// 正则匹配文件名
		if (std::regex_match(o_file_name.path().filename().string(), file_name_regex)) {
			std::string file_name = o_file_name.path().filename().string();
			size_t start = file_name.find("_") + 1;
			size_t end = file_name.find(".");
			// 不存在或位置不合理
			if (start == std::string::npos || end == std::string::npos || end <= start) {
				return false;
			}
			int index = std::stoi(file_name.substr(start, end - start));
			FileInfo index_name;
			index_name.index = index;
			index_name.name = o_file_name.path().filename().string();
			file_list.push_back(index_name);
		}
	}
	if (file_list.size() == 0) {
		creat_temp_file();
		return false;
	}
	else if (file_list.size() == 1) {
		return true;
	}
	// 按照文件序号降序排序(冒泡)
	for (int i = 0; i < file_list.size(); ++i) {
		if (file_list[i].index < file_list[i + 1].index) {
			FileInfo temp_file_info = file_list[i];
			file_list[i] = file_list[i + 1];
			file_list[i + 1] = temp_file_info;
		}
	}
	// 删除多余的备份文件
	if (file_list.size() > max_file_backup) {
		for (int i = file_list.size() - 1; i >= max_file_backup; --i) {
			delete_file(file_list[i].name);
			file_list.pop_back();
		}
	}
	// 刷新各文件名称
	reflash_file_name();
	return true;
}

bool FileManager::is_file_exist(std::string file) {
	if (!std::filesystem::exists(file)) {
		return false;
	}
	return true;
}

bool FileManager::open_file(const std::string name) {
	// 目标文件是否存在，不存在则返回false
	if (!is_file_exist(file_path + name)) {
		return false;
	}
	// 临时文件是否存在，存在则返回false
	if (is_file_exist(file_path + name)) {
		return false;
	}
	// 复制目标文件为临时文件，失败返回false
	if (!std::filesystem::copy_file(file_path + name, file_path + file_name)) {
		return false;
	}
	return true;
}

bool FileManager::delete_file(const std::string& name) {
	if (std::filesystem::exists(file_path + name)) {
		std::filesystem::remove(file_path + name);
		return true;
	}
	return false;
}

bool FileManager::creat_temp_file() {
	if (is_file_exist(file_path + file_name)) {
		return true;
	}
	std::ofstream o_file;
	o_file.open(file_path + file_name);
	if (o_file.is_open()) {
		o_file.close();
		return true;
	}
	return false;
}

bool FileManager::save_file() {
	// 临时文件是否存在，不存在则返回false
	if (!is_file_exist(file_path + file_name)) {
		return false;
	}
	// 目标文件是否存在，存在则返回false
	if (is_file_exist(get_current_file_name())) {
		return false;
	}
	// 复制临时文件为目标文件，失败则返回false
	if (!std::filesystem::copy_file(file_path + file_name, get_current_file_name())) {
		return false;
	}
	return true;
}

int FileManager::choose_file() {
	show_file_list();
	int input;
	while (true) {
		std::cout << "输入打开文件序号：";
		std::cin >> input;
		if (input > 0 && input < file_list.size()) {
			std::cout << CLEAR_LINE;
			break;
		}
		std::cout << "输入错误！重新输入!";
	}
	return input;
}

void FileManager::show_file_list() {
	int current_number = 0;
	for (auto file_info : file_list) {
		std::cout << "序号" + file_info.index << "\t";
		std::cout << "名称" + file_info.name << "\t";
		current_number++;
		if (current_number >= max_show_number) {
			std::cout << "\n";
			current_number = 0;
		}
	}
}

void FileManager::reflash_file_name() {
	for (auto file_info : file_list) {
		std::string current_file_name = "Student_" + file_info.index;
		std::filesystem::rename(file_path + file_info.name, file_path + current_file_name);
	}
}

std::string FileManager::get_current_file_name() {
	std::string current_file_name = "Student_" + current_file_index;
	return current_file_name;
}

Student FileManager::get_student_data() {
	Student student_data = {
		.id = "0000000000",
		.name = "错误",
		.gender = true,
		.age = 16,
		.native_place = {
			.province = "错误省份",
			.city = "错误城市",
			.district = "错误区县",
		},
		.phone_number = "00000000000",
	};
	if (!is_file_exist(file_path + file_name)) {
		return student_data;
	}
	std::ifstream i_file;
	i_file.open(file_path + file_name);
	if (!i_file.is_open()) {
		return student_data;
	}
	std::string line;
	std::smatch match;
	while (std::getline(i_file, line)) {
		if (std::regex_search(line, match, id_regex)) {
			all_student.push_back(student_data);
			student_data.id = match.str(0);
			std::regex_search(line, match, name_regex);
			student_data.name = match.str(0);
			std::regex_search(line, match, gender_regex);
			student_data.gender = (match.str(0) == "男") ? true : false;
			std::regex_search(line, match, age_regex);
			student_data.age = std::stoi(match.str(0));
			// --后续添加读取籍贯部分--
			std::regex_search(line, match, phone_number_regex);
			student_data.phone_number = match.str(0);
		}
	}
}
