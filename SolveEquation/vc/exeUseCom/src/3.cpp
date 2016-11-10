#include "StdAfx.h"
#define COBJMACROS
#include "comMIDL.h"

/******************************************************************************\
1、编译 COM 组件时，MIDL.exe 会把 idl 文件编译为 tlb 文件，同时生成了 C/C++ 接口
   文件（本程序里就是 comMIDL.h  和 comMIDL.c）。C/C++ 客户程序通过这两个文件，即
   可访问 COM 组件。
2、下面的函数通过 comMIDL.h 里的 C++ 类 IEquation 访问 COM 组件。
\******************************************************************************/
int Solve3MIDL_cpp(const double z[10],double x[12])
{
    IEquation*  e   =   NULL;
    long        n   =   0;

    CoInitialize(NULL);
    if(CoCreateInstance(CLSID_Equation,NULL,CLSCTX_INPROC_SERVER,IID_IEquation,(LPVOID*)&e) == S_OK)
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
            e->Solve(&v,&n);
            VariantClear(&v);
        }
        {//计算结果赋给 double x[]
            int p   =   0;
            int i   =   0;
            for(;i < n;++i)
            {
                e->real(i,&x[p++]);
                e->imag(i,&x[p++]);
                e->diff(i,&x[p++]);
            }
        }
        e->Release();
    }
    CoUninitialize();
    return n;
}
