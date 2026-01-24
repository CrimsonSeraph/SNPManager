//——————————————————————————————————————————————————————注释标准：27个制表符宽度
#include "../include/StudentManager.h"
#include <Windows.h>
#include <iostream>

int main() {
	// 设置控制台输出为 UTF-8
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	StudentManager student_manager;
	student_manager.change_to_status(StudentManagerStatus::kSStartLoad);

	return 0;
}