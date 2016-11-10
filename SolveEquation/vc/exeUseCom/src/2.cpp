#include "StdAfx.h"
#import "SolveEquationCom.dll"

/******************************************************************************\
1、预处理器对 #import "SolveEquationCom.dll" 的处理：
   1）根据 SolveEquationCom.dll 里的类型库生成 SolveEquationCom.tlh（COM 组件接
      口函数的 C++ 声明）和 SolveEquationCom.tli（COM 组件接口函数的 C++ 实现）
   2）#include "SolveEquationCom.tlh" 即包含文件 SolveEquationCom.tlh，该文件又
      包含了 SolveEquationCom.tli。
2、下面的函数通过智能指针 IEquationPtr 访问 COM 组件。IEquationPtr 在 SolveEqua
   tionCom.tlh 里声明，SolveEquationLib 是命名空间。
\******************************************************************************/
int Solve2import(const double z[10],double x[12])
{
    long n = 0;
    CoInitialize(NULL);
    try
    {
        SolveEquationLib::IEquationPtr e(__uuidof(SolveEquationLib::Equation));
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
            n   =   e->Solve(&v);
            VariantClear(&v);
        }
        int p       =   0;
        for(int i = 0;i < n;++i)
        {
            x[p++]  =   e->real(i);
            x[p++]  =   e->imag(i);
            x[p++]  =   e->diff(i);
        }
    }//运行到此，智能指针 e 将被析构，e->Relase 将被自动调用
    catch(_com_error&e)
    {
        AfxMessageBox(e.Description() + "\n" + e.ErrorMessage());
    }
    CoUninitialize();
    return n;
}
