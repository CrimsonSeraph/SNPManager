//——————————————————————————————————————————————————————注释标准：27个制表符宽度
#include "AllRegex.h"

const std::regex& AllRegex::get_id_regex() {
	// 学号正则表达式：10位数字
	static std::regex id_regex = std::regex(R"([0-9]{10})");
	return id_regex;
}

const std::regex& AllRegex::get_name_regex() {
	// 姓名正则表达式：2-5个中文字符（UTF-8 三字节通用匹配）
	// comment by ChatGPT-5 mini:
	// 说明：
	// - 改为匹配 UTF-8 三字节序列的起始字节范围 [\xE0-\xEF]，配合两个续字节 [\x80-\xBF]
	// - 整体匹配 2 到 5 个这样的三字节字符
	// 注意：
	// - 确保源文件和输入字符串均为 UTF-8 编码，否则匹配会失败。
	// - 若需要更完善的 Unicode 支持（例如覆盖四字节字符或使用 Unicode 属性），
	//   建议改用 std::wstring/std::wregex（在合适的 locale 下）或使用 ICU。
	static std::regex name_regex = std::regex(R"((([\xE0-\xEF][\x80-\xBF][\x80-\xBF]){2,5}))");
	return name_regex;
}

const std::regex& AllRegex::get_gender_regex() {
	// 性别正则表达式：女 | 男
	static std::regex gender_regex = std::regex(R"((女|男|1|0))");
	return gender_regex;
}

const std::regex& AllRegex::get_age_regex() {
	// 年龄正则表达式：16-30岁整数
	static std::regex age_regex = std::regex(R"((1[6-9]|2[0-9]|30))");
	return age_regex;
}

const std::regex& AllRegex::get_native_place_regex() {
	// 文件存储的籍贯格式对应的正则表达式：XX，XX，XX（由于存在非省、市等常规结尾名称，通过，识别）
	static std::regex native_place_regex = std::regex(R"(([\xE0-\xEF][\x80-\xBF][\x80-\xBF]){3,7}),([\xE0-\xEF][\x80-\xBF][\x80-\xBF]){3,7}),([\xE0-\xEF][\x80-\xBF][\x80-\xBF]){2,8}))");
	return native_place_regex;
}

const std::regex& AllRegex::get_phone_number_regex() {
	// 联系方式正则表达式：11位手机号
	static std::regex phone_number_regex = std::regex(R"(([0-9]{11}))");
	return phone_number_regex;
}

const std::regex& AllRegex::get_file_name_regex() {
	// 目标文件名正则表达式(实例：students_1.txt)
	static std::regex file_name_regex = std::regex(R"(Students_[0-9]{1,}\.txt)");
	return file_name_regex;
}
