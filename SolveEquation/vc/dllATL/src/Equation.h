//Equation.h
#pragma once

class ATL_NO_VTABLE CEquation
 : public ATL::CComObjectRootEx<ATL::CComSingleThreadModel>
 , public ATL::CComCoClass<CEquation, &CLSID_Equation>
 , public ATL::IDispatchImpl<IEquation, &IID_IEquation, &LIBID_SolveEquationLib,/*wMajor =*/1,/*wMinor =*/ 0>
{
public:
	CEquation()
	{
        m_nRootCount =   0;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_REG_EQUATION)

BEGIN_COM_MAP(CEquation)
	COM_INTERFACE_ENTRY(IEquation)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

DECLARE_PROTECT_FINAL_CONSTRUCT()

#if _MSC_VER >= 1300 //VC++7.0(2002) 及其以上的版本
	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	void FinalRelease()
	{
	}
#endif
// ISolveEquation
public:
	STDMETHOD(get_RootCount)(/*[out, retval]*/ long *pVal);
	STDMETHOD(diff)(/*[in]*/ long i,/*[out,retval]*/ double*v);
	STDMETHOD(imag)(/*[in]*/ long i,/*[out,retval]*/ double*v);
	STDMETHOD(real)(/*[in]*/ long i,/*[out,retval]*/ double*v);
	STDMETHOD(Solve)(/*[in]*/ VARIANT*z,/*[out,retval]*/long*n);
protected:
    static bool GetZ(VARIANT *z,double dz[10]);
    static bool GetZ_VBA (VARIANT *z,double dz[10],SAFEARRAY*sa);
    static bool GetZ_VBS (VARIANT *z,double dz[10],SAFEARRAY*sa);
    static bool GetZ_JS  (VARIANT *z,double dz[10],IDispatch*p ); 
    static bool GetZ_BSTR(VARIANT *z,double dz[10],const wchar_t*s); 
protected:
    long    m_nRootCount;   //根的个数
    double  m_x[12];        //求出的根
};
