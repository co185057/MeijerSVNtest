#if !defined(AFX_STDOPOSKEYLOCK_H__B838F1F3_0024_4258_817D_000843F9193F__INCLUDED_)
#define AFX_STDOPOSKEYLOCK_H__B838F1F3_0024_4258_817D_000843F9193F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CStdOPOSKeylock wrapper class

template<class TYPE>
class TOPOSKeylock : public TYPE
   {
   public:
	   CLSID const& GetClsid()
	      {
		   static CLSID const clsid
			   = { 0xccb90092, 0xb81e, 0x11d2, { 0xab, 0x74, 0x0, 0x40, 0x5, 0x4c, 0x37, 0x19 } };
		   return clsid;
	      }
	   virtual BOOL Create(LPCTSTR lpszClassName,
		   LPCTSTR lpszWindowName, DWORD dwStyle,
		   const RECT& rect,
		   CWnd* pParentWnd, UINT nID,
		   CCreateContext* pContext = NULL)
	      { 
         return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
         }

       BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle,
		   const RECT& rect, CWnd* pParentWnd, UINT nID,
		   CFile* pPersist = NULL, BOOL bStorage = FALSE,
		   BSTR bstrLicKey = NULL)
	      { 
         return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		      pPersist, bStorage, bstrLicKey); 
         }
   // Attributes
   public:
   // Operations
   public:
      long GetOpenResult()
         {
         long result;
         InvokeHelper(0x31, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
         return result;
         }
      CString GetCheckHealthText()
         {
         CString result;
         InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
         return result;
         }
      BOOL GetClaimed()
         {
         BOOL result;
         InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
         return result;
         }
      BOOL GetDeviceEnabled()
         {
         BOOL result;
         InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
         return result;
         }
      void SetDeviceEnabled(BOOL bNewValue)
         {
         static BYTE parms[] = VTS_BOOL;
         InvokeHelper(0x11, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, bNewValue);
         }
      BOOL GetFreezeEvents()
         {
         BOOL result;
         InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
         return result;
         }
      void SetFreezeEvents(BOOL bNewValue)
         {
         static BYTE parms[] = VTS_BOOL;
         InvokeHelper(0x12, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, bNewValue);
         }
      long GetResultCode()
         {
         long result;
         InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
         return result;
         }
      long GetResultCodeExtended()
         {
         long result;
         InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
         return result;
         }
      long GetState()
         {
         long result;
         InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
         return result;
         }
      CString GetControlObjectDescription()
         {
         CString result;
         InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
         return result;
         }
      long GetControlObjectVersion()
         {
         long result;
         InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
         return result;
         }
      CString GetServiceObjectDescription()
         {
         CString result;
         InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
         return result;
         }
      long GetServiceObjectVersion()
         {
         long result;
         InvokeHelper(0x1c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
         return result;
         }
      CString GetDeviceDescription()
         {
         CString result;
         InvokeHelper(0x1d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
         return result;
         }
      CString GetDeviceName()
         {
         CString result;
         InvokeHelper(0x1e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
         return result;
         }
      long CheckHealth(long Level)
         {
         long result;
         static BYTE parms[] = VTS_I4;
         InvokeHelper(0x1f, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Level);
         return result;
         }
      long ClaimDevice(long Timeout)
         {
         long result;
         static BYTE parms[] = VTS_I4;
         InvokeHelper(0x20, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Timeout);
         return result;
         }
      long Claim(long Timeout)
         {
         long result;
         static BYTE parms[] = VTS_I4;
         InvokeHelper(0x20, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Timeout);
         return result;
         }
      long Close()
         {
         long result;
         InvokeHelper(0x23, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
         return result;
         }
      long DirectIO(long Command, long* pData, BSTR* pString)
         {
         long result;
         static BYTE parms[] = VTS_I4 VTS_PI4 VTS_PBSTR;
         InvokeHelper(0x24, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
            Command, pData, pString);
         return result;
         }
      long Open(LPCTSTR DeviceName)
         {
         long result;
         static BYTE parms[] = VTS_BSTR;
         InvokeHelper(0x25, DISPATCH_METHOD, VT_I4, (void*)&result, parms, DeviceName);
         return result;
         }
      long ReleaseDevice()
         {
         long result;
         InvokeHelper(0x26, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
         return result;
         }
      long Release()
         {
         long result;
         InvokeHelper(0x26, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
         return result;
         }
      long GetKeyPosition()
         {
         long result;
         InvokeHelper(0x32, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
         return result;
         }
      long GetPositionCount()
         {
         long result;
         InvokeHelper(0x33, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
         return result;
         }
      long WaitForKeylockChange(long KeyPosition, long Timeout)
         {
         long result;
         static BYTE parms[] = VTS_I4 VTS_I4;
         InvokeHelper(0x3c, DISPATCH_METHOD, VT_I4, (void*)&result, parms, KeyPosition, Timeout);
         return result;
         }
      long GetBinaryConversion()
         {
         long result;
         InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
         return result;
         }
      void SetBinaryConversion(long nNewValue)
         {
         static BYTE parms[] = VTS_I4;
         InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nNewValue);
         }
      long GetCapPowerReporting()
         {
         long result;
         InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
         return result;
         }
      long GetPowerNotify()
         {
         long result;
         InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
         return result;
         }
      void SetPowerNotify(long nNewValue)
         {
         static BYTE parms[] = VTS_I4;
         InvokeHelper(0x14, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nNewValue);
         }
      long GetPowerState()
         {
         long result;
         InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
         return result;
         }
      BOOL GetCapStatisticsReporting()
         {
         BOOL result;
         InvokeHelper(0x27, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
         return result;
         }
      BOOL GetCapUpdateStatistics()
         {
         BOOL result;
         InvokeHelper(0x28, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
         return result;
         }
      long ResetStatistics(LPCTSTR StatisticsBuffer)
         {
         long result;
         static BYTE parms[] = VTS_BSTR;
         InvokeHelper(0x29, DISPATCH_METHOD, VT_I4, (void*)&result, parms, StatisticsBuffer);
         return result;
         }
      long RetrieveStatistics(BSTR* pStatisticsBuffer)
         {
         long result;
         static BYTE parms[] = VTS_PBSTR;
         InvokeHelper(0x2a, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pStatisticsBuffer);
         return result;
         }
      long UpdateStatistics(LPCTSTR StatisticsBuffer)
         {
         long result;
         static BYTE parms[] = VTS_BSTR;
         InvokeHelper(0x2b, DISPATCH_METHOD, VT_I4, (void*)&result, parms, StatisticsBuffer);
         return result;
         }
   };

// This is the standard MFC Wizard wrapper equivalent for the Common OPOS Keylock OCX. 
// Place IMPLEMENT_DYNCREATE(CStdOPOSKeylock, CWnd) in your code. 

class CStdOPOSKeylock : public TOPOSKeylock<CWnd>
   {
   protected:
	   DECLARE_DYNCREATE(CStdOPOSKeylock)
   };

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDOPOSKEYLOCK_H__B838F1F3_0024_4258_817D_000843F9193F__INCLUDED_)
