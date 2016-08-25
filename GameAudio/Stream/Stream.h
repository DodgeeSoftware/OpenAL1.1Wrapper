/**
  * @file   Stream.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  Stream provides the ability to load and buffer
  * audio files in real-time so that an entire file
  * need not be loaded. This massively decreases load time
*/

#ifndef STREAM_H
#define STREAM_H

// C++ Includes
#include <iostream>
#include <vector>

// libSndFile Includes
#include <sndfile.hh>

// OPENAL Includes
#include <al.h>
#include <alc.h>

// GAME AUDIO Includes
#include "Utils/OpenALUtils.h"
#include "Utils/OpenALVector2D.h"
#include "Utils/OpenALVector3D.h"
#include "Source/Source.h"

/** @class Stream
  * @brief A container around an OpenAL Source and a FileStream
  * @detail This class will open a file stream and read it little
  * by little creating buffers which are cycled to create seamless
  * audio (as opposed to Sound/Sound2D/Sound3D which have to load
  * SoundBuffers ) All formats supported by libsnd are supported.
  * I deliberatly don not support mp3 because it is a proprietary
  * format requiring royalites use ogg files instead **/
class Stream : public Source
{
    // ****************************
    // * CONSTRUCTOR / DESTRUCTOR *
    // ****************************
    public:
        //! Constructor
        Stream()
        {
            // Stream File
            this->pStreamFile = 0;
            // Sample Rate
            this->sampleRate = -1;
            // Channels
            this->channels = -1;
            // Filename
            this->filename.clear();
        }
        //! Destructor
        virtual ~Stream() {}

    protected:
        // Methods and members

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        // No functions

    protected:
        //! Stream Assignment operator
        Stream& operator=(const Stream& other) { return *this; }

    // ***********
    // * GENERAL *
    // ***********
    public:
        /** @brief Load Stream
          * @param filename[in] filename of the Sound to loade
          * @return true on success false on failure **/
        virtual bool load(std::string filename);
        /** @brief Play **/
        virtual void play();
        /** @brief Stop **/
        virtual void stop();
        /** @brief Pause **/
        virtual void pause();
        /** @brief Resume **/
        virtual void resume();
        /** @brief update Stream
          * @param dTime[in] difference between last frame and this one **/
        virtual void update(float dTime);
        /** @brief Clear **/
        virtual void clear();
        /** @brief Free **/
        virtual void free();

    protected:
        /** @brief Grab the next chunk of data and push it into buffer
          * @param buffer[in] buffer to push data into **/
        virtual bool stream(int buffer);

    protected:
        // Sound File
        SNDFILE* pStreamFile;
        // Buffers
        ALuint buffer[6]; // NUM_BUFFERS

    // ***********
    // * LOOPING *
    // ***********
    /* NOTE: we override the default loop functions here
        because a streaming source cannot loop, we handle
        looping when a stream comes to an end we stop/play
        it again */
    public:
        /** @brief Is Looping
          * @return true if is looping otherwise false **/
        virtual bool isLooping();
        /** @brief Set Loop Mode
          * @param mode[in] true to make the Stream loop, false to play once **/
        virtual void setLooping(bool mode);

    protected:
        // methods and members

    // ************
    // * CHANNELS *
    // ************
    public:
        /** @brief Get Channels
          * @return number of channels (1 for mono 2 for stereo) **/
        virtual int getChannels();

    protected:
        // channels
        int channels;

    // **************
    // * SAMPLERATE *
    // **************
    public:
        /** @brief Get SampleRate
          * @return sampleRate in htz (22050 or 44100) **/
        virtual int getSampleRate();

    protected:
        // sampleRate
        int sampleRate;

    // **********************
    // * FILENAME FUNCTIONS *
    // **********************
    public:
        /** @brief Get filename
          * @return filename the stream is playing **/
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

#endif // STREAM_H
