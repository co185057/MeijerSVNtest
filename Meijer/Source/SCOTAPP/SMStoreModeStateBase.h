//////////////////////////////////////////////////////////////////////////////////////////////////
//
// File:  SMStoreModeStateBase.h
//
// Description: Derived from SMStateBase .  All store mode states are derived from this state.
//
// Author: Jeff Connelly
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _SMStoreModeStateBase
#define _SMStoreModeStateBase

#include "SMState.h"

////////////////////////////////////////
#ifdef _SCOTSSF_
class DLLIMPORT
#else
class DLLEXPORT
#endif
  SMStoreModeStateBase : public STATE(State)
{

protected:
  
	
public:
	SMStoreModeStateBase();
  virtual bool  storeMode() { return true; }
  virtual bool PSRemoteLegalForState(); //awk.10.22.2
  virtual bool PSAssistMenuLegalForState();

  // Override to create versions of msgs that do not require operator/password, since
  // to be in store mode an operator/password must already have been entered.
  // See description of createLevel1Message, etc. in State h file.
  virtual SMStateBase * createLevel1Message( LPCTSTR szMsg,
		                                    PSTEXT pstMsg,
		                                    PSTEXT prompt,
		                                    long   value,
		                                    long   device,
		                                    bool   checkHealth, 
											bool displayHTML=false); //SR672
  virtual SMStateBase * createLevel2Message( LPCTSTR szMsg,
		                                    PSTEXT pstMsg,
		                                    PSTEXT prompt,
		                                    long   value,
		                                    long   device,
		                                    bool   checkHealth,
											bool displayHTML=false); //SR672
  virtual SMStateBase * createLevel3Message( LPCTSTR szMsg,
		                                    PSTEXT pstMsg,
		                                    PSTEXT prompt,
		                                    long   value,
		                                    long   device,
		                                    bool   checkHealth,
											bool displayHTML=false); //SR672

   
  	/**
     * Trick the base that the cash device is not Glory 
     * so that cash will not be rejected in this state.
	 * \note Add Glory CM Support
     */
    virtual bool DMCashRecyclerShouldReject(const CString &csStateName);
	virtual SMStateBase *DMAcceptor(void);	// SSCOP-2197
	virtual SMStateBase *PSParse( const MessageElement* );	//SSCOB_257
    virtual SMStateBase *HandleOutstandingInterventions();
	
  DECLARE_DYNCREATE(SMStoreModeStateBase)// MFC Runtime class/object information
};
//
// The following macro declares the function:
//
//    DLLEXPORT SMStateBase *makeSMStoreModeState(void);
// or
//    DLLEXPORT SMStateBase *makeSMStoreModeStateBase(void);
// 
// depending on whether _BUILDLIB_ is defined or not. This function
// creates the SMStoreModeState objects.  This function is called by
// RETURNSTATE(StoreModeState) instead of calling new STATE(StoreModeState) so
// that SCOTSSF works correctly.
//
// The function is implemented in SMStoreModeStateBase.cpp and SMStoreModeState.cpp
// by using the macro IMPLEMENT_STATE(StoreModeState)

//DECLARE_STATE(StoreModeState)

#endif
