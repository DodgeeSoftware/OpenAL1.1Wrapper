#include "AudioManager.h"

SoundBuffer* AudioManager::getSoundBuffer(std::string filename)
{
    return this->getSoundBuffer(filename, true);
}

SoundBuffer* AudioManager::getSoundBuffer(std::string filename, bool addToMap)
{
    // Validate Filename
    if (filename.size() == 0)
        return 0;
    // Make the filename uppercase
    filename = this->toUpperCase(filename);
    // Send a message to the console
    std::cout << "SoundSample* AudioManager::getSoundBuffer(std::string filename, bool addToMap)" << std::endl;
    // Try and find existing SoundBuffer
    std::map<std::string, SoundBuffer*>::iterator i = this->soundBufferMap.find(filename);
    if (i != this->soundBufferMap.end())
    {
        // Send a message to the console
        std::cout << filename.c_str() << " already loaded. Function Successful" << std::endl;
        return i->second;
    }
    // Make a new SoundBuffer
    SoundBuffer* pSoundBuffer = new SoundBuffer();
    // Variable for Results of OpenAL Function calls
    ALint result = -1;
    // Make a Buffer
    ALuint bufferID = -1;
    // Generate the Buffer
    alGenBuffers(1, &bufferID);
    // If there was a problem making the buffer
    if ((result = alGetError()) != AL_NO_ERROR)
    {
        // Send a message to the console
        std::cout << " ERROR: " << Utils::getALErrorString(result) << std::endl;
        // Failure
        return 0;
    }
    // Sound Info Structure
    SF_INFO soundFileInfo;
    // Try and Open our Sound file
    SNDFILE* pSoundFile = sf_open(filename.c_str(), SFM_READ, &soundFileInfo);
    // If there was a problem
    if (pSoundFile == 0)
    {
        // Send a message to the console
        std::cout << "ERROR: " << sf_strerror(pSoundFile) << std::endl;
        // Failure
        return 0;
    }
    // Send a message to the console
    std::cout << "Sample Rate: " << soundFileInfo.samplerate << std::endl;
    std::cout << "Channels: " << soundFileInfo.channels << std::endl;
    std::cout << "Format: " << soundFileInfo.format << std::endl;
    std::cout << "Frames: " << soundFileInfo.frames << std::endl;
    // Data just ready straight out of the file
    std::vector<int16_t> data;
    size_t readSize = 0;
    // Final container for the PCM Data responsible for the soundBuffer
    std::vector<int16_t> readBuffer;
        // Set the size of our read buffer
        readBuffer.resize(4096);
    // While there is data to read
    while((readSize = sf_read_short(pSoundFile, readBuffer.data(), readBuffer.size())) != 0)
    {
        // Put the data into the readbuffer
        data.insert(data.end(), readBuffer.begin(), readBuffer.begin() + readSize);
    }
    // Send a message to the console
    std::cout << "Size of Data: " << data.size() << std::endl;
    // Close the Sound File
    sf_close(pSoundFile);
    /* NOTE: I tested the format here using 8/16 bit stereo/mono and it seems
        than libsnd converts the audiobuffers to always be 16 bit. This has to do
        with 'normalisation' in that the buffers are converted into ranges 0.0f - 1.0f
        then scaled to PCM format between -32768 and 32768. As a consequence it
        seems safe, for now, to assume all formats are 16 bit */
    // Set the Buffer Format (8/16 bit mono/stereo)
    ALenum format = ((soundFileInfo.channels == 2) ? (AL_FORMAT_STEREO16) : (AL_FORMAT_MONO16));
    // Place our Buffer Data into the Buffer
    alBufferData(bufferID, format, (void*)data.data(), data.size() * sizeof(int16_t), soundFileInfo.samplerate);
    // Set the BufferID for our SoundBuffer
    pSoundBuffer->setBufferID(bufferID);
    // Set the Filename for our SoundBuffer
    pSoundBuffer->setFilename(filename);
    // Set Frequency in Hertz
    pSoundBuffer->setFrequency(soundFileInfo.samplerate);
    // Set Size in bytes
    pSoundBuffer->setSize(data.size() * sizeof(int16_t));
    // Set Channels
    pSoundBuffer->setChannels(soundFileInfo.channels);
    // Set Bits per Sample
    pSoundBuffer->setBits(16); // NOTE: I hard code this because of the way libsnd seems to work. It converts all samples to 16 bits
    // If addToMap is true
    if (addToMap == true)
    {
        // Add our new SoundBuffer to our SoundBufferMap
        this->soundBufferMap[filename] = pSoundBuffer;
    }
    // Return our new Sound
    return pSoundBuffer;
}

void AudioManager::clear()
{
    // Go through each SoundBuffer in our Map
    for (std::map<std::string, SoundBuffer*>::iterator i = this->soundBufferMap.begin(); i != this->soundBufferMap.end(); i++)
    {
        // Grab the SoundBuffer
        SoundBuffer* pSoundBuffer = i->second;
        // Grab the BufferID
        ALuint bufferID = pSoundBuffer->getBufferID();
        // Delete the Buffer
        alDeleteBuffers(1, &bufferID);
        // Delete the SoundBuffer
        delete pSoundBuffer;
    }
    // Clear the SoundBufferMap
    this->soundBufferMap.clear();
}

