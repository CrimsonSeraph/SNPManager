#include "../include/StudentManager.h"
#include <iostream>

int main() {
	StudentManager student_manager;
	student_manager.change_to_status(StudentManagerStatus::kSStartLoad);

	return 0;
}