// $Header: /Integration_Customer/Meijer/CURRENT_DEV/Platform-Core-Patch/remote console manager/src/rap/actions/ActionBaseRAP.cpp 3     10/21/08 4:07p Sm133076 $
/*
 * @(#)RCMActionBase.cpp    $Revision: 3 $ $Date: 10/21/08 4:07p $
 *
 * Copyright 2004 by NCR Corporation,
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
* $Log: /Integration_Customer/Meijer/CURRENT_DEV/Platform-Core-Patch/remote console manager/src/rap/actions/ActionBaseRAP.cpp $
 * 
 * 3     10/21/08 4:07p Sm133076
 * Patch G Migration
 * 
 * 6     10/20/06 9:50a Tn185011
 * Roll back to 244
 * 
 * 2     2/28/05 4:06p Dm185016
 * lint
 * 
 * 1     1/26/05 2:18p Dm185016
 * Moved to new Repository.
// 
// 1     10/29/04 8:53a Dm185016
*/
/*lint -save -e1774     Don't want to use dynamic_cast */
#include "StdAfx.h"
#include "ActionBaseRAP.h"
#include "RemoteAPMgr.h"

using namespace rap;


CRemoteAPMgr &CActionBaseRAP::rapmgr() { return *CSingleton<CRemoteAPMgr>::instance(); }

/*lint -restore */
