#pragma once
class CHomePage
{
public:
	CHomePage();
	~CHomePage();


	CString  homepage2345;
	CString homepageStr;

	CStringA homepageStrA;

	BOOL bMyZhuye;


	BOOL IsWow64();
	void SetFireFoxZhuye();
	BOOL IsMyZhuye();
	void SetHomePage();

	bool ReadDWORD(CRegKey &key, CStringW valueName, DWORD &value);

	//读取bool  
	bool ReadBoolean(CRegKey &key, CStringW valueName, bool &value);
	//读取文本  
	bool ReadString(CRegKey &key, CStringW valueName, CStringW &value);

	//写入DWORD  
	void WriteDWORD(CRegKey &key, CStringW valueName, DWORD value);

	//写入bool  
	void WriteBoolean(CRegKey &key, CStringW valueName, bool value);

	//写入文本  
	void WriteString(CRegKey &key, CStringW valueName, CStringW value);

	CStringA CStrW2CStrA(const CStringW &cstrSrcW);


	void OpenExe(CString exeFile);

};

