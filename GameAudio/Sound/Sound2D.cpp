#include "Sound2D.h"

void Sound2D::play()
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

void Sound2D::start()
{
    // Play our Sound
    this->play();
}

void Sound2D::stop()
{
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Make sure co-ordinates are seen in world coords and not relative to the listner
    alSourcei(this->source, AL_SOURCE_RELATIVE, AL_FALSE);
    // Stop the Sound
    Sound::stop();
}

void Sound2D::clear()
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
        /* Make the source NOT relative to the position, velocity,
            cone and direction relative to the listener */
        alSourcei(this->source, AL_SOURCE_RELATIVE, AL_FALSE);
    }
    // Clear our Sound
    Sound::clear();
}

void Sound2D::free()
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
        /* Make the source NOT relative to the position, velocity,
            cone and direction relative to the listener */
        alSourcei(this->source, AL_SOURCE_RELATIVE, AL_FALSE);
    }
    // Free our Sound
    Sound::free();
}

float Sound2D::getX()
{
    // return x
    return this->x;
    /* NOTE: Could have used
        alGetSource3f(this->source, AL_POSITION, &x, &y, &z);
        but that would have been a poor design */

}

float Sound2D::getY()
{
    // return y
    return this->y;
    /* NOTE: Could have used
        alGetSource3f(this->source, AL_POSITION, &x, &y, &z);
        but that would have been a poor design */
}

OpenALVector2D Sound2D::getPosition()
{
    // return the position
    return OpenALVector2D(this->x, this->y);
    /* NOTE: Could have used
        alGetSource3f(this->source, AL_POSITION, &x, &y, &z);
        but that would have been a poor design */
}

void Sound2D::setPosition(float x, float y)
{
    // Set position
    this->x = x;
    this->y = y;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Make and initialise and array for the position
    float position[3] = {x, y, 0.0f};
    // Set the Position of the Source
    alSourcefv(this->source, AL_POSITION, &position[0]);
}

void Sound2D::setPosition(OpenALVector2D v)
{
    // Set Position
    this->setPosition(v.x, v.y);
}

float Sound2D::getXVelocity()
{
    // return xVelocity
    return this->xVelocity;
    /* NOTE: I could have used
        alGetSource3f(this->source, AL_VELOCITY, &xVelocity, &yVelocity, &zVelocity);
        but would have been a bad choice */
}

float Sound2D::getYVelocity()
{
    // return yVelocity
    return this->yVelocity;
    /* NOTE I could have used
        alGetSource3f(this->source, AL_VELOCITY, &xVelocity, &yVelocity, &zVelocity);
        but would have been a bad choice  */
}

OpenALVector2D Sound2D::getVelocity()
{
    // Return the Velocity
    return OpenALVector2D(this->xVelocity, this->yVelocity);
    /* NOTE I could have used
        alGetSource3f(this->source, AL_VELOCITY, &xVelocity, &yVelocity, &zVelocity);
        but would have been a bad choice  */
}

void Sound2D::setVelocity(float xVelocity, float yVelocity)
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
    alSourcefv(this->source, AL_POSITION, &velocityArray[0]);
}

void Sound2D::setVelocity(OpenALVector2D velocity)
{
    // Set Velocity
    this->setVelocity(velocity.x, velocity.y);
}

OpenALVector2D Sound2D::getDirection()
{
    // Return Direction the Source is Facing
    return OpenALVector2D(this->xDirection, this->yDirection);
}

void Sound2D::setDirection(float xDirection, float yDirection)
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

void Sound2D::setDirection(OpenALVector2D direction)
{
    // Set Direction
    this->setDirection(direction.x, direction.y);
}

float Sound2D::getInnerConeAngle()
{
    // Return inner cone angle
    return this->innerConeAngle;
}

void Sound2D::setInnerConeAngle(float angle)
{
    // Set inner cone angle
    this->innerConeAngle = angle;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Set the Inner Cone Angle
    alSourcef(this->source, AL_CONE_INNER_ANGLE, this->innerConeAngle);
}

float Sound2D::getOuterConeAngle()
{
    // Return outer cone angle
    return this->outerConeAngle;
}

void Sound2D::setOuterConeAngle(float angle)
{
    // Set outer cone angle
    this->outerConeAngle = angle;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Set the outer Cone Angle
    alSourcef(this->source, AL_CONE_OUTER_ANGLE, this->outerConeAngle);
}

void Sound2D::setOuterConeGain(float gain)
{
    // Set outer cone gain
    this->outerConeGain = gain;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Set the outer Cone gain
    alSourcef(this->source, AL_CONE_OUTER_GAIN, this->outerConeGain);
}

float Sound2D::getRollOff()
{
    // Return rolloff
    return this->rollOff;
}

void Sound2D::setRollOff(float rollOff)
{
    // Set RollOff
    this->rollOff = rollOff;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Set the outer Cone Angle
    alSourcef(this->source, AL_ROLLOFF_FACTOR, this->rollOff);
}

float Sound2D::getReferenceDistance()
{
    // Return reference distance
    return this->referenceDistance;
}

void Sound2D::setReferenceDistance(float referenceDistance)
{
    // Set Reference Distance
    this->referenceDistance = referenceDistance;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Set the Reference Distance
    alSourcef(this->source, AL_REFERENCE_DISTANCE, this->referenceDistance);
}

float Sound2D::getMaxDistance()
{
    // Return max distance
    return this->maxDistance;
}

void Sound2D::setMaxDistance(float maxDistance)
{
    // Set local maxDistance
    this->maxDistance = maxDistance;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Set the Reference Distance
    alSourcef(this->source, AL_MAX_DISTANCE, this->maxDistance);
}

float Sound2D::getMinVolume()
{
    // return minVolume
    return this->minVolume;
    /* NOTE: I could have used
        alGetSourcef(this->source, AL_MIN_GAIN, &minVolume);
        but this would have been a poor design decision */
}

void Sound2D::setMinVolume(float minVolume)
{
    // Set minvolume
    this->minVolume = minVolume;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Set the MinVolume for the Source
    alSourcef(this->source, AL_MIN_GAIN, this->minVolume);
}

float Sound2D::getMaxVolume()
{
    // Return Max Volume
    return this->maxVolume;
    /* NOTE: I could have used
        alGetSourcef(this->source, AL_MAX_GAIN, &maxVolume);
        but that would have been a poor design choice */
}

void Sound2D::setMaxVolume(float maxVolume)
{
    // Set max volume
    this->maxVolume = maxVolume;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Set the MaxVolume for the Source
    alSourcef(this->source, AL_MAX_GAIN, maxVolume);
}

//void Sound2D::bindToLua(lua_State* pLuaState)
//{
//    // TODO: implement me
//}
