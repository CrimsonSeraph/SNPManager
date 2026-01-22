#include "../include/StudentManager.h"

StudentManager::StudentManager() {
}

StudentManager::~StudentManager() {
}

void StudentManager::change_status() {
	switch (status) {
	case StudentManagerStatus::kAddId:
		change_to_status(kAddName);
		break;
	case StudentManagerStatus::kAddName:
		change_to_status(kAddGender);
		break;
	case StudentManagerStatus::kAddGender:
		change_to_status(kAddAge);
		break;
	case StudentManagerStatus::kAddAge:
		change_to_status(kAddNativePlace);
		break;
	case StudentManagerStatus::kAddNativePlace:
		change_to_status(kAddPhoneNumber);
		break;
	case StudentManagerStatus::kAddPhoneNumber:
		change_to_status(kNone);
		break;
	default:
	case StudentManagerStatus::kNone:
		break;
	}
}

void StudentManager::change_to_status(StudentManagerStatus to_status) {
	status = to_status;
	switch (to_status) {
	case StudentManagerStatus::kAddId:
		break;
	case StudentManagerStatus::kAddName:
		break;
	case StudentManagerStatus::kAddGender:
		break;
	case StudentManagerStatus::kAddAge:
		break;
	case StudentManagerStatus::kAddNativePlace:
		break;
	case StudentManagerStatus::kAddPhoneNumber:
		break;
	default:
	case StudentManagerStatus::kNone:
		break;
	}
}

void StudentManager::add_id() {
	std::cout << "当前输入 学号：10位数字，唯一标识，不能重复\n";
	std::cout << "请输入：";
	std::string i_id = enter_as_regex(id_regex);
	all_student[index].id = i_id;
}

void StudentManager::add_name() {
	std::cout << "当前输入 姓名：2-5个中文字符，支持复姓\n";
	std::cout << "请输入：";
	std::string i_name = enter_as_regex(name_regex);
	all_student[index].name = i_name;
}

void StudentManager::add_gender() {
	std::cout << "当前输入 性别：0 -> 女 | 1 -> 男\n";
	std::cout << "请选择：";
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
	std::cout << "请选择：";
	while (true) {
		int input;
		if (std::cin >> input) {
			if (input >= 16 && input <= 30) {
				all_student[index].age = input;
				break;
			}
			else {
				std::cout << CLEAR_LINE;
				std::cout << "\n输入错误！请重新输入：";
				continue;
			}
		}
		else {
			std::cout << CLEAR_LINE;
			std::cout << "\n输入错误！请重新输入：";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
	}
}

void StudentManager::add_native_place() {
}

void StudentManager::add_phone_number() {
	std::cout << "当前输入 联系方式：11位手机号\n";
	std::cout << "请输入：";
	std::string i_phone_number = enter_as_regex(phone_number_regex);
	all_student[index].phone_number = i_phone_number;
}

std::string StudentManager::enter_as_regex(std::regex i_regex) {
	std::string input;
	while (true) {
		std::cin >> input;
		if (std::regex_match(input, i_regex)) {
			std::cout << CLEAR_LINE;
			break;
		}
		std::cout << CLEAR_LINE;
		std::cout << "\n输入格式错误！请重新输入：";
	}
	return input;
}
