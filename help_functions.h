#pragma once

#include <ctime>
#include <string>
#include <fstream>
#include <iostream>
#include <qstring.h>
#include <qfileinfo.h>
#include <Windows.h>
#include <thread>
#include <WinUser.h>
#include <QtNetwork\qtcpsocket.h>
#include <WinInet.h>



	void loginit(std::string logPath);

	void log(QString stringForLog);
	static std::ofstream ofs;
	void log(int stringForLog);

	void logclose();
	static bool logopen;
	static char logPath[512];


	std::string getTimeStamp();
	
	bool fileExists(QString path);
	void start_the_eg();
	void callmsg(std::string str, std::string str2);


	char* DownloadBytes(LPCSTR szUrl);
	

	bool intToBool(int);
	int boolToInt(bool);


	template <typename T>
	std::string convertoString(T a) {
		return std::to_string(a);
	}

	void replace(std::string &string, std::string rpl, std::string orig);