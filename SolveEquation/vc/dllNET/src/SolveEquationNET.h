//SolveEquationCLR.h
#pragma once

#include <complex>

namespace SolveEquationNET
{
    public ref class Equation
    {
    public:        
        static cli::array<double>^ Solve(cli::array<double>^ z)
        {
            cli::array<double>^ x   =   nullptr;
            if(z != nullptr && z->Length >= 10)
            {
                double  zd[10];
                for(int i = 0;i < 10;++i)
                {
                    zd[i]   =   z[i];
                }
                double  xd[12];
                int     n   =   SolveEquation(zd,xd);
                if(n > 0)
                {
                    n  *=   3;
                    x   =   gcnew cli::array<double>(n);
                    for(int i = n - 1;i >= 0;--i)
                    {
                        x[i]    =   xd[i];
                    }
                }
            }
            return x;
        }
    };
}
