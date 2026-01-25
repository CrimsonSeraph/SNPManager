//——————————————————————————————————————————————————————注释标准：27个制表符宽度
#include "../include/StudentManager.h"

StudentManager::StudentManager() {
}

StudentManager::~StudentManager() {
}

void StudentManager::change_status() {
	switch (s_status) {
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
		change_to_status(kSAddProvince);
		break;
	case StudentManagerStatus::kSAddProvince:
		change_to_status(kSAddCity);
		break;
	case StudentManagerStatus::kSAddCity:
		change_to_status(kSAddDistrict);
		break;
	case StudentManagerStatus::kSAddDistrict:
		change_to_status(kSAddPhoneNumber);
		break;
	case StudentManagerStatus::kSAddPhoneNumber:
		change_to_status(kSNone);
		break;
	case StudentManagerStatus::kSGetStudentData:
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

void StudentManager::change_to_status(const StudentManagerStatus to_status) {
	s_status = to_status;
	switch (s_status) {
	case StudentManagerStatus::kSAddId:
		add_id();
		change_status();
		break;
	case StudentManagerStatus::kSAddName:
		add_name();
		change_status();
		break;
	case StudentManagerStatus::kSAddGender:
		add_gender();
		change_status();
		break;
	case StudentManagerStatus::kSAddAge:
		add_age();
		change_status();
		break;
	case StudentManagerStatus::kSAddProvince:
		add_province();
		change_status();
		break;
	case StudentManagerStatus::kSAddCity:
		add_city();
		change_status();
		break;
	case StudentManagerStatus::kSAddDistrict:
		add_district();
		change_status();
		break;
	case StudentManagerStatus::kSAddPhoneNumber:
		add_phone_number();
		change_status();
		break;
	case StudentManagerStatus::kSGetStudentData:
		all_student = file_manager.get_student_data();
		change_status();
		break;
	case StudentManagerStatus::kSStartLoad:
		start_load();
		change_status();
		break;
	default:
	case StudentManagerStatus::kSNone:
		break;
	}
}

void StudentManager::start_load() {
	file_manager.change_to_status(FileManagerStatus::kFStartLoad);
	file_manager.change_to_status(FileManagerStatus::kFLoadStudentData);
	change_to_status(kSAddId);
}

void StudentManager::add_id() {
	std::cout << "当前输入 学号：10位数字，唯一标识，不能重复\n";
	std::string i_id = enter_as_regex(AllRegex::get_id_regex());
	std::cout << CLEAR_CUR_AND_PREV_LINE;
	// 边界检查：如果索引越界，则不进行赋值
	if (all_student.size() <= index) {
		return;
	}
	// 将读取到的 ID 写入当前学生记录
	all_student[index].id = i_id;
}

void StudentManager::add_name() {
	std::cout << "当前输入 姓名：2-5个中文字符，支持复姓\n";
	std::string i_name = enter_as_regex(AllRegex::get_name_regex());
	std::cout << CLEAR_CUR_AND_PREV_LINE;
	// 边界检查：如果索引越界，则不进行赋值
	if (all_student.size() <= index) {
		return;
	}
	all_student[index].name = i_name;
}

void StudentManager::add_gender() {
	std::cout << "当前输入 性别：1/0 或 男/女，单选输入\n";
	std::string i_gender = enter_as_regex(AllRegex::get_gender_regex());
	std::cout << CLEAR_CUR_AND_PREV_LINE;
	// 边界检查：如果索引越界，则不进行赋值
	if (all_student.size() <= index) {
		return;
	}
	bool true_gender = true;
	if (i_gender == "女" || i_gender == "0") {
		true_gender = false;
	}
	all_student[index].name = true_gender;
}

void StudentManager::add_age() {
	std::cout << "当前输入 年龄：16-30岁整数，需要符合大学生年龄范围\n";
	std::string i_age = enter_as_regex(AllRegex::get_age_regex());
	std::cout << CLEAR_CUR_AND_PREV_LINE;
	// 边界检查：如果索引越界，则不进行赋值
	if (all_student.size() <= index) {
		return;
	}
	// 使用 std::stoi 将字符串转为整数（假定正则已保证格式合法）
	all_student[index].age = std::stoi(i_age);
}

void StudentManager::add_province() {
	currect_number = 0;
	print_province();
	std::cout << "请选择省份，输入省份前的序号：";
	current_province = choose_from_vector(AreaData::get_province_names());
	std::cout << CLEAR_CUR_AND_PREV_LINE;
	all_student[index].native_place.province = current_province;

}

void StudentManager::add_city() {
	if (current_province.empty()) {
		change_to_status(StudentManagerStatus::kSAddProvince);
		return;
	}
	currect_number = 0;
	print_city(current_province);
	std::cout << "请选择城市，输入城市前面的序号：";
	current_city = choose_from_vector(AreaData::get_cities_names_by_province(current_province));
	std::cout << CLEAR_CUR_AND_PREV_LINE;
	all_student[index].native_place.city = current_city;
}

void StudentManager::add_district() {
	if (current_province.empty()) {
		change_to_status(StudentManagerStatus::kSAddProvince);
		return;
	}
	if (current_city.empty()) {
		change_to_status(StudentManagerStatus::kSAddCity);
		return;
	}
	currect_number = 0;
	print_district(current_province, current_city);
	std::cout << "请选择区/县，输入区/县前面的序号：";
	std::string current_district = choose_from_vector(AreaData::get_districts_names_by_province_city(current_province, current_city));
	std::cout << CLEAR_CUR_AND_PREV_LINE;
	all_student[index].native_place.city = current_district;
}

void StudentManager::add_phone_number() {
	std::cout << "当前输入 联系方式：11位手机号\n";
	std::string i_phone_number = enter_as_regex(AllRegex::get_phone_number_regex());
	// 边界检查：如果索引越界，则不进行赋值
	std::cout << CLEAR_CUR_AND_PREV_LINE;
	if (all_student.size() <= index) {
		return;
	}
	all_student[index].phone_number = i_phone_number;
}

void StudentManager::print_province() {
	int count = 0;																							// 当前行已输出项数
	int prince_index = 0;																					// 省份编号（从 1 开始）
	// 遍历所有省份名称并格式化输出
	for (const std::string prince_name : AreaData::get_province_names()) {
		prince_index++;
		// 显示格式 "编号:名称"
		std::string show_district = std::to_string(prince_index) + ":" + prince_name;
		// 使用 setw 和 left 保持向左列对齐
		std::cout << std::setw(prince_field_width) << std::left << show_district;
		count++;
		if (count >= max_province_show_number) {
			// 换行并重置计数，控制每行显示数量
			std::cout << "\n";
			count = 0;
		}
	}
	// 如果最后一行未满也需要换行
	if (count > 0) {
		std::cout << "\n";
	}
	// 将当前可选项数量记录到 currect_number（用于后续输入验证）
	currect_number = prince_index;
}

void StudentManager::print_city(const std::string& province_name) {
	int count = 0;
	int city_index = 0;
	for (const std::string city_name : AreaData::get_cities_names_by_province(province_name)) {
		city_index++;
		std::string show_city = std::to_string(city_index) + ":" + city_name;
		std::cout << std::setw(city_field_width) << std::left << show_city;
		count++;
		if (count >= max_city_show_number) {
			std::cout << "\n";
			count = 0;
		}
	}
	if (count > 0) {
		std::cout << "\n";
	}
	currect_number = city_index;
}

void StudentManager::print_district(const std::string& province_name, const std::string& city_name) {
	int count = 0;
	int district_index = 0;
	for (const std::string district_name : AreaData::get_districts_names_by_province_city(province_name, city_name)) {
		district_index++;
		std::string show_district = std::to_string(district_index) + ":" + district_name;
		std::cout << std::setw(district_field_width) << std::left << show_district;
		count++;
		if (count >= max_district_show_number) {
			std::cout << "\n";
			count = 0;
		}
	}
	if (count > 0) {
		std::cout << "\n";
	}
	currect_number = district_index;
}

void StudentManager::reload_index() {
}

std::string StudentManager::choose_from_vector(const std::vector<std::string>& all_string) {
	int choose_index = 0;
	while (true) {
		std::cin >> choose_index;
		if (std::cin.fail()) {
			std::cin.clear();
			while (std::cin.get() != '\n' || std::cin.get() != EOF) {
				std::cin.ignore();
			}
		}
		break;
	}
	return all_string[choose_index];
}

// 封装的正则输入读取函数：不断读取直到输入匹配给定正则
// 参数：i_regex - 期望匹配的 std::regex
// 返回：匹配成功的原始输入字符串
std::string StudentManager::enter_as_regex(std::regex i_regex) {
	std::cout << "请输入：";
	std::string input;
	while (true) {
		// 从标准输入读取单词（以空白分隔）
		std::cin >> input;
		// 如果匹配，清除行显示后返回
		if (std::regex_match(input, i_regex)) {
			std::cout << CLEAR_CUR_AND_PREV_LINE;
			break;
		}
		// 不匹配则清除行并继续等待输入
		std::cout << CLEAR_CUR_AND_PREV_LINE;
		std::cout << "输入错误！请重新输入：";
	}
	return input;
}
