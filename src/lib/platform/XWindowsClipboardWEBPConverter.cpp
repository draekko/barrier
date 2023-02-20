/*
 * barrier -- mouse and keyboard sharing utility
 * Copyright (C) 2012-2016 Symless Ltd.
 * Copyright (C) 2004 Chris Schoeneman
 *
 * This package is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * found in the file LICENSE that should have accompanied this file.
 *
 * This package is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "base/Log.h"
#include "platform/XWindowsClipboardWEBPConverter.h"

//
// XWindowsClipboardWEBPConverter
//

XWindowsClipboardWEBPConverter::XWindowsClipboardWEBPConverter(
                Display* display) :
    m_atom(XInternAtom(display, "image/webp", False))
{
    // do nothing
}

XWindowsClipboardWEBPConverter::~XWindowsClipboardWEBPConverter()
{
    // do nothing
}

IClipboard::EFormat
XWindowsClipboardWEBPConverter::getFormat() const
{
    return IClipboard::kWebp;
}

Atom
XWindowsClipboardWEBPConverter::getAtom() const
{
    return m_atom;
}

int
XWindowsClipboardWEBPConverter::getDataSize() const
{
    return 8;
}

std::string XWindowsClipboardWEBPConverter::fromIClipboard(const std::string& webpdata) const
{
    return webpdata;
}

std::string XWindowsClipboardWEBPConverter::toIClipboard(const std::string& webpdata) const
{
    // check WEBPF file header, veirfy if Big or Little Endian
    const UInt8* rawWEBPHeader = reinterpret_cast<const UInt8*>(webpdata.data());

    if (rawWEBPHeader[0] == 'R' && rawWEBPHeader[1] == 'I' && rawWEBPHeader[2] == 'F' && rawWEBPHeader[3] == 'F' &&
        rawWEBPHeader[8] == 'W' && rawWEBPHeader[9] == 'E' && rawWEBPHeader[10] == 'B' && rawWEBPHeader[11] == 'P' ) {
        LOG((CLOG_DEBUG2 "Prepare WEBP"));
        return webpdata;
    }

    return {};
}
