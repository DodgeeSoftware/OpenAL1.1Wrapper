/**
  * @file   Sound3D.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  Sound uses a SoundBuffer and a Source to play 3D positional audio
*/

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
        /** @brief Play **/
        virtual void play();
        /** @brief Start **/
        virtual void start();
        /** @brief Stop **/
        virtual void stop();
        /** @brief Clear **/
        virtual void clear();
        /** @brief Free **/
        virtual void free();

    protected:
        // Methods and members

    // *******************
    // * TRANSFORM STUFF *
    // *******************
    public:
        /** @brief Get X
          * @return X Position **/
        virtual float getX();
        /** @brief Get Y
          * @return Y Position **/
        virtual float getY();
        /** @brief Get Z
          * @return Z Position **/
        virtual float getZ();
        /** @brief Get Position
          * @return Position as an OpenALVector3D **/
        virtual OpenALVector3D getPosition();
        /** @brief Set Position
          * @param x[in] horizontal position
          * @param y[in] vertical position
          * @param z[in] depth position **/
        virtual void setPosition(float x, float y, float z);
        /** @brief Set Position
          * @param v[in] the position as an OpenALVector **/
        virtual void setPosition(OpenALVector3D v);
        /** @brief Get X Velocity
          * @return horizontal velocity **/
        virtual float getXVelocity();
        /** @brief Get Y Velocity
          * @return vertical velocity **/
        virtual float getYVelocity();
        /** @brief Get Z Velocity
          * @return depth velocity **/
        virtual float getZVelocity();
        /** @brief Get Velocity
          * @return the velocity as an OpenALVector3D **/
        virtual OpenALVector3D getVelocity();
        /** @brief Set Velocity
          * @param horizontal part of the velocity vector
          * @param vertical part of the velocity vector
          * @param depth part of the velocity vector **/
        virtual void setVelocity(float x, float y, float z);
        /** @brief Set Velocity
          * @param v[in] velocity vector as an OpenALVector3D **/
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
        /** @brief Get Direction
          * @return Directional Vector as an OpenALVector3D **/
        virtual OpenALVector3D getDirection();
        /** @brief Set Direction
          * @param xDirection[in] horizontal part of the direction vector
          * @param yDirection[in] vertical part of the direction vector
          * @param zDirection[in] depth part of the direction vector **/
        virtual void setDirection(float xDirection, float yDirection, float zDirection);
        /** @brief Set Direction
          * @param direction[in] direction vector as an OpenALVector3D **/
        virtual void setDirection(OpenALVector3D direction);
        /** @brief Get Inner Cone Angle
          * @return Inner Cone Angle **/ // TODO: Note sure if this is in radians or degrees
        virtual float getInnerConeAngle() { return this->innerConeAngle; }
        /** @brief Set Inner Cone Angle
          * @param angle[in] angle of the inner code **/ // TODO: Note sure if this is in radians or degrees
        virtual void setInnerConeAngle(float angle);
        /** @brief Get Outer Cone Angle
          * @return OuterConeAngle **/ // TODO: Note sure if this is in radians or degrees
        virtual float getOuterConeAngle() { return this->outerConeAngle; }
        /** @brief Set Outer Cone Angle
          * @param angle[in] Outer Cone Angle **/ // TODO: Note sure if this is in radians or degrees
        virtual void setOuterConeAngle(float angle);
        /** @brief Set Outer Cone Gain
          * @param gain[in] OuterConeGain **/
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
        /** @brief Get RollOff
          * @return rollOff **/
        virtual float getRollOff();
        /** @brief Set RollOff
          * @param rolloff[in] the Roll off to use **/ // TODO: better comment me from openal documentation
        virtual void setRollOff(float rollOff);
        /** @brief Get Reference Distances
          * @return reference distance */ // TODO: better comment me from openal documentation
        virtual float getReferenceDistance();
        /** @brief Set Reference Distances
          * @param referenceDistance[in] reference distance to use **/ // TODO: better comment me from openal documentation
        virtual void setReferenceDistance(float referenceDistance);
        /** @brief Get Max Distance
          * @return maxDistance **/ // TODO: better comment me from openal documentation
        virtual float getMaxDistance();
        /** @brief Set Max Distance
          * @param maxDistance[in] **/ // TODO: better comment me from openal documentation
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
        /** @brief Get Min Volume
          * @return minVolume **/
        virtual float getMinVolume();
        /** @brief Set Min Volume
          * @param minVolume[in] the minimum volume **/ // TODO: better comment me from openal documentation
        virtual void setMinVolume(float minVolume);
        /** @brief Get Max Volume
          * @return maxVolume **/
        virtual float getMaxVolume();
        /** @brief Set Max Volume
          * @param maxVolume[in] maxVolume **/ // TODO: better comment me from openal documentation
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
