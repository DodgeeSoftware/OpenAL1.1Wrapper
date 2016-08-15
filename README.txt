
***********
* READ ME *
***********

This OpenALWrapper is released under GPLv3

What dependancies are there

- libsndfile version 1.0.28 (Abstracts out audiofile formats so one simply deals with raw pcm data)
- libxmp version 4.4.0 (Astracks out the tracker music so one simple deals with raw pcm data)
- openal 1.1 (A really basic Audio library based off a similar interface to the opengl graphics library)

To use include the header "GameAudio.h" add the GameAudio folder to your Game Project
and call the init method of the audiosystem; be sure to update it in your update loop
and shut it down on quitting. The audiosystem is the centre of AudioPlayback.
You can query device properties such as frequency, set the position of the listener and
also manager Capture devices.

A CaptureDevice is an object which allows you to open a recording device and record audio. You
can access them via the AudioSystem's getAudioCaptureDevice(int id) method. To record, open
the device with the open method, start recording with the start method, stop recording with the
stop method and collect your buffer with a call to captureSamples(...). Don't forget to close the
device when you are done.

A Music object open a file for streaming. Files in usually in formats such as *.xm, *.s3m, *.mod etc.
Once you use the musics load method, simply invoke play to begin playing; being certain to
call update on your music object in your game's update loop. To clean up your music object, call clear
then free on it.

A Sound Object is an instance of a SoundBuffer. You can load a SoundBuffer using the AudioManager Provided.
Use the audioManager.getSoundBuffer(filename) method to return an id to a usuable soundbuffer. (I do not
support mp3 here or any commercial royalty based audio formats, so stick with wav or ogg or any of the
other formats supported by libsnd). After passing a SoundBuffer to your Sound Object invoke the play method
to start playback; being certain to call update in your games update function.

A Stream object opens a file for streaming, reading in small chunks at a time. You can load any of the formats
supported by libsnd (I prefer ogg, NOTE: I do not support mp3 and other non-free formats). After invoking the
Stream's load method call play to begin playback. Being sure to update your stream in your programs update
loop.

~~~~~~~~~~~~~~~~~~~
Developmental Notes
~~~~~~~~~~~~~~~~~~~

SKIPPED: Because I have solid class heirachies that differetiate
    between streams and preloaded audio sources
    int sourceType = -1;
    alGetSourcei(this->source, AL_SOURCE_TYPE, &sourceType);
    Valid Source Types are
    AL_UNDETERMINED - no buffers for the source
    AL_STATIC - a single buffer for the source
    AL_STREAMING - multiple buffers for the source

SKIPPED: We don't need to expose this information
    int buffersQueued = -1;
    alGetSourcei(this->source, AL_BUFFERS_QUEUED, &buffersQueued); // How many buffers have we queued

SKIPPED: We don't need to expose this information
    int buffersProcessed = -1;
    alGetSourcei(this->source, AL_BUFFERS_PROCESSED, &buffersProcessed); // How many buffers in a source have been processed

SKIPPED: We don't need to know the frequency of a buffer
    int value = -1;
    alGetBufferi(this->source, AL_FREQUENCY, &value); // Frequency of a buffer
    alGetBufferi(this->source, AL_SIZE, &value); // Size of a buffer in bytes
    alGetBufferi(this->source, AL_BITS, &value); // Number of bits per sample data contained in the buffer
    alGetBufferi(this->source, AL_CHANNELS, &value); // Number of channels used by the buffer
