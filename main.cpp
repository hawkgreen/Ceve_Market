/*
������ 10000002
get all 606to1006 buy max and print
C++�������л������ַ���:
Google Protocol Buffers��protobuf�� ��Ч.��������(Cpp, Java, Python) .����չ :protobuf֧�ֵ��������Ͳ��Ǻܷḻ,��֧��STL�������л�
Boost.Serialization                 �������л�STL��������������ģ���
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
//string���͵����л��ͷ����л���
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
	//node->Value() //��ȡ�ڵ������
	//node->GetText() //��ȡ�ڵ�������ı������ǲ���������Ľڵ�
	const char* title = titleElement->Value();
	const char* contain_text = titleElement->GetText();
	//printf("%s:%s\n", title, contain_text);
	string s(contain_text);//��const char*ת��Ϊstring
	//�������ļ��д����ǽ�stringת��Ϊdouble,ʹ�õ���<sstream>
	stringstream stream;
	double market_price;
	stream << s;
	stream >> market_price;
	//�жϵ�λ��С�������ݵ�λ����ͬ�Ĵ�ӡ
	if (market_price>1e8)
	{
		cout << title << ":" << /*contain_text*/ (market_price/1e8)<<"��" << endl;
	}
	else
	{
		if (market_price > 1e4)
		{
			cout << title << ":" << /*contain_text*/ (market_price/1e4)<<"��" << endl;
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
		//string��char*��ת��ʹ��data()����
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
	cout << "������Ʒ����۸�" << endl;
	for (auto i = good_goods.begin(); i != good_goods.end(); ++i)
	{
		cout << i->first << ":" << (i->second/1e8)<<"��" << endl;
	}
	/////////////////////////////////////////////////////////////////
	cout << "�밴�������������" << endl;
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
	myMap.emplace("3215", "�츳ֲ�� ǹ��� ����������̨ LE-1006");
	myMap.emplace("3224", "��ŵ �ѻ��� ���ͻ����̨ LH-1006");
	myMap.emplace("3482", "�츳ֲ�� ŵ���� �������� HG-1006");
	myMap.emplace("3475", "�츳ֲ�� ŵ���� ��еѧ MC-806");
	myMap.emplace("3470", "�츳ֲ�� ŵ���� Զ��װ��ά��ϵͳ RA-706");
	myMap.emplace("3267", "��ŵ ������ CPU���� EE-606");
	myMap.emplace("3258", "�츳ֲ�� ��� ����դ����� EG-606");
	myMap.emplace("3255", "�츳ֲ�� ��� ����դ������ EU-706");
	myMap.emplace("3252", "�츳ֲ�� ��� ������������ EP-706");
	myMap.emplace("3246", "�츳ֲ�� ��� ����ϵͳ���� EO-606");
	myMap.emplace("3239", "�츳ֲ�� ��� ���ݹ��� EM-806");
	myMap.emplace("3235", "��ŵ �ѻ��� ��ȷ��� ST-906");
	myMap.emplace("3233", "��ŵ �ѻ��� ���ͻ����̨ MH-806");
	myMap.emplace("3230", "��ŵ ٪�� �������� WU-1006");
	myMap.emplace("3221", "��ŵ �ѻ��� �������� TA-706");
	myMap.emplace("3216", "�츳ֲ�� ǹ��� ����������̨ ME-806");
	myMap.emplace("3213", "�츳ֲ�� ǹ��� �ܿص��� CB-706");
	myMap.emplace("3195", "���ƶ���˾ ��ǹ�� ��ƴ�� SS-906");
	myMap.emplace("3192", "���ƶ���˾ ��ǹ�� ����Ԥ�� MR-706");
	myMap.emplace("3189", "���ƶ���˾ ��ǹ�� �����䵯��̨ MP-806");
	myMap.emplace("3183", "��ŵ ���� Ѳ������ CM-606");
	myMap.emplace("3172", "��ŵ ���� ���͵��� LM-906");
	myMap.emplace("3167", "��ŵ ���� ���͵��� HM-706");
	myMap.emplace("3159", "��ŵ ���� ���͹������� AM-706");
	myMap.emplace("3143", "��ŵ �ѻ��� Ŀ�굼��Ԥ�� TN-906");
	myMap.emplace("3135", "��ŵ �ѻ��� �������� MP-706");
	myMap.emplace("3127", "��ŵ �ѻ��� ������ȷ��� GP-806");
	myMap.emplace("3124", "���ƶ���˾ ���� ���ٿ��� AC-606");
	myMap.emplace("3116", "���ƶ���˾ ���� ���ٻ��� HS-906");
	myMap.emplace("3095", "���ƶ���˾ ���� ��ܻ��� EM-706");
	myMap.emplace("3084", "��ŵ ٪�� ���ܹ��� SM-706");
	myMap.emplace("3079", "��ŵ ٪�� �������� SU-606");
	myMap.emplace("54732", "���缶");
	myMap.emplace("54786", "������� M");
	myMap.emplace("54785", "�����ѻ� M");
	//myMap.emplace("", "");
	//myMap.emplace("", "");
	return myMap;
}

//string���͵����л��ͷ����л���
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
//	str = string(recvBuf + step, size);//�ù��캯��������ʱ������Ȼ����и�ֵ
//	step += size;
//}

//ʹ��MFC���л�map:
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