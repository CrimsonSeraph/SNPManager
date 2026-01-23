import json
import sys

def load_json_file(filename):
    """加载JSON文件"""
    try:
        with open(filename, 'r', encoding='utf-8') as f:
            return json.load(f)
    except FileNotFoundError:
        print(f"错误: 找不到文件 {filename}")
        sys.exit(1)
    except json.JSONDecodeError as e:
        print(f"错误: {filename} 不是有效的JSON格式 - {e}")
        sys.exit(1)

def transform_data(provinces_data, cities_data, areas_data):
    """
    将省、市、区数据转换为层级结构
    
    返回结构:
    [
        {
            "name": "省份名",
            "cities": [
                {
                    "name": "城市名",
                    "districts": ["区名1", "区名2", ...]
                },
                ...
            ]
        },
        ...
    ]
    """
    # 构建数据索引
    provinces_by_code = {p["code"]: p["name"] for p in provinces_data}
    cities_by_code = {}
    
    # 按省份组织城市数据
    cities_by_province = {}
    for city in cities_data:
        province_code = city["provinceCode"]
        if province_code not in cities_by_province:
            cities_by_province[province_code] = []
        cities_by_province[province_code].append(city)
        cities_by_code[city["code"]] = city
    
    # 按城市组织区数据
    areas_by_city = {}
    for area in areas_data:
        city_code = area["cityCode"]
        if city_code not in areas_by_city:
            areas_by_city[city_code] = []
        areas_by_city[city_code].append(area["name"])
    
    # 构建最终结果
    result = []
    
    for province in provinces_data:
        province_code = province["code"]
        province_name = province["name"]
        
        # 获取该省份下的所有城市
        province_cities = []
        
        # 处理该省份的城市
        if province_code in cities_by_province:
            for city_data in cities_by_province[province_code]:
                city_code = city_data["code"]
                city_name = city_data["name"]
                
                # 特殊处理直辖市：将"市辖区"替换为直辖市名称
                if city_name == "市辖区" and province_name.endswith("市"):
                    city_name = province_name
                
                # 获取该城市下的所有区
                districts = areas_by_city.get(city_code, [])
                
                # 按区名排序（可选）
                districts.sort()
                
                # 添加到城市列表
                province_cities.append({
                    "name": city_name,
                    "districts": districts
                })
        
        # 按城市名排序（可选）
        province_cities.sort(key=lambda x: x["name"])
        
        # 添加到省份列表
        result.append({
            "name": province_name,
            "cities": province_cities
        })
    
    # 按省份名排序（可选）
    result.sort(key=lambda x: x["name"])
    
    return result

def generate_cpp_code(transformed_data, output_filename=None):
    """
    生成C++代码
    
    Args:
        transformed_data: 转换后的数据
        output_filename: 输出文件名，如果为None则打印到控制台
    """
    cpp_code = """#include <string>
#include <vector>
#include <unordered_map>

struct City {
    std::string name;
    std::vector<std::string> districts;
};

struct Province {
    std::string name;
    std::vector<City> cities;
};

static std::vector<Province> data = {
"""
    
    # 生成每个省份的数据
    for i, province in enumerate(transformed_data):
        province_name = province["name"]
        cities = province["cities"]
        
        cpp_code += f'    {{"{province_name}", {{\n'
        
        for j, city in enumerate(cities):
            city_name = city["name"]
            districts = city["districts"]
            
            # 生成区列表
            districts_str = ", ".join([f'"{d}"' for d in districts])
            
            cpp_code += f'        {{"{city_name}", {{{districts_str}}}}},\n'
        
        # 移除最后一个城市后的逗号（如果有城市的话）
        if cities:
            cpp_code = cpp_code.rstrip(',\n') + '\n'
        
        cpp_code += '    }},\n' if i < len(transformed_data) - 1 else '    }}\n'
    
    cpp_code += "};\n"
    
    # 输出到文件或控制台
    if output_filename:
        with open(output_filename, 'w', encoding='utf-8') as f:
            f.write(cpp_code)
        print(f"转换完成！C++代码已保存到 {output_filename}")
    else:
        print(cpp_code)
    
    return cpp_code

def main():
    """主函数"""
    print("开始转换中国行政区划数据...")
    
    # 加载JSON数据
    print("1. 加载JSON文件...")
    provinces_data = load_json_file("provinces.json")
    cities_data = load_json_file("cities.json")
    areas_data = load_json_file("areas.json")
    
    print(f"   - 加载了 {len(provinces_data)} 个省份")
    print(f"   - 加载了 {len(cities_data)} 个城市")
    print(f"   - 加载了 {len(areas_data)} 个区/县")
    
    # 转换数据
    print("2. 转换数据结构...")
    transformed_data = transform_data(provinces_data, cities_data, areas_data)
    
    # 统计信息
    total_cities = sum(len(province["cities"]) for province in transformed_data)
    total_districts = sum(
        len(city["districts"]) 
        for province in transformed_data 
        for city in province["cities"]
    )
    
    print(f"   - 转换了 {len(transformed_data)} 个省份")
    print(f"   - 转换了 {total_cities} 个城市")
    print(f"   - 转换了 {total_districts} 个区")
    
    # 生成C++代码
    print("3. 生成C++代码...")
    output_file = "china_regions.cpp"
    cpp_code = generate_cpp_code(transformed_data, output_file)
    
    print("\n转换完成！")
    print(f"生成的C++文件: {output_file}")
    print(f"文件大小: {len(cpp_code)} 字符")
    
    # 显示一些示例数据
    print("\n示例数据（前3个省份）:")
    for i, province in enumerate(transformed_data[:3]):
        print(f"{i+1}. {province['name']}: {len(province['cities'])}个城市")
        for j, city in enumerate(province['cities'][:2]):  # 只显示前2个城市
            print(f"   - {city['name']}: {len(city['districts'])}个区")
            if j == 1 and len(province['cities']) > 2:
                print(f"   - ...（还有{len(province['cities'])-2}个城市）")
                break
        if i == 2 and len(transformed_data) > 3:
            print(f"...（还有{len(transformed_data)-3}个省份）")
            break

if __name__ == "__main__":
    main()