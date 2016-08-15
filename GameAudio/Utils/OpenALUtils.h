// ********************************
// * COMPANY: Dodgee Software     *
// * AUTHOR: Shem Taylor          *
// * Written 2016 Dodgee Software *
// * GPLv3                        *
// ********************************

#ifndef OPENALUTILS_H
#define OPENALUTILS_H

// C++ Includes
#include <string>

// OPENAL Includes
#include <al.h>
#include <alc.h>

namespace Utils
{
    //! Convert an AL Error Enumeration into a readable String
    inline extern std::string getALErrorString(int errorCode)
    {
        switch(errorCode)
        {
            case AL_NO_ERROR:
            {
                return "AL_NO_ERROR";
                break;
            }
            case AL_INVALID_NAME:
            {
                return "AL_INVALID_NAME";
                break;
            }
            case AL_INVALID_ENUM:
            {
                return "AL_INVALID_ENUM";
                break;
            }
            case AL_INVALID_VALUE:
            {
                return "AL_INVALID_VALUE";
                break;
            }
            case AL_INVALID_OPERATION:
            {
                return "AL_INVALID_OPERATION";
                break;
            }
            case AL_OUT_OF_MEMORY:
            {
                return "AL_OUT_OF_MEMORY";
                break;
            }
            default:
            {
                return "UNKNOWN_ERROR";
                break;
            }
        }
    }
    //! Convert an ALC Error Enumeration into a readable String
    inline extern std::string getALCErrorString(int errorCode)
    {
        switch(errorCode)
        {
            case ALC_NO_ERROR:
            {
                return "ALC_NO_ERROR";
                break;
            }
            case ALC_INVALID_DEVICE:
            {
                return "ALC_INVALID_DEVICE";
                break;
            }
            case ALC_INVALID_CONTEXT:
            {
                return "ALC_INVALID_CONTEXT";
                break;
            }
            case ALC_INVALID_ENUM:
            {
                return "ALC_INVALID_ENUM";
                break;
            }
            case ALC_INVALID_VALUE:
            {
                return "ALC_INVALID_VALUE";
                break;
            }
            case ALC_OUT_OF_MEMORY:
            {
                return "ALC_OUT_OF_MEMORY";
                break;
            }
            default:
            {
                return "UNKNOWN_ERROR";
                break;
            }
        }
    }
}

#endif // OPENALUTILS_H
