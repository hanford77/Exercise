#pragma once

#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __SolveEquationCom_h__
#define __SolveEquationCom_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEquation_FWD_DEFINED__
#define __IEquation_FWD_DEFINED__
typedef interface IEquation IEquation;
#endif 	/* __IEquation_FWD_DEFINED__ */


#ifndef __Equation_FWD_DEFINED__
#define __Equation_FWD_DEFINED__

#ifdef __cplusplus
typedef class Equation Equation;
#else
typedef struct Equation Equation;
#endif /* __cplusplus */

#endif 	/* __Equation_FWD_DEFINED__ */


/* header files for imported files */
//#include "oaidl.h"
//#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IEquation_INTERFACE_DEFINED__
#define __IEquation_INTERFACE_DEFINED__

/* interface IEquation */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IEquation;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("20907E97-4E8D-4682-BA03-AB1164C199CA")
    IEquation : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Solve( 
            /* [in] */ VARIANT __RPC_FAR *z,
            /* [retval][out] */ long __RPC_FAR *n) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE real( 
            /* [in] */ long i,
            /* [retval][out] */ double __RPC_FAR *v) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE imag( 
            /* [in] */ long i,
            /* [retval][out] */ double __RPC_FAR *v) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE diff( 
            /* [in] */ long i,
            /* [retval][out] */ double __RPC_FAR *v) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RootCount( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEquationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEquation __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEquation __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEquation __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IEquation __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IEquation __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IEquation __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IEquation __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Solve )( 
            IEquation __RPC_FAR * This,
            /* [in] */ VARIANT __RPC_FAR *z,
            /* [retval][out] */ long __RPC_FAR *n);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *real )( 
            IEquation __RPC_FAR * This,
            /* [in] */ long i,
            /* [retval][out] */ double __RPC_FAR *v);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *imag )( 
            IEquation __RPC_FAR * This,
            /* [in] */ long i,
            /* [retval][out] */ double __RPC_FAR *v);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *diff )( 
            IEquation __RPC_FAR * This,
            /* [in] */ long i,
            /* [retval][out] */ double __RPC_FAR *v);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RootCount )( 
            IEquation __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        END_INTERFACE
    } IEquationVtbl;

    interface IEquation
    {
        CONST_VTBL struct IEquationVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEquation_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEquation_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEquation_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEquation_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IEquation_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IEquation_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IEquation_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IEquation_Solve(This,z,n)	\
    (This)->lpVtbl -> Solve(This,z,n)

#define IEquation_real(This,i,v)	\
    (This)->lpVtbl -> real(This,i,v)

#define IEquation_imag(This,i,v)	\
    (This)->lpVtbl -> imag(This,i,v)

#define IEquation_diff(This,i,v)	\
    (This)->lpVtbl -> diff(This,i,v)

#define IEquation_get_RootCount(This,pVal)	\
    (This)->lpVtbl -> get_RootCount(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEquation_Solve_Proxy( 
    IEquation __RPC_FAR * This,
    /* [in] */ VARIANT __RPC_FAR *z,
    /* [retval][out] */ long __RPC_FAR *n);


void __RPC_STUB IEquation_Solve_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEquation_real_Proxy( 
    IEquation __RPC_FAR * This,
    /* [in] */ long i,
    /* [retval][out] */ double __RPC_FAR *v);


void __RPC_STUB IEquation_real_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEquation_imag_Proxy( 
    IEquation __RPC_FAR * This,
    /* [in] */ long i,
    /* [retval][out] */ double __RPC_FAR *v);


void __RPC_STUB IEquation_imag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEquation_diff_Proxy( 
    IEquation __RPC_FAR * This,
    /* [in] */ long i,
    /* [retval][out] */ double __RPC_FAR *v);


void __RPC_STUB IEquation_diff_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEquation_get_RootCount_Proxy( 
    IEquation __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IEquation_get_RootCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEquation_INTERFACE_DEFINED__ */



#ifndef __SolveEquationLib_LIBRARY_DEFINED__
#define __SolveEquationLib_LIBRARY_DEFINED__

/* library SolveEquationLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_SolveEquationLib;

EXTERN_C const CLSID CLSID_Equation;

#ifdef __cplusplus

class DECLSPEC_UUID("E2E86938-6DE1-49E1-98A3-A0DD9882E837")
Equation;
#endif
#endif /* __SolveEquationLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long __RPC_FAR *, unsigned long            , VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long __RPC_FAR *, VARIANT __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
