#pragma once


//������:
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
//����ص������ɿ�����ʵ��.
/*
buffer:�������.��char*����
bufferCount:�������ĸ���
totalCount:һ���ж�������������Ľ��
ErrorCode:������
*/
typedef void (__stdcall *TFNFindCallback)(TCHAR** buffer,int bufferCount, int totalCount,int ErrorCode);

//��ѯ�ӿ���DLL�к�����Ϊ"_Find"
/*
AStr:��ѯ���� ���� *.exe
ACallback:������ʵ�ֵĻص�����
ADir:��ѯ��Ŀ¼
AExcludeDir:�ų���Ŀ¼
AFilter:��������һ�����Ϊ���ַ���
ACount:���β�ѯ��Ҫ��ض��ٽ��
Afrom:�ӵڼ������������Ŀ�ʼ����
ASpaceOr:��ѯ�����Ŀո���Ϊor����and
AWholeWords:�Ƿ�ȫ��ƥ��
ACaseSensitive:�Ƿ����ִ�Сд
AIncludeDir:����Ƿ����Ŀ¼
AIncludeFiles:����Ƿ�����ļ�
ATimeoutMS:��ʱʱ��(����)
����ֵ:�ɹ�����ERR_OK,����Ϊʧ��.
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
//����Finder
typedef bool (__stdcall *TFNLaunchFinder)();
//Finder�Ƿ���������
typedef bool (__stdcall *TFNIsFinderRunning)();
/*
��黷��
����ֵ��0��ʾOKû����.
����:ERR_FINDER_NOT_RUN(��������û������),ERR_FINDER_NOT_INSTALLED(��������û�а�װ),ERR_FINDER_VER(������֧��SDK�İ汾��),ERR_FINDER_INITIALIZING(�����������ڳ�ʼ��)
*/
typedef int (__stdcall *TFNCheckRequirement)();
