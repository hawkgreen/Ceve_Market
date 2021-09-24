/*
伏尔戈 10000002
get all 606to1006 buy max and print


*/
#include <stdio.h>
#include <iostream>  
#include <curl/curl.h>    
#include "tinyxml2.h"
#include <utility>   //pair head file


using namespace std;
using namespace tinyxml2;

void xml_print(XMLElement* titleElement);
string Get_url(string input);
void print_max_buy(string input);

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

void xml_print(XMLElement* titleElement)
{
	//XMLElement* titleElement = xml_name.FirstChildElement(xml_path1)->FirstChildElement(xml_path2)->FirstChildElement(xml_path3);
	//node->Value() //获取节点的名称
	//node->GetText() //获取节点里面的文本，但是不包含里面的节点
	const char* title = titleElement->Value();
	const char* contain_text = titleElement->GetText();
	//printf("%s:%s\n", title, contain_text);
	cout << title << ":" << contain_text << endl;
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
	string input[5] = { "3140","3198","3215","3224","3482" };
	for (int i=0;i<5;++i)
	{
		print_max_buy(input[i]);
	}
	/////////////////////////////////////////////////////////////////
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
void print_max_buy(string input)
{
	string test_str_s   = Get_url(input);

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
	xml_print(titleElement);
	//titleElement = doc.FirstChildElement("cevemarket")->FirstChildElement("buy")->FirstChildElement("volume");
	//xml_print(titleElement);
}

void my_data_base()
{
	pair<string, string> pair1("3140","载诺 狙击手 导弹发射效率 RL-1006");


}