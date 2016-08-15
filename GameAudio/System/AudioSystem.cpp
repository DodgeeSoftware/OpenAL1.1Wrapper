#include "AudioSystem.h"

bool AudioSystem::init()
{
    // Send a message to the console
    std::cout << "bool AudioSystem::init()" << std::endl;
    // Open the Audio Device
    this->pAudioDevice = alcOpenDevice(0);
    // If we were unable to Open the Audio Device
    if (this->pAudioDevice == 0)
    {
        // Grab the Error
        int result = alGetError();
        // Send a message to the console
        std::cout << "ERROR: " << Utils::getALErrorString(alGetError()) << std::endl;
        std::cout << "ERROR: " << alGetString(result) << std::endl;
        // Failure
        return false;
    }
    // Create the Context
    this->pContext = alcCreateContext(this->pAudioDevice, 0);
    // If we were unable to Create the Context
    if (this->pContext == 0)
    {
        // Grab the Error
        int result = alcGetError(this->pAudioDevice);
        // Send a message to the console
        std::cout << "ERROR: " << Utils::getALCErrorString(result) << std::endl;
        std::cout << "ERROR: " << alcGetString(this->pAudioDevice, result) << std::endl;
        // Failure
        return false;
    }
    // Set the Global for OpenAL Frequency
    OpenALGlobals::frequency = this->getFrequency();
    // Make the Context Current
    alcMakeContextCurrent(this->pContext);
    // Send a message to the console
    std::cout << std::endl;
    std::cout << "OpenAL Version: " << this->getVersion() << std::endl;
    std::cout << "Renderer: " << this->getRenderer() << std::endl;
    std::cout << "Vendor: " << this->getVendor() << std::endl;
    //std::cout << "Extensions: " << this->getExtensions() << std::endl;
    std::cout << "Frequency: " << this->getFrequency() << " htz" << std::endl;
    std::cout << "Refresh Rate: " << this->getRefreshRate() << " fps" << std::endl;
    std::cout << std::endl;
    // Send a message to the console
    int nummono = 0;
    alcGetIntegerv(this->pAudioDevice, ALC_MONO_SOURCES, 1, &nummono);
    int numstereo = 0;
    alcGetIntegerv(this->pAudioDevice, ALC_STEREO_SOURCES, 1, &numstereo);
    std::cout << "Number of Mono and Stereo Sources supported " << std::endl;
    std::cout << "ALC_MONO_SOURCES: " << nummono << std::endl;
    std::cout << "ALC_STEREO_SOURCES: " << numstereo << std::endl;
    std::cout << std::endl;
    // If there is at least one capture device
    if (this->isDefaultAudioCaptureDeviceAvailable() == true)
    {
        // Grab our list of capture devices
        std::vector<std::string> captureDevicesList = this->getAudioCaptureDevices();
        // Go through our list of capture devices
        for (int i = 0; i < captureDevicesList.size(); i++)
        {
            // Grab the capture Device name
            std::string captureDeviceName = captureDevicesList.at(i);
            // Send a message to the console
            std::cout << "ID:" << i << std::endl;
            std::cout << "Name: " << captureDeviceName << std::endl;
            // Create a new capture device
            CaptureDevice* pCaptureDevice = new CaptureDevice();
                // Set ID
                pCaptureDevice->setID(i);
                // Set the Name for our Device
                pCaptureDevice->setName(captureDevicesList.at(0));
            // Add our Cpature Device onto our captureDevices
            this->captureDevices.push_back(pCaptureDevice);
        }
    }
    else
    {
        // Send a message to the console
        std::cout << "NOTICE: No Audio Capture Devices Available" << std::endl;
    }
    // Send a message to the console
    std::cout << std::endl;
    std::cout << "bool AudioSystem::init() Success" << std::endl;
    std::cout << std::endl;
    // Success
    return true;
}

void AudioSystem::update()
{
    // Process Context
    alcProcessContext(this->pContext);
}

void AudioSystem::shutdown()
{
    // Send a message to the console
    std::cout << "void AudioSystem::shutdown()" << std::endl;
    // Go through each device
    for (std::vector<CaptureDevice*>::iterator i = captureDevices.begin(); i != this->captureDevices.end(); i++)
    {
        CaptureDevice* pCaptureDevice  = *i;
        // Send a message to the console
        std::cout << "NOTICE: Deleting device: " << pCaptureDevice->getName() << std::endl;
        // Delete the Capture Device
        delete pCaptureDevice;
    }
    // Clear the CaptureDevices vector
    this->captureDevices.clear();
    // Destroy the Context
    alcDestroyContext(this->pContext);
    // Close Audio Device
    alcCloseDevice(this->pAudioDevice);
    // Send a message to the console
    std::cout << "void AudioSystem::shutdown()" << std::endl;
}

bool AudioSystem::isDefaultAudioDeviceAvailable()
{
    // Determine if there is an Audio Capture Device Available
    return (alcGetString(0, ALC_DEFAULT_DEVICE_SPECIFIER) != 0) ? true : false;
}

std::string AudioSystem::defaultAudioDeviceName()
{
    // Return the name of the Default Audio Output Device
    return std::string(alcGetString(0, ALC_DEFAULT_DEVICE_SPECIFIER));
}

bool AudioSystem::isAudioDeviceAvailable()
{
    // Determine if there is an Audio Capture Device Available
    return (alcGetString(0, ALC_DEVICE_SPECIFIER) != 0) ? true : false;
}

std::vector<std::string> AudioSystem::getAudioDevices()
{
    // A container for the list of devices
    std::vector<std::string> deviceList;
    // If there is no audio device then return empty vector
    if (this->isAudioDeviceAvailable() == false)
        return deviceList;
    /* Return a list of available devices, names are seperated
        by null characters; string terminated with two null
        characters */
    // Grab out list of Devices
    const char* bigList = alcGetString(0, ALC_DEVICE_SPECIFIER);
    // If our list is empty return
    if (strlen(bigList) == 0)
        return deviceList;
    // The name of a device
    std::string deviceName;
    // Seperate the null terminated strings
    while(true)
    {
        // Save our Device onto our list
        deviceList.push_back(std::string(bigList));
        // Move on to the next Device name
        bigList+=(deviceList.back().size() + 1);
        // Break on double null terminated character
        if (*bigList == '\0')
            break;
    }
    // Return the Device List
    return deviceList;
}

std::string AudioSystem::getVendor()
{
    return alGetString(AL_VENDOR);
}

std::string AudioSystem::getVersion()
{
    // Grab the Version of OpenAL in use
    const ALchar* version = alGetString(AL_VERSION);
    // Return the Version information as a String
    return std::string(version);
}

std::string AudioSystem::getRenderer()
{
    // Return the renderer
    return alGetString(AL_RENDERER);
}

int AudioSystem::getFrequency()
{
    // Make a variable to contain the frequency
    ALCint frequency = 0;
    // Grab the Device Frequency
    alcGetIntegerv(this->pAudioDevice, ALC_FREQUENCY, 1, &(frequency));
    // Return the frequency
    return frequency;
}

int AudioSystem::getRefreshRate()
{
    // Make a variable to contain the Refresh Rate
    ALCint refreshRate = 0;
    // Grab the Device Refresh Rate
    alcGetIntegerv(this->pAudioDevice, ALC_REFRESH, 1, &(refreshRate));
    // Return the refreshRate
    return refreshRate;
}

std::string AudioSystem::getExtensions()
{
    // Make a string for the extension list
    std::string extensions;
    // Grab the AL Extensions
    extensions = extensions + alGetString(AL_EXTENSIONS);
    extensions = extensions + '\n';
    // Grab the ALC Extensions
    extensions = extensions + alcGetString(this->pAudioDevice, ALC_EXTENSIONS);
    extensions = extensions + '\n';
    // Return exensions
    return extensions;
}

bool AudioSystem::isExtensionPresent(std::string extensionName)
{
    // Return true if an extension is present
    return alcIsExtensionPresent(this->pAudioDevice, extensionName.c_str());
}

float AudioSystem::getDopplerFactor()
{
    /* NOTE: See pg29 of openal 1.1 specification for more info */
    // Make a variable for the doppler factor
    float dopplerFactor = 0.0f;
    // Get the Doppler Factor
    alGetFloatv(AL_DOPPLER_FACTOR, &dopplerFactor);
    // Return the Doppler Factor
    return dopplerFactor;
}

void AudioSystem::setDopplerFactor(float dopplerFactor)
{
    /* NOTE: See pg29 of openal 1.1 specification for more info */
    // Doppler Factor
    alDopplerFactor(dopplerFactor);
}

float AudioSystem::getSpeedOfSound()
{
    /* NOTE: // See pg30 of openal 1.1 specification for more info */
    // Make a variable for the Speed of Sound
    float speed = 0.0f;
    // Grab the Speed of Sound
    alGetFloatv(AL_SPEED_OF_SOUND, &speed);
    // Return the Speed of sound
    return speed;
}

void AudioSystem::setSpeedOfSound(float speed)
{
    // Set the Speed of Sound
    alSpeedOfSound(speed);
}

float AudioSystem::getListenerX()
{
    // Position
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    // Get the listener position
    alGetListener3f(AL_POSITION, &x, &y, &z);
    // Return x
    return x;
}

float AudioSystem::getListenerY()
{
    // Position
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    // Get the listener position
    alGetListener3f(AL_POSITION, &x, &y, &z);
    // Return y
    return y;
}

float AudioSystem::getListenerZ()
{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    // Get the listener position
    alGetListener3f(AL_POSITION, &x, &y, &z);
    // Return z
    return z;
}

void AudioSystem::setListenerPosition(float x, float y)
{
    // Set the Listener Position
    alListener3f(AL_ORIENTATION, x, y, 0.0f);
}

void AudioSystem::setListenerPosition(float x, float y, float z)
{
    // Set the Listener Position
    alListener3f(AL_ORIENTATION, x, y, z);
}

void AudioSystem::setListenerDirection(float xDirection, float yDirection, float zDirection, float xUp, float yUp, float zUp)
{
    // Set Listener Direction
    float listenerAngle = 0.0f;
    float direction[6] = {0.0f};
    // Look At Vector
    direction[0] = xDirection;
    direction[1] = yDirection;
    direction[2] = zDirection;
    // Up Vector
    direction[3] = xUp;
    direction[4] = yUp;
    direction[5] = zUp;
    // Set the Listener Orientation
    alListenerfv(AL_ORIENTATION, direction);
}

int AudioSystem::getDistanceModel()
{
    // Get the Distance Model
    return alGetInteger(AL_DISTANCE_MODEL);
}

void AudioSystem::setDistanceModel(int model)
{
    /* NOTES: Valid Values are
        See pg24 of openal 1.1 specification for more info
        AL_NONE,
        AL_INVERSE_DISTANCE)
        AL_INVERSE_DISTANCE_CLAMPED
        AL_LINEAR_DISTANCE
        AL_LINEAR_DISTANCE_CLAMPED
        AL_EXPONENT_DISTANCE
        AL_EXPONENT_DISTANCE_CLAMPED
        */
    //Set the Distance Model
    alDistanceModel(model);
}

bool AudioSystem::isEnabled(int feature)
{
    // Return if a feature is enabled or not
    return alIsEnabled(feature);
}

void AudioSystem::enable(int feature)
{
    // Enable feature
    alEnable(feature);
}

void AudioSystem::disable(int feature)
{
    // Disable feature
    alEnable(feature);
}

float AudioSystem::getMusicVolume()
{
    // return volume
    return OpenALGlobals::musicVolume;
}

void AudioSystem::setMusicVolume(float volume)
{
    // Validate Volume
    if (volume < 0.0f)
        volume = 0.0f;
    if (volume > 1.0f)
        volume = 1.0f;
    // Set volume
    OpenALGlobals::musicVolume = volume;
}

float AudioSystem::getSoundVolume()
{
    // return volume
    return OpenALGlobals::soundVolume;
}

void AudioSystem::setSoundVolume(float volume)
{
    // Validate Volume
    if (volume < 0.0f)
        volume = 0.0f;
    if (volume > 1.0f)
        volume = 1.0f;
    // Set volume
    OpenALGlobals::soundVolume = volume;
}

bool AudioSystem::isMute()
{
    // Return muteflag
    return OpenALGlobals::muteFlag;
}

void AudioSystem::setMute(bool state)
{
    // Set the global mute flag
    OpenALGlobals::muteFlag = state;
}

void AudioSystem::mute()
{
    // Set mute
    this->setMute(true);
}

void AudioSystem::unmute()
{
    // Set mute
    this->setMute(false);
}

bool AudioSystem::isDefaultAudioCaptureDeviceAvailable()
{
    // Determine if there is an Audio Capture Device Available
    return (alcGetString(0, ALC_CAPTURE_DEFAULT_DEVICE_SPECIFIER) != 0) ? true : false;
}

std::string AudioSystem::getDefaultAudioCaptureDeviceName()
{
    // Return the Default Audio Capture Device Name
    return std::string(alcGetString(0, ALC_CAPTURE_DEFAULT_DEVICE_SPECIFIER));
}

bool AudioSystem::isAudioCaptureDeviceAvailable()
{
    // Determine if there is an Audio Capture Device Available
    return (alcGetString(0, ALC_CAPTURE_DEVICE_SPECIFIER) != 0) ? true : false;
}

std::vector<std::string> AudioSystem::getAudioCaptureDevices()
{
    // Make a list for our capture devices
    std::vector<std::string> captureDeviceList;
    /* Grab the list of devices, separated by null characters
        string termined by a double null */
    const char* bigList = alcGetString(0, ALC_CAPTURE_DEVICE_SPECIFIER);
    // If there are no devices then return
    if (strlen(bigList) == 0)
        return captureDeviceList;
    // The name of a device
    std::string deviceName;
    // Seperate the null terminated strings
    while(true)
    {
        // Save our Device onto our list
        captureDeviceList.push_back(std::string(bigList));
        // Move on to the next Device name
        bigList+=(captureDeviceList.back().size() + 1);
        // Break on double null terminated character
        if (*bigList == '\0')
            break;
    }
    // Return our capture device list
    return captureDeviceList;
}

CaptureDevice* AudioSystem::getAudioCaptureDevice(int id)
{
    // Validate our ID
    if (id < 0 || id > this->captureDevices.size())
        return 0;
    // Return our capture device
    return this->captureDevices.at(id);
}

//void AudioSystem::bindToLua(lua_State* pLuaState)
//{
//    // TODO: implement me
//}
