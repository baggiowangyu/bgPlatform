// bgIpcListener.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "base/at_exit.h"
#include "base/message_loop.h"
#include "base/command_line.h"
#include "base/file_util.h"
#include "base/time.h"
#include "base/stringprintf.h"
#include "base/strings/sys_string_conversions.h"


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

	return 0;
}

