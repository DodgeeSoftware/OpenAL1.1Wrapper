#include "Sound.h"

void Sound::play()
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
    // If we have a Valid SoundBuffer
    if (pSoundBuffer != 0)
    {
        // Bind our Buffer to our Source
        alSourcei(source, AL_BUFFER, this->pSoundBuffer->getBufferID());
    }
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

void Sound::update(float dTime)
{
    // Only update when we are playing
    if (this->isPlaying() == false)
        return;
    // Don't Update a paused Source
    if (this->isPaused() == true)
        return;
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

void Sound::start()
{
    // Play our Sound
    this->play();
}

void Sound::stop()
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

void Sound::pause()
{
    // Set Paused
    this->setPaused(true);
}

void Sound::resume()
{
    // Set Paused
    this->setPaused(false);
}

void Sound::clear()
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
    // Clear Name
    this->name.clear();
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
    // Clean out the SoundBuffer
    this->pSoundBuffer = 0;
}

void Sound::free()
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
    // Clear Name
    this->name.clear();
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
    // Clean out the SoundBuffer
    this->pSoundBuffer = 0;
}

//void Sound::bindToLua(lua_State* pLuaState)
//{
//    // TODO: Implement me
//}
