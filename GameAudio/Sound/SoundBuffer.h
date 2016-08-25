// ********************************
// * COMPANY: Dodgee Software     *
// * AUTHOR: Shem Taylor          *
// * Written 2016 Dodgee Software *
// * GPLv3                        *
// ********************************

#ifndef SOUNDBUFFER_H
#define SOUNDBUFFER_H

// C++ Includes
#include <string>

// OPENAL Includes
#include <al.h>
#include <alc.h>

//// LUA AND LUABIND Includes
//extern "C"
//{
//    #include <lua.h>
//    #include <lualib.h>
//    #include <lauxlib.h>
//}
//#include <luabind/luabind.hpp>

/** @class SoundBuffer
  * @brief A container around an OpenAL AudioBuffer
  * @detail AudioBuffers are PCM Data and this wrapper
  * uses libsndfile to extract our PCM Data and create
  * an OpenAL AudioBuffer. We Pass this Object to a
  * Sound, Sound2D or Sound3D class so that we can play
  * it
**/
class SoundBuffer
{
    // ****************************
    // * CONSTRUCTOR / DESTRUCTOR *
    // ****************************
    public:
        //!  Constructor
        SoundBuffer()
        {
            // BufferID
            this->bufferID = -1;
            // Frequency
            this->frequency = -1;
            // Size of the Buffer in bytes
            this->size = -1;
            // Stero 2 or mono 1
            this->channels = 2;
            // Bits
            this->bits = 16;
            // Filename
            this->filename.clear();
        }
        //! Destructor
        virtual ~SoundBuffer()
        {
            // If the Buffer is still valid
            if (alIsBuffer(this->bufferID) == true)
            {
                // Delete the Buffer
                alDeleteBuffers(1, &(this->bufferID));
                // Reset the Buffer ID
                this->bufferID = -1;
            }
        }

    protected:
        //! Copy Constructor
        SoundBuffer(const SoundBuffer&) {}

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        // Members and methods

    protected:
        //! SoundBuffer Assignment operator
        SoundBuffer& operator=(const SoundBuffer& other) { return *this; }

    // **********************
    // * FILENAME FUNCTIONS *
    // **********************
    public:
        //! Get filename
        virtual std::string getFilename() { return this->filename.c_str(); }
        //! Set filename
        virtual void setFilename(std::string filename) { this->filename = filename; }

    protected:
        // Sound filename
        std::string filename;

    // **********
    // * BUFFER *
    // **********
    public:
        //! Get Frequency
        virtual int getFrequency() { return this->frequency; }
        //! Set Frequecy
        virtual void setFrequency(int frequency) { this->frequency = frequency; }
        //! Size of the Buffer in Bytes
        virtual int getSize() { return this->size; }
        //! Set Size of the Buffer in Bytes
        virtual void setSize(int size) { this->size = size; }
        //! Get Channels
        virtual int getChannels() { return this->channels; }
        //! Set Channels
        virtual void setChannels(int channels) { this->channels = channels; }
        //! Get Bits
        virtual int getBits() { return this->bits; }
        //! Set Bits
        virtual void setBits(int bits) { this->bits = bits; }

    public:
        //! Get BufferID
        virtual const ALuint getBufferID() const { return this->bufferID; }
        //! Set BufferID
        virtual void setBufferID(ALuint bufferID) { this->bufferID = bufferID; }

    protected:
        // BUffer ID
        ALuint bufferID;
        // Frequency
        int frequency;
        // Size in Bytes
        int size;
        // Number of channels 1 for mono, 2 for stereo
        int channels;
        // Bits
        int bits;

//    // ****************
//    // * LUA BINDINGS *
//    // ****************
//    public:
//        //! Bind this class to a lua state
//        static void bindToLua(lua_State* pLuaState);
};

#endif // SOUNDBUFFER_H
