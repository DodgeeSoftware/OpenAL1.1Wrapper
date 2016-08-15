#include "Source.h"

void Source::play()
{
    // If we are already playing this sound then do nothing
    if (this->isPlaying() == true)
        return;
    // Set PlayingFlag
    this->playingFlag = true;
    // Generate a Source
    alGenSources(1, &(this->source));
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    /* NOTE: Here is where you would setup the buffer for the
        Source */
    // Play the Source
    alSourcePlay(this->source);
    // Set Paused for the Source
    this->setPaused(this->pauseFlag);
    // Set Volume
    this->setVolume(this->volume);
    // Set Mute
    this->setMute(this->muteFlag);
    // Set Looping
    this->setLooping(this->loopFlag);
    // Set Pitch
    this->setPitch(this->pitch);
}

void Source::update(float dTime)
{
    // Only update when we are playing
    if (this->isPlaying() == false)
        return;
    // Don't Update a paused Source
    if (this->isPaused() == true)
        return;
    // Set the Volume
    alSourcef(this->source, AL_GAIN, OpenALGlobals::soundVolume * this->volume);
    // If our Sound isn't looping
    if (this->loopFlag == false)
    {
        // Variable for our source state
        int sourceState = -1;
        // Grab our source state
        alGetSourcei(this->source, AL_SOURCE_STATE, &sourceState);
        // its not playing and its not paused
        if ((sourceState != AL_PLAYING) && (sourceState != AL_PAUSED))
        {
            // Stop the sound
            this->stop();
        }
    }
}

void Source::start()
{
    // Play
    this->play();
}

void Source::stop()
{
    // Only allow Stop on playing Sounds
    if (this->isPlaying() == false)
        return;
    // Set PlayingFlag
    this->playingFlag = false;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Stop the Source
    alSourceStop(this->source);
    // Delete the Source
    alDeleteSources(1, &(this->source));
    // Default source value
    this->source = -1;
}

void Source::pause()
{
    // Set Paused
    this->setPaused(true);
}

void Source::resume()
{
    // Set Paused
    this->setPaused(false);
}

void Source::clear()
{
    // Default source value
    this->source = -1;
    // Playing Flag
    this->playingFlag = false;
    // Pause flag
    this->pauseFlag = false;
    // Volume
    this->volume = 255;
    // Mute Flag
    this->muteFlag = false;
    // Set LoopFlag
    this->loopFlag = false;
    // Pitch
    this->pitch = 1.0f;
    // If we still have a Source
    if (this->source != -1)
    {
        // If our Source is valid
        if (alIsSource(this->source) == AL_TRUE)
        {
            // Delete the Source
            alDeleteSources(1, &(this->source));
        }
        // Reset the value of Source
        this->source = -1;
    }
}

void Source::free()
{
    // Default source value
    this->source = -1;
    // Playing Flag
    this->playingFlag = false;
    // Pause flag
    this->pauseFlag = false;
    // Volume
    this->volume = 255;
    // Mute Flag
    this->muteFlag = false;
    // Set LoopFlag
    this->loopFlag = false;
    // Pitch
    this->pitch = 1.0f;
    // If we still have a Source
    if (this->source != -1)
    {
        // If our Source is valid
        if (alIsSource(this->source) == AL_TRUE)
        {
            // Delete the Source
            alDeleteSources(1, &(this->source));
        }
        // Reset the value of Source
        this->source = -1;
    }
}

bool Source::isPlaying()
{
    // Return playingflag
    return this->playingFlag;
}

bool Source::isPaused()
{
    // return PauseFlag
    return this->pauseFlag;
    /* NOTE: We could have used this but it
        would have been bad design
    alGetSourcei(this->source, AL_SOURCE_STATE, &sourceState); */
}

void Source::setPaused(bool state)
{
    // Set the Paused Flag
    this->pauseFlag = state;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Set the Paused State of the Source
    (this->pauseFlag == true) ? alSourcePause(this->source) : alSourcePlay(this->source);
}

int Source::getVolume()
{
    // Return the volume
    return this->volume;
    /* NOTE: although its possible to use
        alGetSourcei(this->source, AL_GAIN, &volume);
        that would be poor design */
}

void Source::setVolume(int volume)
{
    // Set the Volume
    this->volume = volume;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Set the Volume
    alSourcef(this->source, AL_GAIN, this->volume);
}

bool Source::isMute()
{
    // Return muteFlag
    return this->muteFlag;
}

void Source::setMute(bool state)
{
    // Set the MuteFlag
    this->muteFlag = muteFlag;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Mute/Unmute the Source
    alSourcef(this->source, AL_GAIN, (this->muteFlag == true) ? 0 : this->volume);
}

void Source::mute()
{
    // Set mute state
    this->setMute(true);
}

void Source::unmute()
{
    // Set mute state
    this->setMute(false);
}

bool Source::isLooping()
{
    //return flag;
    return this->loopFlag;
    /* NOTE: we could have used
        alGetSource(this->source, AL_LOOPING, &flag);
        but that would have been a very poor design choice */
}

void Source::setLooping(bool mode)
{
    /* NOTE:  Queries to AL_BUFFERS_PROCESSED will always
        return false if our source is set to looping
        thus here we keep a local lopp flag */
    this->loopFlag = mode;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Loop / Unloop the sound
    alSourcei(this->source, AL_LOOPING, (this->loopFlag == true) ? AL_TRUE : AL_FALSE);
}

float Source::getPitch()
{
    // Return pitch
    return this->pitch;
}

void Source::setPitch(float pitch)
{
    // Set Pitch
    this->pitch = pitch;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Set Pitch
    alSourcef(this->source, AL_PITCH, pitch);
}

//void Source::bindToLua(lua_State* pLuaState)
//{
//    // TODO: implement me
//}
