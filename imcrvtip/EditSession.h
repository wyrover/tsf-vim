﻿
#ifndef EDITSESSION_H
#define EDITSESSION_H

#include "imcrvtip.h"
#include "TextService.h"

class CEditSessionBase : public ITfEditSession
{
public:
	CEditSessionBase(CTextService *pTextService, ITfContext *pContext)
	{
		_cRef = 1;
		_pContext = pContext;
		_pContext->AddRef();

		_pTextService = pTextService;
		_pTextService->AddRef();
	}
	virtual ~CEditSessionBase()
	{
		_pContext->Release();
		_pTextService->Release();
	}

	// IUnknown
	STDMETHODIMP QueryInterface(REFIID riid, void **ppvObj)
	{
		if(ppvObj == NULL)
		{
			return E_INVALIDARG;
		}

		*ppvObj = NULL;

		if(IsEqualIID(riid, IID_IUnknown) || IsEqualIID(riid, IID_ITfEditSession))
		{
			*ppvObj = (ITfLangBarItemButton *)this;
		}

		if(*ppvObj)
		{
			AddRef();
			return S_OK;
		}

		return E_NOINTERFACE;
	}
	STDMETHODIMP_(ULONG) AddRef(void)
	{
		return ++_cRef;
	}
	STDMETHODIMP_(ULONG) Release(void)
	{
		if(--_cRef == 0)
		{
			delete this;
			return 0;
		}

		return _cRef;
	}

	// ITfEditSession
	virtual STDMETHODIMP DoEditSession(TfEditCookie ec) = 0;

protected:
	ITfContext *_pContext;
	CTextService *_pTextService;

private:
	LONG _cRef;
};

#endif //EDITSESSION_H
