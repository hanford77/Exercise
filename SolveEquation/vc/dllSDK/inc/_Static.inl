//_Static.inl
#ifndef SolveEquationDllI
    #define SolveEquationDllI
#endif

#ifdef _MT
    #ifdef _DLL  //C runtime library - multi thread DLL
        #pragma comment(lib,SolveEquationDllI "SolveEquationDllD.lib")
    #else        //C runtime library - multi thread
        #pragma comment(lib,SolveEquationDllI "SolveEquationDllT.lib")
    #endif
#else            //C runtime library - single thread
    #pragma comment(lib,SolveEquationDllI "SolveEquationDllS.lib")
#endif

#undef SolveEquationDllI
