#include "Sound3D.h"

void Sound3D::play()
{
    // Play Our Sound (generates our source)
    Sound::play();
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Make sure co-ordinates are seen in world coords and not relative to the listner
    alSourcei(this->source, AL_SOURCE_RELATIVE, AL_FALSE);
    // Set MinVolume
    this->setMinVolume(this->minVolume);
    // Set MaxVolume
    this->setMaxVolume(this->maxVolume);
    // Set Position
    this->setPosition(this->x, this->y, this->z);
    // Set Velocity
    this->setVelocity(this->xVelocity, this->yVelocity, this->zVelocity);
    // Set Direction
    this->setDirection(this->xDirection, this->yDirection, this->zDirection);
    // Set Inner Cone Angle
    this->setInnerConeAngle(this->innerConeAngle);
    // Set Outer Cone Angle
    this->setOuterConeAngle(this->outerConeAngle);
    // Set Outer Cone Gain
    this->setOuterConeGain(this->outerConeGain);
    // Set RollOff
    this->setRollOff(this->rollOff);
    // Set Reference Distance
    this->setReferenceDistance(this->referenceDistance);
    // Set Max Distance
    this->setMaxDistance(this->maxDistance);
}

void Sound3D::start()
{
    // Play our Sound
    this->play();
}

void Sound3D::stop()
{
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Make sure co-ordinates are seen in world coords and not relative to the listner
    alSourcei(this->source, AL_SOURCE_RELATIVE, AL_FALSE);
    // Stop the Sound
    Sound::stop();
}

void Sound3D::clear()
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
    // Cone
    this->innerConeAngle = 360.0f;
    this->outerConeAngle = 360.0f;
    this->outerConeGain = 0.0f;
    // Attenuation
    this->rollOff = 1.0f;
    this->referenceDistance = 1.0f;
    // Validate the Source
    if (alIsSource(this->source) == AL_TRUE)
    {
        /* Make the source NOT relative to the position, velocity,
            cone and direction relative to the listener */
        alSourcei(this->source, AL_SOURCE_RELATIVE, AL_FALSE);
    }
    // Clear our Sound
    Sound::clear();
}

void Sound3D::free()
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
    // Cone
    this->innerConeAngle = 360.0f;
    this->outerConeAngle = 360.0f;
    this->outerConeGain = 0.0f;
    // Attenuation
    this->rollOff = 1.0f;
    this->referenceDistance = 1.0f;
    // Validate the Source
    if (alIsSource(this->source) == AL_TRUE)
    {
        /* Make the source NOT relative to the position, velocity,
            cone and direction relative to the listener */
        alSourcei(this->source, AL_SOURCE_RELATIVE, AL_FALSE);
    }
    // Free our Sound
    Sound::free();
}

float Sound3D::getX()
{
    // return x
    return this->x;
    /* NOTE: Could have used
        alGetSource3f(this->source, AL_POSITION, &x, &y, &z);
        but that would have been a poor design */
}

float Sound3D::getY()
{
    // return y
    return this->y;
    /* NOTE: Could have used
        alGetSource3f(this->source, AL_POSITION, &x, &y, &z);
        but that would have been a poor design */
}

float Sound3D::getZ()
{
    // return z
    return this->z;
    /* NOTE: Could have used
        alGetSource3f(this->source, AL_POSITION, &x, &y, &z);
        but that would have been a poor design */
}

OpenALVector3D Sound3D::getPosition()
{
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return OpenALVector3D(0.0f, 0.0f, 0.0f);
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    alGetSource3f(this->source, AL_POSITION, &x, &y, &z);
    // Return the Position
    return OpenALVector3D(x, y, z);
}

void Sound3D::setPosition(float x, float y, float z)
{
    // Set position
    this->x = x;
    this->y = y;
    this->z = z;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Make and initialise and array for the position
    float position[3] = {x, y, z};
    // Set the Position of the Source
    alSourcefv(this->source, AL_POSITION, &position[0]);
}

void Sound3D::setPosition(OpenALVector3D v)
{
    // Set Position
    this->setPosition(v.x, v.y, v.z);
}

float Sound3D::getXVelocity()
{
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return 0.0f;
    // Make and Initialise Velcotiy
    float xVelocity = 0.0f;
    float yVelocity = 0.0f;
    float zVelocity = 0.0f;
    alGetSource3f(this->source, AL_VELOCITY, &xVelocity, &yVelocity, &zVelocity);
    // Return xVelocity
    return xVelocity;
}

float Sound3D::getYVelocity()
{
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return 0.0f;
    // Make and Initialise Velcotiy
    float xVelocity = 0.0f;
    float yVelocity = 0.0f;
    float zVelocity = 0.0f;
    // Grab the Velocity
    alGetSource3f(this->source, AL_VELOCITY, &xVelocity, &yVelocity, &zVelocity);
    // Return yVelocity
    return yVelocity;
}

float Sound3D::getZVelocity()
{
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return 0.0f;
    // Make and Initialise Velcotiy
    float xVelocity = 0.0f;
    float yVelocity = 0.0f;
    float zVelocity = 0.0f;
    // Grab the Velocity
    alGetSource3f(this->source, AL_VELOCITY, &xVelocity, &yVelocity, &zVelocity);
    // Return zVelocity
    return zVelocity;
}

OpenALVector3D Sound3D::getVelocity()
{
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return OpenALVector3D(0.0f, 0.0f, 0.0f);
    // Make and Initialise Velcotiy
    float xVelocity = 0.0f;
    float yVelocity = 0.0f;
    float zVelocity = 0.0f;
    // Grab the Velocity
    alGetSource3f(this->source, AL_VELOCITY, &xVelocity, &yVelocity, &zVelocity);
    // Return Velocity
    return OpenALVector3D(xVelocity, yVelocity, zVelocity);
}

void Sound3D::setVelocity(float xVelocity, float yVelocity, float zVelocity)
{
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Make and initialise and array for the velocity
    float velocity[3] = {xVelocity, yVelocity, zVelocity};
    // Set the Position of the Source
    alSourcefv(this->source, AL_VELOCITY, &velocity[0]);
}

void Sound3D::setVelocity(OpenALVector3D v)
{
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Make and initialise and array for the velocity
    float velocity[3] = {v.x, v.y, v.z};
    // Set the Position of the Source
    alSourcefv(this->source, AL_VELOCITY, &velocity[0]);
}

OpenALVector3D Sound3D::getDirection()
{
    // Return Direction the Source is Facing
    return OpenALVector3D(this->xDirection, this->yDirection, this->zDirection);
}

void Sound3D::setDirection(float xDirection, float yDirection, float zDirection)
{
    // Set Direction
    this->xDirection = xDirection;
    this->yDirection = yDirection;
    this->zDirection = zDirection;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Make and initialise and array for the direction
    float directionArray[3] = {xDirection, yDirection, zDirection};
    // Set the Direction the the Source is facing
    alSourcefv(this->source, AL_DIRECTION, &(directionArray[0]));
}

void Sound3D::setDirection(OpenALVector3D direction)
{
    // Set Direction
    this->setDirection(direction.x, direction.y, direction.z);
}

void Sound3D::setInnerConeAngle(float angle)
{
    // Set inner cone angle
    this->innerConeAngle = angle;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Set the Inner Cone Angle
    alSourcef(this->source, AL_CONE_INNER_ANGLE, this->innerConeAngle);
}

void Sound3D::setOuterConeAngle(float angle)
{
    // Set outer cone angle
    this->outerConeAngle = angle;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Set the outer Cone Angle
    alSourcef(this->source, AL_CONE_OUTER_ANGLE, this->outerConeAngle);
}

void Sound3D::setOuterConeGain(float gain)
{
    // Set outer cone gain
    this->outerConeGain = gain;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Set the outer Cone gain
    alSourcef(this->source, AL_CONE_OUTER_GAIN, this->outerConeGain);
}

float Sound3D::getRollOff()
{
    return this->rollOff;
}

void Sound3D::setRollOff(float rollOff)
{
    // Set RollOff
    this->rollOff = rollOff;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Set the outer Cone Angle
    alSourcef(this->source, AL_ROLLOFF_FACTOR, this->rollOff);
}

void Sound3D::setReferenceDistance(float referenceDistance)
{
    // Set Reference Distance
    this->referenceDistance = referenceDistance;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Set the Reference Distance
    alSourcef(this->source, AL_REFERENCE_DISTANCE, this->referenceDistance);
}

float Sound3D::getMaxDistance()
{
    // Return max distance
    return this->maxDistance;
}

void Sound3D::setMaxDistance(float maxDistance)
{
    // Set local maxDistance
    this->maxDistance = maxDistance;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Set the Reference Distance
    alSourcef(this->source, AL_MAX_DISTANCE, this->maxDistance);
}

float Sound3D::getMinVolume()
{
    // return minVolume
    return this->minVolume;
    /* NOTE: I could have used
        alGetSourcef(this->source, AL_MIN_GAIN, &minVolume);
        but this would have been a poor design decision */
}

void Sound3D::setMinVolume(float minVolume)
{
    // Set minvolume
    this->minVolume = minVolume;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Set the MinVolume for the Source
    alSourcef(this->source, AL_MIN_GAIN, this->minVolume);
}

float Sound3D::getMaxVolume()
{
    // Return Max Volume
    return this->maxVolume;
    /* NOTE: I could have used
        alGetSourcef(this->source, AL_MAX_GAIN, &maxVolume);
        but that would have been a poor design choice */
}

void Sound3D::setMaxVolume(float maxVolume)
{
    // Set max volume
    this->maxVolume = maxVolume;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Set the MaxVolume for the Source
    alSourcef(this->source, AL_MAX_GAIN, maxVolume);
}

//void Sound3D::bindToLua(lua_State* pLuaState)
//{
//    // TODO: implement me
//}
