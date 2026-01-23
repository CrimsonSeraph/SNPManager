#include "AllRegex.h"

const std::regex& AllRegex::get_id_regex() {
	// 学号正则表达式：10位数字
	static std::regex id_regex = std::regex(R"([0-9]{10})");
	return id_regex;
}

const std::regex& AllRegex::get_name_regex() {
	// 姓名正则表达式：2-5个中文字符
	// commented by ChatGPT-5 mini:
	// 注意：std::regex 默认使用 char 类型，不能直接用 \u4e00-\u9fa5，需要用 UTF-8 字节范围匹配
	// 匹配2-5个中文字符（UTF-8编码下的汉字字节范围：[\xE4-\xE9][\x80-\xBF][\x80-\xBF]）
	static std::regex name_regex = std::regex(R"(([\xE4-\xE9][\x80-\xBF]{2}){2,5})");
	return name_regex;
}

const std::regex& AllRegex::get_gender_regex() {
	// 性别正则表达式：女 | 男
	static std::regex gender_regex = std::regex(R"((女|男))");
	return gender_regex;
}

const std::regex& AllRegex::get_age_regex() {
	// 年龄正则表达式：16-30岁整数
	static std::regex age_regex = std::regex(R"((1[6-9]|2[0-9]|30))");
	return age_regex;
}

const std::regex& AllRegex::get_phone_number_regex() {
	// 联系方式正则表达式：11位手机号
	static std::regex phone_number_regex = std::regex(R"((1[3-9][0-9]{9}))");
	return phone_number_regex;
}

const std::regex& AllRegex::get_file_name_regex() {
	// 目标文件名正则表达式(实例：Student_1.txt)
	static std::regex file_name_regex = std::regex(R"(students_[0-9]{1,}\.txt)");
	return file_name_regex;
}
