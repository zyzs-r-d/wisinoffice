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
#pragma once
#ifndef PPTX_LOGIC_RUNELEM_INCLUDE_H_
#define PPTX_LOGIC_RUNELEM_INCLUDE_H_

#include "./../WrapperWritingElement.h"
#include "Runs/RunBase.h"
#include "Runs/Run.h"
#include "Runs/Fld.h"
#include "Runs/Br.h"
#include "Runs/MathParaWrapper.h"

namespace PPTX
{
	namespace Logic
	{
		class RunElem : public WrapperWritingElement
		{
		public:
			WritingElement_AdditionConstructors(RunElem)

			RunElem() {}

			virtual OOX::EElementType getType () const
			{
				if (Elem.IsInit())
					return Elem->getType();
				return OOX::et_Unknown;
			}		
			virtual void fromXML(XmlUtils::CXmlLiteReader& oReader)
			{
				std::wstring name = XmlUtils::GetNameNoNS(oReader.GetName());

				if(name == _T("r"))
					Elem.reset(new Logic::Run(oReader));
				else if(name == _T("fld"))
					Elem.reset(new Logic::Fld(oReader));
				else if(name == _T("br"))
					Elem.reset(new Logic::Br(oReader));
				else if(name == _T("m"))
					Elem.reset(new Logic::MathParaWrapper(oReader));
				else
					Elem.reset();
			}

			virtual void fromXML(XmlUtils::CXmlNode& node)
			{
				std::wstring name = XmlUtils::GetNameNoNS(node.GetName());

				if(name == _T("r"))
					Elem.reset(new Logic::Run(node));
				else if(name == _T("fld"))
					Elem.reset(new Logic::Fld(node));
				else if(name == _T("br"))
					Elem.reset(new Logic::Br(node));
				else if(name == _T("m"))
					Elem.reset(new Logic::MathParaWrapper(node));
				else 
					Elem.reset();
			}
			virtual std::wstring toXML() const
			{
				if (is_init())
					return Elem->toXML();
				return _T("");
			}
			virtual void toXmlWriter(NSBinPptxRW::CXmlWriter* pWriter) const
			{
				if (is_init())
					Elem->toXmlWriter(pWriter);
			}

			virtual void toPPTY(NSBinPptxRW::CBinaryFileWriter* pWriter) const
			{
				if (Elem.is_init())
					Elem->toPPTY(pWriter);
			}

			void InitRun(RunBase* pRun)
			{
				Elem.reset(pRun);
			}

			virtual bool is_init() const {return (Elem.IsInit());};
			virtual std::wstring GetText() const{return Elem->GetText();}
			smart_ptr<RunBase> GetElem()
			{
				return Elem;
			}
			template<class T> AVSINLINE const bool	is() const	{ return Elem.is<T>(); }
			template<class T> AVSINLINE T&			as()		{ return Elem.as<T>(); }
			template<class T> AVSINLINE const T&	as() const 	{ return Elem.as<T>(); }

		private:
			smart_ptr<RunBase> Elem;
		protected:
			virtual void FillParentPointersForChilds(){};
		public:
			virtual void SetParentPointer(const WrapperWritingElement* pParent){if(is_init()) Elem->SetParentPointer(pParent);}
		};
	} // namespace Logic
} // namespace PPTX

#endif // PPTX_LOGIC_RUNELEM_INCLUDE_H
