///////////////////////////////////////////////////////////////////////////
///
/// \file BaseCurrentTotals.h
/// \brief interface for the CBaseCurrentTotals class.
///
///	@author: FastLane POSI
///
//////////////////////////////////////////////////////////////////////////
#if !defined(AFX_BaseCurrentTotals_H__INCLUDED_)
#define AFX_BaseCurrentTotals_H__INCLUDED_

#include "totaldetailsmsg.h"

//////////////////////////////////////////////////////////////////////
///
/// CBaseCurrentTotals is an implementaion of CBaseCurrentTotals
///
///	@author: FastLane POSI
///
//////////////////////////////////////////////////////////////////////
class CBaseCurrentTotals : public CTotalDetailsMsg
{
public:
		//////////////////////////////////////////////////////////////////////
		///
		/// Destructor
		///
		//////////////////////////////////////////////////////////////////////
    virtual ~CBaseCurrentTotals();
    
		//////////////////////////////////////////////////////////////////////
		///
		/// ResetTotalDetails, reset member variables assocaited with class
		///
		//////////////////////////////////////////////////////////////////////
    virtual void ResetTotalDetails(void);

		//////////////////////////////////////////////////////////////////////
		///
		/// GetSubTotal, accessors for member variable
		///
		///	@return long sub total
		//////////////////////////////////////////////////////////////////////
    long GetSubTotal();

		//////////////////////////////////////////////////////////////////////
		///
		/// SetSubTotal, accessors for member variable
		///
		///	@param long sub total
		//////////////////////////////////////////////////////////////////////
    void SetSubTotal(long lVal);
		
		//////////////////////////////////////////////////////////////////////
		///
		/// GetChangeDue, accessors for member variable
		///
		///	@return long change due
		//////////////////////////////////////////////////////////////////////
    long GetChangeDue();

		//////////////////////////////////////////////////////////////////////
		///
		/// SetChangeDue, accessors for member variable
		///
		///	@param long change due
		//////////////////////////////////////////////////////////////////////
    void SetChangeDue(long lVal);
    
		//////////////////////////////////////////////////////////////////////
		///
		/// GetBalanceDue, accessors for member variable
		///
		///	@return long balance due
		//////////////////////////////////////////////////////////////////////
    long GetBalanceDue();

		//////////////////////////////////////////////////////////////////////
		///
		/// SetBalanceDue, accessors for member variable
		///
		///	@param long balance due
		//////////////////////////////////////////////////////////////////////
    void SetBalanceDue(long lVal);
    
		//////////////////////////////////////////////////////////////////////
		///
		/// GetAvailableBenefitAmount, accessors for member variable
		///
		///	@return long benefit amount
		//////////////////////////////////////////////////////////////////////
    long GetAvailableBenefitAmount();

		//////////////////////////////////////////////////////////////////////
		///
		/// SetAvailableBenefitAmount - accessors for member variable
		///
		///	@param long benefit amount
		//////////////////////////////////////////////////////////////////////
    void SetAvailableBenefitAmount(long lVal);

		//////////////////////////////////////////////////////////////////////
		///
		/// Refresh - casts a CTotalDetailsMsg to a this*, get msg data into class
		///
		///	@param CTotalDetailsMsg *
		//////////////////////////////////////////////////////////////////////
    void Refresh(CTotalDetailsMsg *);

protected:
	  //////////////////////////////////////////////////////////////////////
		///
		/// Constructor
		///
		//////////////////////////////////////////////////////////////////////
    CBaseCurrentTotals();
    
private:
	  //////////////////////////////////////////////////////////////////////
		///
		/// Hide copy const
		///
		//////////////////////////////////////////////////////////////////////
    CBaseCurrentTotals(const CBaseCurrentTotals &);                    // hide copy const

		//////////////////////////////////////////////////////////////////////
		///
		/// Hide Assignment
		///
		//////////////////////////////////////////////////////////////////////
    CBaseCurrentTotals & operator =(const CBaseCurrentTotals &); // hide assignment

    long m_lSubTotal;  ///< variable for sub total
    long m_lChangeDue;	///< variable for change due
    long m_lBalanceDue;	///< variable for balance due
    long m_lAvailableBenefitAmount;	///< variable for benefit amount, e.g. EBT
    long m_lAvailableFoodStampAmount;	///< variable for foodstamp amount, e.g. EBT

};

#endif 
