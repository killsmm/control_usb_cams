#ifndef _CAMERA_BRANDA_H
#define _CAMERA_BRANDA_H

#include "camera.h"

class CameraBrandA : Camera {
public:
    CameraBrandA();
    ~CameraBrandA();
    int init(libusb_device *device);
    int open();
    int close();
    int capture(const char *path);
    int setExp(uint32_t exp_time_ms);
    int setTrigMode(TrigMode mode);
    int getId();
    int setGain(uint32_t gain);
};

#endif