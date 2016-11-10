#include <windows.h>
#define COBJMACROS
#include "comMIDL.h"

/******************************************************************************\
1、编译 COM 组件时，MIDL.exe 会把 idl 文件编译为 tlb 文件，同时生成了 C/C++ 接口
   文件（本程序里就是 comMIDL.h  和 comMIDL.c）。C/C++ 客户程序通过这两个文件，即
   可访问 COM 组件。
2、下面的函数通过 comMIDL.h 里的 interface IEquation 和 struct IEquationVtbl 访
   问 COM 组件
\******************************************************************************/
int Solve4MIDL_c(const double z[10],double x[12])
{
    IClassFactory*  pcf =   NULL;
    IEquation*      e   =   NULL;
    long            n   =   0;

    CoInitialize(NULL);
#if 0
    if(CoCreateInstance(&CLSID_Equation,NULL,CLSCTX_INPROC_SERVER,&IID_IEquation,(LPVOID*)&e) == S_OK)
#else
    if(CoGetClassObject(&CLSID_Equation,CLSCTX_INPROC_SERVER,NULL,&IID_IClassFactory,(void**)&pcf) == S_OK
    && pcf->lpVtbl->CreateInstance(pcf,NULL,&IID_IEquation,(void**)&e) == S_OK)
#endif
    {
        VARIANT v;
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
            e->lpVtbl->Solve(e,&v,&n);
            VariantClear(&v);
        }
        {//计算结果赋给 double x[]
            int p   =   0;
            int i   =   0;
            for(;i < n;++i)
            {
                e->lpVtbl->real(e,i,&x[p++]);
                e->lpVtbl->imag(e,i,&x[p++]);
                e->lpVtbl->diff(e,i,&x[p++]);
            }
        }
        e->lpVtbl->Release(e);
    }
    if(pcf)
    {
        pcf->lpVtbl->Release(pcf);
    }
    CoUninitialize();
    return n;
}
