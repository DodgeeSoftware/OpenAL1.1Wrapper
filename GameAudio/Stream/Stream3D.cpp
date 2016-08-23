#include "Stream3D.h"

void Stream3D::play()
{
    // Play Our Stream (generates our source)
    Stream::play();
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
}

void Stream3D::start()
{
    // Play our Sound
    this->play();
}

void Stream3D::stop()
{
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    /* Make the source NOT relative to the position, velocity,
        cone and direction relative to the listener */
    alSourcei(this->source, AL_SOURCE_RELATIVE, AL_TRUE);
    // Stop the Stream3D
    Stream::stop();
}

void Stream3D::clear()
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
    // Validate the Source
    if (alIsSource(this->source) == AL_TRUE)
    {
        /* Make the source NOT relative to the position, velocity,
            cone and direction relative to the listener */
        alSourcei(this->source, AL_SOURCE_RELATIVE, AL_FALSE);
    }
    // Clear our Stream
    Stream::clear();
}

void Stream3D::free()
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
    // Validate the Source
    if (alIsSource(this->source) == AL_TRUE)
    {
        /* Make the source NOT relative to the position, velocity,
            cone and direction relative to the listener */
        alSourcei(this->source, AL_SOURCE_RELATIVE, AL_FALSE);
    }
    // Free our Stream
    Stream::free();
}

float Stream3D::getX()
{
    // Return x
    return this->x;
}

float Stream3D::getY()
{
    // Return y
    return this->y;
}

float Stream3D::getZ()
{
    // Return z
    return this->z;
}

OpenALVector3D Stream3D::getPosition()
{
    // Return the Position
    return OpenALVector3D(this->x, this->y, this->z);
}

void Stream3D::setPosition(float x, float y, float z)
{
    // Set Position
    this->x = x;
    this->y = y;
    this->z = z;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Make and initialise and array for the position
    float positionArray[3] = {x, y, z};
    // Set the Position of the Source
    alSourcefv(this->source, AL_POSITION, &positionArray[0]);
}

void Stream3D::setPosition(OpenALVector3D v)
{
    // Set Position
    this->setPosition(v.x, v.y, v.z);
}

float Stream3D::getXVelocity()
{
    // Return xVelocity
    return this->xVelocity;
}

float Stream3D::getYVelocity()
{
    // Return yVelocity
    return this->yVelocity;
}

float Stream3D::getZVelocity()
{
    // Return zVelocity
    return this->zVelocity;
}

OpenALVector3D Stream3D::getVelocity()
{
    // Return Velocity
    return OpenALVector3D(this->xVelocity, this->yVelocity, this->zVelocity);
}

void Stream3D::setVelocity(float x, float y, float z)
{
    // Set Velocity
    this->xVelocity = xVelocity;
    this->yVelocity = yVelocity;
    this->zVelocity = zVelocity;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Make and initialise and array for the velocity
    float velocity[3] = {x, y, z};
    // Set the Position of the Source
    alSourcefv(this->source, AL_VELOCITY, &velocity[0]);
}

void Stream3D::setVelocity(OpenALVector3D v)
{
    // Set Velocity
    this->setVelocity(v.x, v.y, v.z);
}

OpenALVector3D Stream3D::getDirection()
{
    // Return Direction the Source is Facing
    return OpenALVector3D(this->xDirection, this->yDirection, this->zDirection);
}

void Stream3D::setDirection(float xDirection, float yDirection, float zDirection)
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

void Stream3D::setDirection(OpenALVector3D direction)
{
    // Set Direction
    this->setDirection(direction.x, direction.y, direction.z);
}

float Stream3D::getInnerConeAngle()
{
    // Return inner cone angle
    return this->innerConeAngle;
}

void Stream3D::setInnerConeAngle(float angle)
{
    // Set inner cone angle
    this->innerConeAngle = angle;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Set the Inner Cone Angle
    alSourcef(this->source, AL_CONE_INNER_ANGLE, this->innerConeAngle);
}

float Stream3D::getOuterConeAngle()
{
    // Return outer cone angle
    return this->outerConeAngle;
}

void Stream3D::setOuterConeAngle(float angle)
{
    // Set outer cone angle
    this->outerConeAngle = angle;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Set the outer Cone Angle
    alSourcef(this->source, AL_CONE_OUTER_ANGLE, this->outerConeAngle);
}

void Stream3D::setOuterConeGain(float gain)
{
    // Set outer cone gain
    this->outerConeGain = gain;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Set the outer Cone gain
    alSourcef(this->source, AL_CONE_OUTER_GAIN, this->outerConeGain);
}

float Stream3D::getRollOff()
{
    // Return rolloff
    return this->rollOff;
}

void Stream3D::setRollOff(float rollOff)
{
    // Set RollOff
    this->rollOff = rollOff;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Set the outer Cone Angle
    alSourcef(this->source, AL_ROLLOFF_FACTOR, this->rollOff);
}

float Stream3D::getReferenceDistances()
{
    // Return reference Distance
    return this->referenceDistance;
}

void Stream3D::setReferenceDistance(float referenceDistance)
{
    // Set Reference Distance
    this->referenceDistance = referenceDistance;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Set the Reference Distance
    alSourcef(this->source, AL_REFERENCE_DISTANCE, this->referenceDistance);
}

float Stream3D::getMaxDistance()
{
    // return max distance
    return this->maxDistance;
}

void Stream3D::setMaxDistance(float maxDistance)
{
    // Set local maxDistance
    this->maxDistance = maxDistance;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Set the Reference Distance
    alSourcef(this->source, AL_MAX_DISTANCE, this->maxDistance);
}

float Stream3D::getMinVolume()
{
    // return minVolume
    return this->minVolume;
    /* NOTE: I could have used
        alGetSourcef(this->source, AL_MIN_GAIN, &minVolume);
        but this would have been a poor design decision */
}

void Stream3D::setMinVolume(float minVolume)
{
    // Set minvolume
    this->minVolume = minVolume;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Set the MinVolume for the Source
    alSourcef(this->source, AL_MIN_GAIN, this->minVolume);
}

float Stream3D::getMaxVolume()
{
    // Return Max Volume
    return this->maxVolume;
    /* NOTE: I could have used
        alGetSourcef(this->source, AL_MAX_GAIN, &maxVolume);
        but that would have been a poor design choice */
}

void Stream3D::setMaxVolume(float maxVolume)
{
    // Set max volume
    this->maxVolume = maxVolume;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Set the MaxVolume for the Source
    alSourcef(this->source, AL_MAX_GAIN, maxVolume);
}

//void Stream3D::bindToLua(lua_State* pLuaState)
//{
//    // TODO: implement me
//}
