#include "Music.h"

bool Music::load(std::string filename)
{
    // Send a message to the console
    std::cout << "bool Music::load(std::string " << filename << ")" << std::endl;
    // Variable to track status
    int result = 0;
    // Load Module
    if ((result = xmp_load_module(this->context, (char*)filename.c_str())) < 0)
    {
        // Send a message to the console
        std::cout << "ERROR: Failed to load music module file: " << filename << " " << Utils::getLibXMPErrorString(result) <<std::endl;
        // Failure
        return false;
    }
    // Send a message to the console
    std::cout << "NOTICE: Successfully opened tracker file: " << filename << std::endl;
    // Set local filename
    this->filename = filename;
    // Grab Module information
    xmp_get_module_info(this->context, &(this->moduleInfo));
    // SEND SOME INFORMATION ABOUT THIS MODULE TO THE CONSOLE
    std::cout << "NAME: " << this->moduleInfo.mod->name << " TYPE: " << this->moduleInfo.mod->type << std::endl;
    std::cout << "BPM: " << this->moduleInfo.mod->bpm << " CHANNELS: " << this->moduleInfo.mod->chn << std::endl;
    std::cout << "INSTRUMENTS: " << this->moduleInfo.mod->ins << " LENGTH: " << this->moduleInfo.mod->len << std::endl;
    // Send a message to the console
    std::cout << "bool Music::load(std::string " << filename << ") success" << std::endl;

    // Success
    return true;
}

bool Music::load(void* pBuffer, long size)
{
    // Send a message to the console
    std::cout << "bool Music::load(void* " << (long)pBuffer << ", long " << size  << ")" << std::endl;
    // Variable to track status
    int result = 0;
    // Try and load a module from memory
    if ((result = xmp_load_module_from_memory(this->context, pBuffer, size)) < 0)
    {
        // Send a message to the console
        std::cout << "ERROR: Failed to load music module file: " << filename << " " << Utils::getLibXMPErrorString(result) <<std::endl;
        // Failure
        return false;
    }
    // Send a message to the console
    std::cout << "NOTICE: Successfully opened tracker file: " << filename << std::endl;
    // Set local filename
    this->filename = filename;
    // Grab Module information
    xmp_get_module_info(this->context, &(this->moduleInfo));
    // SEND SOME INFORMATION ABOUT THIS MODULE TO THE CONSOLE
    std::cout << "NAME: " << this->moduleInfo.mod->name << " TYPE: " << this->moduleInfo.mod->type << std::endl;
    std::cout << "BPM: " << this->moduleInfo.mod->bpm << " CHANNELS: " << this->moduleInfo.mod->chn << std::endl;
    std::cout << "INSTRUMENTS: " << this->moduleInfo.mod->ins << " LENGTH: " << this->moduleInfo.mod->len << std::endl;
    // Send a message to the console
    std::cout << "bool Music::load(void* " << (long)pBuffer << ", " << size  << ") success" << std::endl;

    // Success
    return true;
}

//bool Music::load(FILE* pFile, long size)
//{
//    // Send a message to the console
//    std::cout << "bool Music::load(FILE* " << (long)pFile << ", long " << size  << ")" << std::endl;
//    // Variable to track status
//    int result = 0;
//    // Try and load a module from memory
//    if ((result = xmp_load_module_from_file(this->context, pFile, size)) < 0)
//    {
//        // Send a message to the console
//        std::cout << "ERROR: Failed to load music module file " << filename << std::endl;
//        std::cout << "ERROR: Failed to load music module file: " << filename << " " << Utils::getLibXMPErrorString(result) <<std::endl;
//        // Failure
//        return false;
//    }
//    // Send a message to the console
//    std::cout << "NOTICE: Successfully opened tracker file: " << filename << std::endl;
//    // Set local filename
//    this->filename = filename;
//    // Grab Module information
//    xmp_get_module_info(this->context, &(this->moduleInfo));
//    // SEND SOME INFORMATION ABOUT THIS MODULE TO THE CONSOLE
//    std::cout << "NAME: " << this->moduleInfo.mod->name << " TYPE: " << this->moduleInfo.mod->type << std::endl;
//    std::cout << "BPM: " << this->moduleInfo.mod->bpm << " CHANNELS: " << this->moduleInfo.mod->chn << std::endl;
//    std::cout << "INSTRUMENTS: " << this->moduleInfo.mod->ins << " LENGTH: " << this->moduleInfo.mod->len << std::endl;
//    // Send a message to the console
//    std::cout << "bool Music::load(FILE* " << (long)pFile << ", long " << size  << ") success" << std::endl;
//
//    // Failure
//    return false;
//}

void Music::play()
{
    // Don't call play multiple times
    if (this->isPlaying() == true)
        return;
    // Set our Playing Flag
    this->playingFlag = true;
    // Make a Source
    alGenSources(1, &(this->source));
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Frequency
    int frequency = OpenALGlobals::frequency;
    // Start the Player
    xmp_start_player(this->context, frequency, 0);
    // Generate our buffers
    alGenBuffers(6, &(this->buffer[0])); // NUM_BUFFERS
    // Frame Info
    xmp_frame_info frameInfo;
    // Fill our buffers
    for (int i = 0; i < 6; i++) // NUM_BUFFERS
    {
        // Advance the frame
        xmp_play_frame(this->context);
        // Get the frame info
        xmp_get_frame_info(this->context, &(frameInfo));
        // Place PCM Data into the buffer
        alBufferData(buffer[i], AL_FORMAT_STEREO16, frameInfo.buffer, frameInfo.buffer_size, frequency);
    }
    // Queue Buffers into our source
    alSourceQueueBuffers(this->source, 6, &(this->buffer[0])); // NUM_BUFFERS
    // Start Playing our Source
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

bool Music::play(std::string filename)
{
    // Variable to track success
    bool result = false;
    // Try and load our music file
    result = this->load(filename);
    // If loading the music file failed
    if (result == false)
    {
        // return false
        return false;
    }
    // Play the music
    this->play();

    // Success
    return true;
}

int Music::seek(int time)
{
    // Seek to a certain time in the tracker
    int newPos = xmp_seek_time(this->context, time);
    // PURGE OLD BUFFERS
    // old Buffers
    ALuint oldBuffers[6]; // NUM_BUFFERS
    // Unqueue the last used buffer
    alSourceUnqueueBuffers(this->source, 6, &(oldBuffers[0]));
    // Generate our buffers
    alDeleteBuffers(6, &(oldBuffers[0])); // NUM_BUFFERS
    // Generate our buffers
    alGenBuffers(6, &(this->buffer[0])); // NUM_BUFFERS
    // FILL NEW BUFFERS
    // Frame Info
    xmp_frame_info frameInfo;
    int frequency = OpenALGlobals::frequency;
    // Fill our buffers
    for (int i = 0; i < 6; i++) // NUM_BUFFERS
    {
        // Advance the frame
        xmp_play_frame(this->context);
        // Get the frame info
        xmp_get_frame_info(this->context, &(frameInfo));
        // Place PCM Data into the buffer
        alBufferData(buffer[i], AL_FORMAT_STEREO16, frameInfo.buffer, frameInfo.buffer_size, frequency);
    }
    // QUEUE NEW BUFFERS INTO OUR SOURCE
    // Queue Buffers into our source
    alSourceQueueBuffers(this->source, 6, &(this->buffer[0])); // NUM_BUFFERS
    // Return new Pos
    return newPos;
}

int Music::setPosition(int pos)
{
    // Set playback to a certain position in the tracker
    int newPos = xmp_set_position(this->context, pos);
    // PURGE OLD BUFFERS
    // old Buffers
    ALuint oldBuffers[6]; // NUM_BUFFERS
    // Unqueue the last used buffer
    alSourceUnqueueBuffers(this->source, 6, &(oldBuffers[0]));
    // Generate our buffers
    alDeleteBuffers(6, &(oldBuffers[0])); // NUM_BUFFERS
    // Generate our buffers
    alGenBuffers(6, &(this->buffer[0])); // NUM_BUFFERS
    // FILL NEW BUFFERS
    int frequency = OpenALGlobals::frequency;
    // Frame Info
    xmp_frame_info frameInfo;
    // Fill our buffers
    for (int i = 0; i < 6; i++) // NUM_BUFFERS
    {
        // Advance the frame
        xmp_play_frame(this->context);
        // Get the frame info
        xmp_get_frame_info(this->context, &(frameInfo));
        // Place PCM Data into the buffer
        alBufferData(buffer[i], AL_FORMAT_STEREO16, frameInfo.buffer, frameInfo.buffer_size, frequency);
    }
    // QUEUE NEW BUFFERS INTO OUR SOURCE
    // Queue Buffers into our source
    alSourceQueueBuffers(this->source, 6, &(this->buffer[0])); // NUM_BUFFERS
    // return newpos
    return newPos;
}

void Music::update(float dTime)
{
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Only update Music that is playing
    if (this->isPlaying() == false)
        return;
    // If the music isn't muted
    if (this->isMute() == false)
    {
        // Set the Volume
        alSourcef(this->source, AL_GAIN, this->volume);
    }
    // Set the Volume
    alSourcef(this->source, AL_GAIN, OpenALGlobals::musicVolume * this->volume);
    // Value
    ALint value =-1;
    // Grab how many buffers have been used
    alGetSourcei(this->source, AL_BUFFERS_PROCESSED, &value);
    if (value <= 0)
        return;
    // Must be a valid frame in order to update
    if (xmp_play_frame(this->context) != 0)
    {
        return;
    }
   // Frame Info
    xmp_frame_info frameInfo;
    // Grab Frame Info
    xmp_get_frame_info(this->context, &frameInfo);
    // If our music isn't looping
    if (this->loopFlag == false)
    {
        // Check for our loop count
        if (frameInfo.loop_count > 0)
        {
            this->stop();
            std::cout << "STOP CALLED" << std::endl;
        }
    }
   // New Buffer
    ALuint newBuffer;
    // Unqueue the last used buffer
    alSourceUnqueueBuffers(this->source, 1, &newBuffer);
    /* NOTE: 8 Bit Data is expressed in the range 0 to 255, 128 being an audio output level of 0
                16 Bit Data is expressed in the range -32768 to 32767, 0 being an audio output level of 0
                Stereo data is expressed as an interleaved format, meaning that left and right audio data
                alternats i.e. i + 0 is left channel i + 1 is right channel and i = i + 2 */
    // Clear the newley released buffer and insert new PCM data into it
    alBufferData(newBuffer, AL_FORMAT_STEREO16, frameInfo.buffer, frameInfo.buffer_size, OpenALGlobals::frequency);
    // Queue the Newly filled buffer onto our source
    alSourceQueueBuffers(this->source, 1, &newBuffer);
    // Grab the State our Source is in
    alGetSourcei(this->source, AL_SOURCE_STATE, &value);
    // If the source currently isn't playing then
    if (value != AL_PLAYING)
    {
        // Make the Source play
        alSourcePlay(this->source);
    }
}

void Music::start()
{
    // Play
    this->play();
}

void Music::stop()
{
    // Only call stop on a playing sample
    if (this->isPlaying() == false)
        return;
    // Set our Playing Flag
    this->playingFlag = false;
    // Validate the Source
    if (alIsSource(this->source) == AL_FALSE)
        return;
    // Stop the Source
    alSourceStop(this->source);
   // old Buffers
    ALuint oldBuffers[6]; // NUM_BUFFERS
    // Unqueue the last used buffer
    alSourceUnqueueBuffers(this->source, 6, &(oldBuffers[0]));
    // Generate our buffers
    alDeleteBuffers(6, &(oldBuffers[0])); // NUM_BUFFERS
    // Delete the Source
    alDeleteSources(1, &(this->source));
    // Default source value
    this->source = -1;
    // Stop the module
    xmp_stop_module(this->context);
    // End the Player
    xmp_end_player(this->context);
}

void Music::pause()
{
    // Set Paused
    this->setPaused(true);
}

void Music::resume()
{
    // Set Paused
    this->setPaused(false);
}

void Music::clear()
{
    // Do nothing here, clean up is done in free
}

void Music::free()
{
    // Delete our buffers
    alDeleteBuffers(6, &(this->buffer[0]));
    // Set our Playing Flag
    this->playingFlag = false;
    // Set our Pause Flag
    this->pauseFlag = false;
    // Loop Flag
    this->loopFlag = true;
    // Volume
    this->volume = 1.0f;
    // Clear filename
    this->filename.clear();
    // Clear module info
    this->moduleInfo = xmp_module_info();
    // Clear Module
    xmp_release_module(this->context);
}

//void Music::bindToLua(lua_State* pLuaState)
//{
//    // TODO: implement me
//}
