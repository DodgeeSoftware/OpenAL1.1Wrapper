/**
  * @file   AudioSystem.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  AudioSystem is a simple wrapper around the OpenAL AudioDevice
  * and the OpenAL AudioDevice context and provides basic services like
  * indexing Recording devices, makie quieries about extensions, setting
  * the global music/sound volume and setting the listener position
*/

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

/** @class AudioSystem
  * @brief A container around an OpenAL Device and Context
  * @detail This class is the core of Audio in the wrapper.
  * Initialise this before using the wrapper and be sure
  * to shutdown when you are finished with it. Use this to set
  * the position of the listener, get the frequency of the audio
  * device, record audio and set globals such as muting the
  * AudioSystem or changing System Volume (OpenAL doesn't support
  * global volume / mute, I tried to implement them myself and
  * OpenAL's design isn't very flexible this way) **/
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

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        // Methods and members

    protected:
        //! AudioSystem Assignment operator
        AudioSystem& operator=(const AudioSystem& other) { return *this; }

    // ***********
    // * GENERAL *
    // ***********
    public:
        /** @brief Initialise the AudioSystem
          * @return true on success false on failure **/
        virtual bool init();
        /** @brief Advance to the next frame **/
        virtual void update();
        /** @brief Shutdown the AudioSystem **/
        virtual void shutdown();

    public:
        /** @brief Is Default Audio Output Device Available
          * @return true if there is a default device available otherwise false **/
        virtual bool isDefaultAudioDeviceAvailable();
        /** @brief Get the Name of the Default Output Device (if there is one)
          * @return The Name of the Default Audio Device **/
        virtual std::string defaultAudioDeviceName();
        /** @brief Is there an Audio Output Device Available *
            @return true if there is an Audio Deviec Available otherwise false */
        virtual bool isAudioDeviceAvailable();
        /** @brief Get a list of Available Output Devices
          * @return an stl::vector of strings each entry containing
          * the name of a single Audio Device **/
        virtual std::vector<std::string> getAudioDevices();

    protected:
        // Pointer to the OpenAL AudioDevice
        ALCdevice* pAudioDevice;
        // Pointer to the OpenAL Context
        ALCcontext* pContext;

    // **********
    // * VENDOR *
    // **********
    public:
        /** @brief Get the OpenAL Driver Vendor
          * @return The name of the Vendor **/
        virtual std::string getVendor();

    protected:
        // Members and Methods

    // ***********
    // * VERSION *
    // ***********
    public:
        /** @brief Get the Version of OpenAL
          * @return The version of OpenAL **/
        virtual std::string getVersion();

    protected:
        // Members and Methods

    // ************
    // * RENDERER *
    // ************
    public:
        /** @brief Get Renderer for OpenAL
          * @return The OpenAL renderer **/
        virtual std::string getRenderer();

    protected:
        // Members and Methods

    // *************
    // * FREQUENCY *
    // *************
    public:
        /** @brief Get frequency
          * @return The Device Requency
          * (aka 22050 htz or 44100htz) **/
        virtual int getFrequency();

    protected:
        // Members and Methods

    // ****************
    // * REFRESH RATE *
    // ****************
    public:
        /** @brief Get Refresh Rate
          * @return The rate at which OpenAL updates
          * in frames per second **/
        virtual int getRefreshRate();

    protected:
        // Members and Methods

    // **************
    // * EXTENSIONS *
    // **************
    public:
        /** @brief Get A list of Extensions
          * @return A string with a list of extensions **/
        virtual std::string getExtensions();
        /** @brief Is Extension Present?
          * @return true if an extension is present otherwise false **/
        virtual bool isExtensionPresent(std::string extensionName);

    protected:
        // Members and Methods

    // ******************
    // * DOPPLER FACTOR *
    // ******************
    public:
        /** @brief Get Doppler Factor
          * @return the Doppler Factor **/
        virtual float getDopplerFactor();
        /** @brief Set Doppler Factor **/
        virtual void setDopplerFactor(float dopplerFactor);

    protected:
        // Members and Methods

    // ******************
    // * SPEED OF SOUND *
    // ******************
    public:
        /** @brief Get Speed of Sound
          * @return The Speed Of Sound being used **/
        virtual float getSpeedOfSound();
        /** @brief Set Speed of Sound **/
        virtual void setSpeedOfSound(float speed);

    protected:
        // Members and Methods

    // ************
    // * LISTENER *
    // ************
    /* NOTE: Listener functions will only affect positional audio */
    public:
        /** @brief Get Listener X
          * @return listener X **/
        virtual float getListenerX();
        /** @brief Get Listener Y
          * @return listener Y **/
        virtual float getListenerY();
        /** @brief Get Listener Z
          * @return listener Z **/
        virtual float getListenerZ();
        /** @brief Set Listener 2D Position
          * @param x[in] horizontal position
          * @param y[in] vertical position **/
        virtual void setListenerPosition(float x, float y);
        /** @brief Set Listener 3D Position
          * @param x[in] horizontal position
          * @param y[in] horizontal position
          * @param z[in] vertical position **/
        virtual void setListenerPosition(float x, float y, float z);
        /** @brief Set Listener Direction
          * @param directionX[in] x part of the direction vector the listener is facing
          * @param directionY[in] y part of the direction vector the listener is facing
          * @param directionZ[in] z part of the direction vector the listener is facing
          * @param upX[in] the x part of the upward vector for the listener
          * @param upY[in] the y part of the upward vector for the listener
          * @param upZ[in] the z part of the upward vector for the listener **/
        virtual void setListenerDirection(float directionX, float directionY, float directionZ, float upX, float upY, float upZ);

    protected:
        // Methods and members

    // ******************
    // * DISTANCE MODEL *
    // ******************
    public:
        /** @brief Get the Distance Model
          * @return the distance model being used.
          * NOTE: I have been unable to find documentation
          * that explains this**/
        virtual int getDistanceModel();
        /** @brief Set Distance Model
          * @param[in] model the distane model to be used
          * NOTE: I have been unable to find documentation **/
        virtual void setDistanceModel(int model);

    // **********************************
    // * ENABLED / DISABLE CAPABILITIES *
    // **********************************
    /* NOTE: This section exists to enable and disable
        context capabilities */
    public:
        /** @brief Is Context Capability Enabled
          * @param feature[in] the feature we are querying **/
        virtual bool isEnabled(int feature);
        /** @brief Enable context capablility
          * @param feature[in] the feature we are enabling **/
        virtual void enable(int feature);
        /** @brief Disable context capablility
          * @param feature[in] the feature we are enabling **/
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
        /** @brief Get Music Volume
            @return the music volume in the range of 0.0f - 1.0f **/
        virtual float getMusicVolume();
        /** @brief Set Music Volume
          * @param volume[in] the volume in the range of 0.0f - 1.0f **/
        virtual void setMusicVolume(float volume);
        /** @brief Get Sound Volume
          * @return the sound volume in the range of 0.0f - 1.0f **/
        virtual float getSoundVolume();
        /** @brief Set Sound Volume
          * @param volume[in] the sound volume in the range of 0.0f - 1.0f **/
        virtual void setSoundVolume(float volume);
        /** @brief Is Mute
          * @return true if the AudioSystem is muted false otherwise **/
        virtual bool isMute();
        /** @brief Set Mute Flag
          * @param state[in] true to mute the AudioSystem false otherwise **/
        virtual void setMute(bool state);
        /** @brief Mute the AudioSystem **/
        virtual void mute();
        /** @brief Unmute the AudioSystem **/
        virtual void unmute();

    protected:
        // Methods and members

    // *************
    // * RECORDING *
    // *************
    public:
        /** @brief Is Default Audio Capture Device Available
          * @return true if there is a default audio capture device available otherwise false **/
        virtual bool isDefaultAudioCaptureDeviceAvailable();
        /** @brief Get Default Audio CaptureDevice Name
          * @return the name of the Default Audio CaptureDevice**/
        virtual std::string getDefaultAudioCaptureDeviceName();
        /** @brief Is any Audio Capture Device Available
          * @return true if there is a audio capture device available otherwise false **/
        virtual bool isAudioCaptureDeviceAvailable();
        /** @brief Get A List of Available Audio Capture Devices
          * @return an stl vector where each element is the string name
          * of an AudioDevice **/
        virtual std::vector<std::string> getAudioCaptureDevices();
        /** @brief Get Audio Capture Device by Number
          * @param id[in] a numberic ID associated with the CaptureDevice (0 being the first and default)
          * @return A CaptureDevice **/
        virtual CaptureDevice* getAudioCaptureDevice(int id);
        /** @brief Get CaptureDeviceCount
          * @return the number of Capture Devices available **/
        virtual int getCaptureDeviceCount();

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
