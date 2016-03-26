

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sat Mar 26 18:32:03 2016
 */
/* Compiler settings for Welfare.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __Welfare_h_h__
#define __Welfare_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IWelfare_FWD_DEFINED__
#define __IWelfare_FWD_DEFINED__
typedef interface IWelfare IWelfare;
#endif 	/* __IWelfare_FWD_DEFINED__ */


#ifndef __Welfare_FWD_DEFINED__
#define __Welfare_FWD_DEFINED__

#ifdef __cplusplus
typedef class Welfare Welfare;
#else
typedef struct Welfare Welfare;
#endif /* __cplusplus */

#endif 	/* __Welfare_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __Welfare_LIBRARY_DEFINED__
#define __Welfare_LIBRARY_DEFINED__

/* library Welfare */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_Welfare;

#ifndef __IWelfare_DISPINTERFACE_DEFINED__
#define __IWelfare_DISPINTERFACE_DEFINED__

/* dispinterface IWelfare */
/* [uuid] */ 


EXTERN_C const IID DIID_IWelfare;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("5ED7BFFF-BF58-4689-A65C-11D4A2C93DA8")
    IWelfare : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IWelfareVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWelfare * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWelfare * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWelfare * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWelfare * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWelfare * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWelfare * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWelfare * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IWelfareVtbl;

    interface IWelfare
    {
        CONST_VTBL struct IWelfareVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWelfare_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWelfare_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWelfare_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWelfare_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWelfare_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWelfare_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWelfare_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IWelfare_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Welfare;

#ifdef __cplusplus

class DECLSPEC_UUID("064F636F-DB71-4D4A-BA15-5F33353F180B")
Welfare;
#endif
#endif /* __Welfare_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


