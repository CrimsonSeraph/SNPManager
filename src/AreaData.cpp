#include "../include/AreaData.h"

const std::vector<Province>& AreaData::get_province_data() {
	static std::vector<Province> data = {
		{"北京市", {
			{"北京市", {"东城区", "西城区", "朝阳区", "丰台区", "石景山区", "海淀区"}}
		}},
		{"上海市", {
			{"上海市", {"黄浦区", "徐汇区", "长宁区", "静安区", "普陀区"}}
		}},
		{"广东省", {
			{"广州市", {"天河区", "越秀区", "海珠区", "荔湾区", "白云区"}},
			{"深圳市", {"福田区", "罗湖区", "南山区", "宝安区", "龙岗区"}}
		}}
	};
	return data;
}
