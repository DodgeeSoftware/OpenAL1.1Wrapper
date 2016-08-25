/**
  * @file   Sound.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  Sound uses a SoundBuffer and a Source to play audio
*/

#ifndef SOUND_H
#define SOUND_H

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

// GAME AUDIO Includes
#include "Utils/OpenALUtils.h"
#include "Utils/OpenALVector2D.h"
#include "Utils/OpenALVector3D.h"
#include "Sound/SoundBuffer.h"
#include "Source/Source.h"

/** @class Sound
  * @brief An playable instance of a SoundBuffer
  * @detail Sources only come into existance when you call the play function.
  * Properties of a source are stored locally and used either while
  * a source is valid (aka playing) or initially set in the play function. **/
class Sound : public Source
{
    // ****************************
    // * CONSTRUCTOR / DESTRUCTOR *
    // ****************************
    public:
        //! Constructor
        Sound()
        {
            // Clear Name
            this->name.clear();
            // Rest pSoundBuffer pointer
            this->pSoundBuffer = 0;
        }
        //! Destructor
        virtual ~Sound() {}

    protected:
        //! Copy Constructor
        Sound(const Sound& other) {}

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        // Methods and functions

    protected:
        //! Sound Assignment operator
        Sound& operator=(const Sound& rhs) { return *this; }

    // ***********
    // * GENERAL *
    // ***********
    public:
        /** @brief Play **/
        virtual void play();
        /** @brief Update
          * @param dTime[in] time difference between the last
          * frame and this one **/
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
        // Methods and members

    // ********
    // * NAME *
    // ********
    public:
        /** @brief Get Name
          * @return name of this sound **/
        virtual std::string getName() { return this->name; }
        /** @brief Set Name
          * @param name[in] the name to call this sound **/
        virtual void setName(std::string name) { this->name = name; }
        /** @brief Is Named
          * @return true if the sound is named otherwise false **/
        virtual bool isNamed() { return (this->name.size() > 0); }
        /** @brief Clear Name **/
        virtual void clearName() { this->name.clear(); }

    protected:
        // unique name
        std::string name;

    // ****************
    // * SOUND BUFFER *
    // ****************
    public:
        /** @brief Get the SoundBuffer
          * @return The SoundBuffer for this Sound **/
        virtual const SoundBuffer* getSoundBuffer() const { return this->pSoundBuffer; }
        /** @brief Set the SoundBuffer
          * @param pSoundBuffer[in] The SoundBuffer this Sound will use **/
        virtual void setSoundBuffer(SoundBuffer* pSoundBuffer)
        {
            // Keep a local reference to our SoundBuffer
            this->pSoundBuffer = pSoundBuffer;
        }

    protected:
        // SoundBuffer
        SoundBuffer* pSoundBuffer;

//    // ****************
//    // * LUA BINDINGS *
//    // ****************
//    public:
//        //! Bind this class to a lua state
//        static void bindToLua(lua_State* pLuaState);
};

#endif // SOUND_H
