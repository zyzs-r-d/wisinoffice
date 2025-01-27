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

#include <string>
#include <deque>
#include <fstream>
#include <vector>
#include <list>

#if defined(_WIN32) || defined (_WIN64)
	#include <direct.h>
    #include <windows.h>
#endif

#include "OfficeUtilsCommon.h"
#include "../../DesktopEditor/common/Types.h"

using namespace std;

#include "zlib-1.2.11/contrib/minizip/unzip.h"
#include "zlib-1.2.11/contrib/minizip/zip.h"
#if defined(_WIN32) || defined (_WIN64)
	#include "zlib-1.2.11/contrib/minizip/iowin32.h"
#endif
#include <zlib.h>

namespace ZLibZipUtils
{
  zipFile zipOpenHelp(const wchar_t* filename);
  unzFile unzOpenHelp(const wchar_t* filename);

  int ZipDir( const WCHAR* dir, const WCHAR* outputFile, const OnProgressCallback* progress, bool sorted = false, int method = Z_DEFLATED, int compressionLevel = -1, bool bDateTime = false);
  int ZipFile( const WCHAR* inputFile, const WCHAR* outputFile, int method = Z_DEFLATED, int compressionLevel = -1, bool bDateTime = false );
  bool ClearDirectory( const WCHAR* dir, bool delDir = false );
  int UnzipToDir( const WCHAR* zipFile, const WCHAR* unzipDir, const OnProgressCallback* progress, const WCHAR* password = NULL, bool opt_extract_without_path = false, bool clearOutputDirectory = false );
  int UncompressBytes( BYTE* destBuf, ULONG* destSize, const BYTE* sourceBuf, ULONG sourceSize );
  int CompressBytes( BYTE* destBuf, ULONG* destSize, const BYTE* sourceBuf, ULONG sourceSize, SHORT level );
  
  bool IsArchive(const WCHAR* filename);
  bool IsFileExistInArchive(const WCHAR* zipFile, const WCHAR* filePathInZip);
  bool LoadFileFromArchive(const WCHAR* zipFile, const WCHAR* filePathInZip, BYTE** fileInBytes, ULONG& nFileSize);
  bool ExtractFiles(const WCHAR* zip_file_path, const ExtractedFileCallback& callback, void* pParam);
  bool CompressFiles(const WCHAR* zip_file_path, const RequestFileCallback& callback, void* pParam, int compression_level);
  bool GetFilesSize(const WCHAR* zip_file_path, const std::wstring& searchPattern, ULONG64& nCommpressed, ULONG64& nUncommpressed);
}
