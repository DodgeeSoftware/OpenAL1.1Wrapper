#include "Stream.h"

bool Stream::load(std::string filename)
{
    // Send a message to the console
    std::cout << "bool Stream::load(std::string " << filename << ")" << std::endl;
    // Validate Filename
    if (filename.size() == 0)
        return false;
    // Sound File Info
    SF_INFO soundFileInfo;
    // Try and Open our Sound file
    this->pStreamFile = sf_open(filename.c_str(), SFM_READ, &soundFileInfo);
    // If there was a problem
    if (this->pStreamFile == 0)
    {
        // Send a message to the console
        //std::cout << "ERROR: " << sf_strerror(this->pStreamFile) << std::endl;
        std::cout << "ERROR: " << sf_error_number(sf_error(this->pStreamFile)) << std::endl;
        // Failure
        return false;
    }
    // Set local filename
    this->filename = filename;
    // Set local sampleRate
    this->sampleRate = soundFileInfo.samplerate;
    // Se local channels
    this->channels = soundFileInfo.channels;
    // Send a message to the console
    std::cout << "bool Stream::load(std::string " << filename << ") success" << std::endl;
    std::cout << "Sample Rate: " << soundFileInfo.samplerate << std::endl;
    std::cout << "Channels: " << soundFileInfo.channels << std::endl;
    std::cout << "Format: " << soundFileInfo.format << std::endl;
    std::cout << "Frames: " << soundFileInfo.frames << std::endl;
    // Success
    return true;
}

void Stream::play()
{
    // Don't call play multiple times
    if (this->isPlaying() == true)
        return;
    // Set Playing Flag
    this->playingFlag = true;
    // Generate Sources
    alGenSources(1, &(this->source));
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Make Buffers
    alGenBuffers(6, &(this->buffer[0]));  // NUM_BUFFERS
    // Queue our first few buffers
    for (int i = 0; i < 6; i++) // NUM_BUFFERS
    {
        // Stream some file data into the buffers
        this->stream(this->buffer[i]);
        // Queue the buffers intot hte source
        alSourceQueueBuffers(this->source, 1, &(this->buffer[i]));
    }
    /* NOTE: Make sure the source isn't looping
        this is important because otherwise
        Queries made of AL_BUFFERS_PROCESSED
        will always return 0 buffers processed
        meaning that we can never move on to
        queue another audio tile. Looping is handle
        in update and the bahviour chosen on the
        basis of the loopFlag */
    alSourcei(this->source, AL_LOOPING, AL_FALSE);
    // Play the Source
    alSourcePlay(this->source);
    // Set Paused for the Source
    this->setPaused(this->pauseFlag);
    // Set Volume
    this->setVolume(this->volume);
    // Set Mute
    this->setMute(this->muteFlag);
//    // Set Looping
//    this->setLooping(this->loopFlag);
    // Set Pitch
    this->setPitch(this->pitch);
}

void Stream::stop()
{
    // Only allow Stop on playing Sounds
    if (this->isPlaying() == false)
        return;
    // Set Playing Flag
    this->playingFlag = false;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
   // old Buffers
    ALuint oldBuffers[6]; // NUM_BUFFERS
    // Unqueue the last used buffer
    alSourceUnqueueBuffers(this->source, 6, &(oldBuffers[0]));
    // Generate our buffers
    alDeleteBuffers(6, &(oldBuffers[0])); // NUM_BUFFERS
    // Stop the Source
    alSourceStop(this->source);
    // Delete the Source
    alDeleteSources(1, &(this->source));
    // Default source value
    this->source = -1;
    // Go back to the beginning of the Stream
    sf_seek(this->pStreamFile, SEEK_SET, 0);
}

void Stream::pause()
{
    // Set Paused
    this->setPaused(true);
}

void Stream::resume()
{
    // Set Paused
    this->setPaused(false);
}

void Stream::update(float dTime)
{
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Don't Update a paused Source
    if (this->isPaused() == true)
        return;
    // Set the Volume
    alSourcef(this->source, AL_GAIN, OpenALGlobals::soundVolume * this->volume);
    // Ask how many buffers have been used
    int buffersProcessed = -1;
    // Grab the number of buffers used
    alGetSourcei(this->source, AL_BUFFERS_PROCESSED, &buffersProcessed);
    // Where no buffers have been fully processed return
    if (buffersProcessed <= 0)
        return;
    // Handle for our newlyFreedBuffer
    ALuint newBuffer = -1;
    // Remove a used buffer from our source
    alSourceUnqueueBuffers(this->source, 1, &(newBuffer));
    /* If our request to grab more data
        (and put it in newbuffer) fails
        then handle our loop logic */
    if (this->stream(newBuffer) == false)
    {
        // Where loop flag is false
        if (this->loopFlag == false)
        {
            // Stop
            this->stop();
            // Return
            return;
        }
        else // Where loop flag is true
        {
            // Go back to the beginning of the Stream
            sf_seek(this->pStreamFile, SEEK_SET, 0);
            // Stop
            this->stop();
            // Play
            this->play();
            // Return;
            return;
        }
    }
    // Add our new buffer to our source
    alSourceQueueBuffers(this->source, 1, &(newBuffer));
}

void Stream::clear()
{
    // Do nothing here let the free function clean up
}

void Stream::free()
{
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
    // Clear the sample rate
    this->sampleRate = -1;
    // Clear number of channels
    this->channels = -1;
    // Delete Buffers
    alDeleteBuffers(6, &(this->buffer[0])); // NUM_BUFFERS
}

bool Stream::stream(int buffer)
{
    // Create a read buffer
    std::vector<int16_t> readBuffer;
        readBuffer.resize(4096); // NOTE: 4096 is the buffersize
    // Create a buffer for our data
    std::vector<int16_t> data;
    // Read as much information from the stream as will fit inside our buffer (if less return how many much we able to read)
    size_t readSize = sf_read_short(this->pStreamFile, readBuffer.data(), readBuffer.size());
    if (readSize > 0)
    {
        // pursh information from our readBuffer into our data stream
        data.insert(data.end(), readBuffer.begin(), readBuffer.begin() + readSize);
        // Grab the audiosystem's frequency
        ALsizei frequency = OpenALGlobals::frequency;
        // Here I assume that playback will be stereo and 16 bits per channel
        ALenum format = AL_FORMAT_STEREO16;
        // Place our Buffer Data into the Buffer
        alBufferData(buffer, format, (void*)data.data(), data.size() * sizeof(int16_t), frequency);
        // Success
        return true;
    }
    // Unable to grab any more data
    return false;
}

bool Stream::isLooping()
{
    //return flag;
    return this->loopFlag;
    /* NOTE: we could have used
        alGetSource(this->source, AL_LOOPING, &flag);
        but that would have been a very poor design choice */
}

void Stream::setLooping(bool mode)
{
    /* NOTE:  Queries to AL_BUFFERS_PROCESSED will always
        return false if our source is set to looping
        thus here we keep a local lopp flag */
    this->loopFlag = mode;
}

int Stream::getChannels()
{
    return this->channels;
}

int Stream::getSampleRate()
{
    return this->sampleRate;
}

//void Stream::bindToLua(lua_State* pLuaState)
//{
//    // TODO: implement me
//}
