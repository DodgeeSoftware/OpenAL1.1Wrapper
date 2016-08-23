// ********************************
// * COMPANY: Dodgee Software     *
// * AUTHOR: Shem Taylor          *
// * Written 2016 Dodgee Software *
// * GPLv3                        *
// ********************************

#ifndef SOUND2D_H
#define SOUND2D_H

// C++ Includes
#include <limits>

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

// GAMEAUDIO Includes
#include "Utils/OpenALUtils.h"
#include "Utils/OpenALVector2D.h"
#include "Sound/SoundBuffer.h"
#include "Source/Source.h"
#include "Sound/Sound.h"

/** The Sound2D is a single instance of a playable SoundBuffer
        Sources only come into existance when you call the play function.
        Properties of a source are stored locally and used either while
        a source is valid (aka playing) or initially set in the play function. **/
class Sound2D : public Sound
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Constructor
        Sound2D() : Sound()
        {
            // Min Volume
            this->minVolume = 0.0f;
            // Max Volume
            this->maxVolume = 1.0f;
            // Position
            this->x = 0.0f;
            this->y = 0.0f;
            // Velocity
            this->xVelocity = 0.0f;
            this->yVelocity = 0.0f;
            // Direction
            this->xDirection = 0.0f;
            this->yDirection = 0.0f;
            // Cone
            this->innerConeAngle = 360.0f;
            this->outerConeAngle = 360.0f;
            this->outerConeGain = 0.0f;
            // Attenuation
            this->rollOff = 1.0f;
            this->referenceDistance = 1.0f;
            this->maxDistance = std::numeric_limits<float>::max();
        }
        //! Destructor
        virtual ~Sound2D() {}

    protected:
        //! Copy Constructor
        Sound2D(Sound2D& other) : Sound() {}

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        // Methods and members

    protected:
        //! Sound2D Assignment operator
        Sound2D& operator=(const Sound2D& other) { return *this; }

    // *********************
    // * GENERAL FUNCTIONS *
    // *********************
    public:
        //! Play
        virtual void play();
        //! Start
        virtual void start();
        //! Stop
        virtual void stop();
        //! Clear
        virtual void clear();
        //! Free
        virtual void free();

    protected:
        // Methods and members

    // *******************
    // * TRANSFORM STUFF *
    // *******************
    public:
        //! Get X
        virtual float getX();
        //! Get Y
        virtual float getY();
        //! Get Position
        virtual OpenALVector2D getPosition();
        //! Set Position
        virtual void setPosition(float x, float y);
        //! Set Position
        virtual void setPosition(OpenALVector2D v);
        //! Get X Velocity
        virtual float getXVelocity();
        //! Get Y Velocity
        virtual float getYVelocity();
        //! Get Velocity
        virtual OpenALVector2D getVelocity();
        //! Set Velocity
        virtual void setVelocity(float xVelocity, float yVelocity);
        //! Set Velocity
        virtual void setVelocity(OpenALVector2D velocity);

    protected:
        // X Position
        float x;
        // Y Position
        float y;
        // X Velocity
        float xVelocity;
        // Y Velocity
        float yVelocity;

    // *******************
    // * DIRECTION, CONE *
    // *******************
    public:
        //! Get Direction
        virtual OpenALVector2D getDirection();
        //! Set Direction
        virtual void setDirection(float xDirection, float yDirection);
        //! Set Direction
        virtual void setDirection(OpenALVector2D direction);
        //! Get Inner Cone Angle
        virtual float getInnerConeAngle();
        //! Set Inner Cone Angle
        virtual void setInnerConeAngle(float angle);
        //! Get Outer Cone Angle
        virtual float getOuterConeAngle();
        //! Set Outer Cone Angle
        virtual void setOuterConeAngle(float angle);
        //! Set Outer Cone Gain
        virtual void setOuterConeGain(float gain);

    protected:
        // xDirection
        float xDirection;
        // yDirection
        float yDirection;
        // Inner Cone Angle
        float innerConeAngle;
        // OuterConeAngle
        float outerConeAngle;
        // Outer Cone Gain
        float outerConeGain;

    // ***************
    // * ATTENUATION *
    // ***************
    public:
        //! Get RollOff
        virtual float getRollOff();
        //! Set RollOff
        virtual void setRollOff(float rollOff);
        //! Get Reference Distances
        virtual float getReferenceDistance();
        //! Set Reference Distances
        virtual void setReferenceDistance(float referenceDistance);
        //! Get Max Distance
        virtual float getMaxDistance();
        //! Set Max Distance
        virtual void setMaxDistance(float maxDistance);

    protected:
        // RollOff
        float rollOff;
        // Reference Distance
        float referenceDistance;
        // Max Distance
        float maxDistance;

    // **********************
    // * MIN AND MAX VOLUME *
    // **********************
    public:
        //! Get Min Volume (works on positional sources only)
        virtual float getMinVolume();
        //! Set Min Volume (works on positional sources only)
        virtual void setMinVolume(float minVolume);
        //! Get Max Volume (works on positional sources only)
        virtual float getMaxVolume();
        //! Set Max Volume (works on positional sources only)
        virtual void setMaxVolume(float maxVolume);

    protected:
        // Min Volumes
        float minVolume;
        // Max Volume
        float maxVolume;

//    // ****************
//    // * LUA BINDINGS *
//    // ****************
//    public:
//        //! Bind this class to a lua state
//        static void bindToLua(lua_State* pLuaState);
};

#endif // SOUND2D_H
