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
#ifndef PPTX_WRAPPER_FILE_INCLUDE_H_
#define PPTX_WRAPPER_FILE_INCLUDE_H_

#include "../../Common/DocxFormat/Source/DocxFormat/File.h"
#include "Namespaces.h"
#include "FileMap.h"

#include "../Editor/BinWriters.h"

namespace PPTX
{
	class WrapperFile : public OOX::File
	{
	public:
		WrapperFile(OOX::Document *pMain) : OOX::File(pMain)
		{
			m_written = false;
			m_WrittenFileName = _T("");
		}
		virtual ~WrapperFile()
		{
		}

		virtual void read(const OOX::CPath& filename)
		{
			return;
		}
		virtual void read(const OOX::CPath&, FileMap& map) = 0;
		virtual void write(const OOX::CPath& filename, const OOX::CPath& directory, OOX::CContentTypes& content) const;

	protected:
		mutable bool			m_written;
		mutable OOX::CPath		m_WrittenFileName;
	public:
		bool GetWrittenStatus()const
		{
			return m_written;
		}
		void WrittenSetFalse()
		{
			m_written = false;
			m_WrittenFileName = _T("");
		}
		const OOX::CPath GetWrittenFileName()const
		{
			return m_WrittenFileName;
		}

		// PPTY format serialise
		virtual void fromPPTY(NSBinPptxRW::CBinaryFileReader* pReader)
		{
			pReader->SkipRecord();
		}
        virtual void toPPTY(NSBinPptxRW::CBinaryFileWriter* pWriter) const
		{
		}
		virtual void toXmlWriter(NSBinPptxRW::CXmlWriter* pWriter) const
		{
		}
	};
} // namespace PPTX

#endif // PPTX_WRAPPER_FILE_INCLUDE_H_