using System;
using System.Runtime.InteropServices;

namespace SolveEquationNET
{
    public class Equation
    {
#if true
        //假定 <exePath> 是 exe 文件所在目录，则
        //32 位的 SolveEquationDll.dll 请放在 <exePath> 目录下
        //64 位的 SolveEquationDll.dll 请更名为 SolveEquationDll_x64.dll，然后放在 <exePath> 目录下
        [DllImport("SolveEquationDll.dll", CallingConvention = CallingConvention.Winapi, EntryPoint = "SolveEquation")]
        private static extern Int32 SolveEquation32(double[] z, double[] x);
        [DllImport("SolveEquationDll_x64.dll", CallingConvention = CallingConvention.Winapi, EntryPoint = "SolveEquation")]
        private static extern Int32 SolveEquation64(double[] z, double[] x);
        public static double[] Solve(double[] z)
        {
            double[] x = null;
            if (z != null && z.Length >= 10)
            {
                try
                {
                    x = new double[12];
                    Int32 n = 0;
                    if (Environment.Is64BitProcess)
                    {
                        n = 3 * SolveEquation64(z, x);  //调用 DLL 里的导出函数，可能会引起异常
                    }
                    else
                    {
                        n = 3 * SolveEquation32(z, x);  //调用 DLL 里的导出函数，可能会引起异常
                    }                    
                    if (n > 0)
                    {
                        if (n < 12)
                        {
                            Array.Resize(ref x, n);
                        }
                    }
                    else
                    {
                        x = null;
                    }
                }
                catch (System.Exception ex)
                {
                    x = null;
                }
            }
            return x;
        }
#else
        //假定 <exePath> 是 exe 文件所在目录，则
        //32 位的 SolveEquationDll.dll 请放在 <exePath>\vc6-win32-RA  目录下
        //64 位的 SolveEquationDll.dll 请放在 <exePath>\vc2010-x64-RU 目录下
        [DllImport("SolveEquationDll.dll", CallingConvention = CallingConvention.Winapi, EntryPoint = "SolveEquation")]
        private static extern Int32 SolveEquation(double[] z, double[] x);
        [DllImport("Kernel32.dll", CallingConvention = CallingConvention.Winapi,CharSet = CharSet.Ansi,EntryPoint = "GetModuleHandleA")]
        private static extern UIntPtr GetModuleHandle(string lpModuleName);

        public static double[] Solve(double[] z)
        {
            double[] x   =   null;
            if(z != null && z.Length >= 10)
            {
                try
                {
                    if (GetModuleHandle("SolveEquationDll.dll") == UIntPtr.Zero)
                    {//修改当前目录，以便顺利载入 SolveEquationDll.dll
                        string sPath = System.AppDomain.CurrentDomain.BaseDirectory;
                        if (Environment.Is64BitProcess)
                        {//64位
                            sPath += "vc2010-x64-RU";
                        }
                        else
                        {//32位
                            sPath += "vc6-win32-RA";
                        }
                        System.IO.Directory.SetCurrentDirectory(sPath); //设置当前目录，可能会引起异常
                    }
                    x = new double[12];
                    Int32 n = 3 * SolveEquation(z, x);  //调用 DLL 里的导出函数，可能会引起异常
                    if (n > 0)
                    {
                        if (n < 12)
                        {
                            Array.Resize(ref x, n);
                        }
                    }
                    else
                    {
                        x = null;
                    }
                }
                catch (System.Exception ex)
                {
                    x = null;
                }
            }
            return x;
        }
#endif
    };
}
