// ********************************
// * COMPANY: Dodgee Software     *
// * AUTHOR: Shem Taylor          *
// * Written 2016 Dodgee Software *
// * GPLv3                        *
// ********************************

#ifndef AUDIOSYSTEM_H
#define AUDIOSYSTEM_H

// C++ Includes
#include <cmath>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <conio.h>

// OPENAL Includes
#include <al.h>
#include <alc.h>

// GAMEAUDIO Includes
#include "OpenALGlobals.h"
#include "Utils/OpenALUtils.h"
#include "Capture/CaptureDevice.h"

/** The AudioSystem is the main core of the AudioWrapper **/
class AudioSystem
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Constructor
        AudioSystem()
        {
            // Audio Device
            this->pAudioDevice = 0;
            // Context
            this->pContext = 0;
        }
        //! Destructor
        virtual ~AudioSystem() {}

    protected:
        //! Copy Constructors
        AudioSystem(AudioSystem& audioSystem) {}

    // ***********
    // * GENERAL *
    // ***********
    public:
        //! Initialise the AudioSystem
        virtual bool init();
        //! Advance to the next frame
        virtual void update();
        //! Shutdown the AudioSystem
        virtual void shutdown();

    public:
        //! Is Default Audio Output Device Available
        virtual bool isDefaultAudioDeviceAvailable();
        //! Get the Name of the Default Output Device (if there is one)
        virtual std::string defaultAudioDeviceName();
        //! Is Audio Output Device Available
        virtual bool isAudioDeviceAvailable();
        //! Get a list of Available Output Devices
        virtual std::vector<std::string> getAudioDevices();

    public:
        //! Get the AudioDevice
        virtual const ALCdevice* getAudioDevice() const { return this->pAudioDevice; }

    protected:
        // Pointer to the OpenAL AudioDevice
        ALCdevice* pAudioDevice;
        // Pointer to the OpenAL Context
        ALCcontext* pContext;

    // **********
    // * VENDOR *
    // **********
    public:
        //! Get Vendor
        virtual std::string getVendor();

    protected:
        // Members and Methods

    // ***********
    // * VERSION *
    // ***********
    public:
        //! Get the Version of OpenAL
        virtual std::string getVersion();

    protected:
        // Members and Methods

    // ************
    // * RENDERER *
    // ************
    public:
        //! Get Renderer
        virtual std::string getRenderer();

    protected:
        // Members and Methods

    // *************
    // * FREQUENCY *
    // *************
    public:
        //! Get frequency
        virtual int getFrequency();

    protected:
        // Members and Methods

    // ****************
    // * REFRESH RATE *
    // ****************
    public:
        //! Get Refresh Rate
        virtual int getRefreshRate();

    protected:
        // Members and Methods

    // **************
    // * EXTENSIONS *
    // **************
    public:
        //! Get Extensions
        virtual std::string getExtensions();
        //! Is Extension Present
        virtual bool isExtensionPresent(std::string extensionName);

    protected:
        // Members and Methods

    // ******************
    // * DOPPLER FACTOR *
    // ******************
    public:
        //! Get Doppler Factor
        virtual float getDopplerFactor();
        //! Set Doppler Factor
        virtual void setDopplerFactor(float dopplerFactor);

    protected:
        // Members and Methods

    // ******************
    // * SPEED OF SOUND *
    // ******************
    public:
        //! Get Speed of Sound
        virtual float getSpeedOfSound();
        //! Set Speed of Sound
        virtual void setSpeedOfSound(float speed);

    protected:
        // Members and Methods

    // ************
    // * LISTENER *
    // ************
    /* NOTE: Listener functions will only affect positional audio */
    public:
        //! Get Lister X
        virtual float getListenerX();
        //! Get Lister Y
        virtual float getListenerY();
        //! Get Lister Z
        virtual float getListenerZ();
        //! Set Listener Position
        virtual void setListenerPosition(float x, float y);
        //! Set Listener Position
        virtual void setListenerPosition(float x, float y, float z);
        //! Set Listener Direction
        virtual void setListenerDirection(float directionX, float directionY, float directionZ, float upX, float upY, float upZ);

    protected:
        // Methods and members

    // ******************
    // * DISTANCE MODEL *
    // ******************
    public:
        //! Get the Distance Model
        virtual int getDistanceModel();
        //! Set Distance Model
        virtual void setDistanceModel(int model);

    // **********************************
    // * ENABLED / DISABLE CAPABILITIES *
    // **********************************
    /* NOTE: This section exists to enable and disable
        context capabilities */
    public:
        //! Is Context Capability Enabled
        virtual bool isEnabled(int feature);
        //! Enable context capablility
        virtual void enable(int feature);
        //! Disable context capablility
        virtual void disable(int feature);

    protected:
        // Methods and members

    // **********
    // * VOLUME *
    // **********
    /* NOTE: OpenAL has no decent way of setting system volume or
        a real mute system. The functions here will only work with
        positional sounds if even that because it varies from driver
        to driver */
    public:
        //! Get Music Volume
        virtual float getMusicVolume();
        //! Set Music Volume
        virtual void setMusicVolume(float volume);
        //! Get Sound Volume
        virtual float getSoundVolume();
        //! Set Sound Volume
        virtual void setSoundVolume(float volume);
        //! Is Mute
        virtual bool isMute();
        //! Set Mute Flag
        virtual void setMute(bool state);
        //! Mute
        virtual void mute();
        //! Unmute
        virtual void unmute();

    protected:
        // Methods and members

    // *************
    // * RECORDING *
    // *************
    public:
        //! Is Default Audio Capture Device Available
        virtual bool isDefaultAudioCaptureDeviceAvailable();
        //! Get Default Audio Capture Device Name
        virtual std::string getDefaultAudioCaptureDeviceName();
        //! Is Audio Capture Device Available
        virtual bool isAudioCaptureDeviceAvailable();
        //! Get A List of Available Audio Capture Devices
        virtual std::vector<std::string> getAudioCaptureDevices();
        //! Get Audio Capture Device by Number
        virtual CaptureDevice* getAudioCaptureDevice(int id);

    protected:
        // Capture Device Map
        std::vector<CaptureDevice*> captureDevices;

//    // ****************
//    // * LUA BINDINGS *
//    // ****************
//    public:
//        //! Bind this class to a lua state
//        static void bindToLua(lua_State* pLuaState);
};

#endif // AUDIOSYSTEM_H
