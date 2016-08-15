#include "CaptureDevice.h"

bool CaptureDevice::open(int frequency, int format, int bufferSize)
{
    // Open the Capture device
    this->pCaptureDevice = alcCaptureOpenDevice(this->name.c_str(), frequency, format, bufferSize);
    // If no capture device was found
    if (this->pCaptureDevice == 0)
    {
        // Show Error
        std::cout << "ERROR: " << Utils::getALErrorString(alGetError()) << std::endl;
        // return false
        return false;
    }
    // return true
    return true;
}

void CaptureDevice::close()
{
    // Close the device (if one is open)
    if (this->pCaptureDevice != 0)
    {
        // Close the Capture Device
        alcCaptureCloseDevice(this->pCaptureDevice);
        // Clear the Pointer to the Capture Device
        this->pCaptureDevice = 0;
    }
}

void CaptureDevice::start()
{
    // Validate Capture Device
    if (this->pCaptureDevice == 0)
        return;
    // Start Capturing Audio
    alcCaptureStart(this->pCaptureDevice);
}

void CaptureDevice::stop()
{
    // Validate Capture Device
    if (this->pCaptureDevice == 0)
        return;
    // Stop Capturing Audio
    alcCaptureStop(this->pCaptureDevice);
}

void CaptureDevice::captureSamples(void* pBuffer, int samples)
{
    // Validate Capture Device
    if (this->pCaptureDevice == 0)
        return;
    // Capture Audio Samples
    alcCaptureSamples(this->pCaptureDevice, pBuffer, samples);
}
