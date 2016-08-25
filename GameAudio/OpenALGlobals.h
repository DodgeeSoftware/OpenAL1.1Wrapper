// ********************************
// * COMPANY: Dodgee Software     *
// * AUTHOR: Shem Taylor          *
// * Written 2016 Dodgee Software *
// * GPLv3                        *
// ********************************

#ifndef OPENALGLOBALS_H
#define OPENALGLOBALS_H

// OPENAL Includes
#include <al.h>
#include <alc.h>

/** OpenALGlobals is a name space
    for our AudioWrapper **/
namespace OpenALGlobals
{
    extern float musicVolume;
    extern float soundVolume;
    extern bool muteFlag;
    extern int frequency;
}

#endif // OPENALGLOBALS_H
