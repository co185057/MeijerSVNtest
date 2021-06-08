// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "DevMgr.h"

/////////////////////////////////////////////////////////////////////////////
// CDevMgr

/////////////////////////////////////////////////////////////////////////////
// CDevMgr properties

CString CDevMgr::GetFileDescription()
{
	CString result;
	GetProperty(0x1, VT_BSTR, (void*)&result);
	return result;
}

void CDevMgr::SetFileDescription(LPCTSTR propVal)
{
	SetProperty(0x1, VT_BSTR, propVal);
}

CString CDevMgr::GetFileVersion()
{
	CString result;
	GetProperty(0x2, VT_BSTR, (void*)&result);
	return result;
}

void CDevMgr::SetFileVersion(LPCTSTR propVal)
{
	SetProperty(0x2, VT_BSTR, propVal);
}

CString CDevMgr::GetLegalCopyright()
{
	CString result;
	GetProperty(0x3, VT_BSTR, (void*)&result);
	return result;
}

void CDevMgr::SetLegalCopyright(LPCTSTR propVal)
{
	SetProperty(0x3, VT_BSTR, propVal);
}

BOOL CDevMgr::GetInputEventEnabled()
{
	BOOL result;
	GetProperty(0x4, VT_BOOL, (void*)&result);
	return result;
}

void CDevMgr::SetInputEventEnabled(BOOL propVal)
{
	SetProperty(0x4, VT_BOOL, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// CDevMgr operations

void CDevMgr::Open()
{
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CDevMgr::Close()
{
	InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


void CDevMgr::Enable(long DeviceID, long DeviceClass, BOOL fEnable)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_BOOL;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 DeviceID, DeviceClass, fEnable);
}


long CDevMgr::GetAvailableDevices(long DeviceClass)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x2e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		DeviceClass);
	return result;
}




CString CDevMgr::GetDeviceDescription(long DeviceID, long DeviceClass)
{
	CString result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x32, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		DeviceID, DeviceClass);
	return result;
}


void CDevMgr::ClearInput(long DeviceClass)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 DeviceClass);
}


void CDevMgr::MiscSetIndicator(long DeviceID, long Indicator, long State)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 DeviceID, Indicator, State);
}

void CDevMgr::MiscGetIndicatorStatus(long DeviceID, long Indicator, long* pState)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_PI4;
	InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 DeviceID, Indicator, pState);
}

void CDevMgr::EncryptorClearKey(long DeviceID, long KeyNumber)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 DeviceID, KeyNumber);
}

void CDevMgr::EncryptorGetPinBlock(long DeviceID, long KeyNumber, LPCTSTR AccountNum)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_BSTR;
	InvokeHelper(0x14, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 DeviceID, KeyNumber, AccountNum);
}

void CDevMgr::EncryptorStoreKey(long DeviceID, long KeyNumber, LPCTSTR Key, long Action, long ExchangeKey)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_BSTR VTS_I4 VTS_I4;
	InvokeHelper(0x15, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 DeviceID, KeyNumber, Key, Action, ExchangeKey);
}


void CDevMgr::CashChangerDispense(long DeviceID, long Amount)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x17, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 DeviceID, Amount);
}

//+dp185016 
void CDevMgr::CashChangerDispense(long DeviceID, LPCTSTR CashCounts)
{
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x18, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 DeviceID, CashCounts);
}
//-dp185016

void CDevMgr::CashChangerGetCashCounts(long DeviceID, BSTR* pCashCounts, BOOL* pDiscrepancy)
{
	static BYTE parms[] =
		VTS_I4 VTS_PBSTR VTS_PBOOL;
	InvokeHelper(0x19, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 DeviceID, pCashCounts, pDiscrepancy);
}


void CDevMgr::CashChangerGetTamperStatus(long DeviceID, BSTR* pTamperStatus)
{
	static BYTE parms[] =
		VTS_I4 VTS_PBSTR;
	InvokeHelper(0x1b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 DeviceID, pTamperStatus);
}




CString CDevMgr::GetCashChangerCurrencyCashList(long DeviceID)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x36, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		DeviceID);
	return result;
}

CString CDevMgr::GetCashChangerCurrencyCode(long DeviceID)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x37, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		DeviceID);
	return result;
}

CString CDevMgr::GetCashChangerCurrencyCodeList(long DeviceID)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x38, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		DeviceID);
	return result;
}

CString CDevMgr::GetCashChangerCurrencyContainerMap(long DeviceID)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x39, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		DeviceID);
	return result;
}


BOOL CDevMgr::GetCashChangerTampIndicatorEnabled(long DeviceID)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		DeviceID);
	return result;
}

void CDevMgr::SetCashChangerTampIndicatorEnabled(long DeviceID, BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_BOOL;
	InvokeHelper(0x3b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 DeviceID, bNewValue);
}

BOOL CDevMgr::GetCashChangerCashTaken(long DeviceID)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		DeviceID);
	return result;
}

void CDevMgr::SetCashChangerCashTaken(long DeviceID, BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_BOOL;
	InvokeHelper(0x3c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 DeviceID, bNewValue);
}

CString CDevMgr::GetEncryptorEncryptedPIN(long DeviceID)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		DeviceID);
	return result;
}

long CDevMgr::GetCashAcceptorAsyncResultCode(long lDeviceID)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		lDeviceID);
	return result;
}

CString CDevMgr::GetCashAcceptorCurrencyAcceptList(long lDeviceID)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		lDeviceID);
	return result;
}

void CDevMgr::SetCashAcceptorCurrencyAcceptList(long lDeviceID, LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x3f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lDeviceID, lpszNewValue);
}

CString CDevMgr::GetCashAcceptorCurrencyCashList(long lDeviceID)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x40, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		lDeviceID);
	return result;
}

CString CDevMgr::GetCashAcceptorCurrencyCode(long lDeviceID)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x41, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		lDeviceID);
	return result;
}

void CDevMgr::SetCashAcceptorCurrencyCode(long lDeviceID, LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x41, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lDeviceID, lpszNewValue);
}

CString CDevMgr::GetCashAcceptorCurrencyCodeList(long lDeviceID)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x42, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		lDeviceID);
	return result;
}

long CDevMgr::GetCashAcceptorDeviceStatus(long lDeviceID)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x43, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		lDeviceID);
	return result;
}

BOOL CDevMgr::GetCashAcceptorCapEscrow(long lDeviceID)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x44, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		lDeviceID);
	return result;
}

BOOL CDevMgr::GetCashAcceptorAutoDisable(long lDeviceID)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x45, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		lDeviceID);
	return result;
}

void CDevMgr::SetCashAcceptorAutoDisable(long lDeviceID, BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_BOOL;
	InvokeHelper(0x45, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lDeviceID, bNewValue);
}

void CDevMgr::CashAcceptorAccept(long lDeviceID)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x20, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 lDeviceID);
}

void CDevMgr::CashAcceptorReject(long lDeviceID)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x21, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 lDeviceID);
}

void CDevMgr::CashAcceptorReadBillCounts(long lDeviceID, BSTR* pCashCounts)
{
	static BYTE parms[] =
		VTS_I4 VTS_PBSTR;
	InvokeHelper(0x22, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 lDeviceID, pCashCounts);
}

void CDevMgr::CashAcceptorResetBillCounts(long lDeviceID)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x23, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 lDeviceID);
}


CString CDevMgr::GetCashChangerLowIndicatorList(long DeviceID)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x48, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		DeviceID);
	return result;
}


void CDevMgr::CheckHealth(long DeviceClass, long DeviceID, long Level)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x25, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 DeviceClass, DeviceID, Level);
}

CString CDevMgr::GetDeviceAvailability(long DeviceClass)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x4a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		DeviceClass);
	return result;
}

CString CDevMgr::GetCashChangerDispensedCashList(long DeviceID)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x4b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		DeviceID);
	return result;
}


BOOL CDevMgr::GetAutoDisable(long DeviceID, long DeviceClass)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x4d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		DeviceID, DeviceClass);
	return result;
}

void CDevMgr::SetAutoDisable(long DeviceID, long DeviceClass, BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_BOOL;
	InvokeHelper(0x4d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 DeviceID, DeviceClass, bNewValue);
}

void CDevMgr::SigCapBeginCapture(long DeviceID, LPCTSTR FormName)
{
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x4e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 DeviceID, FormName);
}

void CDevMgr::SigCapEndCapture(long DeviceID)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x4f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 DeviceID);
}

void CDevMgr::SigCapDataToBitmap(long DeviceID, LPCTSTR FileName)
{
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x50, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 DeviceID, FileName);
}

void CDevMgr::SigCapSetWindowHandle(long DeviceID, long* pHWnd)
{
	static BYTE parms[] =
		VTS_I4 VTS_PI4;
	InvokeHelper(0x51, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 DeviceID, pHWnd);
}

void CDevMgr::SigCapDataTo5991Format(long DeviceID, BSTR* pbsData)
{
	static BYTE parms[] =
		VTS_I4 VTS_PBSTR;
	InvokeHelper(0x52, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 DeviceID, pbsData);
}

long CDevMgr::GetSigCapNotifyStyle(long DeviceID)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x53, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		DeviceID);
	return result;
}

void CDevMgr::SetSigCapNotifyStyle(long DeviceID, long nNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x53, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 DeviceID, nNewValue);
}


void CDevMgr::CoinAcceptorAccept(long DeviceID)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x57, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 DeviceID);
}

void CDevMgr::CoinAcceptorReadCoinCounts(long DeviceID, BSTR* pCoinCounts)
{
	static BYTE parms[] =
		VTS_I4 VTS_PBSTR;
	InvokeHelper(0x58, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 DeviceID, pCoinCounts);
}

void CDevMgr::CoinAcceptorReject(long DeviceID)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x59, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 DeviceID);
}

void CDevMgr::CoinAcceptorResetCoinCounts(long DeviceID)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x5a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 DeviceID);
}

CString CDevMgr::GetCoinAcceptorCurrencyCode(long DeviceID)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x5b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		DeviceID);
	return result;
}

void CDevMgr::SetCoinAcceptorCurrencyCode(long DeviceID, LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x5b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 DeviceID, lpszNewValue);
}

BOOL CDevMgr::GetCoinAcceptorEnableCoins(long DeviceID)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x5c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		DeviceID);
	return result;
}

void CDevMgr::SetCoinAcceptorEnableCoins(long DeviceID, BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_BOOL;
	InvokeHelper(0x5c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 DeviceID, bNewValue);
}

long CDevMgr::GetCoinAcceptorAsyncResultCodeExt(long DeviceID)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x5d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		DeviceID);
	return result;
}

BOOL CDevMgr::GetCoinAcceptorCapFullSensor(long DeviceID)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x5e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		DeviceID);
	return result;
}

BOOL CDevMgr::GetCoinAcceptorCapEscrow(long DeviceID)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x5f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		DeviceID);
	return result;
}

BOOL CDevMgr::GetCoinAcceptorCapNearFullSensor(long DeviceID)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		DeviceID);
	return result;
}

CString CDevMgr::GetCoinAcceptorCoinData(long DeviceID)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x61, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		DeviceID);
	return result;
}

long CDevMgr::GetCoinAcceptorCoinEscrowAmount(long DeviceID)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x62, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		DeviceID);
	return result;
}

long CDevMgr::GetCoinAcceptorCoinEscrowCount(long DeviceID)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x63, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		DeviceID);
	return result;
}

CString CDevMgr::GetCoinAcceptorCoinList(long DeviceID)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		DeviceID);
	return result;
}

CString CDevMgr::GetCoinAcceptorCurrencyCodeList(long DeviceID)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		DeviceID);
	return result;
}

long CDevMgr::GetCoinAcceptorDeviceStatus(long DeviceID)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		DeviceID);
	return result;
}

long CDevMgr::GetCoinAcceptorAsyncResultCode(long DeviceID)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		DeviceID);
	return result;
}


long CDevMgr::GetEncryptorPINBlockFormat(long DeviceID)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		DeviceID);
	return result;
}

void CDevMgr::SetEncryptorPINBlockFormat(long DeviceID, long nNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x69, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 DeviceID, nNewValue);
}

void CDevMgr::CashChangerReplenishCoins(long DeviceID, long* plData, BSTR* pbsData)
{
	static BYTE parms[] =
		VTS_I4 VTS_PI4 VTS_PBSTR;
	InvokeHelper(0x6b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 DeviceID, plData, pbsData);
}

void CDevMgr::CashChangerGetStatusValues(long DeviceID, long* plCoinStatus, long* plBillStatus)
{
	static BYTE parms[] =
		VTS_I4 VTS_PI4 VTS_PI4;
	InvokeHelper(0x6c, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 DeviceID, plCoinStatus, plBillStatus);
}

long CDevMgr::GetResultCodeExtended(long DeviceClass, long DeviceID)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x6d, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		DeviceClass, DeviceID);
	return result;
}

CString CDevMgr::GetDeviceName(long DeviceClass, long DeviceID)
{
	CString result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x6e, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		DeviceClass, DeviceID);
	return result;
}

//+SR742
void CDevMgr::CoinAcceptorOpenDevice(long DeviceID)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6F, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 DeviceID);
}
void CDevMgr::CashAcceptorOpenDevice(long DeviceID)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x70, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 DeviceID);
}
void CDevMgr::CashChangerOpenDevice() 
{
	InvokeHelper(0x71, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}
void CDevMgr::CashChangerCloseDevice() 
{
	InvokeHelper(0x72, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}
//-SR742
