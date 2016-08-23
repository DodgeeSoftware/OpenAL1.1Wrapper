// ********************************
// * COMPANY: Dodgee Software     *
// * AUTHOR: Shem Taylor          *
// * Written 2016 Dodgee Software *
// * GPLv3                        *
// ********************************

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

/** The Stream class is a container for streaming audio.
    Rather than prebuffering it only reads enough information
    for the next frame eliminating load time**/
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
        //! Load Stream
        virtual bool load(std::string filename);
        //! Play
        virtual void play();
        //! Stop
        virtual void stop();
        //! Pause
        virtual void pause();
        //! Resume
        virtual void resume();
        //! update Stream
        virtual void update(float dTime);
        //! Clear
        virtual void clear();
        //! Free
        virtual void free();

    protected:
        //! Grab the next chunk of data and push it into buffer
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
        //! Is Looping
        virtual bool isLooping();
        //! Set Loop Mode
        virtual void setLooping(bool mode);

    protected:
        // methods and members

    // ************
    // * CHANNELS *
    // ************
    public:
        //! Get Channels
        virtual int getChannels();

    protected:
        // channels
        int channels;

    // **************
    // * SAMPLERATE *
    // **************
    public:
        //! Get SampleRate
        virtual int getSampleRate();

    protected:
        // sampleRate
        int sampleRate;

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

#endif // STREAM_H
