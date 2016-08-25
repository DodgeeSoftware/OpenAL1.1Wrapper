/**
  * @file   OpenALGlobals.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  OpenALGlobals is a header that we store
  * device globals in such as mute, device frequency
  * sound and music volume
*/

#ifndef OPENALGLOBALS_H
#define OPENALGLOBALS_H

// OPENAL Includes
#include <al.h>
#include <alc.h>

/** OpenALGlobals is a name space
    for our AudioWrapper globals
    such as music/sound volume
    mute flag and device frequency **/
namespace OpenALGlobals
{
    extern float musicVolume;
    extern float soundVolume;
    extern bool muteFlag;
    extern int frequency;
}

#endif // OPENALGLOBALS_H
