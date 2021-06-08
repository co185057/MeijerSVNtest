//////////////////////////////////////////////////////////////////////////////////////////////////
//
// FILE:  SMSmDataEntry.CPP
//
// TITLE: Class implementation for store mode Restricted Items state
//
//
// AUTHOR:    Peter Denhoed
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdafx.h>                 // MS MFC always needed first
#include <afxtempl.h>               // MS MFC template header

#include "Common.h"                 // MGV common includes

#include "SMState.h"                // MGV base state
#include "SMSmDataEntry.h"    // MGV this state

#define COMP_ID ID_SM               // base state component
#define T_ID    _T("SmDataEntry")

IMPLEMENT_DYNCREATE(SMSmDataEntry, CObject)// MFC Runtime class/object information


DEFINE_TIMESTAMP

//////////////////////////////////////////
// Constructor
//////////////////////////////////////////
SMSmDataEntry::SMSmDataEntry()
{
  IMPLEMENT_TIMESTAMP
}
