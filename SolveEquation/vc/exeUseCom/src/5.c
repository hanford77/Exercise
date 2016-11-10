#include <windows.h>

/******************************************************************************\
下面的函数使用 C 语言，通过 IDispatch 访问 COM 组件
\******************************************************************************/
int Solve5IDispatch(const double z[10],double x[12])
{
    IDispatch*  e   =   NULL;
    long        n   =   0;
    CLSID       EQU;

    CoInitialize(NULL);
    if(CLSIDFromProgID(L"SolveEquation",&EQU) == S_OK
    && CoCreateInstance(&EQU,NULL,CLSCTX_INPROC_SERVER,&IID_IDispatch,&e) == S_OK)
    {
        VARIANT     v;
        DISPPARAMS  dps;
        VARIANT     vaResult;
        UINT        nArgErr =   0;
        DISPID      did     =   0;
        OLECHAR*    szName  =   NULL;

        VariantInit(&v);
        {//把 double z[10] 封装到 VARIANT 变量 v 内
            v.vt = VT_R8 | VT_ARRAY;
            if(v.parray = SafeArrayCreateVector(VT_R8,0,10))
            {
		        void*pData  =   NULL;
                if(SafeArrayAccessData(v.parray,&pData) == S_OK)
                {
		            memcpy(pData,z,SafeArrayGetElemsize(v.parray) * 10);
		            SafeArrayUnaccessData(v.parray);
                }
                else
                {
                    SafeArrayDestroy(v.parray);
                    v.parray = NULL;
                }
            }
        }
        if(v.parray)
        {
            nArgErr         =   (UINT)-1;
            memset(&dps,0,sizeof(dps));
            dps.cArgs       =   1;
            dps.rgvarg      =   (VARIANTARG*)malloc(sizeof(VARIANTARG));
            dps.rgvarg[0]   =   v;
            VariantInit(&vaResult);
            szName          =   L"Solve";
            if(e->lpVtbl->GetIDsOfNames(e,&IID_NULL,&szName,1,LOCALE_SYSTEM_DEFAULT,&did)          == S_OK
            && e->lpVtbl->Invoke(e,did,&IID_NULL,0,DISPATCH_METHOD,&dps,&vaResult, NULL, &nArgErr) == S_OK
            && VariantChangeType(&vaResult,&vaResult,0,VT_I4) == S_OK)
            {
                n   =   vaResult.lVal;
            }
            VariantClear(&vaResult);
            free(dps.rgvarg);
            VariantClear(&v);
        }
        {//计算结果赋给 double x[]
            int p   =   0;
            int i   =   0;

            memset(&dps,0,sizeof(dps));
            dps.cArgs           =   1;
            dps.rgvarg          =   (VARIANTARG*)malloc(sizeof(VARIANTARG));
            dps.rgvarg[0].vt    =   VT_I4;

            for(;i < n;++i)
            {
                dps.rgvarg[0].lVal  =   i;
                //real
                nArgErr =   (UINT)-1;
                VariantInit(&vaResult);
                szName          =   L"real";
                if(e->lpVtbl->GetIDsOfNames(e,&IID_NULL,&szName,1,LOCALE_SYSTEM_DEFAULT,&did)          == S_OK
                && e->lpVtbl->Invoke(e,did,&IID_NULL,0,DISPATCH_METHOD,&dps,&vaResult, NULL, &nArgErr) == S_OK
                && VariantChangeType(&vaResult,&vaResult,0,VT_R8) == S_OK)
                {
                    x[p]        =   vaResult.dblVal;
                }
                else
                {
                    x[p]        =   0.0;
                }
                VariantClear(&vaResult);
                //imag
                nArgErr =   (UINT)-1;
                VariantInit(&vaResult);
                szName          =   L"imag";
                if(e->lpVtbl->GetIDsOfNames(e,&IID_NULL,&szName,1,LOCALE_SYSTEM_DEFAULT,&did)          == S_OK
                && e->lpVtbl->Invoke(e,did,&IID_NULL,0,DISPATCH_METHOD,&dps,&vaResult, NULL, &nArgErr) == S_OK
                && VariantChangeType(&vaResult,&vaResult,0,VT_R8) == S_OK)
                {
                    x[p + 1]    =   vaResult.dblVal;
                }
                else
                {
                    x[p + 1]    =   0.0;
                }
                VariantClear(&vaResult);
                //diff
                nArgErr =   (UINT)-1;
                VariantInit(&vaResult);
                szName          =   L"diff";
                if(e->lpVtbl->GetIDsOfNames(e,&IID_NULL,&szName,1,LOCALE_SYSTEM_DEFAULT,&did)          == S_OK
                && e->lpVtbl->Invoke(e,did,&IID_NULL,0,DISPATCH_METHOD,&dps,&vaResult, NULL, &nArgErr) == S_OK
                && VariantChangeType(&vaResult,&vaResult,0,VT_R8) == S_OK)
                {
                    x[p + 2]    =   vaResult.dblVal;
                }
                else
                {
                    x[p + 2]    =   0.0;
                }
                VariantClear(&vaResult);
                //
                p  +=   3;
            }
            free(dps.rgvarg);
        }
        e->lpVtbl->Release(e);
    }
    CoUninitialize();
    return n;
}