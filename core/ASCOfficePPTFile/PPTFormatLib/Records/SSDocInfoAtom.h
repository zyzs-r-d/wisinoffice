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
#include "../Reader/Records.h"

class CRecordSSDocInfoAtom : public CUnknownRecord
{
public:
	SColorAtom		m_oPenColor;
	_INT32			m_nRestartTime;
	short			m_nStartSlide;
	short			m_nEndSlide;
	std::wstring	m_pName;
	
	bool fAutoAdvance;
	bool fWillSkipBuilds;
	bool fUseSlideRange;
	bool fDocUseNamedShow;
	bool fBrowseMode;
	bool fKioskMode;
	bool fWillSkipNarration;
	bool fLoopContinuously;
	bool fHideScrollBar;

	CRecordSSDocInfoAtom()
	{
	}

	~CRecordSSDocInfoAtom()
	{
	}

	virtual void ReadFromStream(SRecordHeader & oHeader, POLE::Stream* pStream)
	{
		m_oHeader = oHeader;

		unsigned short flags;
		unsigned char nm[64];

		NSStreamReader::Read(pStream, m_oPenColor);
		m_nRestartTime	= StreamUtils::ReadLONG(pStream);
		m_nStartSlide	= StreamUtils::ReadSHORT(pStream);
		m_nEndSlide		= StreamUtils::ReadSHORT(pStream);

		pStream->read(nm, 64);
		m_pName = NSFile::CUtf8Converter::GetWStringFromUTF16((unsigned short*)nm, 32);

		flags = StreamUtils::ReadWORD(pStream);
		
		fAutoAdvance		= GETBIT(flags, 15);
		fWillSkipBuilds		= GETBIT(flags, 14);
		fUseSlideRange		= GETBIT(flags, 13);
		fDocUseNamedShow	= GETBIT(flags, 12);
		fBrowseMode			= GETBIT(flags, 11);
		fKioskMode			= GETBIT(flags, 10);
		fWillSkipNarration	= GETBIT(flags, 9);
		fLoopContinuously	= GETBIT(flags, 8);
		fHideScrollBar		= GETBIT(flags, 7);

		unsigned short unused = StreamUtils::ReadWORD(pStream);
	}

};