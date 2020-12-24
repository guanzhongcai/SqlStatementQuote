#pragma once

#include <sstream>
#include <iterator>
#include "sql_wrapper.h"

using namespace std;


CSqlWrapper::CSqlWrapper()
{
	// 初始化SQL关键词 todo add more ...
	const char keywords[][10] = { "by", "or","set",
		"and","join","left","into",
		"from","right","order","group","limit","where",
		"select","update","insert", "delete","values" };
	int size = sizeof(keywords) / sizeof(keywords[0]);
	for (int i = 0; i < size; i++) {
		m_mapKeyWords[keywords[i]] = true;
	}
}

CSqlWrapper::~CSqlWrapper() {
	m_mapKeyWords.clear();
}

bool CSqlWrapper::isKeyword(const string& s) {
	if (s.empty() || s.size() == 1) {
		return false;
	}
	string lower;
	const size_t size = s.size();
	for (size_t i = 0; i < size; i++) {
		lower.push_back(tolower(s[i]));
	}
	return m_mapKeyWords[lower] == true;
}

vector<string> CSqlWrapper::split(const string& s) {
	std::stringstream ss(s);
	std::istream_iterator<std::string> begin(ss);
	std::istream_iterator<std::string> end;
	std::vector<std::string> vstrings(begin, end);

	return vstrings;
}

void CSqlWrapper::replaceStr(string& str, const string& from, const string& to) {
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
	}
}

string CSqlWrapper::Convert(const string& statement)
{
	string str = "", sReplace = statement;

	// 把所有的SQL符号左右两侧都加上空格 
	const size_t num = m_punctuation.length();
	for (size_t i = 0; i < num; i++) {
		string src = m_punctuation.substr(i, 1);
		string obj = " " + src + " ";
		replaceStr(sReplace, src, obj);
	}

	// splite为数组
	vector<string> vArray1 = split(sReplace);
	for (auto itr = vArray1.begin(); itr != vArray1.end(); ++itr) {
		string s = (*itr);

		// 检查是否是单个SQL语法字符
		if (s.length() == 1 && m_punctuation.find(s) != string::npos) {
			str += s;
			continue;
		}

		// 检查是否是SQL关键词
		if (isKeyword(s)) {
			str += " " + s + " ";
			continue;
		}

		// 检查是否是SOCI占位符
		if (s[0] == ':') {
			str += s;
			continue;
		}

		str += "\"" + s + "\"";
	}

	cout << "convert:: " << str << endl;
	return str;
}
