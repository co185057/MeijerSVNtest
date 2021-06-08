//////////////////////////////////////////////////////////////////////////////////////////////////
//
// FILE:  SMSmVisualItemsBase.CPP
//
// TITLE: Class implementation for store mode Visual Items state
//
//
// AUTHOR: gary miller
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdafx.h>                 // MS MFC always needed first
//               // MS MFC template header

#include "Common.h"                 // MGV common includes

#include "SMState.h"                // MGV base state
#include "SMSmVisualItems.h"        // MGV this state
#include "SMSmAuthorization.h"      // MGV auth state
#include "SMSmAssistMenu.h"      // MGV auth state
#include "SMSmAssistMode.h"         // TAR 391593

#define COMP_ID ID_SM               // base state component
#define T_ID _T("SmVisualItemsBase")

IMPLEMENT_DYNCREATE(SMSmVisualItemsBase, CObject)// MFC Runtime class/object information

//IMPLEMENT_STATE(SmVisualItems)


DEFINE_TIMESTAMP

//////////////////////////////////
SMSmVisualItemsBase::SMSmVisualItemsBase()
{
  IMPLEMENT_TIMESTAMP
}

/////////////////////////////////////////
SMStateBase  *SMSmVisualItemsBase::Initialize(void)
{
    CString csNumItems;
    bStoreModeApprovals = true;
    csNumItems.Format(_T("%s (%d/%d)"), 
                      ps.GetPSText(LTT_VERIFYITEMS, SCOT_LANGUAGE_PRIMARY),
                      lUnapprovedVisualVerifyItems, 
                      lVisualVerifyItems);
    
		
// NewUI
	ps.SetFrame(_T("SmVisualItems"));
    ps.SetLeadthruText(csNumItems, _T(""));
	ps.SetButtonText(_T("SMButton1"), BTT_VISUALITEMS);
	ps.Echo(PS_BLANK); //tar 228451
// NewUI
    ps.ShowSMTotal(true);
	ps.ShowSMTBText(csTBMessage2Scot);	//thp

    ps.SMShowVisualItemReceipt(true);
	ps.ShowFrame();

	//SR81 begin
	if (!co.fOperationsImmediateInterventionForVisualVerifyItems)
	{
		ps.ButtonState( _T("SMButton2"), false, false);
		//TAR 408485+
		//ps.ButtonEnable(_T("SMButton8"), true);
		if (ps.RemoteMode())
		{
			ps.Button(_T("SMButton8"), BTT_GOBACK, true);
		}
		else
		{
			ps.Button(_T("SMButton8"), TTL_STOREAUTH, true);
		}
		//TAR 408485-

	}
	else
	{
		ps.ButtonState( _T("SMButton2"), true, true);
		//TAR 408485+
		//ps.ButtonEnable(_T("SMButton8"), false);
		if (ps.RemoteMode())
		{
			ps.Button(_T("SMButton8"), BTT_GOBACK, false);
		}
		else
		{
			ps.Button(_T("SMButton8"), TTL_STOREAUTH, false);
		}
		//TAR 408485-
	}
	//SR81 end

    // (*) SR898 ====================
	DMTurnOffTriColorLight();
    
	// (*) SR898 ====================
    DMSetTriColorLight(DM_TRICOLORLIGHT_GREEN,
                       DM_TRICOLORLIGHT_ON,
                       DM_TRICOLORLIGHT_NORMALREQUEST);
  
    return STATE_NULL;
}


////////////////////////////////////////
SMStateBase  *SMSmVisualItemsBase::PSButton1(void) // approve visual verify items
{
  lUnapprovedVisualVerifyItems = 0;
	
    POSITION nPos = g_mapTransactionVisualVerify.GetStartPosition();
    while (nPos != NULL)
    {
        COleVariant vValue;
        CString csItemId;
        int nKey;
        bool bValue;
        g_mapTransactionVisualVerify.GetNextAssoc(nPos, nKey, bValue);

        if( !bValue )
        {
            bValue = true;
            g_mapTransactionVisualVerify.SetAt(nKey, bValue);
            csItemId.Format(_T("%d"), nKey);
            vValue = (long) bValue;
            ps.GetPSXObject()->SetReceiptItemVariable(_T("CMSMReceipt"), csItemId, _T("ITEM_AUTOAPPROVAL_FLAG"), vValue);
        }
    }
    ps.GetPSXObject()->UpdateReceiptControls(_T("CMSMReceipt"));
	// remote approval
    trace(L7, _T("+ra.OnVisualValidationApproval"));
	ra.OnVisualValidationApproval();
	trace(L7, _T("-ra.OnVisualValidationApproval"));
	bInApprovalNeeded = false; //TAR 279092
    //sscoadk-5431
    //return STATE_NULL; // wait for WMRA_SEND_INTERVENTION_APPROVED
    trace(L6, _T("Going to SmAuthorization to wait on WMRA_SEND_INTERVENTION_APPROVED"));
    RETURNSTATE(SmAuthorization)  //wait for WMRA_SEND_INTERVENTION_APPROVED at SmSmAuthorization state
}

//SR81 begin
/////////////////////////////////////////////
// PSButton2 - assist mode button
/////////////////////////////////////////////
SMStateBase  *SMSmVisualItemsBase::PSButton2(void)
{
	bForceApprovalBeforeSuspend = true;
	lUnapprovedVisualVerifyItems = 1;
    bStoreModeApprovals = false; //sscoadk-5431

	if (co.fStateAssistMenuFromStoreModeAllowed)
	{
		RETURNSTATE(SmAssistMenu)
	}

	RETURNSTATE(SmAssistMode) // TAR 391593
}
//SR81 end

////////////////////////////////////////
SMStateBase  *SMSmVisualItemsBase::PSButton8(void) // cancel
{
  bForceApprovalBeforeSuspend = false; //TAR 364905
  bInApprovalNeeded = false; //TAR 279092
  trace(L7, _T("Cashier selected Store Authorization button instead of approving visual verify item(s)"));
  bStoreModeGoBack = true;
  bStoreModeApprovals = false; //sscoadk-5431
  //TAR 290433
  if (co.IsInAssistMenus())
  {
	  RETURNSTATE(SmAssistMenu)
  }
  RETURNSTATE(SmAuthorization)
}
////////////////////////////////////////
// NewUI
SMStateBase  *SMSmVisualItemsBase::PSReceiptUp(void)
{
  ps.ScrollUp(_T("SMReceiptVisualItem"));
  return STATE_NULL;

}
SMStateBase  *SMSmVisualItemsBase::PSReceiptDown(void)
{
  ps.ScrollDown(_T("SMReceiptVisualItem"));
  return STATE_NULL;

}
// NewUI
//SMStateBase  *SMSmVisualItemsBase::PSCancelKey(void) // cancel ----> removed per tar 121487
//{
//  DMSayPhrase("KeyPadValid");
//  return PSButton8();
//}

/*
//sscoadk-5431+
SMStateBase *SMSmVisualItemsBase::RAParse(MessageElement *me)
{
    trace(L4,_T("SMSmVisualItemsBase::RAParse: me->raInfo.msg = %d on thread 0x%08.8x"), me->raInfo.msg, GetCurrentThreadId());

    if (me->raInfo.msg == WMRA_SEND_INTERVENTION_APPROVED )
    {
        if (!isAnyApprovalRequired())
        {
            g_bInterventionApproval = false;
            if( g_bInterventionsOnStoreModeEntry )
            {
                g_bInterventionsOnStoreModeEntry = false;
                rp.ClearOperator();
                return createAnchorState();
            }
            else
                RETURNSTATE(SmAuthorization)
        }
        else
            RETURNSTATE(SmAuthorization)
    }

    return STATE(StoreModeState)::RAParse(me);
}
//sscoadk-5431-
*/
