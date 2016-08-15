#include <iostream>
#include <cstdio>
#include <conio.h>
#include "GameAudio.h"

#include <sndfile.hh>

using namespace std;

int main()
{

    AudioSystem audioSystem;

    if (audioSystem.init() == false)
    {
        std::cout << "ERROR: Failed to initialise AudioSystem" << std::endl;
        return -1;
    }
    std::cout << "NOTICE: Successfully Initialised AudioSystem" << std::endl;

    SndfileHandle file;

    file = SndfileHandle("media/sounds/hit.wav");
    std::cout << "Sample Rate: " << file.samplerate() << std::endl;
    std::cout << "Channels: " << file.channels() << std::endl;
    std::cout << "Format: " << file.format() << std::endl;
    std::cout << "Frames: " << file.frames() << std::endl;


    short int fileBuffer[31978];
    file.read(fileBuffer, 31978);

    ALuint buffer;
    ALsizei size = 31978;
    ALsizei frequency = 44100;
    ALenum format = AL_FORMAT_MONO16;

    alGenBuffers(1, &buffer);
    alBufferData(buffer, format, (void*)fileBuffer, size, frequency);

    ALuint source;
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, buffer);
    alSourcePlay(source);



    std::cout << std::endl;
    std::cout << "Push any key to continue" << std::endl;
    std::cout << std::endl;

    getche();

    alSourceStop(source);

    audioSystem.shutdown();

    std::cout << "NOTICE: Shutdown AudioSystem" << std::endl;

    return 0;
}
