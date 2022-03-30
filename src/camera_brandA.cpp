#include "camera_brandA.h"
#include "brandA_sdk.h"
#include "iostream"

CameraBrandA::CameraBrandA() {
    
}

CameraBrandA::~CameraBrandA() {
    
}

int CameraBrandA::init(libusb_device *device) {
    this->udev = device;
    return 0;
}

int CameraBrandA::open() {
    //call camera brandA sdk
    return 0;
}

int CameraBrandA::close() {
    //call camera brandA sdk
    return 0;
}

int CameraBrandA::capture(const char *path) {
    //call camera brandA sdk
    std::cout << "brand A camera capture" << std::endl;
    return 0;
}

int CameraBrandA::setExp(uint32_t exp_time_ms) {
    //call camera brandA sdk
    return 0;
}

int CameraBrandA::setTrigMode(TrigMode mode) {
    //call camera brandA sdk
    return 0;
}

int CameraBrandA::getId() {
    int id = 1234;
    //call camera brandA sdk
    return id;
}

int CameraBrandA::setGain(uint32_t gain) {
    if (gain < 0 && gain > 16) {
        return -1;
    }
    return 0;
}
