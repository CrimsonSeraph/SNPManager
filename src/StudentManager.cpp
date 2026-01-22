#include "../include/StudentManager.h"

StudentManager::StudentManager() {
}

StudentManager::~StudentManager() {
}

void StudentManager::change_status() {
	switch (status) {
	case StudentManagerStatus::kSAddId:
		change_to_status(kSAddName);
		break;
	case StudentManagerStatus::kSAddName:
		change_to_status(kSAddGender);
		break;
	case StudentManagerStatus::kSAddGender:
		change_to_status(kSAddAge);
		break;
	case StudentManagerStatus::kSAddAge:
		change_to_status(kSAddNativePlace);
		break;
	case StudentManagerStatus::kSAddNativePlace:
		change_to_status(kSAddPhoneNumber);
		break;
	case StudentManagerStatus::kSAddPhoneNumber:
		change_to_status(kSNone);
		break;
	case StudentManagerStatus::kSStartLoad:
		change_to_status(kSNone);
		break;
	default:
	case StudentManagerStatus::kSNone:
		break;
	}
}

void StudentManager::change_to_status(StudentManagerStatus to_status) {
	status = to_status;
	switch (to_status) {
	case StudentManagerStatus::kSAddId:
		add_id();
		break;
	case StudentManagerStatus::kSAddName:
		add_name();
		break;
	case StudentManagerStatus::kSAddGender:
		add_gender();
		break;
	case StudentManagerStatus::kSAddAge:
		add_age();
		break;
	case StudentManagerStatus::kSAddNativePlace:
		add_native_place();
		break;
	case StudentManagerStatus::kSAddPhoneNumber:
		add_phone_number();
		break;
	case StudentManagerStatus::kSStartLoad:
		start_load();
		break;
	default:
	case StudentManagerStatus::kSNone:
		break;
	}
}

void StudentManager::start_load() {
	file_manager.change_to_status(FileManagerStatus::kFStartLoad);
	file_manager.change_to_status(FileManagerStatus::kFChooseFile);
}

void StudentManager::add_id() {
	std::cout << "当前输入 学号：10位数字，唯一标识，不能重复\n";
	std::string i_id = enter_as_regex(AllRegex::get_id_regex());
	std::cout << CLEAR_LINE;
	all_student[index].id = i_id;
}

void StudentManager::add_name() {
	std::cout << "当前输入 姓名：2-5个中文字符，支持复姓\n";
	std::string i_name = enter_as_regex(AllRegex::get_name_regex());
	std::cout << CLEAR_LINE;
	all_student[index].name = i_name;
}

void StudentManager::add_gender() {
	std::cout << "当前输入 性别：0 -> 女 | 1 -> 男\n";
	while (true) {
		int input;
		if (std::cin >> input) {
			if (input == 0 || input == 1) {
				all_student[index].gender = static_cast<bool>(input);
			}
			else {
				std::cout << CLEAR_LINE;
				std::cout << "\n输入错误！请重新选择：";
				continue;
			}
		}
		else {
			std::cout << CLEAR_LINE;
			std::cout << "\n输入错误！请重新选择：";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
	}
}

void StudentManager::add_age() {
	std::cout << "当前输入 年龄：16-30岁整数，需符合大学生年龄范围\n";
	std::string i_age = enter_as_regex(AllRegex::get_age_regex());
	std::cout << CLEAR_LINE;
	all_student[index].age = std::stoi(i_age);
}

void StudentManager::add_native_place() {
	// --后续添加籍贯添加部分--
}

void StudentManager::add_phone_number() {
	std::cout << "当前输入 联系方式：11位手机号\n";
	std::string i_phone_number = enter_as_regex(AllRegex::get_phone_number_regex());
	std::cout << CLEAR_LINE;
	all_student[index].phone_number = i_phone_number;
}

std::string StudentManager::enter_as_regex(std::regex i_regex) {
	std::cout << "请输入/选择：";
	std::string input;
	while (true) {
		std::cin >> input;
		if (std::regex_match(input, i_regex)) {
			std::cout << CLEAR_LINE;
			break;
		}
		std::cout << CLEAR_LINE;
		std::cout << "输入格式错误！请重新输入/选择：";
	}
	return input;
}
