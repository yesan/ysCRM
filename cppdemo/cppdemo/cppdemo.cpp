// cppdemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "FinderSDK.h"

TFNfind             find             = (TFNfind)GetProcAddress(LoadLibrary(__T("finderlib.dll")),FNFind);
TFNCheckRequirement CheckRequirement = (TFNCheckRequirement)GetProcAddress(LoadLibrary(__T("finderlib.dll")),FNCheckRequirement);
TFNLaunchFinder     LaunchFinder     = (TFNLaunchFinder)GetProcAddress(LoadLibrary(__T("finderlib.dll")),FNLaunchFinder);


std::string WChar2Ansi(LPCWSTR pwszSrc)
{
	int nLen = WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, NULL, 0, NULL, NULL);
	if (nLen<= 0) return std::string("");
	char* pszDst = new char[nLen];
	if (NULL == pszDst) return std::string("");
	WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, pszDst, nLen, NULL, NULL);
	pszDst[nLen -1] = 0;
	std::string strTemp(pszDst);
	delete [] pszDst;
	return strTemp;
}

void __stdcall callback(TCHAR** buffer,int bufferCount, int totalCount,int ErrorCode){

	for(int i=0; i<bufferCount; i++){
       //wprintf(("%s\r\n"),*buffer);
	   //_tprintf(__T("%s\r\n"),*buffer);
	   //_tprintf(*buffer);
	   
#ifdef UNICODE
		string str = WChar2Ansi(*buffer);
#else
		string str(*buffer);
#endif
	   //str = str.substr(0,10);
	   cout <<str<<std::endl;
	   buffer++;
	}
	 //sprintf();

}
/*
Ö´ÐÐÀý×Ó
cppdemo "*" "c:\windows;d:\;d:\;e:\" "c:\windows\system32" ".rar;.zip;.kz;.7zip;.7z"

*/
int _tmain(int argc, _TCHAR* argv[])
{
	int      req = CheckRequirement();
	switch(req){
	case ERR_OK:{
		if(find != NULL){
			find((argc > 1)?argv[1]:(__T("")), 
				callback, 
				(argc > 2)?argv[2]:(__T("")), 
				(argc > 3)?argv[3]:(__T("")), 
				//(argc > 4)?argv[4]:(__T("")), 
                __T(""),
				1000,
				0,
				true,
				false,
				false,
				false,
				true,
				1000); 
		}				   
				}
				break;
	case ERR_FINDER_NOT_RUN:
		//LaunchFinder();
		break;
	}
    
	return 0;
}

