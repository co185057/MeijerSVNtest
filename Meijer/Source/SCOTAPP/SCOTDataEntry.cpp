#include "stdafx.h"
#include "SCOTDataEntry.h"
#include "PSConfigData.h"

// Populate all fields from an INI file section or Registry key.
// TAR 268133 - Add bPrimLang parameter to pass to GetFormattedString()
bool CSCOTDataEntry::FromConfigData(CString sSource, CString sSection, bool bPrimLang, bool bTranslate)
   {
   bool bStatus = false;
   int iButtons = 0;
   CPSConfigData cd;
   CString sTemp;
   CString sStringName;

   cd.SetSource(sSource);
   Clear();
   m_sContents.Empty();

   // RFQ 2605 - Increase flexibility of ScotDataEntry object by allowing it to load all strings defined in a ini section
   int index = 0;
   while (cd.EnumSectionValues(sSection, sStringName, index++))
   {
       if (bTranslate)
       {
           cd.GetFormattedString(sSection, sStringName, sTemp, _T(""), bPrimLang);
       }
       else
       {
           cd.GetString(sSection, sStringName, sTemp);
       }
	   InsertString(sStringName, sTemp);
   }

   /* //RFQ 2506 -  Use of EnumSectionValues makes following calls obsolete
   sStringName = _T("TopCaption");
   cd.GetFormattedString(sSection, sStringName, sTemp, _T(""), bPrimLang);
   InsertString(sStringName, sTemp);
	
   //TAR344460 begin - Now CSCOTDataEntry::FromConfigData handles all ScotDataEntry.ini settings that are accepted by CDataEnty::FromContents
   sStringName = _T("LaneButtonText");
   cd.GetFormattedString(sSection, sStringName, sTemp, _T(""), bPrimLang);
   InsertString(sStringName, sTemp);
   
   sStringName = _T("LSWND1");
   cd.GetFormattedString(sSection, sStringName, sTemp, _T(""), bPrimLang);
   InsertString(sStringName, sTemp);
   
   sStringName = _T("LSWND2");
   cd.GetFormattedString(sSection, sStringName, sTemp, _T(""), bPrimLang);
   InsertString(sStringName, sTemp);
   
   sStringName = _T("LSWND3");
   cd.GetFormattedString(sSection, sStringName, sTemp, _T(""), bPrimLang);
   InsertString(sStringName, sTemp);
   //TAR 344460 end

   sStringName = _T("BottomCaption");
   cd.GetFormattedString(sSection, sStringName, sTemp, _T(""), bPrimLang);
   InsertString(sStringName, sTemp);

   sStringName = _T("InputMask");
   cd.GetFormattedString(sSection, sStringName, sTemp, _T(""), bPrimLang);
   InsertString(sStringName, sTemp);

   sStringName = _T("SummaryInstruction");
   cd.GetFormattedString(sSection, sStringName, sTemp, _T(""), bPrimLang);
   InsertString(sStringName, sTemp);

   sStringName = _T("ScannerInputEnabled");
   cd.GetFormattedString(sSection, sStringName, sTemp, _T(""), bPrimLang);
   InsertString(sStringName, sTemp);

   sStringName = _T("ViewType");
   cd.GetFormattedString(sSection, sStringName, sTemp, _T(""), bPrimLang);
   InsertString(sStringName, sTemp);

   sStringName = _T("DefaultButton");
   cd.GetFormattedString(sSection, sStringName, sTemp, _T(""), bPrimLang);
   InsertString(sStringName, sTemp);

   sStringName = _T("StoreLogon");
   cd.GetFormattedString(sSection, sStringName, sTemp, _T(""), bPrimLang);
   InsertString(sStringName, sTemp);

   sStringName = _T("HideTotal");
   cd.GetFormattedString(sSection, sStringName, sTemp, _T(""), bPrimLang);
   InsertString(sStringName, sTemp);

   sStringName = _T("HideHelp");
   cd.GetFormattedString(sSection, sStringName, sTemp, _T(""), bPrimLang);
   InsertString(sStringName, sTemp);

   sStringName = _T("HideInput");
   cd.GetFormattedString(sSection, sStringName, sTemp, _T(""), bPrimLang);
   InsertString(sStringName, sTemp);

   sStringName = _T("SayPhrase");
   cd.GetFormattedString(sSection, sStringName, sTemp, _T(""), bPrimLang);
   InsertString(sStringName, sTemp);

   sStringName = _T("DetailedInstruction");
   cd.GetFormattedString(sSection, sStringName, sTemp, _T(""), bPrimLang);
   InsertString(sStringName, sTemp);

   sStringName = _T("ContextToDisplay");
   cd.GetFormattedString(sSection, sStringName, sTemp, _T(""), bPrimLang);
   InsertString(sStringName, sTemp);

   sStringName = _T("ButtonFont");
   cd.GetFormattedString(sSection, sStringName, sTemp, _T(""), bPrimLang);
   InsertString(sStringName, sTemp);

   sStringName = _T("InputLengthMin");
   cd.GetFormattedString(sSection, sStringName, sTemp, _T(""), bPrimLang);
   InsertString(sStringName, sTemp);

   //Reporting 
   sStringName = _T("csSection");
   InsertString(sSection, sTemp);
   //Reporting 
   
   InsertString(_T("Section"), sSection); //Tar 228161 Need to pick up the Section title too.

    //+RFC375568
    sStringName = _T("AutoRunResponse");
    cd.GetFormattedString(sSection, sStringName, sTemp, _T(""), bPrimLang);
    InsertString(sStringName, sTemp);
    //-RFC375568
   for (int iIndex = 0; iIndex < 8; iIndex++)
      {
      sStringName.Format(_T("Button%d"), iIndex);
      cd.GetFormattedString(sSection, sStringName, sTemp, _T(""), bPrimLang);
      InsertString(sStringName, sTemp);
      }
*/  //End RFQ 2506

   InsertString(_T("Section"), sSection); //Tar 425528
   bStatus = FromContents();

   return bStatus;
   }
CString CSCOTDataEntry::GetSectionName() const
{
	return ExtractString(_T("Section"));
}

void CSCOTDataEntry::SetSectionName(CString s)
{
	InsertString(_T("Section"), s);
}
