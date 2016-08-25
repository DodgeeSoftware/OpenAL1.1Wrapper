/**
  * @file   Source.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  Source is a small container around an OpenAL Source
  * and forms the base class for other clases which emitt audio
*/

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

/** @class Source
  * @brief A container around an OpenAL Source
  * @detail The Source Class is a wrapper around a single OpenAL source and
  * all of the functions that operate on a source. It brings common
  * source functions into one base interface
  * it **/
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
        /** @brief Play **/
        virtual void play();
        /** @brief Update
          * @param dTime[in] the difference between the last frame
          * and this one **/
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

    public:
        /** @brief Is the Source Playing
          * @return true if Source is currently playing otherwise false **/
        virtual bool isPlaying() ;
        /** @brief Is Paused
          * @return true if the Source is paused **/
        virtual bool isPaused();
        /** @brief Set Paused
          * @param state[in] true to pause false to resume **/
        virtual void setPaused(bool state);
        /** @brief Get Volume
          * @return volume **/
        virtual int getVolume();
        /** @brief Set Volume
          * @param volumep[in] the volume in range 0 - 255 */
        virtual void setVolume(int volume);
        /** @brief Is Mute
          * @return true if is muted false otherwise **/
        virtual bool isMute();
        /** @brief Set Mute Flag
          * @param state[in] true to mute false to unmute **/
        virtual void setMute(bool state);
        /** @brief Mute **/
        virtual void mute();
        /** @brief unmute **/
        virtual void unmute();
        /** @brief Is Looping
          * @return true if is looping false otherwise **/
        virtual bool isLooping();
        /** @brief Set Loop Mode
          * @param state[in] true to loop false to play o nce **/
        virtual void setLooping(bool mode);
        /** @brief Get Pitch
          * @return pitch **/
        virtual float getPitch();
        /** @brief Set Pitch
          * @param pitch[in] pitch **/
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
