#pragma once
// $Header: /Integration_Customer/Meijer/CURRENT_DEV/Platform-Core-Patch/remote console manager/src/rap/actions/SendClientMachineNameEvent.h 3     10/21/08 4:08p Sm133076 $
/*
 * @(#)SendClientMachineNameEvent.h    $Revision: 3 $ $Date: 10/21/08 4:08p $
 *
 * Copyright 2005 by NCR Corporation,
 *
 * All rights reserved.
 *
 * This software is the confidential and proprietary information
 * of NCR Corporation. ("Confidential Information").  You
 * shall not disclose such Confidential Information and shall use
 * it only in accordance with the terms of the license agreement
 * you entered into with NCR.
 */
/*
* $Log: /Integration_Customer/Meijer/CURRENT_DEV/Platform-Core-Patch/remote console manager/src/rap/actions/SendClientMachineNameEvent.h $
 * 
 * 3     10/21/08 4:08p Sm133076
 * Patch G Migration
 * 
 * 5     10/20/06 9:50a Tn185011
 * Roll back to 244
 * 
 * 1     2/18/05 9:43a Dm185016
 * TAR 293708
*/

#include "SMConstants.h"
#include "Createable.h"
#include "RCMActionBase.h"
#include "ActionBaseRAP.h"
#include "RAConnections.h"
#include "Pool.h"

namespace STATE_MACHINE_NAMESPACE 
{
    class IMessage;
}
using namespace STATE_MACHINE_NAMESPACE;

using namespace rap;

class CSendClientMachineNameEvent
    : public CRCMActionBase
    , public CActionBaseRAP
    , public CCreateable<CSendClientMachineNameEvent, IAction>
//    , public CPool<CSendClientMachineNameEvent>
{

public:

    CSendClientMachineNameEvent();
	virtual ~CSendClientMachineNameEvent();
    
    virtual HRESULT Execute(bool *, IMessage &);

private:

    // hide copy and assignment
	CSendClientMachineNameEvent(const CSendClientMachineNameEvent&);
	CSendClientMachineNameEvent& operator = (const CSendClientMachineNameEvent &);
};
