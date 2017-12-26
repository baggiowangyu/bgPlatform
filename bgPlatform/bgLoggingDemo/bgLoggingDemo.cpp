// bgLoggingDemo.cpp : �������̨Ӧ�ó������ڵ㡣
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
	// Google Chromium ��������
	base::AtExitManager exit_manager;
	base::MessageLoop message_loop;

	LPTSTR cmdline = GetCommandLine();
	CommandLine commandline = CommandLine::FromString(cmdline);
	commandline.Init(argc, nullptr);

	// �õ���ǰ��������Ŀ¼
	base::FilePath current_dirctory;
	bool bret = file_util::GetCurrentDirectory(&current_dirctory);

	// ��ȡ��־ģ�������ļ�
	// ����log4cxx�������ļ�������ʹ���������ļ�
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

	//���һ��Logger������ʹ����RootLogger  
	log4cxx::LoggerPtr logger = log4cxx::Logger::getLogger(logfile_path);  


	//����INFO������������
	while (true)
	{
		LOG4CXX_DEBUG(logger, L"L It really working..."); 
		LOG4CXX_INFO(logger, L"L It really working...");
		LOG4CXX_WARN(logger, L"L It really working...");
		LOG4CXX_ERROR(logger, L"L It really working...");
		LOG4CXX_FATAL(logger, L"L It really working...");
	} 

	//rootLogger->info(_T("����ȷ������"));//�������Ǿ仰�����൱  

	system("pause");
	return 0;
}

