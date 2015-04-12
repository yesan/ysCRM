#pragma once


//错误码:
const int ERR_OK = 0;
const int ERR_TIMEOUT = 1;
const int ERR_FINDER_NOT_RUN = 2;
const int ERR_COMM = 3;
const int ERR_FINDER_NOT_INSTALLED = 9;
const int ERR_FINDER_INITIALIZING = 10;
const int ERR_UNKNOWN = 99;

#ifdef UNICODE
   #define FNFind "FindW"
#else
   #define FNFind "FindA"
#endif
#define FNLaunchFinder "LaunchFinder"
#define FNIsFinderRunning "IsFinderRunning"
#define FNCheckRequirement "CheckRequirement"
//结果回调函数由开发者实现.
/*
buffer:结果缓冲.是char*数组
bufferCount:结果数组的个数
totalCount:一共有多少项符合条件的结果
ErrorCode:错误码
*/
typedef void (__stdcall *TFNFindCallback)(TCHAR** buffer,int bufferCount, int totalCount,int ErrorCode);

//查询接口在DLL中函数名为"_Find"
/*
AStr:查询条件 例如 *.exe
ACallback:开发者实现的回调函数
ADir:查询的目录
AExcludeDir:排除的目录
AFilter:过滤条件一般可以为空字符串
ACount:本次查询需要查回多少结果
Afrom:从第几个符合条件的开始返回
ASpaceOr:查询条件的空格作为or还是and
AWholeWords:是否全词匹配
ACaseSensitive:是否区分大小写
AIncludeDir:结果是否包含目录
AIncludeFiles:结果是否包含文件
ATimeoutMS:超时时间(毫秒)
返回值:成功返回ERR_OK,否则为失败.
*/
typedef int (__stdcall *TFNfind)(TCHAR* AStr,
									TFNFindCallback ACallback,
									TCHAR* ADir, 
									TCHAR* AExcludeDir,
									TCHAR* AFilter,
									int ACount,
									int Afrom,
									bool ASpaceOr,
									bool AWholeWords,
									bool ACaseSensitive,
									bool AIncludeDir,
									bool AIncludeFiles,
									unsigned short ATimeoutMS);
//启动Finder
typedef bool (__stdcall *TFNLaunchFinder)();
//Finder是否正在运行
typedef bool (__stdcall *TFNIsFinderRunning)();
/*
检查环境
返回值是0表示OK没问题.
否则:ERR_FINDER_NOT_RUN(光速搜索没有运行),ERR_FINDER_NOT_INSTALLED(光速搜索没有安装),ERR_FINDER_VER(不符合支持SDK的版本号),ERR_FINDER_INITIALIZING(光速搜索正在初始化)
*/
typedef int (__stdcall *TFNCheckRequirement)();
