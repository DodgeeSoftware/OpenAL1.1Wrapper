/**
  * @file   SoundBuffer.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  SoundBuffer is a small container around an OpenAL Audio buffer
  * used by Sound, Sound2D and Sound3D to create playable instances
  * of loaded audio buffers
*/

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
        /** @brief Get filename
          * @return The filename of this SoundBuffer **/
        virtual std::string getFilename() { return this->filename.c_str(); }
        /** @brief Set filename
          * @param filename[in[ The Filename for this SoundBuffer **/
        virtual void setFilename(std::string filename) { this->filename = filename; }

    protected:
        // Sound filename
        std::string filename;

    // **********
    // * BUFFER *
    // **********
    public:
        /** @brief Get Frequency
          * @return The Frequency of this SoundBuffer **/
        virtual int getFrequency() { return this->frequency; }
        /** @brief Set Frequecy
          * @param frequency[in] The Frequenec of this SoundBuffer **/
        virtual void setFrequency(int frequency) { this->frequency = frequency; }
        /** @brief Size of the Buffer in Bytes
          * @return The size, in bytes, of the SoundBuffer **/
        virtual int getSize() { return this->size; }
        /** @brief Set Size of the Buffer in Bytes
          * @param size[in[ the size of the Buffer in bytes **/
        virtual void setSize(int size) { this->size = size; }
        /** @brief Get Channels
          * @return number of channels (1 for mono and 2 for stereo) **/
        virtual int getChannels() { return this->channels; }
        /** @brief Set Channels
          * @param channels[in] number of channels (1 for mono 2 for stereo) **/
        virtual void setChannels(int channels) { this->channels = channels; }
        /** @brief Get Bits
          * @return bits **/ // TODO: I want some documentation on this
        virtual int getBits() { return this->bits; }
        /** @brief Set Bits
          * @param bits[in] bits **/ // TODO: I want some documentation on this
        virtual void setBits(int bits) { this->bits = bits; }

    public:
        /** @brief Get BufferID
          * @return Buffer ID **/
        virtual const ALuint getBufferID() const { return this->bufferID; }
        /** @brief Set BufferID
          * @param BufferID **/
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
