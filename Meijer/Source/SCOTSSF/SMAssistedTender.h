//////////////////////////////////////////////////////////////////////////////////////////////////
//
// FILE:  SMAssistedTender.h
//
// TITLE: Class header for Finish State
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _ASSISTEDTENDERSTATE
#define _ASSISTEDTENDERSTATE

#include "SMAssistedTenderBase.h"

#ifdef _SCOTSSF_
class DLLEXPORT
#else
class DLLIMPORT
#endif
 SMAssistedTender : public SMAssistedTenderBase
{
public:
    SMAssistedTender();
    virtual bool DeliverDescriptorList(CDescriptorList &dlParameterList);
    virtual SMStateBase *Initialize();
    virtual void UnInitialize();
    virtual SMStateBase  *OnWtIncreaseNotAllowed(void);
    virtual SMStateBase  *OnWtDecrease(void);
    virtual bool IsLoginBypassAllowed();

protected:
    virtual void SetupViewData();
    virtual SMStateBase *HandleRAPData();
    virtual void showScreen(bool passwordVerified);
    virtual SMStateBase *PSButtonGoBack(void);

    DECLARE_DYNCREATE(SMAssistedTender)// MFC Runtime class/object information

};

#endif