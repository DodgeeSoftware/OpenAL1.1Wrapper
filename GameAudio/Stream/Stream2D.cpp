#include "Stream2D.h"

void Stream2D::play()
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
    this->setPosition(this->x, this->y);
    // Set Velocity
    this->setVelocity(this->xVelocity, this->yVelocity);
    // Set Direction
    this->setDirection(this->xDirection, this->yDirection);
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

void Stream2D::start()
{
    // Play
    this->play();
}

void Stream2D::stop()
{
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Make sure co-ordinates are seen in world coords and not relative to the listner
    alSourcei(this->source, AL_SOURCE_RELATIVE, AL_FALSE);
    // Stop the Stream
    Stream::stop();
}

void Stream2D::clear()
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
    // Validate the Source
    if (alIsSource(this->source) == AL_TRUE)
    {
        // Make sure co-ordinates are seen in world coords and not relative to the listner
        alSourcei(this->source, AL_SOURCE_RELATIVE, AL_FALSE);
    }
    // Clear our Stream
    Stream::clear();
}

void Stream2D::free()
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
    // Validate the Source
    if (alIsSource(this->source) == AL_TRUE)
    {
        // Make sure co-ordinates are seen in world coords and not relative to the listner
        alSourcei(this->source, AL_SOURCE_RELATIVE, AL_FALSE);
    }
    // Free our Sound
    Stream::free();
}

float Stream2D::getX()
{
    // Return x
    return this->x;
}

float Stream2D::getY()
{
    // Return y
    return this->y;
}

OpenALVector2D Stream2D::getPosition()
{
    // Return the Position
    return OpenALVector2D(this->x, this->y);
}

void Stream2D::setPosition(float x, float y)
{
    // Set Position
    this->x = x;
    this->y = y;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Make and initialise and array for the position
    float positionArray[3] = {x, y, 0.0f};
    // Set the Position of the Source
    alSourcefv(this->source, AL_POSITION, &positionArray[0]);
}

void Stream2D::setPosition(OpenALVector2D v)
{
    this->setPosition(v.x, v.y);
}

float Stream2D::getXVelocity()
{
    // Return xVelocity
    return this->xVelocity;
}

float Stream2D::getYVelocity()
{
    // Return yVelocity
    return this->yVelocity;
}

OpenALVector2D Stream2D::getVelocity()
{
    // Return the Velocity
    return OpenALVector2D(this->xVelocity, this->yVelocity);
}

void Stream2D::setVelocity(float xVelocity, float yVelocity)
{
    // Set Velocity
    this->xVelocity = xVelocity;
    this->yVelocity = yVelocity;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Make and initialise and array for the velocity
    float velocityArray[3] = {xVelocity, yVelocity, 0.0f};
    // Set the Position of the Source
    alSourcefv(this->source, AL_VELOCITY, &velocityArray[0]);
}

void Stream2D::setVelocity(OpenALVector2D v)
{
    // Set Velocity
    this->setVelocity(v.x, v.y);
}

OpenALVector2D Stream2D::getDirection()
{
    // Return Direction the Source is Facing
    return OpenALVector2D(this->xDirection, this->yDirection);
}

void Stream2D::setDirection(float xDirection, float yDirection)
{
    // Set Direction
    this->xDirection = xDirection;
    this->yDirection = yDirection;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Make and initialise and array for the direction
    float directionArray[3] = {xDirection, yDirection, 0.0f};
    // Set the Direction the the Source is facing
    alSourcefv(this->source, AL_DIRECTION, &(directionArray[0]));
}

void Stream2D::setDirection(OpenALVector2D direction)
{
    // Set Direction
    this->setDirection(direction.x, direction.y);
}

float Stream2D::getInnerConeAngle()
{
    // Return inner cone angle
    return this->innerConeAngle;
}

void Stream2D::setInnerConeAngle(float angle)
{
    // Set inner cone angle
    this->innerConeAngle = angle;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Set the Inner Cone Angle
    alSourcef(this->source, AL_CONE_INNER_ANGLE, this->innerConeAngle);
}

float Stream2D::getOuterConeAngle()
{
    // Return outer cone angle
    return this->outerConeAngle;
}

void Stream2D::setOuterConeAngle(float angle)
{
    // Set outer cone angle
    this->outerConeAngle = angle;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Set the outer Cone Angle
    alSourcef(this->source, AL_CONE_OUTER_ANGLE, this->outerConeAngle);
}

void Stream2D::setOuterConeGain(float gain)
{
    // Set outer cone gain
    this->outerConeGain = gain;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Set the outer Cone gain
    alSourcef(this->source, AL_CONE_OUTER_GAIN, this->outerConeGain);
}

float Stream2D::getRollOff()
{
    // Return rolloff
    return this->rollOff;
}

void Stream2D::setRollOff(float rollOff)
{
    // Set RollOff
    this->rollOff = rollOff;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Set the outer Cone Angle
    alSourcef(this->source, AL_ROLLOFF_FACTOR, this->rollOff);
}

float Stream2D::getReferenceDistance()
{
    // Return reference Distance
    return this->referenceDistance;
}

void Stream2D::setReferenceDistance(float referenceDistance)
{
    // Set Reference Distance
    this->referenceDistance = referenceDistance;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Set the Reference Distance
    alSourcef(this->source, AL_REFERENCE_DISTANCE, this->referenceDistance);
}

float Stream2D::getMaxDistance()
{
    // return max distance
    return this->maxDistance;
}

void Stream2D::setMaxDistance(float maxDistance)
{
    // Set local maxDistance
    this->maxDistance = maxDistance;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Set the Reference Distance
    alSourcef(this->source, AL_MAX_DISTANCE, this->maxDistance);
}

float Stream2D::getMinVolume()
{
    // return minVolume
    return this->minVolume;
    /* NOTE: I could have used
        alGetSourcef(this->source, AL_MIN_GAIN, &minVolume);
        but this would have been a poor design decision */
}

void Stream2D::setMinVolume(float minVolume)
{
    // Set minvolume
    this->minVolume = minVolume;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Set the MinVolume for the Source
    alSourcef(this->source, AL_MIN_GAIN, this->minVolume);
}

float Stream2D::getMaxVolume()
{
    // Return Max Volume
    return this->maxVolume;
    /* NOTE: I could have used
        alGetSourcef(this->source, AL_MAX_GAIN, &maxVolume);
        but that would have been a poor design choice */
}

void Stream2D::setMaxVolume(float maxVolume)
{
    // Set max volume
    this->maxVolume = maxVolume;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Set the MaxVolume for the Source
    alSourcef(this->source, AL_MAX_GAIN, maxVolume);
}

//void Stream2D::bindToLua(lua_State* pLuaState)
//{
//    // TODO: implement me
//}
