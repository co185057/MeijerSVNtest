//////////////////////////////////////////////////////////////////////////////////////////////////
//
// File:  SMSystemMessageBase.cpp
//
// Description: Base class for system message classes.  Differences between
//   subclasses are what combination of Continue and Cancel buttons they have.
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdafx.h>                 // MS MFC always needed first
#include <afxtempl.h>               // MS MFC template header

#include "Common.h"                 // Common includes

#include "SMSystemMessage.h"
#include "SMTakeReceipt.h"
#include "SMSmAuthorization.h"
#include "ncrpid.h"
#include "SMInProgress.h"
//+dp185016 
#include "SMSmAssistMode.h"
//-dp185016
#include "SMSmMediaStatus.h"
#include "SMFinish.h"
#include "SMTakeChange.h"			// SR742

#include "SafePayC.h"				// Need SafePay error constants.
#define COMP_ID ID_SM               // Base state component
#define T_ID _T("SystemMessageBase")

IMPLEMENT_DYNCREATE(SMSystemMessageBase, CObject)// MFC Runtime class/object information

DEFINE_TIMESTAMP

bool bInSystemMessage = false;   

////////////////////////////////////////////////
SMSystemMessageBase::SMSystemMessageBase(BMPS   bitmap,
										 PSTEXT title,
										 bool   continueButton,
										 bool   cancelButton,
										 LPCTSTR szMessage,   // string text message or NULL
										 PSTEXT psMessage,   // PSTEXT message number or PS_NOTEXT
										 PSTEXT promptText,  // PSTEXT prompt number or PS_NOTEXT
										 long   promptValue, // prompt area sale value
										 long   deviceClass, // device class, -1 for none
										 bool   checkHealth, // DMCheckHealth after msg?
										 bool showTotal,
										 bool showRetractedTotal,
										 bool okButton,       //OK button (button #1)
										 bool flashBtn1)
										 : bitmap(bitmap),
										 title(title),
										 continueButton(continueButton),
										 cancelButton(cancelButton),
										 csMessage(szMessage),
										 psMessage(psMessage),
										 promptText(promptText),
										 promptValue(promptValue),
										 deviceClass(deviceClass),
										 checkHealth(checkHealth),
										 showTotal(showTotal),
										 showRetractedTotal(showRetractedTotal),
										 okButton(okButton),
										 flashButton1(flashBtn1),
										 m_bDeviceErrorNotFixed(false),
										 m_bUseBitmap(false),
										 m_nWave(PS_NOSOUND),
										 csCurContext(EMPTY_STRING),
										 m_bDeviceErrorLogged(false)
{
	IMPLEMENT_TIMESTAMP
}

////////////////////////////////////////
SMSystemMessageBase::SMSystemMessageBase()
: bitmap(0),
  continueButton(false),
  cancelButton(false),
  title(PS_NOTEXT),
  psMessage(PS_NOTEXT),
  promptText(PS_NOTEXT),
  promptValue(-1),
  deviceClass(-1),
  checkHealth(false),
  showTotal(false),
  showRetractedTotal(false),
  okButton(false),
  flashButton1(false),
  m_nWave(PS_NOSOUND),
  m_bUseBitmap(false),
  m_bCashChangerHopperDefault(false),
  m_bBillDispenserError(false),
  m_bCashChangerError(false),
  m_bDeviceErrorNotFixed(false),
  m_bForceFixDeviceError(false),	//SR742+
  csCurContext(EMPTY_STRING),
  m_bDeviceErrorLogged(false)
{
	IMPLEMENT_TIMESTAMP
}



////////////////////////////////////////
SMStateBase  *SMSystemMessageBase::Deliver(BMPS   argBitmap,
										   PSTEXT argTitle,
										   bool   argContinueButton,
										   bool   argCancelButton,
										   LPCTSTR argszMessage,   // string text message or NULL
										   PSTEXT argpsMessage,   // PSTEXT message number or PS_NOTEXT
										   PSTEXT argPromptText,  // PSTEXT prompt number or PS_NOTEXT
										   long   argPromptValue, // prompt area sale value
										   long   argDeviceClass, // device class, -1 for none
										   bool   argCheckHealth, // DMCheckHealth after msg?
										   bool argShowTotal,
										   bool argShowRetractedTotal,
										   bool argOkButton,       //OK button (button #1)
										   bool argFlashBtn1)
{
	bInSystemMessage = true;
	bitmap = argBitmap;
	title = argTitle;
	continueButton = argContinueButton;
	cancelButton = argCancelButton;
	csMessage = argszMessage;
	psMessage = argpsMessage;
	promptText = argPromptText;
	promptValue = argPromptValue;
	deviceClass = argDeviceClass;
	checkHealth = argCheckHealth;
	showTotal = argShowTotal;
	showRetractedTotal = argShowRetractedTotal;
	okButton = argOkButton;
	flashButton1 = argFlashBtn1;
	m_bDeviceErrorNotFixed = false;  //SCOT 3.1 Error Handling
	m_csMovie.Empty();  //Error Handling
	m_bUseBitmap = false;
	m_nWave = PS_NOSOUND;
	m_csTitle1.Empty();  
	m_csTitle2.Empty();  
//	if (ps.RemoteMode() && (m_View == DATANEEDED_DEVICEERROR)) // TAR 290396
	//when date format is wrong or date enter under age, we do not want to display Cancel button
	if (ps.RemoteMode() && (csMessage.Find(_T("Date should be in")) == -1) && (csMessage.Find(_T("Birth date does not")) == -1))
	{
		cancelButton = true;  	//Tar 228577
	}
	m_bSavedSafetyCoverClosed = g_bSafetyCoverClosed;  //TAR 298987-II 
	return this;
}

bool SMSystemMessageBase::DeliverDescriptorList(CDescriptorList &dlParameterList)
{
    
    // There should be ten parameters, 11, 12, 13 or 14 a variety of types
    if (dlParameterList.GetDescriptorCount() == 10)
    {
        trace(L6, _T("+SMSystemMessageBase::DeliverDescriptorList() - Parameter Count of 10"));
        Deliver((BMPS)DLParamDWORD(dlParameterList),    // bitmap
                (PSTEXT)DLParamDWORD(dlParameterList),  // title
                (bool)DLParamWORD(dlParameterList),     // continueButton,
                (bool)DLParamWORD(dlParameterList),     // cancelButton,
                (LPCTSTR)DLParamCString(dlParameterList), // szMessage
                (PSTEXT)DLParamDWORD(dlParameterList),  // psMessage
                (PSTEXT)DLParamDWORD(dlParameterList),  // promptText
                DLParamDWORD(dlParameterList),          // promptValue
                DLParamDWORD(dlParameterList),          // DeviceClass
                (bool)DLParamWORD(dlParameterList));    // checkHealth
        return true;
    }
    else if (dlParameterList.GetDescriptorCount() == 11)
    {
        trace(L6, _T("+SMSystemMessageBase::DeliverDescriptorList() - Parameter Count of 11"));
        Deliver((BMPS)DLParamDWORD(dlParameterList),    // bitmap
                (PSTEXT)DLParamDWORD(dlParameterList),  // title
                (bool)DLParamWORD(dlParameterList),     // continueButton,
                (bool)DLParamWORD(dlParameterList),     // cancelButton,
                (LPCTSTR)DLParamCString(dlParameterList), // szMessage
                (PSTEXT)DLParamDWORD(dlParameterList),  // psMessage
                (PSTEXT)DLParamDWORD(dlParameterList),  // promptText
                DLParamDWORD(dlParameterList),          // promptValue
                DLParamDWORD(dlParameterList),          // DeviceClass
                (bool)DLParamWORD(dlParameterList),     // checkHealth
                (bool)DLParamWORD(dlParameterList));    // argShowTotal
        return true;
    }
    else if (dlParameterList.GetDescriptorCount() == 12)
    {
        trace(L6, _T("+SMSystemMessageBase::DeliverDescriptorList() - Parameter Count of 12"));
        Deliver((BMPS)DLParamDWORD(dlParameterList),    // bitmap
                (PSTEXT)DLParamDWORD(dlParameterList),  // title
                (bool)DLParamWORD(dlParameterList),     // continueButton,
                (bool)DLParamWORD(dlParameterList),     // cancelButton,
                (LPCTSTR)DLParamCString(dlParameterList), // szMessage
                (PSTEXT)DLParamDWORD(dlParameterList),  // psMessage
                (PSTEXT)DLParamDWORD(dlParameterList),  // promptText
                DLParamDWORD(dlParameterList),          // promptValue
                DLParamDWORD(dlParameterList),          // DeviceClass
                (bool)DLParamWORD(dlParameterList),     // checkHealth
                (bool)DLParamWORD(dlParameterList),     // argShowTotal
                (bool)DLParamWORD(dlParameterList));    // argShowRetractedTotal
        return true;
    }
    else if (dlParameterList.GetDescriptorCount() == 13)
    {
        trace(L6, _T("+SMSystemMessageBase::DeliverDescriptorList() - Parameter Count of 13"));
        Deliver((BMPS)DLParamDWORD(dlParameterList),    // bitmap
                (PSTEXT)DLParamDWORD(dlParameterList),  // title
                (bool)DLParamWORD(dlParameterList),     // continueButton,
                (bool)DLParamWORD(dlParameterList),     // cancelButton,
                (LPCTSTR)DLParamCString(dlParameterList), // szMessage
                (PSTEXT)DLParamDWORD(dlParameterList),  // psMessage
                (PSTEXT)DLParamDWORD(dlParameterList),  // promptText
                DLParamDWORD(dlParameterList),          // promptValue
                DLParamDWORD(dlParameterList),          // DeviceClass
                (bool)DLParamWORD(dlParameterList),     // checkHealth
                (bool)DLParamWORD(dlParameterList),     // argShowTotal
                (bool)DLParamWORD(dlParameterList),     // argShowRetractedTotal
                (bool)DLParamWORD(dlParameterList));    // argOKButton
        return true;
    }
    else if (dlParameterList.GetDescriptorCount() == 14)
    {
        trace(L6, _T("+SMSystemMessageBase::DeliverDescriptorList() - Parameter Count of 14"));
        Deliver((BMPS)DLParamDWORD(dlParameterList),    // bitmap
                (PSTEXT)DLParamDWORD(dlParameterList),  // title
                (bool)DLParamWORD(dlParameterList),     // continueButton,
                (bool)DLParamWORD(dlParameterList),     // cancelButton,
                (LPCTSTR)DLParamCString(dlParameterList), // szMessage
                (PSTEXT)DLParamDWORD(dlParameterList),  // psMessage
                (PSTEXT)DLParamDWORD(dlParameterList),  // promptText
                DLParamDWORD(dlParameterList),          // promptValue
                DLParamDWORD(dlParameterList),          // DeviceClass
                (bool)DLParamWORD(dlParameterList),     // checkHealth
                (bool)DLParamWORD(dlParameterList),     // argShowTotal
                (bool)DLParamWORD(dlParameterList),     // argShowRetractedTotal
                (bool)DLParamWORD(dlParameterList),     // argOKButton
                (bool)DLParamWORD(dlParameterList));    // argFlashBtn1
        return true;
    }
    else
    {
        trace(L2, _T("+SMSystemMessageOpPassBase::DeliverDescriptorList() - ERROR - Parameter Count %d"), dlParameterList.GetDescriptorCount());
        return false;
    }
}

///////////////////////////////////////////
SMStateBase  *SMSystemMessageBase::Initialize(void)
{
	// Tar 228500
	if(    (deviceClass == DMCLASS_CASHACCEPTOR) 
		&& (lastDMCashAcceptorCode != DM_CASHACCEPTOR_STATUS_TAMPER_OUT ) //TAR268318:
      )
	{
		long lCode = dm.GetCashAcceptorDeviceStatus();
		if (lCode == DM_CASHACCEPTOR_STATUS_OK || lCode == DM_CASHACCEPTOR_STATUS_RESET ) //The problem is fixed already
		{
			return STATE_RETURN;
		}
	}

	// Begin TAR 206353
	// CANNOT enter Remote Assist Mode at this state, if we're not already in Remote AM
    if (!ps.RemoteMode()) 
		ra.RequestEnableAssistMode(false);   //Tar218739 //TAR 213249
	// End TAR 206353
	
	if (bIsInFinalization && g_bAllowRemove) // tar 223051 RJF
		g_bAllowRemove = false;
	TellApplicationStateToSecurity(KEY_AC_SET_APP_STATE_BEGIN, _T("SystemMessage") );

	//HDMerge-062502 Starts here..Added try catch statement around showscreen
	try{
		showScreen();
	}
	catch(...)
	{} //HDMerge-062502 ends here
	nTimeOut = getTimeout();
	
	m_bSavedSafetyCoverClosed = g_bSafetyCoverClosed;  //TAR 298987-II 
	return STATE_NULL;
}

///////////////////////////////////////////////////
// showScreen
///////////////////////////////////////////////////
void SMSystemMessageBase::showScreen(bool showInfo)
{
  bInSystemMessage = true;

  bool bumsg;					// SafePay - is an urgent message available.
  CString csUrgmsg;				// SafePay - holds urgent message text.
  CString csUrgfmt;				// SafePay - format string.

  if(!m_bDeviceErrorLogged//)  //Only log the device error once. Don't log it after pressing Continued button and the error still exists.
    && csMessage != ps.GetPSText( MSG_POS_TB_OUTOFSYNC_NEEDASSISTMODE ) ) //dp185016 if out of sync error, don't log it as a device error
  {
    LogDeviceError();
    m_bDeviceErrorLogged = true;
  }
  CString csPrevContext = ps.GetCurrentContext();
  ps.SetLanguage(SCOT_LANGUAGE_PRIMARY);

  bool bEmpty = false;
  bool bChuteJam = false;
  IsHopperSubstitutionUsed(bEmpty, bChuteJam);
  
  
  //ProcessDeviceErrorXMLFile(csMessage);
  if(csMessage.Find(_T("DeviceError")) != -1)
  {
	 if (csMessage.Find(_T("CashChanger")) != -1)
	 {
		 m_bCashChangerError = true;
		 if (csMessage.Find(_T("NCR_E5633")) != -1)
			m_bBillDispenserError = true;
		 else
		 {
			m_bBillDispenserError = false;
			if (csMessage.Find(_T("HOPPER")) != -1)
				m_bCashChangerHopperDefault = true;
			else
				m_bCashChangerHopperDefault = false;
		 }
	 }
	 else
		 m_bCashChangerError = false;

	 
    ProcessDeviceErrorXMLFile(csMessage, m_csTitle1, m_csTitle2, csMessage, bitmap, m_nWave, m_csMovie);
     // +SafePay Cash Recycler
     if(deviceClass == DMCLASS_CASHRECYCLER && 
        dm.m_csCashRecyclerModel == _CASHDISPENSER_SAFEPAY)
     {
		 // Does this error message contain a format string for displaying
		 // the SafePay urgent message?
         if(csMessage.Find(_T("%s")) != -1)
         {
             bumsg = dm.IsUrgentMessagePending(DMCLASS_CASHRECYCLER, 0);
             csUrgfmt = csMessage;
             csUrgmsg = _T("");

             if(! bumsg)
             {
                 Sleep(300);
                 bumsg = dm.IsUrgentMessagePending(DMCLASS_CASHRECYCLER, 0);
             }
             
             if(bumsg)
             {
                 if(dm.RetrieveUrgentMessage(csUrgmsg, DMCLASS_CASHRECYCLER, 0)
                     == OPOS_SUCCESS)
                 {
                     trace(L6, _T("SafePay Urgent Msg: [%s]"), (LPCTSTR)csUrgmsg);
                 }
             }
             csMessage.Format(csUrgfmt, (LPCTSTR)csUrgmsg);
         }

         // Clear out the urgent message queue.
         while(dm.IsUrgentMessagePending(DMCLASS_CASHRECYCLER, 0))
         {
             dm.RetrieveUrgentMessage(csUrgmsg, DMCLASS_CASHRECYCLER, 0);
         }
     }
     // -SafePay Cash Recycler
    if(bitmap)
      m_bUseBitmap = true;
    else
      m_bUseBitmap = false;
  }

  COleVariant v;

  if(m_nWave)
  {
    DMSayPhrase(m_nWave);
  }

  CPSXRedrawLock csRedrawLock(_T("Display"), _T("SMSystemMessageBase::showScreen"));

  // TAR207300 DMoore starts here
  if (ps.RemoteMode() || co.IsInAssistMenus())
  {
    // while in remote mode, got system message
    showRemoteScreen(showInfo);
    return;
  }// TAR207300 DMoore ends here

  if ( showInfo && !m_bUseBitmap)
  { 
    csCurContext = _T("SystemMessage");
	if (m_bCashChangerError == true && m_bBillDispenserError == false)
	{
		
			if (dm.m_csCoinDispenserModel==_COINDISPENSER_TELEQUIP_HOPPER && !dm.m_csCoinDispenserStage.IsEmpty() )
			{	
				if (m_bCashChangerHopperDefault == true)
				{
					if (lUnapprovedHopperSubstitution > 0)
					{
						csCurContext = _T("SystemMessageHopperSubstitution");
					}
					else if (lChangeDue > 0)
					{
						csCurContext = _T("SystemMessageHopperFailure");
					}
				}
			}
		
	}

	//SR742+ cash changer error don't have the second device error screen during startup or inside trx. 
	//display mode directly on first system message screen
	if ( co.IsDegradedModeOn() 
		&& ( IsCashDeviceError (dm.m_nStartDeviceErrorDeviceClass ) 
		|| IsCardDeviceError(dm.m_nStartDeviceErrorDeviceClass)	|| m_bCashChangerError ) //tar418068
		&& ( !(csMessage.Find(_T("Signature Capture")) != -1 && deviceClass == DMCLASS_SIGCAP) ) ) //TAR410082
	{
		//do not show degraded mode option button on TakeYourReturnedCash screen.
		if ( csMessage.Find(ps.GetPSText(MSG_DONOTINSERTCASHCOIN) ) == -1 ) 
		{
			csCurContext = _T("SystemMessageDegradedMode");	
		}

	}//SR742-

    ps.SetCMFrame(csCurContext);
    ps.ShowAmountDueAmountPaid(lBalanceDue,lTotalPaid);
  }
  else
  {
    if(m_csMovie!=_T(""))
    {
      csCurContext = _T("SystemMessageWithAVI"); // Tar 238987
      v = m_csMovie;
      m_pAppPSX->SetConfigProperty(_T("DeviceErrorVideo"), csCurContext, UI::PROPERTYVIDEO, v);
      ps.SetCMFrame(csCurContext);
    }

    if(m_bUseBitmap)
    {
      csCurContext = _T("SystemMessageWithBitmap"); // Tar 238987
        // If this is a SafePay recycler and fixing the error requires 
        // the removal of the note cover.
        if(dm.m_csCashRecyclerModel == _CASHDISPENSER_SAFEPAY)
        {
            switch(m_SafePayLastErrorCode)
            {
            case SFPAY_ERROR_NOTE_DEPOSIT_JAM:
            case SFPAY_ERROR_NOTE_VALIDATOR_IO_ERROR:
                csCurContext = _T("SystemMessageSafePayNoteJam");
                flashButton1 = false;
                break;
            default:
                break;
            }
        }

	//SR742+ if this condition is true, then were entering degraded modes(system message with bitmap)
	if (  co.IsDegradedModeOn() && 
		( IsCashDeviceError (dm.m_nStartDeviceErrorDeviceClass ) 
		|| IsCardDeviceError(dm.m_nStartDeviceErrorDeviceClass ) ) 
		&& dm.GetDegradedModeType() == DEGRADEDMODE_OFF 
		&& ( !(csMessage.Find(_T("Signature Capture")) != -1 && deviceClass == DMCLASS_SIGCAP) ) ) //TAR410082
	{
		//do not show degraded mode option button on TakeYourReturnCash screen.
		if ( csMessage.Find(ps.GetPSText(MSG_DONOTINSERTCASHCOIN) ) == -1 ) 
		{
			csCurContext = _T("SystemMessageDegradedModeWithBitmap");
		}
		
	}//SR742-

      CString csImagePath;
      GET_PARTITION_PATH(SCOTIMAGE, csImagePath.GetBuffer(_MAX_PATH));
      TCHAR szWork[_MAX_PATH] = _T("");
      _tmakepath(szWork,NULL,csImagePath,ps.GetBmpName(bitmap),NULL);
      csImagePath.ReleaseBuffer();
      v = szWork;
      m_pAppPSX->SetConfigProperty(_T("DeviceErrorBitmap"), csCurContext, UI::PROPERTYPICTURE, v);
      ps.SetCMFrame(csCurContext);
    }
  }

  if(!m_csTitle1.IsEmpty())    
  {
    ps.SetCMLeadthruText(m_csTitle1); 
  }
  else
  {
    ps.SetCMLeadthruText(title);
  }

  csCurContext = EMPTY_STRING;    // Tar 238987
  if(!m_csTitle2.IsEmpty())
  {
    v = ps.ConvertToEscapeSequence(m_csTitle2, _T("\\n"), _T("\n"));
    m_pAppPSX->SetConfigProperty(_T("Title2Area"), csCurContext,UI::PROPERTYTEXTFORMAT, v);
  }
  else
  {
    v= _T("");
    m_pAppPSX->SetConfigProperty(_T("Title2Area"), csCurContext,UI::PROPERTYTEXTFORMAT, v);
  }

  if (!showInfo)
  {
    ps.Button(_T("CMButton1Med"), PS_NOTEXT, false);
  }
  else
  {
    csCurContext = ps.GetCurrentContext();
    COleVariant v;
    v = VARIANT_TRUE;

    if (ps.GetPSText( MSG_POS_TB_OUTOFSYNC_NEEDASSISTMODE ) == csMessage)
      ps.SetButtonText(_T("CMButton1Med"), BTT_ASSISTMODE);

    if( co.fLocaleCashManagementScreen  && 
        (ps.GetPSText( MSG_CASHRECYCLER_FULL ) == csMessage  || 
         ps.GetPSText( MSG_CASHRECYCLER_EMPTY ) == csMessage ||     // Cash Recycler
         ps.GetPSText( MSG_CASHRECYCLER_EMPTY_2 ) == csMessage ||
         (deviceClass == DMCLASS_CASHCHANGER && m_bCashChangerFailToDispense) ||
         ps.GetPSText( LTT_BILLACCEPTORFULL ) == csMessage || 
         ps.GetPSText( MSG_COINACCEPTOR_STATUS_FULL ) == csMessage ||
         m_bShowMediaStatusButton                                   // SafePay
        )
      )
		ps.SetButtonText(_T("CMButton1Med"), TTL_MEDIASTATUS);
    else if(okButton)
      ps.SetButtonText(_T("CMButton1Med"), BTT_OK);
    else if(continueButton)
	{
		if (ps.GetPSText( MSG_SS_COMM_FAILED ) == csMessage) //Tar 415350
			ps.SetButtonText(_T("CMButton1Med"), BTT_CONTINUE);
		else
			ps.SetButtonText(_T("CMButton1Med"), TXT_PAID);  //Tar 402484: use msg id 33 instead of 81
	}
    else  //Disable the button
      v = VARIANT_FALSE;

	//SR742+ Start up error don't have the second device error not fixed screen.
	//Display directly degraded mode option at system message.
	CString csMessageDegradedMode;
	if ( csCurContext.Find(_T("SystemMessageDegradedMode")) != -1 || 
	     csCurContext.Find(_T("SystemMessageDegradedModeWithBitmap")) != -1)
    {
		if ( ( dm.GetDegradedModeType() == DEGRADEDMODE_CASH_ONLY ) && 
			( IsCashDeviceError( dm.m_nStartDeviceErrorDeviceClass ) || 
			  IsCashDeviceError( deviceClass )) )
		{
			ps.Button(_T("CMButton2Med"),LTT_CARDONLYMODE, false);
		}
		else if ( ( dm.GetDegradedModeType() == DEGRADEDMODE_CARD_ONLY ) && 
			( IsCardDeviceError(dm.m_nStartDeviceErrorDeviceClass) || IsCardDeviceError(deviceClass)) )
		{
		    ps.Button(_T("CMButton2Med"),LTT_CASHONLYMODE, false);
		}
		else if ( dm.GetDegradedModeType() == DEGRADEDMODE_OFF )
		{
			bool bCardDeviceError = false, bCashDeviceError = false;
			for (dm.m_lDeviceClassThatWasInErrorIterator = dm.m_lDeviceClassThatWasInError.begin(); 
				 dm.m_lDeviceClassThatWasInErrorIterator != dm.m_lDeviceClassThatWasInError.end(); 
				 dm.m_lDeviceClassThatWasInErrorIterator++)
			{
				if ( ! bCardDeviceError )
				{
					bCardDeviceError = IsCardDeviceError( *(dm.m_lDeviceClassThatWasInError.find(*(dm.m_lDeviceClassThatWasInErrorIterator))) );
				}

				if ( ! bCashDeviceError )
				{
					bCashDeviceError = IsCashDeviceError( *(dm.m_lDeviceClassThatWasInError.find(*(dm.m_lDeviceClassThatWasInErrorIterator))) );
				}
			}

			//if both cash and card devices in error at start-up, then disable degraded mode option.
			if ( bCardDeviceError && bCashDeviceError )
			{
				ps.Button(_T("CMButton2Med"),LTT_CARDONLYMODE, false);
			}
			else if ( IsCashDeviceError(deviceClass) && !(deviceClass==DMCLASS_CASHCHANGER) )
			{
				ps.SetButtonText(_T("CMButton2Med"), LTT_CARDONLYMODE);
				csMessageDegradedMode = ps.GetPSText(TXT_RESTRICT_CARDS_ONLY, SCOT_LANGUAGE_PRIMARY);
			}
			else if ( deviceClass == DMCLASS_CASHCHANGER  )
			{
				if ( co.fLocaleCashManagementScreen  )
				{
					if ( ( csMessage.Find(ps.GetPSText(LTT_CARDONLYMODE)) == -1 ) 
						&&  !IsCashDeviceError (dm.m_nStartDeviceErrorDeviceClass ) )	//if startup error, then avoid displaying message id 1805
					{
					     csMessage = csMessage + ps.GetPSText(MSG_GIVE_CHANGE_MANUAL,SCOT_LANGUAGE_PRIMARY);
					}
				}

				 ps.SetButtonText(_T("CMButton2Med"), LTT_CARDONLYMODE); 
				 csMessageDegradedMode = ps.GetPSText(TXT_RESTRICT_CARDS_ONLY, SCOT_LANGUAGE_PRIMARY);
			}
			else if ( IsCardDeviceError(deviceClass) || IsCardDeviceError(dm.m_nStartDeviceErrorDeviceClass))
			{
				ps.SetButtonText(_T("CMButton2Med"), LTT_CASHONLYMODE); 
				csMessageDegradedMode = ps.GetPSText(TXT_RESTRICT_CASH_ONLY, SCOT_LANGUAGE_PRIMARY);
			}
		}

		//if found "I corrected the problem" text then append "Or restrict to XXXX"
		if ( csMessage.Find(ps.GetPSText(TXT_PAID)) != -1 )  //Tar 402484
		{
			if ( ( csMessage.Find(ps.GetPSText(TXT_RESTRICT_CARDS_ONLY)) == -1 ) || ( csMessage.Find(ps.GetPSText(TXT_RESTRICT_CARDS_ONLY)) == -1 ) )
			{
				csMessage = csMessage + csMessageDegradedMode;
			}
		}
    }//SR742-

    if(csCurContext.Find(_T("SystemMessageSafePayNoteJam")) != -1)
    {
        // ps.SetButtonText() above re-enables the button.
        ps.ButtonEnable(_T("CMButton1Med"), false);
		ps.CMButtonFlash(_T("CMButton2Med"),true);
    }

	if (csCurContext.Find(_T("HopperFailure")) != -1)
	{
		if (bChuteJam)
			ps.SetButtonText(_T("CMButton1Med"), BUTTON_CLEARED_JAM);
		else if (co.fLocaleCashManagementScreen)
			ps.SetButtonText(_T("CMButton1Med"), TTL_MEDIASTATUS);
		else
			ps.SetButtonText(_T("CMButton1Med"), BUTTON_CONDITITON_CORRECTED);
		
		ps.SetButtonText(_T("CMButton2Med"), BTT_CLOSELANE);
		m_pAppPSX->SetConfigProperty(_T("CMButton2Med"), csCurContext, UI::PROPERTYVISIBLE, v);
	}
	if (csCurContext.Find(_T("HopperSubstitution")) != -1)
	{
		if (co.fLocaleCashManagementScreen)
			ps.SetButtonText(_T("CMButton1Med"), TTL_MEDIASTATUS);
		else
			ps.SetButtonText(_T("CMButton1Med"), BUTTON_CONDITITON_CORRECTED);
		ps.SetButtonText(_T("CMButton2Med"), BUTTON_FIX_LATER);
		m_pAppPSX->SetConfigProperty(_T("CMButton2Med"), csCurContext, UI::PROPERTYVISIBLE, v);
	}
    m_pAppPSX->SetConfigProperty(_T("CMButton1Med"), csCurContext, UI::PROPERTYVISIBLE, v);
  }

  ps.SetCMGobackButtonVisible(true);    //TAR121479
  ps.Button(_T("ButtonGoBack"), ((cancelButton && showInfo) ? BTT_CANCEL : PS_NOTEXT), true);   //TAR121479

  if (flashButton1 && showInfo && (okButton ||continueButton))
    ps.CMButtonFlash(_T("CMButton1Med"),true);
  // End NewUI

  ps.ShowAmountDueAmountPaid(lBalanceDue,lTotalPaid);
  ps.ShowCMTBText(csTBMessage2Scot);  //thp

  if (showInfo)
  {
    trace(L4,_T("SMSystemMessageBase::ShowScreen Prev Context=%s, Current Context=%s"), csPrevContext, ps.GetCurrentContext());

    if (psMessage != PS_NOTEXT)
      ps.Message12(psMessage, true);
    else if (csMessage != _T(""))
    {
      LPCTSTR tempstr = _T("Sensormatic");
      int i = csMessage.Find(tempstr, 10);
      if (i >= 1)
      {
        int istrPos = csMessage.ReverseFind(_T('\\'));
        if (istrPos) 
          csMessage.Insert(istrPos, _T(" "));
      }
      ps.Message12(csMessage, true);
    }
    else
      ps.Message12(title, true);
  }
  ps.CMButton(_T("ButtonHelp"),BTT_HELP,false);
  ps.ShowCMFrame();
}

/////////////////////////////////////////
// PSButton 3 - Cancel
/////////////////////////////////////////
SMStateBase  *SMSystemMessageBase::PSButton3(void)
{
	TBRefreshState();					// to allow TB to clear error, if any
	
	if (cancelButton)

	{
		//+Tar229575
		if (ps.RemoteMode())
		{
			ra.OnNoRAPDataNeeded();
		}
		//-Tar229575
		return STATE_RETURN;
	}
	else
		return STATE_NULL;
	
}

///////////////////////////////////////
// PSCancelKey
///////////////////////////////////////
SMStateBase * SMSystemMessageBase::PSCancelKey()
{
	TBRefreshState();					// to allow TB to clear error, if any
	if (cancelButton)
	{
		DMSayPhrase(KEYPADVALID);
		return PSButton3();
	}
	else
	{
		DMSayPhrase(KEYPADINVALID);
		return STATE_NULL;
	}
}

/////////////////////////////////////////
// PSButton 1 - OK or Continue
/////////////////////////////////////////
SMStateBase  *SMSystemMessageBase::PSButton1(void)
{ 
  trace(L4,_T("+SMSystemMessageBase::PSButton1"));
  TBRefreshState();         // to allow TB to clear error, if any

   // +SSCOB-1440
  // Move this code to the (okButton) 
  /*
  if(m_bDeviceErrorNotFixed)   // Device Error not fixed, still show error screen.
  {
    trace(L4,_T("DeviceErrorNotFixed"));

    m_bDeviceErrorNotFixed = false;
    CString csWork;
    //It is possible the old device error is fixed and a new one created, it is better to get extended result code again.
    if(deviceClass == DMCLASS_CASHCHANGER)  //Tar 229266 //not call this for all devices, some devices might not have extended result code.
                                            //CashChanger is the class which use extended result code most.  Tar 229266
    {
      csWork = GetDeviceErrorMnemonic(deviceClass, dm.GetDeviceName(deviceClass,0), EVENTID_ANY, dm.GetResultCodeExtended(deviceClass, 0), nDeviceErrorContext );
      if(csWork.Find(_T("DEVICEERRORUNKNOWN")) == -1)
      {
        csMessage = csWork;     
      }
    }

    showScreen(true);
    trace(L4,_T("-SMSystemMessageBase::PSButton1 (%s)"), "STATE_NULL");
    return STATE_NULL;
  }
   */
   // -SSCOB-1440
  //+dp185016 tar 286970
  if (ps.GetPSText( MSG_DONOTSCAN ) == csMessage)
  {
    bIgnoreScannedData = false;
    trace(L6,_T("bIgnoreScannedData : %d"), bIgnoreScannedData );
  }
  //-dp185016

  //+dp185016 
  if (ps.GetPSText( MSG_POS_TB_OUTOFSYNC_NEEDASSISTMODE ) == csMessage)
  {
    trace(L4,_T("-SMSystemMessageBase::PSButton1 (%s)"), "SmAssistMode");
    RETURNSTATE(SmAssistMode);
  }
  //-dp185016

  /* Tar 396076 - no systemmessage at startup for biometric errors
  	if (co.m_bOperationsUseFingerPrintDevice && ( ps.GetPSText(MSG_FINGERPRINT_DEVICE_ERROR) == csMessage || ps.GetPSText(MSG_FINGERPRINT_SERVER_ERROR) == csMessage))
	{
		g_bBiometricOpened = false;
		BOOL bFTClose = FT_Close();   //exit the fp device since it it's been open
		if (bFTClose == FALSE)
			to.Trace(L6, _T("Failed to close fingerprint device"));
		else
			to.Trace(L6, _T("Sucessfully closed fingerprint device"));
		
		trace(L6, _T("ra.OnNoRAPDataNeeded()"));
        ra.OnNoRAPDataNeeded(); 

		 bInSystemMessage = false;
		 if (dm.fStartUpDevFactoryLoading) 
		{
          gpSCOTAuxDisp = NULL;
          tb.Uninitialize();
		}
		//386142-
        trace(L4,_T("-SMSystemMessageBase::PSButton1 (%s)"), "STATE_RETURN");
		return STATE_RETURN;

	}
	//-SR93 Biometrics support
	*/


  //  Check if the button text is "cash/paper status"
  COleVariant cOleV;
  m_pAppPSX->GetConfigProperty( _T("CMButton1Med"), csCurContext, UI::PROPERTYTEXTFORMAT, cOleV );
  CString sButtonLabel(cOleV.bstrVal);
  trace( L6, _T("SystemMessage Buttontext : %s"), sButtonLabel);

  if( ps.GetPSText( TTL_MEDIASTATUS ) == sButtonLabel )
  {
    trace(L4,_T("-SMSystemMessageBase::PSButton1 (%s)"), "SmMediaStatus");
    RETURNSTATE(SmMediaStatus);
  }

  if (okButton)
  {
       // +SSCOB-1440
      if(m_bDeviceErrorNotFixed)   // Device Error not fixed, still show error screen.
      {
          trace(L4,_T("DeviceErrorNotFixed"));
          
          m_bDeviceErrorNotFixed = false;
          CString csWork;
          //It is possible the old device error is fixed and a new one created, it is better to get extended result code again.
          if(deviceClass == DMCLASS_CASHCHANGER)  //Tar 229266 //not call this for all devices, some devices might not have extended result code.
              //CashChanger is the class which use extended result code most.  Tar 229266
          {
              csWork = GetDeviceErrorMnemonic(deviceClass, dm.GetDeviceName(deviceClass,0), EVENTID_ANY, dm.GetResultCodeExtended(deviceClass, 0), nDeviceErrorContext );
              if(csWork.Find(_T("DEVICEERRORUNKNOWN")) == -1)
              {
                  csMessage = csWork;     
              }
          }
          
          showScreen(true);
          trace(L4,_T("-SMSystemMessageBase::PSButton1 (%s)"), "STATE_NULL");
          return STATE_NULL;
      }
	  //-SSCOB-1440
    //tar 261784
    bInSystemMessage = false;
    SMStateBase *sReturnState = CkStateStackAndReturn();
    if (sReturnState != STATE_NULL)
    {
      trace(L4,_T("-SMSystemMessageBase::PSButton1 (%s)"), sReturnState->getSCOTStateName());
      return sReturnState;
    }
    else
    {
      trace(L4,_T("-SMSystemMessageBase::PSButton1 (%s)"), "STATE_RETURN");
      return STATE_RETURN;
    }
  }
  else if (continueButton)
  {
    // +TAR 298987
		if (dm.fStateTakeawayBelt  
			&& m_bSavedSafetyCoverClosed == false)	 //TAR 298987-II
    {
      // if the safety cover was closed while on this screen    LPM040502
      if (g_bSafetyCoverClosed)
      {
        CKeyValueParmList parmList;
        BSTR bstrResult = NULL;
        CKeyValue<const _TCHAR*>::Put(parmList, KEY_SC_OPERATION, KEY_SC_OPERATION_FLUSH_ITEM);
        _bstr_t bstrParmList((const _TCHAR *)parmList);
        bstrResult = NULL;
        SecMgr.SecurityControl(lSecMgrCookie, bstrParmList, &bstrResult);

        fTABSafetyCoverOpenApprovalPending = false; // TAR's 201268, 202442, & 201239
        // Clear RAP and reset lane light as well as flush belt when needed LPM082202 205237.
        SAClearSecurityCondition();
        //218558 set scanner flag to re-enabled only in state that isn't handling EAS automatically
        trace(L2, _T("bEASReEnableScanner is set to true."));
        bEASReEnableScanner = true;
        //+ TAR 323659 Commented out these lines because m_View is already restored by earlier call to ra.OnNoRAPDataNeeded
        //Restoring again will cause data in m_View to be lost..

        // Restore the previous view
        //m_View = m_PrevView;
        //m_PrevView = DATANEEDED_NOVIEW; //tar 252987

        //-TAR 323659
        //tar 261784
        bInSystemMessage = false;
        SMStateBase *sReturnState = CkStateStackAndReturn();
        if (sReturnState != STATE_NULL)
        {
          trace(L4,_T("-SMSystemMessageBase::PSButton1 (%s)"), sReturnState->getSCOTStateName());
          return sReturnState;
        }
        else
        {
          trace(L4,_T("-SMSystemMessageBase::PSButton1 (%s)"), "STATE_RETURN");
          return STATE_RETURN;
        }
      }
      else
        //return STATE_NULL;
        return ShowDeviceErrorNotFixedScreen();
    } 
    // -TAR 298987
    // if the device is Bag Scale or WLDB
    if ((deviceClass >= PIDCLASS_START) && (deviceClass < PIDCLASS_MAX_CLASS))
    {
      //BSTR bstrDeviceName;
      //BSTR bstrCheckHealthText;
      //long lStatus;

      switch (deviceClass)
      {
      case PIDCLASS_BAGSCALE :
        {
          CKeyValueParmList parmList;
          CKeyValue<const _TCHAR*>::Put(parmList, KEY_SC_OPERATION, KEY_SC_OPERATION_QUERY_DEVICE_STATUS);
          CKeyValue<const _TCHAR*>::Put(parmList, KEY_SC_DEVICE_NAME, VALUE_DEVICE_SS);
          _bstr_t bstrParmList((const _TCHAR *)parmList);
          BSTR bstrResult;
          bstrResult = NULL;
          SecMgr.SecurityControl(lSecMgrCookie, bstrParmList, &bstrResult);
          SecurityControlParms secControlQueryDeviceStatus;
          CString csResult(bstrResult);
          secControlQueryDeviceStatus.ParseKeys(csResult);
          SysFreeString(bstrResult);
          if ( secControlQueryDeviceStatus.m_csDeviceStatus == KEY_SC_DEVICE_STATUS_WORKING )
          {   
            ra.OnNoRAPDataNeeded();
            if (dm.getTriColorLightColor() == DM_TRICOLORLIGHT_RED)
            {
              // tar 211746 don't turn off red if there are other red interventions waiting
              // because turning off red can let any pending virtual yellow be turned on which
              // means both red and yellow will be on if we immediately turned red back on
              // also will help prevent extra pages that can occur when turning it off and then on
              if(!AreAnyRedApprovalsPending())
              {
                dm.setTriColorLight(DM_TRICOLORLIGHT_RED,
                DM_TRICOLORLIGHT_OFF,
                DM_TRICOLORLIGHT_NORMALREQUEST);
                dm.turnOffTriColorLight();

                if (isAnyApprovalRequired())
                {
                  dm.setTriColorLight(DM_TRICOLORLIGHT_YELLOW,
                  DM_TRICOLORLIGHT_ON,
                  DM_TRICOLORLIGHT_NORMALREQUEST);              
                }
                else if (dm.GetCoinsOrBillsVeryLow() || dm.GetPrinterPaperLow())
                {
                  dm.setTriColorLight(DM_TRICOLORLIGHT_GREEN,
                  DM_TRICOLORLIGHT_BLINK_1HZ,
                  DM_TRICOLORLIGHT_NORMALREQUEST);
                }
                else if(fInSignedOn || fInSignedOff || fStateAssist || fSAInTransaction)
                {
                  // If inside the transaction, turn on the green light
                  //  if(fInSignedOn || fInSignedOff || fStateAssist || fSAInTransaction)
                  dm.setTriColorLight(DM_TRICOLORLIGHT_GREEN,
                  DM_TRICOLORLIGHT_ON,
                  DM_TRICOLORLIGHT_NORMALREQUEST);
                }
              }
            }
            //+ TAR 323659 Commented out these lines because m_View is already restored by earlier call to ra.OnNoRAPDataNeeded
            //Restoring again will cause data in m_View to be lost..

            // Restore the previous view
            //m_View = m_PrevView;
            //m_PrevView = DATANEEDED_NOVIEW; //tar 252987

            //-TAR 323659

            if(g_bTBNeedMoreData == true && !m_sButton.IsEmpty())  // TAR 238061 
            {
			  //USSF START
			  USSFHOOK(_T("HandleDataNeeded"), HandleDataNeeded(), ;);
			  //HandleDataNeeded();
			  //USSF END
              CREATE_AND_DISPENSE(InProgress)(storeMode(), helpMode(),
              co.getTimeOutItemTransactionResult());
            }
            else
            {  //tar 261784
              bInSystemMessage = false;
              SMStateBase *sReturnState = CkStateStackAndReturn();
              if (sReturnState != STATE_NULL)
              {
                trace(L4,_T("-SMSystemMessageBase::PSButton1 (%s)"), sReturnState->getSCOTStateName());
                return sReturnState;
              }
              else
              {
                trace(L4,_T("-SMSystemMessageBase::PSButton1 (%s)"), "STATE_RETURN");
                return STATE_RETURN;
              }
            }
            //break;
          }
          trace(L0,_T("Bag Scale Status: FAILED !!!"));
          //return STATE_NULL;
          return ShowDeviceErrorNotFixedScreen();
          //break;
        }

      case  PIDCLASS_WLDBSACONFIG :
        {
          CKeyValueParmList parmList;
          CKeyValue<const _TCHAR*>::Put(parmList, KEY_SC_OPERATION, KEY_SC_OPERATION_QUERY_DEVICE_STATUS);
          _bstr_t bstrParmList((const _TCHAR *)parmList);
          BSTR bstrResult;
          bstrResult = NULL;
          SecMgr.SecurityControl(lSecMgrCookie, bstrParmList, &bstrResult);
          SecurityControlParms secControlQueryDeviceStatus;
          CString csResult(bstrResult);
          secControlQueryDeviceStatus.ParseKeys(csResult);
          SysFreeString(bstrResult);
          if ( secControlQueryDeviceStatus.m_csDeviceStatus == KEY_SC_DEVICE_STATUS_WORKING )
          {   
            ra.OnNoRAPDataNeeded();
            if (dm.getTriColorLightColor() == DM_TRICOLORLIGHT_RED)
            {
              // tar 211746 don't turn off red if there are other red interventions waiting
              // because turning off red can let any pending virtual yellow be turned on which
              // means both red and yellow will be on if we immediately turned red back on
              // also will help prevent extra pages that can occur when turning it off and then on
              if(!AreAnyRedApprovalsPending())
              {
                dm.setTriColorLight(DM_TRICOLORLIGHT_RED,
                DM_TRICOLORLIGHT_OFF,
                DM_TRICOLORLIGHT_NORMALREQUEST);
                dm.turnOffTriColorLight();

                if (isAnyApprovalRequired())
                {
                  dm.setTriColorLight(DM_TRICOLORLIGHT_YELLOW,
                  DM_TRICOLORLIGHT_ON,
                  DM_TRICOLORLIGHT_NORMALREQUEST);              
                }
                else if (dm.GetCoinsOrBillsVeryLow() || dm.GetPrinterPaperLow())
                {
                  dm.setTriColorLight(DM_TRICOLORLIGHT_GREEN,
                  DM_TRICOLORLIGHT_BLINK_1HZ,
                  DM_TRICOLORLIGHT_NORMALREQUEST);
                }
                else if(fInSignedOn || fInSignedOff || fStateAssist || fSAInTransaction)
                {
                  // If inside the transaction, turn on the green light
                  //  if(fInSignedOn || fInSignedOff || fStateAssist || fSAInTransaction)
                  dm.setTriColorLight(DM_TRICOLORLIGHT_GREEN,
                  DM_TRICOLORLIGHT_ON,
                  DM_TRICOLORLIGHT_NORMALREQUEST);
                }
              } 
            }
            //+ TAR 323659 Commented out these lines because m_View is already restored by earlier call to ra.OnNoRAPDataNeeded
            //Restoring again will cause data in m_View to be lost..

            // Restore the previous view
            //m_View = m_PrevView;
            //m_PrevView = DATANEEDED_NOVIEW; //tar 252987

            //-TAR 323659
            //tar 261784
            bInSystemMessage = false;
            SMStateBase *sReturnState = CkStateStackAndReturn();
            if (sReturnState != STATE_NULL)
            {
              trace(L4,_T("-SMSystemMessageBase::PSButton1 (%s)"), sReturnState->getSCOTStateName());
              return sReturnState;
            }
            else
            {
              trace(L4,_T("-SMSystemMessageBase::PSButton1 (%s)"), "STATE_RETURN");
              return STATE_RETURN;
            }
            break;
          }
          trace(L0,_T("DB Manager Client Status: FAILED !!!"));
          //return STATE_NULL;
          return ShowDeviceErrorNotFixedScreen();
          break;
        }

      //Fiscal Printer start
      case PIDCLASS_FISCALPRTR :
        {
          ra.OnNoRAPDataNeeded();
          if (dm.getTriColorLightColor() == DM_TRICOLORLIGHT_RED)
          {
            // tar 211746 don't turn off red if there are other red interventions waiting
            // because turning off red can let any pending virtual yellow be turned on which
            // means both red and yellow will be on if we immediately turned red back on
            // also will help prevent extra pages that can occur when turning it off and then on
            if(!AreAnyRedApprovalsPending())
            {
              dm.setTriColorLight(DM_TRICOLORLIGHT_RED,
              DM_TRICOLORLIGHT_OFF,
              DM_TRICOLORLIGHT_NORMALREQUEST);
              dm.turnOffTriColorLight();

              if (isAnyApprovalRequired())
              {
                dm.setTriColorLight(DM_TRICOLORLIGHT_YELLOW,
                DM_TRICOLORLIGHT_ON,
                DM_TRICOLORLIGHT_NORMALREQUEST);              
              }
              else if (dm.GetCoinsOrBillsVeryLow() || dm.GetPrinterPaperLow())
              {
                dm.setTriColorLight(DM_TRICOLORLIGHT_GREEN,
                DM_TRICOLORLIGHT_BLINK_1HZ,
                DM_TRICOLORLIGHT_NORMALREQUEST);
              }
              else if(fInSignedOn || fInSignedOff || fStateAssist || fSAInTransaction)
              {
                // If inside the transaction, turn on the green light
                //  if(fInSignedOn || fInSignedOff || fStateAssist || fSAInTransaction)
                dm.setTriColorLight(DM_TRICOLORLIGHT_GREEN,
                DM_TRICOLORLIGHT_ON,
                DM_TRICOLORLIGHT_NORMALREQUEST);
              }
            } 
          }
          //+ TAR 323659 Commented out these lines because m_View is already restored by earlier call to ra.OnNoRAPDataNeeded
          //Restoring again will cause data in m_View to be lost..

          // Restore the previous view
          //m_View = m_PrevView;
          //m_PrevView = DATANEEDED_NOVIEW; //tar 252987

          //-TAR 323659
          tb.Print(NULL);
          //tar 261784
          bInSystemMessage = false;
          SMStateBase *sReturnState = CkStateStackAndReturn();
          if (sReturnState != STATE_NULL)
          {
            trace(L4,_T("-SMSystemMessageBase::PSButton1 (%s)"), sReturnState->getSCOTStateName());
            return sReturnState;
          }
          else
          {
            trace(L4,_T("-SMSystemMessageBase::PSButton1 (%s)"), "STATE_RETURN");
            return STATE_RETURN;
          }
          break;
        }
        //Fiscal Printer end
      }
    }
    // if the device is controlled by the Device Manager
    if (((deviceClass >= 0) && (deviceClass < DMCLASS_MAX_CLASSES)) || deviceClass == DMCLASS_CASHRECYCLER)
    {
      if (checkHealth)
      {
        long rc = DMCheckHealth(deviceClass); // issue check health
        // rc == 0 is success // TAR: 159950

        if(!rc && deviceClass == DMCLASS_CASHRECYCLER)  //cash recycler, need get checkhealthtext
        {
          CString csCheckHealthText = dm.CashRecyclerGetCheckHealthText();
          if( (csCheckHealthText.Find(_T(":Full")) != -1 ) || (csCheckHealthText.Find(_T(":Jam")) != -1 ))
            rc = -1;
        }

		//SR742+
		if ( co.IsDegradedModeOn() )
		{
			if ( rc )
			{
				// Force to fix device error and disable degraded mode option if we are in cash only mode and cash devices in error.
				// Or if we are in card only mode and card devices in error. Or both card devices and cash devices in error.
				if  ( ( ( dm.GetDegradedModeType() == DEGRADEDMODE_CASH_ONLY ) && IsCashDeviceError(deviceClass ) ) || 
					  ( ( dm.GetDegradedModeType() == DEGRADEDMODE_CARD_ONLY ) && IsCardDeviceError(deviceClass ) ) ||
					  ( ( IsCashDeviceError(deviceClass) ) && ( IsCardDeviceError(deviceClass) ) ) )
				{
						m_bForceFixDeviceError = true;
				}
			}
		}
		//SR742-

		// +TAR 354761
		if( deviceClass == DMCLASS_CASHRECYCLER && 
			dm.m_csCashRecyclerModel == _CASHDISPENSER_SAFEPAY )
		{
			// +TAR 356035
			if(rc == DM_E_DEVICENOTAVAILABLE || 
				m_SafePayLastErrorCode == OPOS_E_DISABLED)
			{
				// Try to enable the device again.
				if(dm.SetDeviceEnabledRaw(TRUE, DMCLASS_CASHRECYCLER, 0))
				{
					rc = OPOS_SUCCESS;		
				}
			}
			// -TAR 356035
			else if(rc != OPOS_SUCCESS)
			{
				rc = dm.GetResultCodeExtended(deviceClass, 0);
				
				// If CheckHealth failed and the new extended result code is 
				// different from the one we're handling now,
				// then we will get a new event in DMParse().
				if(m_SafePayLastErrorCode != rc)
				{
					rc = OPOS_SUCCESS;
				}
			}
		} 
		// -TAR 354761

        if (rc) // some exception was thrown by DM during check health call
        {
          //TAR225069+ CHU/Dale 6/19/03
          //For DM_CC_STATUS_INOPERABLE only, we are leaving SystemMessage
          //because CheckHealth causes SO to fire another error event.
          if (deviceClass == DMCLASS_CASHCHANGER)
          {
            if ( m_lSavedCashChangerStatusCode == DM_CC_STATUS_INOPERABLE )
            {
              trace(L3, _T("CheckHealth on DMCLASS_CASHCHANGER didn't fix DM_CC_STATUS_INOPERABLE"));
              trace(L3, _T("Leaving SystemMessage because SO is going to fire another event about the same error"));
              m_lSavedCashChangerStatusCode = -999; 
			  return STATE_RETURN;		// TAR 357397
            }
          }
		//TAR225069-

		   //TAR390645+
		  //107=no hardware, printer on RAP is configured, but not connected
          if (deviceClass == DMCLASS_RECEIPT && dm.IsDeviceRemote(deviceClass , 0) && rc == 107 )
          {
			trace(L3, _T("CheckHealth on DMCLASS_RECEIPT on RAP didn't fix 0x%0x"), rc);
			trace(L3, _T("Leaving SystemMessage because SO is going to fire another event about the same error when printing fails again"));
			return STATE_RETURN;		
          }
          //TAR390645-
          trace(L3, _T("!!!!  CheckHealth(%d) revealed that the error:0x%0xd, still exists. Stay on the same screen"), deviceClass,rc);
          //return STATE_NULL;
          return ShowDeviceErrorNotFixedScreen();
        }

        if (deviceClass == DMCLASS_RECEIPT)
        {
          fDMReceiptError = false; // above call to DMCheckHealth takes care of printer error recovery
          //TAR387489 This call is already made in DMCheckHealth() ra.OnNoRAPDataNeeded();  //Tar229575
        }
        else if (deviceClass == DMCLASS_JOURNAL)
        {
          fDMJournalError = false; // above call to DMCheckHealth takes care of printer error recovery
          //TAR387489 This call is already made in DMCheckHealth() ra.OnNoRAPDataNeeded(); //Tar229575
        }
		//Begin RFC 356020: Support Check payment on lane using printer 7167
		else if (deviceClass == DMCLASS_SLIP)
        {
          //fDMReceiptError = false; // above call to DMCheckHealth takes care of printer error recovery
          ra.OnNoRAPDataNeeded();  //Tar229575
        }
		//End RFC 356020
        else if (deviceClass == DMCLASS_MISC)    // Tar 208394
        {
          dm.fPendingMiscIFError = false;
          //TAR387489 This call is already made in DMCheckHealth() ra.OnNoRAPDataNeeded(); //Tar229575
        }

        if (deviceClass == DMCLASS_CASHCHANGER)
        {
		  if (lUnapprovedHopperSubstitution > 0)
		  {
			ClearHopperSubstitution();
		  }
          m_lSavedCashChangerStatusCode = -999; //TAR225059
          if (lChangeDue)
          {
            // this means app failed during dispense
            // on this error screen, it is mentioned that store has to refill them 
            // if any bins or hoppers are low or empty. Assuming this action is taken, tell dm
            // inform dm/SO about coin replenishment

            trace(L4, _T("bgCoinDispenserIsEmpty value is %d"), bgCoinDispenserIsEmpty);
            if (bgCoinDispenserIsEmpty)
            {
              dm.CashChangerReplenishCoins(0, NULL);
              // Get current time
              COleDateTime dtNow;
              dtNow = COleDateTime::GetCurrentTime();
              csDateCoinDispenserRefilled = dtNow.Format( _T("%m/%d") );  
              csTimeCoinDispenserRefilled = dtNow.Format( _T("%H:%M") );  

              // Log to event log.-----------
              CString csWork;
              csWork.Format(ps.GetPSText(MSG_FILLCOINDISPENSER), csDateCoinDispenserRefilled, csTimeCoinDispenserRefilled);
              ScotError(INFO,SM_CAT_HARDWARE, SCOTAPP_DM_INFO, csWork); 
              // Saved data to registry for next time when SCOTAPP is restarted.
              HKEY  hKey;

              // If the entry does not exist, it will create one.
              if (RegCreateKeyEx(HKEY_LOCAL_MACHINE, _T("Software\\NCR\\SCOT\\CurrentVersion\\SCOTAPP"), 
                  0, NULL,REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,NULL,&hKey, NULL) == ERROR_SUCCESS)
              {
                // Write a string value to the registry.
                RegSetValue(hKey,
                TEXT("LastCoinRefilled"), 
                REG_SZ,
                csWork,
                csWork.GetLength() + 1);
              }
              RegCloseKey(hKey);

              // logged coin replenishment --------
            }
          }
          bgCoinDispenserIsEmpty = false;
          // Begin TAR 191990
          // clear the Intervention related to coin dispensing problem by informing RAP
          //trace(L6, _T("ra.OnNoRAPDataNeeded()"));
          //TAR387489 This call is already made in DMCheckHealth() ra.OnNoRAPDataNeeded(); 
          // End TAR 191990
        }
      }
      else
      {
        //TAR213352+ CHU 08/29/02 
        //For some device errors, it doesn't need to do checkhealth, but we need
        //to tell RAP to clear this error.
        trace(L6, _T("ra.OnNoRAPDataNeeded()"));
        ra.OnNoRAPDataNeeded(); 
        //TAR213352-
      }
      if(    NCR_CARD_JAM == lDMLastCode 
        &&  DMCLASS_MSR == deviceClass )
      {
        DMMSREject(); //tar 266004 -- Do eject here (gives user a chance to clear jam before pressing continue)
      }
      //+ TAR 323659 Commented out these lines because m_View is already restored by earlier call to ra.OnNoRAPDataNeeded
      //Restoring again will cause data in m_View to be lost..

      // Restore the previous view
      //m_View = m_PrevView;
      //m_PrevView = DATANEEDED_NOVIEW; //tar 252987

      //-TAR 323659
    }
    //else if the device is controlled by the Device Factory
    else if (deviceClass >= DMCLASS_MAX_CLASSES)
    {
      /*391878+
      if (dm.fStartUpDevFactoryLoading) 
      {
        gpSCOTAuxDisp = NULL;
        tb.Uninitialize();
      }
	  */

      //tar 261784
      bInSystemMessage = false;
      SMStateBase *sReturnState = CkStateStackAndReturn();
      if (sReturnState != STATE_NULL)
      {
        trace(L4,_T("-SMSystemMessageBase::PSButton1 (%s)"), sReturnState->getSCOTStateName());
        return sReturnState;
      }
      else
      {
        //TAR391878+
        if (dm.fStartUpDevFactoryLoading) 
        {
          gpSCOTAuxDisp = NULL;
          tb.Uninitialize(); //only do Uninitialize when it goes back to outofservices
        }
	    //TAR391878-

        trace(L4,_T("-SMSystemMessageBase::PSButton1 (%s)"), "STATE_RETURN");
        return STATE_RETURN;
      }
    }
    else
    {
      if( !co.fTenderCashAllowed && !co.fTenderCreditCashBack && 
          !co.fTenderDebitCashBack && !co.fTenderEBTCBCashBack && lChangeDue)
      {
        trace(L4,_T("-SMSystemMessageBase::PSButton1 (%s)"), "TakeReceipt");
        RETURNSTATE(TakeReceipt)
      }
    }
    //If EncryptorSetup Function fail, go back to Finish & Pay screen
    if(IsEncryptorSetupFail)
    {
      trace(L4,_T("-SMSystemMessageBase::PSButton1 (%s)"), "BES_FINISH");
      return setAndCreateAnchorState(BES_FINISH);
    }
    else
    {
	  /* 386142
      if (dm.fStartUpDevFactoryLoading) 
      {
        gpSCOTAuxDisp = NULL;
        tb.Uninitialize();
      }
	  */

      if (getAnchorState() == BES_SCANANDBAG)
      {
        // then set the re-enable scanner flag to true
        trace(L2, _T("::UnInitialize - bEASReEnableScanner is set to true."));
        bEASReEnableScanner = true;
      }

      //tar 261784
      bInSystemMessage = false;

	  //TAR409151+
	  if ( co.IsDegradedModeOn() )
	  {
		  if ( dm.GetDegradedModeType() == DEGRADEDMODE_CARD_ONLY && IsCashDeviceError(deviceClass) ||
			   dm.GetDegradedModeType() == DEGRADEDMODE_CASH_ONLY && IsCardDeviceError(deviceClass))
		  {
				return STATE_RETURN;			
		  }
	  }
	  //TAR409151-
	  
      SMStateBase *sReturnState = CkStateStackAndReturn();
      if (sReturnState != STATE_NULL)
      {
        trace(L4,_T("-SMSystemMessageBase::PSButton1 (%s)"), sReturnState->getSCOTStateName());
        return sReturnState;
      }
      else
      {
		 //386142+ do uninitialize() only if stack is empty. Otherwise, operator validation will be failed   
		if (dm.fStartUpDevFactoryLoading) 
		{
          gpSCOTAuxDisp = NULL;
          tb.Uninitialize();
		}
		//386142-
	
        	//TAR415626
		 if ((getAnchorState() == BES_SCANANDBAG) && co.fAutoRunOn && co.fAutoRunBypassBagging)
		 {
			 return setAndCreateAnchorState(BES_SCANANDBAG);
		 }
		 else
		trace(L4,_T("-SMSystemMessageBase::PSButton1 (%s)"), "STATE_RETURN");
        	return STATE_RETURN;
      }
    }
  }
  else
  {
    //return STATE_NULL;
    return ShowDeviceErrorNotFixedScreen();
  }
}

SMStateBase  *SMSystemMessageBase::PSButton2(void)
{ 

	CString csCurContext = ps.GetCurrentContext();
	if (csCurContext.Find(_T("HopperFailure")) !=-1 || 
		csCurContext.Find(_T("HopperCloseLane")) !=-1)
	{ 
		nHopperTrxCount = 0;
		fPutSCOTinLC = true;
		DMCheckHealth(DMCLASS_CASHCHANGER); // issue check health

		if (fCancelPayment || cDMLastTrack )
		{
			if ( isAnySoldVoidedItems() )
			{
				ClearStateStackEOT();	
				return TBCancelTransaction(true);       // wait for *VOID TRANSACTION*
			}	
			TellApplicationStateToSecurity(KEY_AC_SET_APP_STATE_END, _T("SmAuthorization") ); 
			return TBFinish();  
		}
		else
		{
		SAClearSecurityCondition();
		RETURNSTATE(TakeReceipt);
		}
	}
	else if (csCurContext.Find(_T("HopperSubstitution")) !=-1) //fix later button
	{
		ClearHopperSubstitution();
		RETURNSTATE(Finish);

	}
	else if(csCurContext.Find(_T("SystemMessageSafePayNoteJam")) != -1)
	{
		// If "Unlock Note Cover" button has been pressed.
		DMUnlockNoteCover();

		// Enable the "Continue" button.
		ps.ButtonEnable(_T("CMButton1Med"), true);
		ps.CMButtonFlash(_T("CMButton1Med"),true);
		ps.CMButtonFlash(_T("CMButton2Med"),false);

		return STATE_NULL;
	}
	//SR742+
	else if	(csCurContext.Find(_T("SystemMessageDegradedMode")) != -1 || 
		     csCurContext.Find(_T("SystemMessageDegradedModeWithBitmap")) != -1 ) 
	{ 
		COleVariant cOleV;
		m_pAppPSX->GetConfigProperty( _T("CMButton2Med"), csCurContext, UI::PROPERTYTEXTFORMAT, cOleV );
		CString sButtonLabel(cOleV.bstrVal);
		trace( L6, _T("SystemMessage Buttontext : %s"), sButtonLabel);

		if ( IsCashDeviceError (deviceClass ) || IsCardDeviceError (deviceClass )  )  //device error during trx
		{
			if ( ps.GetPSText(LTT_CARDONLYMODE) == sButtonLabel )
			{				
				EnterDegradedMode(DEGRADEDMODE_CARD_ONLY);
				co.fTenderCashAllowed = false;

				// if acceptor failure and have money already inserted, 
				// need to return the money.
				if(nDMCashInserted)	
				{
					//fCancelPayment = true;
					//lChangeDue = nDMCashInserted;
					//nDMCashInserted = 0;
					//CREATE_AND_DISPENSE(TakeChange)(false);
					RETURNSTATE(Finish)
				}

				//+ac185097
  				//When error is not corrected in media status, it will go back to SMAuthorization
   				if ( (CString(_T("SMSmMediaStatus")) == this->csLastNonHelpStateName) )
   				{
      				RETURNSTATE(SmAuthorization)
   				}
   				//-ac185097


				if ( m_bCashChangerError && ( this->csLastNonHelpStateName != CString( _T("SMOutOfService") ) ) )
				{
					co.fTenderCashAllowed = false;
					RETURNSTATE(TakeReceipt)	//in transaction
				}

				//When cash device error occur in SMCashPayment screen then enter degraded mode.
				//Screen will goes back to SMFinish instead of staying on cash payment screen. 
				if ( (CString(_T("SMCashPayment")) == this->csLastNonHelpStateName) )
   				{
      				RETURNSTATE(Finish)
   				} 

			}
			else if ( ps.GetPSText(LTT_CASHONLYMODE) == sButtonLabel )
			{
				EnterDegradedMode(DEGRADEDMODE_CASH_ONLY);
				co.fTenderCashAllowed = true;

				//When card device error occur in SMCashPayment screen then enter degraded mode.
				//Screen will goes back to SMFinish instead of staying on swipe card screen. 
				if ( (CString(_T("SMSwipeCard")) == this->csLastNonHelpStateName) )
   				{
      				RETURNSTATE(Finish)
   				} 
			}
		}
		return STATE_RESUME;
	}
	else //SR742-
	  return STATE_NULL;
}

///////////////////////////////////////////////////////////////////////////
SMStateBase *SMSystemMessageBase::OnBackToLGW(void)
{
	// TAB re-enable scanner and clear Wait For Approval State
	TABReEnableScannerAndClearWaitForApprovalState();
	return STATE_NULL;
}

///////////////////////////////////////////////////////////////////////////
void SMSystemMessageBase::UnInitialize(void)      // TAR203166
{
	
	

	// CAN enter Remote Assist Mode after leaving this state
	//ra.OnSetTransactionState(RA_STATE_ASSISTOK);
    ra.RequestEnableAssistMode(true);   //TAR213249
	m_nWave = PS_NOSOUND;
	m_csTitle2.Empty();
	m_csTitle1.Empty();
	m_bDeviceErrorLogged = false;
	m_nDMSavedDev = -1;   //277025

  //+dp185016 tar 286970
  if (ps.GetPSText( MSG_DONOTSCAN ) == csMessage)
  {
    bIgnoreScannedData = false;
		trace(L6,_T("bIgnoreScannedData : %d"), bIgnoreScannedData );
  }
  //-dp185016

  

	if (bIsInFinalization) //tar 223051
		g_bAllowRemove = true;
	TellApplicationStateToSecurity(KEY_AC_SET_APP_STATE_END, _T("SystemMessage") );
	// Rel 3.2 Requirement 4.5.1 - Single Mode RAP
	// Need to tell RAP we're exiting so remote AM can restore its size.
    ra.OnAddOtherEvent(_T("COMMAND=AssistModeSizeRestore;"));  
}

///////////////////////////////////////////////////////////////////////////
SMStateBase *SMSystemMessageBase::OnMatchedWt()
{
	
	//If there is WaitForApproval state waiting, clear it
	if (g_pDelay_WaitForApprovalStateChange != NULL)
	{
		CString csStateName = g_pDelay_WaitForApprovalStateChange->GetRuntimeClass()->m_lpszClassName;
		delete g_pDelay_WaitForApprovalStateChange;
		g_pDelay_WaitForApprovalStateChange = NULL;
		trace(L6,_T("Delete the state %s saved in g_pDelay_WaitForApprovalStateChange"),csStateName);
	}
	//Tar 415379
	if (g_pDelay_TBExpectedStateChange != NULL)
    {
     CString csStateName = g_pDelay_TBExpectedStateChange->GetRuntimeClass()->m_lpszClassName;
	 if (csStateName.Find(_T("SMBagAndEAS")) != -1)
	 {
		delete g_pDelay_TBExpectedStateChange;
		g_pDelay_TBExpectedStateChange = NULL;
		trace(L6,_T("Delete the state %s saved in g_pDelay_TBExpectedStateChange"),csStateName);
	 }
    }


	if(dm.fStateTakeawayBelt)	// is on a take away system, always re-enable the scanner
	{
		trace(L2, _T("bEASReEnableScanner is set to true."));
		bEASReEnableScanner = true;
		if (g_bTBReturnedITEMSOLDforSA)	// if the TB has returned ITEM_SOLD 
		{
			setAnchorState(BES_TRANSPORTITEM);
		}
	}
	else
		setAnchorState(BES_SCANANDBAG);
	
	return STATE_NULL;
}
// 207300 //HDMerge-062502 Starts here
bool SMSystemMessageBase::PSRemoteLegalForState()
{
    //return true; //TAR408719
    return IsRemoteErrorAllowed(deviceClass); 
}


void SMSystemMessageBase::showRemoteScreen(bool showInfo) // not to be called externally but overwritable
{
    // NewUI
	ps.SetFrame(_T("RemoteSystemMessage"));
	ps.SetTitle(ps.GetPSText(title), EMPTY_STRING);
	if (!showInfo)
	{
		ps.Button(_T("SMButton1"),PS_NOTEXT, false);
	}
	else
	{	
		if(okButton)
			ps.SetButtonText(_T("SMButton1"),BTT_OK);
		else if(continueButton)
			ps.SetButtonText(_T("SMButton1"),TXT_PAID);  //Tar 402484
	}
	ps.SetButtonText(_T("SMButton8"),((cancelButton && showInfo) ? BTT_CANCEL : PS_NOTEXT));

	// TAR 236945 - Needed for Remote, this api will check option whether to display or not.
    ps.Weight(lDMScaleWeight);

    // End NewUI
	ps.ShowSMTotal(true);
	if (showInfo)
	{
		if (psMessage != PS_NOTEXT)
			ps.SMInfo(ps.GetPSText(psMessage));
		else
			ps.SMInfo(csMessage);	  
    }
	// Rel 3.2 Requirement 4.5.1 - Single Mode RAP
    // Need to tell RAP to have full screen for remote device error.
    ra.OnAddOtherEvent(_T("COMMAND=AssistModeSizeToFullScreen;"));  
	ps.ShowFrame();
}

/////////////////////////////////////////
// PSButton 8 - Cancel in case of remote mode
/////////////////////////////////////////
SMStateBase  *SMSystemMessageBase::PSButton8(void)
{
    return PSCancelKey();
} //HDMerge-062502 ends here

///////////////////////////////////////////////////
//ShowDeviceErrorNotFixedScreen  Error Handling
//////////////////////////////////////////////////
SMStateBase *SMSystemMessageBase::ShowDeviceErrorNotFixedScreen()
{
	trace(L6, _T("+SMSystemMessageBase::ShowDeviceErrorNotFixedScreen"));

	m_bDeviceErrorNotFixed = true;
    // +SSCOB-1440
	/*
	if (co.IsInAssistMenus())	//TAR343237
	{
		trace(L6, _T("In ShowDeviceError and in assist mode"));
		bool showInfo = true;
		ps.SetFrame(_T("RemoteSystemMessage"));
		ps.SetButtonText(_T("SMButton1"),BTT_OK);
		CString csData = csMessage;
        // TAR 414306 - Show "corrective action" message without appending it to avoid clipped strings.
        csData = (ps.GetPSText(MSG_DEVICEERRORNOTFIXED));
		ps.SMInfo(csData);	
        		ps.ShowFrame();  
		trace(L6, _T("+SMSystemMessageBase::ShowDeviceErrorNotFixedScreen, ps.ShowFrame() passed"));
	}
	else */
	if (ps.RemoteMode() || co.IsInAssistMenus())  //+Tar228161
    {
        trace(L6, _T("In ShowDeviceError and in remote mode or in assisted menus"));
        ps.SetFrame(_T("RemoteSystemMessage"));

        ps.SetTitle(ps.GetPSText(title), EMPTY_STRING);

        if(okButton)
            ps.SetButtonText(_T("SMButton1"),BTT_OK);
        else if(continueButton)
            ps.SetButtonText(_T("SMButton1"),TXT_PAID); //Tar 402484

        ps.Button(_T("SMButton8"),BTT_CANCEL, true);    //Tar228577

        // TAR 236945 - Needed for Remote, this api will check option whether to display or not.
        ps.Weight(lDMScaleWeight);
        ps.ShowSMTotal(true);

        if (psMessage != PS_NOTEXT)
        {
            ps.SMInfo(ps.GetPSText(psMessage));
        }
        else
        {
            //+Tar229577
            CString csData = csMessage;
            // TAR 414306 - Show "corrective action" message without appending it to avoid clipped strings.
            csData = (ps.GetPSText(MSG_DEVICEERRORNOTFIXED));

            ps.SMInfo(csData);
            //-Tar229577

        }
        ps.ShowFrame();
        trace(L6, _T("+SMSystemMessageBase::ShowDeviceErrorNotFixedScreen, ps.ShowFrame() passed"));


    }   //-Tar228161
    // -SSCOB-1440
	else
	{
		trace(L6, _T("ShowDeviceErrorNotFixedScreen local mode"));

        CPSXRedrawLock csRedrawLock(_T("Display"), _T("SMSystemMessageBase::ShowDeviceErrorNotFixedScreen"));

		ps.SetCMFrame(_T("SystemMessage"));
		ps.SetButtonText(_T("CMButton1Med"), BTT_OK);	

		//SR742+
		if ( co.IsDegradedModeOn() && ( IsCardDeviceError(deviceClass) 
			|| IsCashDeviceError(deviceClass) ) )
		{
			ps.SetCMFrame(_T("SystemMessageDegradedMode"));

			if (!m_bForceFixDeviceError)
			{
				if ( IsCashDeviceError(deviceClass) )
				{
					ps.SetButtonText(_T("CMButton2Med"),LTT_CARDONLYMODE);
				}
				else if ( IsCardDeviceError(deviceClass) )
				{
					if( IsMINIHardware() )
					{
						// if MSR devices in error in 3x hw, we don't want to display cash only mode options 
						// since 3x don't accept cash, instead attendant may fix the problem. 
						ps.Button(_T("CMButton2Med"),LTT_CASHONLYMODE, false);
					}
					else
					{
						ps.Message12(MSG_DEVICEERRORNOTFIXED_CASH_ONLY, true);
						ps.SetButtonText(_T("CMButton2Med"),LTT_CASHONLYMODE );
					}
				}
				else
				{
					trace(L6, _T("SMSystemMessageBase:%d is invalid degraded mode type."), dm.GetDegradedModeType());	
				}
			}
			else	
			{
				// Disable degraded mode button option.
				if ( ( dm.GetDegradedModeType() == DEGRADEDMODE_CASH_ONLY ) && IsCashDeviceError( deviceClass ) )
				{
					ps.Button(_T("CMButton2Med"),LTT_CARDONLYMODE, false);
				}
				else if ( ( dm.GetDegradedModeType() == DEGRADEDMODE_CARD_ONLY ) && IsCardDeviceError(deviceClass) )
				{
					ps.Button(_T("CMButton2Med"),LTT_CASHONLYMODE, false);
				}
				else
				{
					//if were not already in degraded mode and if both cash device and card device in error.
					ps.Button(_T("CMButton2Med"),LTT_CARDONLYMODE, false);
				}
			}	

		ps.SetButtonText(_T("CMButton1Med"), BTT_TRYAGAIN);
		}
		//SR742- 

		//moved here SR742
		ps.SetCMLeadthruText(title);
		ps.Message12(MSG_DEVICEERRORNOTFIXED, true);
		DMSayPhrase(SECURITYMED);
		ps.ShowAmountDueAmountPaid(lBalanceDue,lTotalPaid); // TAR 284664

		if(!m_csTitle1.IsEmpty())    
		{
			ps.SetCMLeadthruText(m_csTitle1);	
		}
		else
		{
			ps.SetCMLeadthruText(title);
		}
		
		if(!m_csTitle2.IsEmpty())
		{
			csCurContext = EMPTY_STRING;  // Tar 238987
			COleVariant	v = ps.ConvertToEscapeSequence(m_csTitle2, _T("\\n"), _T("\n"));
			m_pAppPSX->SetConfigProperty(_T("Title2Area"), csCurContext, UI::PROPERTYTEXTFORMAT, v);
		}
		ps.Button(_T("ButtonGoBack"), PS_NOTEXT, false);  // TAR 227479
		ps.ShowCMFrame();
	}
	trace(L6, _T("(-SMSystemMessageBase::ShowDeviceErrorNotFixedScreen()"));

	return STATE_NULL;
}

///////////////////////////////////////////////////
//Log device error to reporing server 
//////////////////////////////////////////////////
void SMSystemMessageBase::LogDeviceError(void)
{
	trace(L7, _T("+SMSystemMessageBase::LogDeviceError"));

    PSTEXT psDevice;

//enum{
//	DMCLASS_RECEIPT     =       DMCLASS_START =0, 
//	DMCLASS_JOURNAL				1,
//	DMCLASS_SLIP				2,
//	DMCLASS_PRINTER				3, // Device Manager Use Only!
//	DMCLASS_CASHDRAWER			4,
//	DMCLASS_CASHCHANGER			5,
//	DMCLASS_KEYLOCK				6,
//	DMCLASS_LINEDISPLAY			7,
//	DMCLASS_MICR				8,
//	DMCLASS_MSR					9,
//	DMCLASS_SCALE				10,
//	DMCLASS_SCANNER				11,
//	DMCLASS_SIGCAP				12,
//	DMCLASS_MISC				13,
//	DMCLASS_ENCRYPTOR			14,
//	DMCLASS_CASHACCEPTOR		15,
//	DMCLASS_COINACCEPTOR		16,        //MHS-09/23/98
//	DMCLASS_MAX_CLASSES		   	//IMPORTANT THIS MUST BE THE LAST Constant in list
//};


	switch(deviceClass)
	{
		case DMCLASS_RECEIPT:
			psDevice = TXT_RECEIPT_PRINTER;
			break;
		case DMCLASS_JOURNAL:
			psDevice = TXT_JOURNAL_PRINTER;
			break;
		case DMCLASS_SLIP:
			psDevice = MSG_SLIP_PRINTER;
			break;
		case DMCLASS_CASHDRAWER:
			psDevice = MSG_CASH_DRAWER;
			break;
		case DMCLASS_CASHRECYCLER:
			// If Error is for note cover, it has already been logged.
			// Don't log again.
			if(csMessage.Find(_T("CHAN_ERROR_NOTE_COVER_OPEN")) != -1)
				break;
		case DMCLASS_CASHCHANGER:
			psDevice = MSG_CASH_CHANGER;
			break;
		case DMCLASS_KEYLOCK:
			psDevice = MSG_KEYLOCK;
			break;
		case DMCLASS_LINEDISPLAY:
			psDevice = MSG_LINE_DISPLAY;
			break;
		case DMCLASS_MICR:
			psDevice = MSG_MICR;
			break;
		case DMCLASS_MSR:
			psDevice = MSG_MSR;
			break;
		case DMCLASS_SCALE:
			psDevice = MSG_SCALE;
			break;
		case DMCLASS_SCANNER:
			psDevice = MSG_SCANNER;
			break;
		case DMCLASS_SIGCAP:
			psDevice = MSG_SIGCAP;
			break;
		case DMCLASS_MISC:
			psDevice = MSG_MISC;
			break;
		case DMCLASS_CASHACCEPTOR:
			psDevice = MSG_CASHACCEPTOR;
			break;
		case DMCLASS_COINACCEPTOR:
			psDevice = MSG_COINACCEPTOR;
			break;	 
		case PIDCLASS_BAGSCALE:
			psDevice = TXT_BAG_SCALE;
			break;
		default:
			psDevice=PS_NOTEXT;
	  
	  }

   if(psDevice !=PS_NOTEXT)
   {
	   rp.LogDeviceError(ps.GetPSText(psDevice, SCOT_LANGUAGE_PRIMARY),"");
   }


	trace(L7, _T("-SMSystemMessageBase::LogDeviceError"));

	return;
}


/**
 * Function:		getInSystemMessage
 * Purpose:			Provide SSF access to the bInSystemMessage global variable.
 * Parameters:		None
 * Returns:			The boolean value of bInSystemMessage.  					
 * Calls:			
 * Side Effects:	
 * Notes:			Created for TAR 321887
 */
bool SMSystemMessageBase::getInSystemMessage(void)
{
	return bInSystemMessage;
}

/**
 * Function:		setInSystemMessage
 * Purpose:			Provide SSF access to the bInSystemMessage global variable.
 * Parameters:		bool b - The new value for bInSystemMessage.
 * Returns:			Nothing. 					
 * Calls:			
 * Side Effects:	
 * Notes:			Created for TAR 321887
 */
void SMSystemMessageBase::setInSystemMessage(bool b)
{
	bInSystemMessage = b;
}


//TAR307389+
long SMSystemMessageBase::GetDeviceClass(void)
{
	return deviceClass;
}

SMStateBase* SMSystemMessageBase::CkStateStackAndReturn(void)
{
	trace(L4, _T("+SMSystemMessageBase::CkStateStackAndReturn"));
    CheckAndCleanStateStack();
	return SMStateBase::CkStateStackAndReturn();
}
//TAR307389-


