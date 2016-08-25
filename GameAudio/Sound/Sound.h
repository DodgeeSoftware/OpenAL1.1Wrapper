// ********************************
// * COMPANY: Dodgee Software     *
// * AUTHOR: Shem Taylor          *
// * Written 2016 Dodgee Software *
// * GPLv3                        *
// ********************************

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

    protected:
        // Methods and members

    // ********
    // * NAME *
    // ********
    public:
        //! Get Name
        virtual std::string getName() { return this->name; }
        //! Set Name
        virtual void setName(std::string name) { this->name = name; }
        //! Is Named
        virtual bool isNamed() { return (this->name.size() > 0); }
        //! Clear Name
        virtual void clearName() { this->name.clear(); }

    protected:
        // unique name
        std::string name;

    // ****************
    // * SOUND BUFFER *
    // ****************
    public:
        //! Get the SoundBuffer
        virtual const SoundBuffer* getSoundBuffer() const { return this->pSoundBuffer; }
        //! Set the SoundBuffer
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
