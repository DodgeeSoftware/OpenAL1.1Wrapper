// ********************************
// * COMPANY: Dodgee Software     *
// * AUTHOR: Shem Taylor          *
// * Written 2016 Dodgee Software *
// * GPLv3                        *
// ********************************

#ifndef SOURCE_H
#define SOURCE_H

// C++ Includes
#include <string>
#include <iostream>

// OPENAL Includes
#include <al.h>
#include <alc.h>

// GAMEAUDIO Includes
#include "OpenALGlobals.h"

/** The Source Class is a wrapper around a single source and
    all of the functions that operate on a source. It brings common
    source functions into one base interface **/
class Source
{
    // *****************************
    // * CONSTRUCTORS / DESTRUCTOR *
    // *****************************
    public:
        //! Constructor
        Source()
        {
            // Source
            this->source = -1;
            // Playing Flag
            this->playingFlag = false;
            // Pause flag
            this->pauseFlag = false;
            // Volume
            this->volume = 255;
            // Mute Flag
            this->muteFlag = false;
            // Set LoopFlag
            this->loopFlag = false;
            // Pitch
            this->pitch = 1.0f;
        }
        //! Destructor
        virtual ~Source()
        {
            // Make absolutely certain the source is destroyed with a music object
            if (this->source != - 1)
            {
                // Delete the Source
                alDeleteSources(1, &(this->source));
                // Reset the value of Source
                this->source = -1;
            }
        }

    protected:
        //! Copy Constructor
        Source(const Source& other) {}

    // *********************
    // * GENERAL FUNCTIONS *
    // *********************
    public:
        //! Play
        virtual void play();
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

    public:
        //! Is the Source Playing
        virtual bool isPlaying() ;
        //! Is Paused
        virtual bool isPaused();
        //! Set Paused
        virtual void setPaused(bool state);
        //! Get Volume
        virtual int getVolume();
        //! Set Volume
        virtual void setVolume(int volume);
        //! Is Mute
        virtual bool isMute();
        //! Set Mute Flag
        virtual void setMute(bool state);
        //! Mute
        virtual void mute();
        //! Unmute
        virtual void unmute();
        //! Is Looping
        virtual bool isLooping();
        //! Set Loop Mode
        virtual void setLooping(bool mode);
        //! Get Pitch
        virtual float getPitch();
        //! Set Pitch
        virtual void setPitch(float pitch);

    protected:
        // OpenAL Source (similar to audio channel)
        ALuint source;
        // Playing Flag
        bool playingFlag;
        // Paused Flag
        bool pauseFlag;
        // volume level
        int volume;
        // mute Flag
        bool muteFlag;
        // Loop Flag
        bool loopFlag;
        // Pitch
        float pitch;

//    // ****************
//    // * LUA BINDINGS *
//    // ****************
//    public:
//        //! Bind this class to a lua state
//        static void bindToLua(lua_State* pLuaState);
};

#endif // SOURCE_H
