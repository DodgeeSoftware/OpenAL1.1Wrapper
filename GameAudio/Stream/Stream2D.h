// ********************************
// * COMPANY: Dodgee Software     *
// * AUTHOR: Shem Taylor          *
// * Written 2016 Dodgee Software *
// * GPLv3                        *
// ********************************

#ifndef STREAM2D_H
#define STREAM2D_H

// C++ Includes
#include <iostream>
#include <vector>
#include <limits>

// libSndFile Includes
#include <sndfile.hh>

// OPENAL Includes
#include <al.h>
#include <alc.h>

// GAMEAUDIO Includes
#include "Utils/OpenALUtils.h"
#include "Utils/OpenALVector2D.h"
#include "Stream/Stream.h"

/** @class Stream2D
  * @brief A container around an OpenAL Source with positin functions
  * and a FileStream
  * @detail This class will open a file stream and read it little
  * by little creating buffers which are cycled to create seamless
  * audio (as opposed to Sound/Sound2D/Sound3D which have to load
  * SoundBuffers ) All formats supported by libsnd are supported.
  * I deliberatly don not support mp3 because it is a proprietary
  * format requiring royalites use ogg files instead **/
class Stream2D : public Stream
{
    // ****************************
    // * CONSTRUCTOR / DESTRUCTOR *
    // ****************************
    public:
        //! Constructor
        Stream2D() : Stream()
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
        virtual ~Stream2D() {}

    protected:
        //! Copy Constructor
        Stream2D(Stream2D& other) : Stream() {}

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        // No functions

    protected:
        //! Stream2D Assignment operator
        Stream2D& operator=(const Stream2D& other) { return *this; }

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
        //! Get Velocity
        virtual void setVelocity(OpenALVector2D v);

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
        virtual float getReferenceDistances();
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

#endif // STREAM2D_H
