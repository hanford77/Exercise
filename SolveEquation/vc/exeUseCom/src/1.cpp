#include "StdAfx.h"
#include "comMFC.h"

/******************************************************************************\
1、如果 COM 组件实现了 IDispatch 接口，那么就可以根据类型库生成 MFC 包装类。
   VC++6.0 生成 MFC 包装类的步骤：Ctrl+W ==> Add Class ==> From a type library
   本程序里生成的 MFC 包装类在文件 comMFC.h 和 comMFC.cpp 里；
2、下面的函数将调用 MFC 包装类，通过 IDispatch 接口访问 COM 组件。
\******************************************************************************/
int Solve1MFC(const double z[10],double x[12])
{
    int n   =   0;
    CoInitialize(NULL);
    {
        TRY 
        {
            IEquation e;
            if(e.CreateDispatch(_T("SolveEquation")))
            {
                COleSafeArray   osa;
                osa.CreateOneDim(VT_R8,10,z);   //把 double z[10] 封装到 VARIANT 变量 osa 内
                n       =   e.Solve(&osa);
                int p   =   0;
                for(int i = 0;i < n;++i)
                {
                    x[p++]  =   e.real(i);
                    x[p++]  =   e.imag(i);
                    x[p++]  =   e.diff(i);
                }
            }
        }//运行到此，equ 被析构。IDispatch 被自动 Release
        CATCH (CException, e)//catch (CException* e)
        {
            e->Delete();
        }
        END_CATCH
    }
    CoUninitialize();
    return n;
}
