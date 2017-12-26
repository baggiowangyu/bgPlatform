// bgLoggingDemo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "base/at_exit.h"
#include "base/message_loop.h"
#include "base/command_line.h"
#include "base/file_util.h"
#include "base/time.h"
#include "base/stringprintf.h"
#include "base/strings/sys_string_conversions.h"

#include "log4cxx/logger.h"
#include "log4cxx/propertyconfigurator.h"

int _tmain(int argc, _TCHAR* argv[])
{
	// Google Chromium 基础库框架
	base::AtExitManager exit_manager;
	base::MessageLoop message_loop;

	LPTSTR cmdline = GetCommandLine();
	CommandLine commandline = CommandLine::FromString(cmdline);
	commandline.Init(argc, nullptr);

	// 得到当前程序所在目录
	base::FilePath current_dirctory;
	bool bret = file_util::GetCurrentDirectory(&current_dirctory);

	// 读取日志模块配置文件
	// 加载log4cxx的配置文件，这里使用了属性文件
	base::FilePath logcfg_path = current_dirctory.AppendASCII("log4cxx.properties");
	std::wstring log4cxx_properties = logcfg_path.value();
	log4cxx::PropertyConfigurator::configure(log4cxx_properties.c_str());

	base::Time current_time = base::Time::Now();
	base::Time::Exploded time;
	current_time.UTCExplode(&time);
	//std::wstring log_file_name = base::StringPrintf(L"log_%d-%02d-%02d_%02d%02d%02d.log", 
	//	time.year, time.month, time.day_of_month, time.hour, time.minute, time.second);

	char log_file_name[4096] = {0};
	sprintf(log_file_name, "log_%d-%02d-%02d_%02d%02d%02d.log", time.year, time.month, time.day_of_month, time.hour, time.minute, time.second);
	base::FilePath log_path = current_dirctory.AppendASCII(log_file_name);
	std::wstring logfile_path = log_path.value();

	//获得一个Logger，这里使用了RootLogger  
	log4cxx::LoggerPtr logger = log4cxx::Logger::getLogger(logfile_path);  


	//发出INFO级别的输出请求
	while (true)
	{
		LOG4CXX_DEBUG(logger, L"L It really working..."); 
		LOG4CXX_INFO(logger, L"L It really working...");
		LOG4CXX_WARN(logger, L"L It really working...");
		LOG4CXX_ERROR(logger, L"L It really working...");
		LOG4CXX_FATAL(logger, L"L It really working...");
	} 

	//rootLogger->info(_T("它的确工作了"));//与上面那句话功能相当  

	system("pause");
	return 0;
}

