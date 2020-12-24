#pragma once

#ifndef SQL_WRAPPER_H_
#define SQL_WRAPPER_H_

#include <string>
#include <vector>
#include <map>

using namespace std;

class CSqlWrapper {

public:
	CSqlWrapper();
	virtual ~CSqlWrapper();

private:
	// SQL关键词
	map<string, bool> m_mapKeyWords;
	
	// SQL语法中的标点符号
	const string m_punctuation = ",*()=!<>.";

	// 检查字符串是否是SQL关键字
	bool isKeyword(const string& s);
	
	// 字符串分割为数组
	vector<string> split(const string& s);
	
	// 替换字符串中的内容
	void replaceStr(string& str, const string& from, const string& to);

public:
	// 将sql语句中的字段名和表名添加双引号
	string Convert(const string& statement);
};

#endif
