/*
伏尔戈 10000002
get all 606to1006 buy max and print
C++对象序列化的四种方法:
Google Protocol Buffers（protobuf） 高效.语言中立(Cpp, Java, Python) .可扩展 :protobuf支持的数据类型不是很丰富,不支持STL容器序列化
Boost.Serialization                 可以序列化STL容器和其他常用模版库
MFC Serialization
.Net Framework
*/
#include <stdio.h>
#include <iostream>  
#include <curl/curl.h>    
#include "tinyxml2.h"
#include <utility>   //pair head file
#include <map>       //map head file
#include <sstream>   //sstream


using namespace std;
using namespace tinyxml2;

double xml_print(XMLElement* titleElement);
string Get_url(string input);
double print_max_buy(string input);
map<string, string> my_data_base();
//string类型的序列化和反序列化：
//void serialize(char* sendBuf, const string& str, int& step);
//void deserialize(string& str, const char* recvBuf, int& step);

size_t receive_data(void* buffer, size_t size, size_t nmemb, FILE* file) 
{
	size_t r_size = fwrite(buffer, size, nmemb, file);
	return r_size;
}

int write_data()
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile("save_file.xml");
	//doc.Parse(xml);

	XMLElement* titleElement;
	//const char* title;
	//const char* contain_text;
	char path1[] = "cevemarket";
	char path2[] = "all";
	char path3[] = "max";
	printf("\n*********\n");
	//
	printf("all:\n");
	titleElement = doc.FirstChildElement(path1)->FirstChildElement(path2)->FirstChildElement("max");
	xml_print(titleElement);
	titleElement = doc.FirstChildElement(path1)->FirstChildElement(path2)->FirstChildElement("min");
	xml_print(titleElement);
	titleElement = doc.FirstChildElement(path1)->FirstChildElement(path2)->FirstChildElement("volume");
	xml_print(titleElement);
	//
	printf("buy:\n");
	titleElement = doc.FirstChildElement(path1)->FirstChildElement("buy")->FirstChildElement("max");
	xml_print(titleElement);
	titleElement = doc.FirstChildElement(path1)->FirstChildElement("buy")->FirstChildElement("min");
	xml_print(titleElement);
	titleElement = doc.FirstChildElement(path1)->FirstChildElement("buy")->FirstChildElement("volume");
	xml_print(titleElement);
	//
	printf("sell:\n");
	titleElement = doc.FirstChildElement(path1)->FirstChildElement("sell")->FirstChildElement("max");
	xml_print(titleElement);
	titleElement = doc.FirstChildElement(path1)->FirstChildElement("sell")->FirstChildElement("min");
	xml_print(titleElement);
	titleElement = doc.FirstChildElement(path1)->FirstChildElement("sell")->FirstChildElement("volume");
	xml_print(titleElement);
	//
	return doc.ErrorID();
}

double xml_print(XMLElement* titleElement)
{
	//XMLElement* titleElement = xml_name.FirstChildElement(xml_path1)->FirstChildElement(xml_path2)->FirstChildElement(xml_path3);
	//node->Value() //获取节点的名称
	//node->GetText() //获取节点里面的文本，但是不包含里面的节点
	const char* title = titleElement->Value();
	const char* contain_text = titleElement->GetText();
	//printf("%s:%s\n", title, contain_text);
	string s(contain_text);//将const char*转换为string
	//接下来的几行代码是将string转换为double,使用的是<sstream>
	stringstream stream;
	double market_price;
	stream << s;
	stream >> market_price;
	//判断单位大小，并根据单位做不同的打印
	if (market_price>1e8)
	{
		cout << title << ":" << /*contain_text*/ (market_price/1e8)<<"亿" << endl;
	}
	else
	{
		if (market_price > 1e4)
		{
			cout << title << ":" << /*contain_text*/ (market_price/1e4)<<"万" << endl;
		}
		else
		{
			cout << title << ":" << /*contain_text*/ market_price << endl;
		}
	}
	return market_price;
}

int main(void)
{
	/*
	CURL* curl;
	//CURLcode res;
	//tinyxml2::XMLDocument ceapi;
	char path[] = "save_file.xml";
	FILE* file = fopen(path, "w");
	//input url:
	string test_str;
	string test_input = "34";
	test_str = Get_url(test_input);
	cout <<"Test input Url:" <<test_str << endl;
	//
	curl_global_init(CURL_GLOBAL_DEFAULT);

	curl = curl_easy_init();
	if (curl) {
		//curl_easy_setopt(curl, CURLOPT_URL, "https://www.ceve-market.org/api/market/region/10000002/type/34.xml");
		//string到char*的转换使用data()函数
		curl_easy_setopt(curl, CURLOPT_URL, data(test_str));
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, receive_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
		cout << curl_easy_perform(curl);
		fclose(file);
		//if (res != CURLE_OK)
		//{ 
		//	fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		//}
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();

	write_data();
	*/
	/////////////////////////////////////////////////////////////////
	map<string, string> My_DataBase;
	map<string, double> good_goods;
	double market_price;
	My_DataBase=my_data_base();
	//string input[5] = { "3140","3198","3215","3224","3482" };
	for (auto i= My_DataBase.begin();i!= My_DataBase.end();++i)
	{
		cout << "" << i->second << "";
		market_price = print_max_buy(i->first);
		if (market_price > 2e9)
		{
			good_goods.emplace(i->second, market_price);
		}
	}
	/////////////////////////////////////////////////////////////////
	cout << "*********" << endl;
	cout << "优质商品及其价格" << endl;
	for (auto i = good_goods.begin(); i != good_goods.end(); ++i)
	{
		cout << i->first << ":" << (i->second/1e8)<<"亿" << endl;
	}
	/////////////////////////////////////////////////////////////////
	cout << "请按任意键结束程序" << endl;
	getchar();
	return 0;
}


string Get_url(string input)
{
	string url_part1= "https://www.ceve-market.org/api/market/region/10000002/type/";
	string url_part2= ".xml";

	string output;
	output = url_part1 + input + url_part2;

	return output;
}

//get number and print max buy
double print_max_buy(string input)
{
	string test_str_s   = Get_url(input);
	double market_price;
	char path[] = "save_buy.xml";
	FILE* file = fopen(path, "w");

	CURL* curl;
	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, data(test_str_s));
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, receive_data);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
	cout << curl_easy_perform(curl);
	fclose(file);
	curl_easy_cleanup(curl);
    curl_global_cleanup();

	//parse xml:
	tinyxml2::XMLDocument doc;
	doc.LoadFile("save_buy.xml");
	//printf("%s buy max:\n",data(input));
	cout << input << " buy max :" << endl;
	XMLElement* titleElement = doc.FirstChildElement("cevemarket")->FirstChildElement("buy")->FirstChildElement("max");
	market_price=xml_print(titleElement);
	//titleElement = doc.FirstChildElement("cevemarket")->FirstChildElement("buy")->FirstChildElement("volume");
	//xml_print(titleElement);
	return market_price;
}

map<string, string> my_data_base()
{
	//pair<string, string> pair1("3140"," RL-1006");
	map<string, string> myMap;
	
	myMap.emplace("3198","LP-1006");
	myMap.emplace("3140", "RL-1006");
	myMap.emplace("3215", "天赋植体 枪骑兵 大型能量炮台 LE-1006");
	myMap.emplace("3224", "载诺 狙击手 大型混合炮台 LH-1006");
	myMap.emplace("3482", "天赋植体 诺贝尔 船体升级 HG-1006");
	myMap.emplace("3475", "天赋植体 诺贝尔 机械学 MC-806");
	myMap.emplace("3470", "天赋植体 诺贝尔 远距装甲维修系统 RA-706");
	myMap.emplace("3267", "载诺 吉普赛 CPU管理 EE-606");
	myMap.emplace("3258", "天赋植体 随从 能量栅格管理 EG-606");
	myMap.emplace("3255", "天赋植体 随从 能量栅格提升 EU-706");
	myMap.emplace("3252", "天赋植体 随从 能量脉冲武器 EP-706");
	myMap.emplace("3246", "天赋植体 随从 电容系统操作 EO-606");
	myMap.emplace("3239", "天赋植体 随从 电容管理 EM-806");
	myMap.emplace("3235", "载诺 狙击手 精确射击 ST-906");
	myMap.emplace("3233", "载诺 狙击手 中型混合炮台 MH-806");
	myMap.emplace("3230", "载诺 侏儒 武器升级 WU-1006");
	myMap.emplace("3221", "载诺 狙击手 弹道分析 TA-706");
	myMap.emplace("3216", "天赋植体 枪骑兵 中型能量炮台 ME-806");
	myMap.emplace("3213", "天赋植体 枪骑兵 受控点射 CB-706");
	myMap.emplace("3195", "埃菲尔公司 神枪手 外科打击 SS-906");
	myMap.emplace("3192", "埃菲尔公司 神枪手 航迹预算 MR-706");
	myMap.emplace("3189", "埃菲尔公司 神枪手 中型射弹炮台 MP-806");
	myMap.emplace("3183", "载诺 快照 巡航导弹 CM-606");
	myMap.emplace("3172", "载诺 快照 轻型导弹 LM-906");
	myMap.emplace("3167", "载诺 快照 重型导弹 HM-706");
	myMap.emplace("3159", "载诺 快照 重型攻击导弹 AM-706");
	myMap.emplace("3143", "载诺 狙击手 目标导航预测 TN-906");
	myMap.emplace("3135", "载诺 狙击手 导弹动力 MP-706");
	myMap.emplace("3127", "载诺 狙击手 导弹精确打击 GP-806");
	myMap.emplace("3124", "埃菲尔公司 游侠 加速控制 AC-606");
	myMap.emplace("3116", "埃菲尔公司 游侠 高速机动 HS-906");
	myMap.emplace("3095", "埃菲尔公司 游侠 规避机动 EM-706");
	myMap.emplace("3084", "载诺 侏儒 护盾管理 SM-706");
	myMap.emplace("3079", "载诺 侏儒 护盾升级 SU-606");
	myMap.emplace("54732", "唤风级");
	myMap.emplace("54786", "超级电击 M");
	myMap.emplace("54785", "超级狙击 M");
	//myMap.emplace("", "");
	//myMap.emplace("", "");
	return myMap;
}

//string类型的序列化和反序列化：
//void serialize(char* sendBuf, const string& str, int& step)
//{
//	int size;
//	size = str.length();
//	serialize(sendBuf, &size, step);
//	memcpy(sendBuf + step, &str[0], size);
//	step += size;
//}
//
//void deserialize(string& str, const char* recvBuf, int& step)
//{
//
//	int size;
//	deserialize(&size, recvBuf, step);
//	str = string(recvBuf + step, size);//用构造函数生成临时变量，然后进行赋值
//	step += size;
//}

//使用MFC序列化map:
//void MyClass::Serialize(CArchive& archive)
//{
//	CObject::Serialize(archive);
//	if (archive.IsStoring()) {
//		archive << m_map.size(); // save element count
//		std::map<int, MapData>::const_iterator iter = m_map.begin(), iterEnd = m_map.end();
//		for (; iter != iterEnd; iter++) {
//			archive << iter->first << iter->second;
//		}
//	}
//	else {
//		m_map.clear();
//		size_t mapSize = 0;
//		archive >> mapSize; // read element count
//		for (size_t i = 0; i < mapSize; ++i) {
//			int key;
//			MapData value;
//			archive >> key;
//			archive >> value;
//			m_map[key] = value;
//		}
//	}
//}