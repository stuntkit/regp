// StuntGP.h : main header file for the STUNTGP application
//
#include <process.h>

#if !defined(AFX_STUNTGP_H__BA89FE99_6AF5_4378_9C99_CAF4B0C5997B__INCLUDED_)
#define AFX_STUNTGP_H__BA89FE99_6AF5_4378_9C99_CAF4B0C5997B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "res/resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CStuntGPApp:
// See StuntGP.cpp for the implementation of this class
//

// VTABLE: STUNTGP 0x0040f3a8
// SIZE: 0x98
class CStuntGPApp : public CWinApp
{
public:
	CStuntGPApp(LPCTSTR lpszAppName = NULL);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStuntGPApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CStuntGPApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

// SYNTHETIC: STUNTGP 0x0040d145
// CWinApp::GetRuntimeClass

// SYNTHETIC: STUNTGP 0x00401030
// CStuntGPApp::`scalar deleting destructor'

// SYNTHETIC: STUNTGP 0x00401190
// CObject::Serialize

// SYNTHETIC: STUNTGP 0x00408a8a
// CCmdTarget::OnCmdMsg

// SYNTHETIC: STUNTGP 0x00408be9
// CCmdTarget::OnFinalRelease

// SYNTHETIC: STUNTGP 0x00408b99
// CCmdTarget::IsInvokeAllowed

// SYNTHETIC: STUNTGP 0x00408c21
// CCmdTarget::GetDispatchIID

// SYNTHETIC: STUNTGP 0x0040840f
// CCmdTarget::GetTypeInfoCount

// TODO: reccmp cannot handle multiple functions with the same address: https://github.com/isledecomp/reccmp/issues/287
// SYNTHETIC: STUNTGP 0x0040840f
// CCmdTarget::GetTypeLibCache

// SYNTHETIC: STUNTGP 0x00408b9f
// CCmdTarget::GetTypeLib

// FUNCTION: STUNTGP 0x00401000
// CStuntGPApp::GetMessageMap

// GLOBAL: STUNTGP 0x0040f370
// CStuntGPApp::messageMap

// GLOBAL: STUNTGP 0x0040f378
// CStuntGPApp::_messageEntries

// FUNCTION: STUNTGP 0x00401050
// CStuntGPApp::~CStuntGPApp

// FUNCTION: STUNTGP 0x0040cfa9
// CWinApp::~CWinApp
#define BUFFER_SIZE 200

extern "C" {
	void __cdecl run(int mode, const char *cmdname, const  char *const *argv);
}

#endif // !defined(AFX_STUNTGP_H__BA89FE99_6AF5_4378_9C99_CAF4B0C5997B__INCLUDED_)
