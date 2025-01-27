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

#include "BiffRecord.h"
#include "../Biff_structures/BorderFillInfo.h"

namespace XLS
{
	class XFProp;
	class ExtProp;
	class CFRecord;
	class Font;

	class GlobalWorkbookInfo;
	typedef boost::shared_ptr<GlobalWorkbookInfo> GlobalWorkbookInfoPtr;

	class XF: public BiffRecord
	{
		BIFF_RECORD_DEFINE_TYPE_INFO(XF)
		BASE_OBJECT_DEFINE_CLASS_NAME(XF)
	public:
		XF(size_t& cell_xf_current_id, size_t& style_xf_current_id);
		~XF();

		BaseObjectPtr clone();
		
		void readFields(CFRecord& record);

		int serialize(std::wostream & stream);

		static const ElementType	type = typeXF;

		_UINT16		font_index;
		_UINT16		ifmt;
		
		_UINT16		ixfParent;

		bool fLocked;
		bool fHidden;
		bool fStyle;
		bool f123Prefix;

	//-----------------------------
		unsigned char	alc;
		bool			fWrap;
		unsigned char	alcV;
		bool			fJustLast;
		unsigned short	trot;
		unsigned char	cIndent;
		bool			fShrinkToFit;
		unsigned char	iReadOrder;
		
		bool			fAtrNum;
		bool			fAtrFnt;
		bool			fAtrAlc;
		bool			fAtrBdr;
		bool			fAtrPat;
		bool			fAtrProt;

		BorderInfo		border;
		FillInfo		fill;
		FontInfo		font;

		FillInfoExt		font_color;

		bool			fHasXFExt;
		bool			fsxButton;
	//------------------------------------------------------------------
		BiffStructurePtrVector ext_props;
		BiffStructurePtrVector xf_props;

		size_t border_x_id;
		size_t fill_x_id;
		size_t font_x_id;
		
		void Update(ExtProp* extProp); // xls ext style
		void Update(XFProp* xfProps); // xlsx style

		void RegisterFillBorderFont();
	//------------------------------------------------------------------------
		size_t&		cell_xf_current_id_;
		size_t&		style_xf_current_id_;
		int			ind_xf;	//for ext

		GlobalWorkbookInfoPtr	global_info;
	};

} // namespace XLS

