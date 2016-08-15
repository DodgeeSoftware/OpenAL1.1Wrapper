// ********************************
// * COMPANY: Dodgee Software     *
// * AUTHOR: Shem Taylor          *
// * Written 2016 Dodgee Software *
// * GPLv3                        *
// ********************************

#ifndef LIBXMPUTILS_H
#define LIBXMPUTILS_H

// XMP Includes
#include <xmp.h>

namespace Utils
{
    //! Convert an AL Error Enumeration into a readable String
    inline extern std::string getLibXMPErrorString(int errorCode)
    {
        switch(errorCode)
        {
            case XMP_ERROR_INTERNAL:
            {
                return std::string("XMP_ERROR_INTERNAL (Internal Error)");
                break;
            }
            case XMP_ERROR_FORMAT:
            {
                return std::string("XMP_ERROR_FORMAT (Unsupported module format)");
                break;
            }
            case XMP_ERROR_LOAD:
            {
                return std::string("XMP_ERROR_LOAD (Error loading file)");
                break;
            }
            case XMP_ERROR_DEPACK:
            {
                return std::string("XMP_ERROR_DEPACK (Error depacking file)");
                break;
            }
            case XMP_ERROR_SYSTEM:
            {
                return std::string("XMP_ERROR_SYSTEM (System error)");
                break;
            }
            case XMP_ERROR_INVALID:
            {
                return std::string("XMP_ERROR_INVALID (Invalid Parameter)");
                break;
            }
            case XMP_ERROR_STATE:
            {
                return std::string("XMP_ERROR_STATE (Invalid player state)");
                break;
            }
            default:
            {
                return std::string("XMP_UNKNOWN_ERROR");
                break;
            }
        }
    }
}

#endif // LIBXMPUTILS_H
