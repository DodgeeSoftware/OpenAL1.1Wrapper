// ********************************
// * COMPANY: Dodgee Software     *
// * AUTHOR: Shem Taylor          *
// * Written 2016 Dodgee Software *
// * GPLv3                        *
// ********************************

#ifndef MUSIC_H
#define MUSIC_H

// C++ Includes
#include <string>
#include <iostream>

// OPENAL Includes
#include <al.h>
#include <alc.h>

// XMP Includes
#include <xmp.h>

//// LUA AND LUABIND Includes
//extern "C"
//{
//    #include <lua.h>
//    #include <lualib.h>
//    #include <lauxlib.h>
//}
//#include <luabind/luabind.hpp>

// GAMEAUDIO Includes
#include "OpenALGlobals.h"
#include "Utils/LibXMPUtils.h"
#include "Source/Source.h"

/** The Music Class is a small container for playing
    instances of tracker files **/
class Music : public Source
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Constructor
        Music()
        {
//            // Default source value
//            this->source = -1;
            // Make our context
            this->context = xmp_create_context();
            // Filename
            this->filename.clear();
//            // Playing Flag
//            this->playingFlag = false;
//            // Pause Flag
//            this->pauseFlag = false;
//            // Mute Flag
//            this->muteFlag = false;
//            // Loop Flag
//            this->loopFlag = true;
//            // Volume
//            this->volume = 1.0f;
//            // Pitch
//            this->pitch = 1.0f;
        }
        //! Destructor
        virtual ~Music()
        {
            // Destroy our context
            xmp_free_context(this->context);
        }

    protected:

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        // No functions

    protected:
        //! Music Assignment operator
        Music& operator=(const Music& other) { return *this; }

    // *********************
    // * GENERAL FUNCTIONS *
    // *********************
    public:
        //! Load from File
        virtual bool load(std::string filename);
        //! Load from Buffer
        virtual bool load(void* pBuffer, long size);
        //! Load from FILE Object
        virtual bool load(FILE* pFile, long size);
        //! Play
        virtual void play();
        //! Play
        virtual bool play(std::string filename);
        //! Seek
        virtual int seek(int time);
        //! Set Position
        virtual int setPosition(int pos);
        //! Update
        virtual void update(float dTime);
        //! Start
        virtual void start();
        //! Stop
        virtual void stop();
        //! Pause
        virtual void pause();
        //! Resume
        virtual void resume();
        //! Clear
        virtual void clear();
        //! Free
        virtual void free();

    protected:
        // Buffers
        ALuint buffer[6]; // NUM_BUFFERS
        // xmp context
        xmp_context context;
        // Module information
        xmp_module_info moduleInfo;

    // **********************
    // * FILENAME FUNCTIONS *
    // **********************
    public:
        //! Get filename
        virtual std::string getFilename() { return this->filename.c_str(); }

    protected:
        // Sound filename
        std::string filename;

//    // ****************
//    // * LUA BINDINGS *
//    // ****************
//    public:
//        //! Bind this class to a lua state
//        static void bindToLua(lua_State* pLuaState);
};

#endif // MUSIC_H
