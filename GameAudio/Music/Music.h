/**
  * @file   Music.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  Music streams a tracker file (xm, s3m, it, mod) from disk
*/

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

/** @class Music
  * @brief A Container for a Tracker Music File (XM, S3M, MOD, IT, and others supported by libxmp)
  * @detail The Music Class is a small container for playing
  * instances of tracker files **/
class Music : public Source
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Constructor
        Music()
        {
            // Make our context
            this->context = xmp_create_context();
            // Filename
            this->filename.clear();
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
        /** @brief Load from File
          * @param filename[in] the path of the tracker music file
          * to load
          * @return true on success and false on failure **/
        virtual bool load(std::string filename);
        /** @brief Load from Buffer
          * @param pBuffer[in] A pointer to a space on the heap full of a cached tracker file
          * @param size[in] The size of the data to read from the heap in bytes **/
        virtual bool load(void* pBuffer, long size);
        // /** @brief Load from FILE Object
        //   * @param pFile[in] pointer to a cstyle file
        //   * @param size[in] **/
        // virtual bool load(FILE* pFile, long size);
        /** @brief Play **/
        virtual void play();
        /** @brief Play
          * @param filename
          * @return true on success, false on failure **/
        virtual bool play(std::string filename);
        /** @brief Seek
          * @param time[in] time to seek to **/
        virtual int seek(int time);
        /** @brief Set Position
          * @param pos[in] sample position to seek to **/
        virtual int setPosition(int pos);
        /** @brief Update
          * @param dTime[in] dTime is the difference between
          * the last frame and this frame **/
        virtual void update(float dTime);
        /** @brief Start **/
        virtual void start();
        /** @brief Stop **/
        virtual void stop();
        /** @brief Pause **/
        virtual void pause();
        /** @brief Resume **/
        virtual void resume();
        /** @brief Clear **/
        virtual void clear();
        /** @brief Free **/
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
        /** @brief Get filename
          * @return the filename **/
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
