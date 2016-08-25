/**
  * @file   CaptureDevice.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  A CaptureDevice is a container for an AudioRecorder
*/

#ifndef CAPTUREDEVICE_H
#define CAPTUREDEVICE_H

// C/C++ Includes
#include <string>
#include <iostream>

// OPENAL Includes
#include <al.h>
#include <alc.h>

//// LUA AND LUABIND Includes
//extern "C"
//{
//    #include <lua.h>
//    #include <lualib.h>
//    #include <lauxlib.h>
//}
//#include <luabind/luabind.hpp>

// GAME AUDIO Includes
#include "Utils/OpenALUtils.h"
#include "Utils/OpenALVector2D.h"
#include "Utils/OpenALVector3D.h"
#include "Sound/SoundBuffer.h"

/** @class CaptureDevice
  * @brief A Container for a Single Audio Capture Device
  * @detail The CaptureDevice Class is a container for
  * a single capture / recording device **/
class CaptureDevice
{
    // *****************************
    // * CONSTRUCTORS / DESTRUCTOR *
    // *****************************
    public:
        //! Constructor
        CaptureDevice()
        {
            // Capture Device
            this->pCaptureDevice = 0;
            // Name
            this->name.clear();
            // ID
            this->id = 0;
        }
        //! Destructor
        virtual ~CaptureDevice() {}

    protected:
        //! Copy Constructor
        CaptureDevice(CaptureDevice& captureDevice) {}

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        // No functions

    protected:
        //! CaptureDevice Assignment operator
        CaptureDevice& operator=(const CaptureDevice& other) { return *this; }

    // *********************
    // * GENERAL FUNCTIONS *
    // *********************
    public:
        /**  @brief Open Capture Device
          *  @param[in] frequency The frequency in hertz to sample audio
          *  @param[in] format The format of the sample (i.e. AL_FORMAT_STEREO16 or AL_FORMAT_MONO16 etc)
          *  @return true on success / false on failure **/
        virtual bool open(int frequency, int format, int bufferSize);
        /** @brief Close Capture Device **/
        virtual void close();
        /** @brief Start **/
        virtual void start();
        /** @brief Stop **/
        virtual void stop();
        /** @brief Capture Samples
          * @param pBuffer[in] is a pointer to a buffer you made to contain the output of recording
          * @param samples[in] is the number of samples in the buffer
          * NOTE: stereo counts as 1 sample despite data for left and right but
          * your buffer needs to take into account both left and right data **/
        virtual void captureSamples(void* pBuffer, int samples);
        /** @brief Get Capture Device **/
        virtual ALCdevice* getCaptureDevice() { return this->pCaptureDevice; }

    protected:
        // Capture Device
        ALCdevice* pCaptureDevice;

    // ********
    // * NAME *
    // ********
    public:
        /** @brief Get Name
          * @return The name of this CaptureDevice **/
        virtual std::string getName() { return this->name; }
        /** @brief Set Name
          * @param name[in] The name for the device**/
        virtual void setName(std::string name) { this->name = name; }
        /** @brief Is Named
          * @return true if the device is named otherwise false **/
        virtual bool isNamed() { return (this->name.size() > 0); }
        /** @brief Clear Name **/
        virtual void clearName() { this->name.clear(); }

    protected:
        // unique name
        std::string name;

    // ******
    // * ID *
    // ******
    public:
        /** @brief Get the ID
          * @return The CaptureDevice's ID **/
        virtual int getID() { return this->id; }
        /** @brief Set the ID
          * @param id[in] Set CaptureDevice's ID **/
        virtual void setID(int id) { this->id = id; }

    protected:
        // ID
        int id;

//    // ****************
//    // * LUA BINDINGS *
//    // ****************
//    public:
//        //! Bind this class to a lua state
//        static void bindToLua(lua_State* pLuaState);
};

#endif // CAPTUREDEVICE_H
