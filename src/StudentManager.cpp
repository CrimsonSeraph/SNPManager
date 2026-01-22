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
