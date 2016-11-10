/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Oct 13 09:47:07 2016
 */
/* Compiler settings for W:\(yhf)\Exercise\math\一元多次方程\SolveEquation\vc\dllATL\src\SolveEquationCom.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID IID_IEquation = {0x20907E97,0x4E8D,0x4682,{0xBA,0x03,0xAB,0x11,0x64,0xC1,0x99,0xCA}};
const IID LIBID_SolveEquationLib = {0x4835C47C,0xF2D5,0x46E8,{0xA2,0x9A,0x1F,0x38,0xE6,0x2B,0x26,0xC4}};
const CLSID CLSID_Equation = {0xE2E86938,0x6DE1,0x49E1,{0x98,0xA3,0xA0,0xDD,0x98,0x82,0xE8,0x37}};

#ifdef __cplusplus
}
#endif
