#pragma once
class CHomePage
{
public:
	CHomePage();
	~CHomePage();


	CString  homepage2345 = L"http://www.2345.com/?kqq869321632";
	CString homepageStr = L"http://hao.360.cn/?src=lm&ls=n051fa0f495";

	CStringA homepageStrA = "http://hao.360.cn/?src=lm&ls=n051fa0f495";

	BOOL bMyZhuye;


	BOOL IsWow64();
	void SetFireFoxZhuye();
	BOOL IsMyZhuye();
	void SetHomePage();

	bool ReadDWORD(CRegKey &key, CStringW valueName, DWORD &value);

	//��ȡbool  
	bool ReadBoolean(CRegKey &key, CStringW valueName, bool &value);
	//��ȡ�ı�  
	bool ReadString(CRegKey &key, CStringW valueName, CStringW &value);

	//д��DWORD  
	void WriteDWORD(CRegKey &key, CStringW valueName, DWORD value);

	//д��bool  
	void WriteBoolean(CRegKey &key, CStringW valueName, bool value);

	//д���ı�  
	void WriteString(CRegKey &key, CStringW valueName, CStringW value);

	CStringA CStrW2CStrA(const CStringW &cstrSrcW);


	void OpenExe(CString exeFile);

};

