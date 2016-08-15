// ********************************
// * COMPANY: Dodgee Software     *
// * AUTHOR: Shem Taylor          *
// * Written 2016 Dodgee Software *
// * GPLv3                        *
// ********************************

#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

// C++ Includes
#include <iostream>
#include <string>
#include <vector>
#include <map>

// libSndFile Includes
#include <sndfile.hh>

// OPENAL Includes
#include <al.h>
#include <alc.h>

// GAME AUDIO Includes
#include "OpenALUtils.h"
#include "LibXMPUtils.h"
#include "SoundBuffer.h"

/** The AudioManager loads SoundBuffer Objects from disc and maintains them
    for reuse in a map, matching the filename to the sound buffer. The ensures
    we only load each sound once **/
class AudioManager
{
    // ****************************
    // * CONSTRUCTOR / DESTRUCTOR *
    // ****************************
    public:
        //! Constructor
        AudioManager()
        {
            this->soundBufferMap.clear();
        }
        //! Destructor
        virtual ~AudioManager() {}

    protected:

    // **************************
    // * SOUND BUFFER FUNCTIONS *
    // **************************
    public:
        //! Get SoundBuffer
        virtual SoundBuffer* getSoundBuffer(std::string filename);
        //! Get SoundBuffer
        virtual SoundBuffer* getSoundBuffer(std::string filename, bool addToMap);

    public:
        //! Clear
        virtual void clear();

    protected:
        // Map for our SoundBuffers
        std::map<std::string, SoundBuffer*> soundBufferMap;

    // *********************
    // * UTILITY FUNCTIONS *
    // *********************
    public:
        //! Get relative path from filename
        virtual std::string getLocalPath(std::string filename)
        {
            std::string relativePath = filename;
            unsigned int pos = relativePath.find_last_of('/');
            if (pos == std::string::npos)
                return std::string();
            relativePath = relativePath.substr(0, pos + 1);
            return relativePath;
        }
        //! Convert a string to upper case
        virtual std::string toUpperCase(std::string text)
        {
            std::string uppercase(text);
            for (std::string::iterator p = uppercase.begin(); p != uppercase.end(); p++)
                *p = std::toupper(*p);
            return uppercase;
        }
        //! Convert a string to lower case
        virtual std::string toLowerCase(std::string text)
        {
            std::string uppercase(text);
            for (std::string::iterator p = uppercase.begin(); p != uppercase.end(); p++)
                *p = std::tolower(*p);
            return uppercase;
        }
        //! Convert a bool to a string
        virtual std::string convertBoolToString(bool value)
        {
            return (value == true) ? "TRUE": "FALSE";
        }
        //! Convert a string to a bool
        virtual bool convertStringToBool(std::string value)
        {
            return (this->toUpperCase(value) == "TRUE") ? true: false;
        }

    protected:
        // Methods and Members
};

#endif // AUDIOMANAGER_H
