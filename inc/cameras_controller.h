#ifndef _CAMERAS_CONTROLLER_H
#define _CAMERAS_CONTROLLER_H

#include "camera.h"
#include "vector"
#include "string"

class CamerasController{
public:
    static CamerasController getInstance();
    int scanCameras();
    int captureAll(std::string path);
    int setAllExpTime(unsigned int exp_time_ms);
    int setAllTrigMode(TrigMode mode);
    int openAllCameras();
    int closeAllCameras();
    int init();
    void deInit();
    Camera* openCameraWithID(int id);
    std::vector<Camera*> camera_list;
    ~CamerasController();

private:
    libusb_context *usb_ctx;
    libusb_device **udev_list;
    CamerasController();

};

#endif // !_CAMERA_CONTROLLER