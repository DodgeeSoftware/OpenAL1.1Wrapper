// ********************************
// * COMPANY: Dodgee Software     *
// * AUTHOR: Shem Taylor          *
// * Written 2016 Dodgee Software *
// * GPLv3                        *
// ********************************

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

/** The CaptureDevice Class is a container for
    a single capture / recording device **/
class CaptureDevice
{
    // *****************************
    // * CONSTRUCTORS / DESTRUCTOR *
    // *****************************
    public:
        //! Constructor
        CaptureDevice()
        {
            this->pCaptureDevice = 0;
            this->name.clear();
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
        //! Open Capture Device
        virtual bool open(int frequency, int format, int bufferSize);
        //! Close Capture Device
        virtual void close();
        //! Start
        virtual void start();
        //! Stop
        virtual void stop();
        //! Capture Samples
        virtual void captureSamples(void* pBuffer, int samples);
        //! Get Capture Device
        virtual ALCdevice* getCaptureDevice() { return this->pCaptureDevice; }

    protected:
        // Capture Device
        ALCdevice* pCaptureDevice;

    // ********
    // * NAME *
    // ********
    public:
        //! Get Name
        virtual std::string getName() { return this->name; }
        //! Set Name
        virtual void setName(std::string name) { this->name = name; }
        //! Is Named
        virtual bool isNamed() { return (this->name.size() > 0); }
        //! Clear Name
        virtual void clearName() { this->name.clear(); }

    protected:
        // unique name
        std::string name;

    // ******
    // * ID *
    // ******
    public:
        //! Get the ID
        virtual int getID() { return this->id; }
        //! Get the ID
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
