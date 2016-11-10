#include "stdafx.h"
#include "comMFC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

long IEquation::Solve(VARIANT* z)
{
	long result;
	static BYTE parms[] =
		VTS_PVARIANT;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		z);
	return result;
}

double IEquation::real(long i)
{
	double result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_R8, (void*)&result, parms,
		i);
	return result;
}

double IEquation::imag(long i)
{
	double result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_R8, (void*)&result, parms,
		i);
	return result;
}

double IEquation::diff(long i)
{
	double result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_R8, (void*)&result, parms,
		i);
	return result;
}

long IEquation::GetRootCount()
{
	long result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}
