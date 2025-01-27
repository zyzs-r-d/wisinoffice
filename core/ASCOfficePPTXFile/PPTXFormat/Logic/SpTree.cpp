﻿/*
 * (c) Copyright Ascensio System SIA 2010-2019
 *
 * This program is a free software product. You can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License (AGPL)
 * version 3 as published by the Free Software Foundation. In accordance with
 * Section 7(a) of the GNU AGPL its Section 15 shall be amended to the effect
 * that Ascensio System SIA expressly excludes the warranty of non-infringement
 * of any third-party rights.
 *
 * This program is distributed WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR  PURPOSE. For
 * details, see the GNU AGPL at: http://www.gnu.org/licenses/agpl-3.0.html
 *
 * You can contact Ascensio System SIA at 20A-12 Ernesta Birznieka-Upisha
 * street, Riga, Latvia, EU, LV-1050.
 *
 * The  interactive user interfaces in modified source and object code versions
 * of the Program must display Appropriate Legal Notices, as required under
 * Section 5 of the GNU AGPL version 3.
 *
 * Pursuant to Section 7(b) of the License you must retain the original Product
 * logo when distributing the program. Pursuant to Section 7(e) we decline to
 * grant you any rights under trademark law for use of our trademarks.
 *
 * All the Product's GUI elements, including illustrations and icon sets, as
 * well as technical writing content are licensed under the terms of the
 * Creative Commons Attribution-ShareAlike 4.0 International. See the License
 * terms at http://creativecommons.org/licenses/by-sa/4.0/legalcode
 *
 */


#include "SpTree.h"
#include "Shape.h"
#include "Pic.h"
#include "../Theme.h"
#include "ClrMap.h"

namespace PPTX
{
	namespace Logic
	{
		void SpTree::toXmlWriterVML(NSBinPptxRW::CXmlWriter *pWriter, NSCommon::smart_ptr<PPTX::Theme>& oTheme, NSCommon::smart_ptr<PPTX::Logic::ClrMap>& oClrMap, const WCHAR* pId, bool in_group)
		{
			pWriter->StartNode(_T("v:group"));
			pWriter->StartAttributes();

			std::wstring strId			= L"group " + std::to_wstring(pWriter->m_lObjectIdVML);
			std::wstring strSpid		= L"_x0000_s"	+ XmlUtils::IntToString(0xFFFF & (pWriter->m_lObjectIdVML >> 16), L"%04d");

			pWriter->m_lObjectIdVML++;

			if (XMLWRITER_DOC_TYPE_XLSX == pWriter->m_lDocType)
			{
				if(NULL == pId)
				{
					pWriter->WriteAttribute(L"id", strSpid);
				}
				else
				{
					pWriter->WriteAttribute(L"id", pId);
					pWriter->WriteAttribute(L"o:spid", strSpid);
				}
			}
			else
			{
				pWriter->WriteAttribute(L"id",		strId);
				pWriter->WriteAttribute(L"o:spid",	strSpid);
			}
		
			NSBinPptxRW::CXmlWriter oStylesWriter;
			
			if (!pWriter->m_strStyleMain.empty())
			{
				if (grpSpPr.xfrm.is_init())
				{
					if (grpSpPr.xfrm->rot.is_init())
					{
						int nRot = (int)((double)(*(grpSpPr.xfrm->rot)) / 60000.0);
						oStylesWriter.WriteAttributeCSS_int(_T("rotation"), nRot);
					}
					bool bIsFH = grpSpPr.xfrm->flipH.get_value_or(false);
					bool bIsFV = grpSpPr.xfrm->flipV.get_value_or(false);
					if (bIsFH && bIsFV)
					{
						oStylesWriter.WriteAttributeCSS(_T("flip"), _T("xy"));
					}
					else if (bIsFH)
					{
						oStylesWriter.WriteAttributeCSS(_T("flip"), _T("x"));
					}
					else if (bIsFV)
					{
						oStylesWriter.WriteAttributeCSS(_T("flip"), _T("y"));
					}
				}

				if (oStylesWriter.GetSize() == 0)
				{
					pWriter->WriteAttribute(_T("style"), pWriter->m_strStyleMain);
				}
				else
				{
					pWriter->WriteAttribute(_T("style"), pWriter->m_strStyleMain + oStylesWriter.GetXmlString());
				}
				pWriter->m_strStyleMain = _T("");
			}
			else
			{
				int dL = 0, dT = 0, dW = 0, dH = 0;
				if (grpSpPr.xfrm.is_init())
				{
					if (grpSpPr.xfrm->offX.is_init())	dL = *grpSpPr.xfrm->offX;
					if (grpSpPr.xfrm->offY.is_init())	dT = *grpSpPr.xfrm->offY;
					if (grpSpPr.xfrm->extX.is_init())	dW = *grpSpPr.xfrm->extX;
					if (grpSpPr.xfrm->extY.is_init())	dH = *grpSpPr.xfrm->extY;
				}

				oStylesWriter.ClearNoAttack();
				oStylesWriter.WriteAttributeCSS(L"position", L"absolute");
				if (in_group)
				{
					oStylesWriter.WriteAttributeCSS_int(L"left",	dL / 100);
					oStylesWriter.WriteAttributeCSS_int(L"top",		dT / 100);
					oStylesWriter.WriteAttributeCSS_int(L"width",	dW / 100);
					oStylesWriter.WriteAttributeCSS_int(L"height",	dH / 100);
				}
				else
				{
					oStylesWriter.WriteAttributeCSS_int_pt(L"left",		dL /  12700);
					oStylesWriter.WriteAttributeCSS_int_pt(L"top",		dT /  12700);
					oStylesWriter.WriteAttributeCSS_int_pt(L"width",	dW /  12700);
					oStylesWriter.WriteAttributeCSS_int_pt(L"height",	dH /  12700);
				}

				if (grpSpPr.xfrm.is_init())
				{
					if (grpSpPr.xfrm->rot.is_init())
					{
						int nRot = (int)((double)(*(grpSpPr.xfrm->rot)) / 60000.0);
						oStylesWriter.WriteAttributeCSS_int(_T("rotation"), nRot);
					}
					bool bIsFH = grpSpPr.xfrm->flipH.get_value_or(false);
					bool bIsFV = grpSpPr.xfrm->flipV.get_value_or(false);
					if (bIsFH && bIsFV)
					{
						oStylesWriter.WriteAttributeCSS(_T("flip"), _T("xy"));
					}
					else if (bIsFH)
					{
						oStylesWriter.WriteAttributeCSS(_T("flip"), _T("x"));
					}
					else if (bIsFV)
					{
						oStylesWriter.WriteAttributeCSS(_T("flip"), _T("y"));
					}
				}
				
				pWriter->WriteAttribute(_T("style"), oStylesWriter.GetXmlString());
			}

			if (!pWriter->m_strAttributesMain.empty())
			{
				pWriter->WriteString(pWriter->m_strAttributesMain);
				pWriter->m_strAttributesMain.clear();
			}

			int dL = 0, dT = 0, dW = 0, dH = 0;

			if (grpSpPr.xfrm.is_init())
			{
				if (grpSpPr.xfrm->chOffX.is_init())	dL = *grpSpPr.xfrm->chOffX;
				if (grpSpPr.xfrm->chOffY.is_init())	dT = *grpSpPr.xfrm->chOffY;
				if (grpSpPr.xfrm->chExtX.is_init())	dW = *grpSpPr.xfrm->chExtX;
				if (grpSpPr.xfrm->chExtY.is_init())	dH = *grpSpPr.xfrm->chExtY;
			}
			oStylesWriter.ClearNoAttack();
			oStylesWriter.m_oWriter.AddSize(30);
			oStylesWriter.m_oWriter.AddIntNoCheck(dL / 100);
			oStylesWriter.m_oWriter.AddCharNoCheck(WCHAR(','));
			oStylesWriter.m_oWriter.AddIntNoCheck(dT / 100);
			pWriter->WriteAttribute(_T("coordorigin"), oStylesWriter.GetXmlString());

			oStylesWriter.ClearNoAttack();
			oStylesWriter.m_oWriter.AddSize(30);
			oStylesWriter.m_oWriter.AddIntNoCheck(dW / 100);
			oStylesWriter.m_oWriter.AddCharNoCheck(WCHAR(','));
			oStylesWriter.m_oWriter.AddIntNoCheck(dH / 100);
			pWriter->WriteAttribute(_T("coordsize"), oStylesWriter.GetXmlString());

			pWriter->EndAttributes();

			size_t nCount = SpTreeElems.size();
			for (size_t i = 0; i < nCount; ++i)
			{
				if (SpTreeElems[i].is<PPTX::Logic::Shape>())
				{
					SpTreeElems[i].as<PPTX::Logic::Shape>().toXmlWriterVML(pWriter, oTheme, oClrMap, NULL, true);
				}
				else if (SpTreeElems[i].is<PPTX::Logic::Pic>())
				{
					SpTreeElems[i].as<PPTX::Logic::Pic>().toXmlWriterVML(pWriter, oTheme, oClrMap, NULL, true);
				}
				else if (SpTreeElems[i].is<PPTX::Logic::SpTree>())
				{
					SpTreeElems[i].as<PPTX::Logic::SpTree>().toXmlWriterVML(pWriter, oTheme, oClrMap, NULL, true);
				}				
			}

			pWriter->WriteString(pWriter->m_strNodes);
			pWriter->m_strNodes = _T("");
			pWriter->EndNode(_T("v:group"));
		}
	}
}
