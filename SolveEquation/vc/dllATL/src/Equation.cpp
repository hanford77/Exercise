//Equation.cpp
#include "stdafx.h"
#include "Equation.h"

/******************************************************************************\
将 COM 客户端(VBA)传过来的参数 z 转换为 double[]
\******************************************************************************/
bool CEquation::GetZ_VBA(VARIANT *z,double dz[10],SAFEARRAY*sa)
{
    if(sa
    && sa->cDims == 1                   //一维数组
    && sa->rgsabound[0].cElements >= 10 //至少有 10 个元素
    )
    {
        long    nLB     =   sa->rgsabound[0].lLbound;
        long    n[1]    =   {nLB};            
        for(int i = 0;i < 10;++i)
        {
            SafeArrayGetElement(sa,n,&dz[i]);
            ++n[0];
        }
        return true;
    }
    return false;
}

/******************************************************************************\
将 COM 客户端(VBS)传过来的参数 z 转换为 double[]
\******************************************************************************/
bool CEquation::GetZ_VBS(VARIANT *z,double dz[10],SAFEARRAY*sa)
{
    if(sa
    && sa->cDims == 1                   //一维数组    
    && sa->rgsabound[0].cElements >= 10 //至少有 10 个元素
    )
    {
        long    nLB     =   sa->rgsabound[0].lLbound;
        long    n[1]    =   {nLB};
        VARIANT*v       =   NULL;
        VARIANT t;
        VariantInit(&t);
        for(int i = 0;i < 10;++i)
        {
            SafeArrayPtrOfIndex(sa,n,(void**)&v);
            ++n[0];
            if(VariantChangeType(&t,v,0,VT_R8) == S_OK)
            {
                dz[i]   =   t.dblVal;
            }
            else
            {
                dz[i]   =   0.0;
            }
        }
        return true;
    }
    return false;
}

/******************************************************************************\
将 COM 客户端(JS)传过来的参数 z 转换为 double[]
\******************************************************************************/
bool CEquation::GetZ_JS(VARIANT *z,double dz[10],IDispatch*p)
{
    if(p)
    {
        ATL::CComDispatchDriver  spArray = p;
        ATL::CComVariant         varLen;
        spArray.GetPropertyByName(L"length",&varLen);
        if(varLen.vt == VT_I4 && varLen.lVal >= 10)
        {
            ATL::CComVariant varVal;
            wchar_t     szNum[32];

            for(int i = 0;i < 10;++i)
            {
                varVal.Clear();
                spArray.GetPropertyByName(_itow(i,szNum,10),&varVal);
                if(varVal.ChangeType(VT_R8) == S_OK)
                {
                    dz[i]   =   varVal.dblVal;
                }
                else
                {
                    dz[i]   =   0.0;
                }
            }
            return true;
        }
    }
    return false;
}

bool CEquation::GetZ_BSTR(VARIANT *z,double dz[10],const wchar_t*s)
{
    if(s)
    {
        memset(dz,0,10 * sizeof(double));
        const wchar_t*  p   =   s;
        if(p[0])
        {
            for(int i = 0;i < 10;++i)
            {
                dz[i]   =   wcstod(p,(wchar_t**)&p);
                if(p[0])
                {
                    ++p;
                }
                else
                {
                    break;
                }
            }
        }
        return true;
    }
    return false;
}

/******************************************************************************\
将 COM 客户端传过来的参数 z 转换为 double[]
\******************************************************************************/
bool CEquation::GetZ(VARIANT *z,double dz[10])
{
    bool    bOK =   false;
    if(z && dz)
    {
        if(z->vt == (VT_ARRAY | VT_BYREF | VT_R8))
        {//VB6/VBA
            bOK =   GetZ_VBA(z,dz,*z->pparray);
        }
        else if(z->vt == (VT_ARRAY | VT_R8))
        {//VB6/VBA
            bOK =   GetZ_VBA(z,dz,z->parray);
        }
        else if(z->vt == (VT_ARRAY | VT_BYREF | VT_VARIANT))
        {//VBS
            bOK =   GetZ_VBS(z,dz,*z->pparray);
        }
        else if(z->vt == (VT_ARRAY | VT_VARIANT))
        {//VBS
            bOK =   GetZ_VBS(z,dz,*z->pparray);
        }
        else if(z->vt == VT_DISPATCH)
        {//JS
            bOK =   GetZ_JS(z,dz,z->pdispVal);
        }
        else if(z->vt == VT_BSTR)
        {//字符串
            bOK =   GetZ_BSTR(z,dz,z->bstrVal);
        }
    }
    return bOK;
}

STDMETHODIMP CEquation::Solve(VARIANT *z,long*n)
{
    m_nRootCount    =   0;  //有效的根数为零
    double dz[10];
    if(!GetZ(z,dz))
    {
        return ERROR_INVALID_PARAMETER;
    }
    //求解一元四次方程
    m_nRootCount    =   SolveEquation(dz,m_x);
    if(n)
    {
        *n  =   m_nRootCount;
    }
	return S_OK;
}

STDMETHODIMP CEquation::real(long i, double *v)
{
    if(v)
    {
	    if(i >= 0 && i < m_nRootCount)
        {
            *v  =   m_x[3 * i];
        }
        else
        {
            *v  =   0.0;
        }
    }
	return S_OK;
}

STDMETHODIMP CEquation::imag(long i, double *v)
{
    if(v)
    {
	    if(i >= 0 && i < m_nRootCount)
        {
            *v  =   m_x[3 * i + 1];
        }
        else
        {
            *v  =   0.0;
        }
    }
	return S_OK;
}

STDMETHODIMP CEquation::diff(long i, double *v)
{
    if(v)
    {
	    if(i >= 0 && i < m_nRootCount)
        {
            *v  =   m_x[3 * i + 2];
        }
        else
        {
            *v  =   0.0;
        }
    }
	return S_OK;
}

STDMETHODIMP CEquation::get_RootCount(long *pVal)
{
    if(pVal)
    {
        if(m_nRootCount >= 0)
        {
            *pVal   =   m_nRootCount;
        }
        else
        {
            *pVal   =   0;
        }
    }
	return S_OK;
}
