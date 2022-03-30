#ifndef _CAMERA_H
#define _CAMERA_H
#include "stdint.h"
#include "libusb.h"

enum TrigMode : uint8_t
{
    TRIG_MODE_HARDWARE = 0,
    TRIG_MODE_SOFTWARE,
    TRIG_MODE_UNKNOWN,
    TRIG_MODE_MAX
};

class Camera{
public:
    virtual int init(libusb_device *device) = 0;
    virtual int open() = 0;
    virtual int close() = 0;
    virtual int capture(const char *path) = 0;
    virtual int setExp(uint32_t exp_time_ms) = 0;
    virtual int setTrigMode(TrigMode mode) = 0;
    virtual int setGain(uint32_t gain) = 0;
    virtual int getId() = 0;
protected:
    struct libusb_device *udev;
};

#endif