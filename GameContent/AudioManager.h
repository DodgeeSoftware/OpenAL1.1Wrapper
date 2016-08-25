// ********************************
// * COMPANY: Dodgee Software     *
// * AUTHOR: Shem Taylor          *
// * Written 2016 Dodgee Software *
// * GPLv3                        *
// ********************************

/**
 * @file   AudioManager.h
 * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
 * @date   August, 2016
 * @brief  Allows Sound/Sound2D/Sound3D Objects to use instances of SoundBuffers
 *
 * Detailed description of file.
 */

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

/** @class AudioManager
  * @brief A simple class for loading and keeping track of Sound files
  * @detail The AudioManager loads SoundBuffer Objects from disk and maintains them
  * for reuse in a map, matching the filename to the sound buffer. The ensures
  * we only load each sound once
**/
class AudioManager
{
    // ****************************
    // * CONSTRUCTOR / DESTRUCTOR *
    // ****************************
    public:
        //! Constructor
        AudioManager()
        {
            // Clear SoundBufferMap
            this->soundBufferMap.clear();
        }
        //! Destructor
        virtual ~AudioManager() {}

    protected:
        //! Copy Constructor
        AudioManager(AudioManager& other) {}

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        // Members and methods

    protected:
        // Members and methods

    // **************************
    // * SOUND BUFFER FUNCTIONS *
    // **************************
    public:
        /** @brief The Get SoundBuffer function uses a hashtable to associate a filename with an instance of a SoundBuffer.
          * If a SoundBuffer isn't associated with a key value, the function will load the a SoundBuffer from file
          * and associate it with that filename.
          * @param filename The path to an audio file (WAV, OGG, SGI, DEC, AU, SND, AIFF, AIFC, RAW, IFF,  SVX, VOC, W64, MAT4, MAT5, PVF, XI, HTK, CAF, SD2, FLAC)
          * @return On success the function returns a SoundBuffer otherwise 0
        **/
        virtual SoundBuffer* getSoundBuffer(std::string filename);
        /** @brief The Get SoundBuffer function uses a hashtable to associate a filename with an instance of a SoundBuffer.
          * If a SoundBuffer isn't associated with a key value, the function will load the a SoundBuffer from file
          * and associate it with that filename. This variation allows us to load a SoundBuffer without adding it to the hashtable
          * @param filename The path to an audio file (WAV, OGG, SGI, DEC, AU, SND, AIFF, AIFC, RAW, IFF,  SVX, VOC, W64, MAT4, MAT5, PVF, XI, HTK, CAF, SD2, FLAC)
          * @param addToMap A flag which allows a SoundBuffer to be loaded but not managed by the AudioManager (i.e. not associated with this filename)
          * @return On success the function returns a SoundBuffer otherwise 0
        **/
        virtual SoundBuffer* getSoundBuffer(std::string filename, bool addToMap);

    public:
        /** @brief The Clear function will clean up all the memory associated with our SoundBuffers and also
          * empty our hashtable
        **/
        virtual void clear();

    protected:
        // Map for our SoundBuffers
        std::map<std::string, SoundBuffer*> soundBufferMap;

    // *********************
    // * UTILITY FUNCTIONS *
    // *********************
    public:
        // Methods and members

    protected:
        /** @brief The GetRelativePath function extracts the name of a file and discards path information
          * @param filename The filename that we wish to discard the path from
          * @return A string representing the filename without the filepath
        **/
        virtual std::string getLocalPath(std::string filename);
        /** @brief The toUpperCase function cconverts a string to upper case
          * @param text The String we want to make upper case
          * @return An upper case version of our text
        **/
        virtual std::string toUpperCase(std::string text);
        /** @brief The toLowerCase function converts a string to lower case
          * @param text The String we want to make lower case
          * @return A lower case version of our text
        **/
        virtual std::string toLowerCase(std::string text);
        /** @brief The convertBoolToString method converts a bool to a string
          * @param value The value we want to convert to string
          * @return A string representing our boolean variable (always uppercase)
        **/
        virtual std::string convertBoolToString(bool value);
        /** @brief The convertStringToBool method converts a string to a bool
          * @param value The value we want to convert to a bool. (not case sensitive)
          * @return A Boolean representing our string variable
        **/
        virtual bool convertStringToBool(std::string value);

    protected:
        // Methods and Members
};

#endif // AUDIOMANAGER_H
