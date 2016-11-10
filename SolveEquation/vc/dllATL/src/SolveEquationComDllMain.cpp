//SolveEquationComDllMain.cpp
#include "stdafx.h"
#include <initguid.h>
#include "SolveEquationCom_i.c"
#include "Equation.h"

/******************************************************************************\
注意：如果 CComModule _Module …… 放在 #else ... #endif 之间，那么 VC++6.0 将
无法插入“New ATL Object”
\******************************************************************************/
#if _MSC_VER < 1300 //VC++6.0/EVC3.0/EVC4.0
    CComModule _Module;
    BEGIN_OBJECT_MAP(ObjectMap)
        OBJECT_ENTRY(CLSID_Equation, CEquation)
    END_OBJECT_MAP()
    #ifdef _ATL_STATIC_REGISTRY
        #include <statreg.h>
        #include <statreg.cpp>
    #endif
    #include <atlimpl.cpp>
#else   //VC++7.0(2002) 及其以上的版本
//     class CTestModule : public ATL::CAtlDllModuleT< CTestModule >
//     {
//     public :
// 	    DECLARE_LIBID(LIBID_SolveEquationLib)
// 	    //DECLARE_REGISTRY_APPID_RESOURCEID(IDR_TEST, "{FE827129-645A-436F-A1E4-4A933F19BA17}")
//     };
    CTestModule _AtlModule;
    OBJECT_ENTRY_AUTO(__uuidof(Equation),CEquation)
#endif

extern "C"
BOOL WINAPI DllMain(HANDLE hInstance, DWORD dwReason, LPVOID lpReserved)
{
#if _MSC_VER >= 1300 //VC++7.0(2002) 及其以上的版本
    return _AtlModule.DllMain(dwReason, lpReserved); 
#else
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        _Module.Init(ObjectMap,(HINSTANCE)hInstance, &LIBID_SolveEquationLib);
        DisableThreadLibraryCalls((HINSTANCE)hInstance);
    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
        _Module.Term();
    }
    return TRUE;    // ok
#endif
}

STDAPI DllCanUnloadNow(void)
{
#if _MSC_VER >= 1300 //VC++7.0(2002) 及其以上的版本
    return _AtlModule.DllCanUnloadNow();
#else
    return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
#endif
}

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
#if _MSC_VER >= 1300 //VC++7.0(2002) 及其以上的版本
    return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
#else
    return _Module.GetClassObject(rclsid, riid, ppv);
#endif
}

STDAPI DllRegisterServer(void)
{
#if _MSC_VER >= 1300 //VC++7.0(2002) 及其以上的版本
    return _AtlModule.DllRegisterServer();
#else
    return _Module.RegisterServer(TRUE);
#endif
}

STDAPI DllUnregisterServer(void)
{
#if _MSC_VER >= 1300 //VC++7.0(2002) 及其以上的版本
    return _AtlModule.DllUnregisterServer();
#else
    return _Module.UnregisterServer(TRUE);
#endif
}

#if _MSC_VER >= 1500 //VC++9.0(2008) 及其以上的版本
STDAPI DllInstall(BOOL bInstall, LPCWSTR pszCmdLine)
{
    HRESULT hr = E_FAIL;
    static const wchar_t szUserSwitch[] = L"user";
    if (pszCmdLine != NULL)
    {
    	if (_wcsnicmp(pszCmdLine, szUserSwitch, _countof(szUserSwitch)) == 0)
    	{
    		ATL::AtlSetPerUserRegistration(true);
    	}
    }
    if (bInstall)
    {	
    	hr = DllRegisterServer();
    	if (FAILED(hr))
    	{	
    		DllUnregisterServer();
    	}
    }
    else
    {
    	hr = DllUnregisterServer();
    }
    return hr;
}
#endif
