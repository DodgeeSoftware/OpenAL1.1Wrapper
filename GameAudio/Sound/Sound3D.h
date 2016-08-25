// ********************************
// * COMPANY: Dodgee Software     *
// * AUTHOR: Shem Taylor          *
// * Written 2016 Dodgee Software *
// * GPLv3                        *
// ********************************

#ifndef SOUND3D_H
#define SOUND3D_H

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
#include "Utils/OpenALVector3D.h"
#include "Sound/SoundBuffer.h"
#include "Source/Source.h"
#include "Sound/Sound.h"

/** @class Sound3D
  * @brief An playable instance of a SoundBuffer with 3D Spacial functions
  * @detail Sources only come into existance when you call the play function.
  * Properties of a source are stored locally and used either while
  * a source is valid (aka playing) or initially set in the play function. **/
class Sound3D : public Sound
{
    // ***************
    // * CONSTRUCTOR *
    // ***************
    public:
        //! Constructor
        Sound3D() : Sound()
        {
            // Min Volume
            this->minVolume = 0.0f;
            // Max Volume
            this->maxVolume = 1.0f;
            // Position
            this->x = 0.0f;
            this->y = 0.0f;
            this->z = 0.0f;
            // Velocity
            this->xVelocity = 0.0f;
            this->yVelocity = 0.0f;
            this->zVelocity = 0.0f;
            // Direction
            this->xDirection = 0.0f;
            this->yDirection = 0.0f;
            this->zDirection = 0.0f;
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
        virtual ~Sound3D() {}

    protected:
        //! Copy Constructor
        Sound3D(Sound3D& other) : Sound() {}

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        // Methods and members

    protected:
        //! Sound3D Assignment operator
        Sound3D& operator=(const Sound3D& other) { return *this; }

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
        //! Get Z
        virtual float getZ();
        //! Get Position
        virtual OpenALVector3D getPosition();
        //! Set Position
        virtual void setPosition(float x, float y, float z);
        //! Set Position
        virtual void setPosition(OpenALVector3D v);
        //! Get X Velocity
        virtual float getXVelocity();
        //! Get Y Velocity
        virtual float getYVelocity();
        //! Get Z Velocity
        virtual float getZVelocity();
        //! Get Velocity
        virtual OpenALVector3D getVelocity();
        //! Set Velocity
        virtual void setVelocity(float x, float y, float z);
        //! Set Velocity
        virtual void setVelocity(OpenALVector3D v);

    protected:
        // X Position
        float x;
        // Y Position
        float y;
        // Z Position
        float z;
        // X Velocity
        float xVelocity;
        // Y Velocity
        float yVelocity;
        // Z Velocity
        float zVelocity;

    // *******************
    // * DIRECTION, CONE *
    // *******************
    public:
        //! Get Direction
        virtual OpenALVector3D getDirection();
        //! Set Direction
        virtual void setDirection(float xDirection, float yDirection, float zDirection);
        //! Set Direction
        virtual void setDirection(OpenALVector3D direction);
        //! Get Inner Cone Angle
        virtual float getInnerConeAngle() { return this->innerConeAngle; }
        //! Set Inner Cone Angle
        virtual void setInnerConeAngle(float angle);
        //! Get Outer Cone Angle
        virtual float getOuterConeAngle() { return this->outerConeAngle; }
        //! Set Outer Cone Angle
        virtual void setOuterConeAngle(float angle);
        //! Set Outer Cone Gain
        virtual void setOuterConeGain(float gain);

    protected:
        // xDirection
        float xDirection;
        // yDirection
        float yDirection;
        // zDirection
        float zDirection;
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

#endif // SOUND3D_H
