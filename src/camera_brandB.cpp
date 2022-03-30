#include "camera_brandB.h"
#include "brandB_sdk.h"
#include "iostream"

CameraBrandB::CameraBrandB() {
    
}

CameraBrandB::~CameraBrandB() {
    
}

int CameraBrandB::init(libusb_device *device) {
    this->udev = device;
    return 0;
}

int CameraBrandB::open() {
    //call camera brandB sdk
    return 0;
}

int CameraBrandB::close() {
    //call camera brandB sdk
    return 0;
}

int CameraBrandB::capture(const char *path) {
    //call camera brandB sdk
    std::cout << "brand B camera capture" << std::endl;
    return 0;
}

int CameraBrandB::setExp(uint32_t exp_time_ms) {
    //call camera brandB sdk
    return 0;
}

int CameraBrandB::setTrigMode(TrigMode mode) {
    //call camera brandB sdk
    return 0;
}

int CameraBrandB::getId(){
    int id = 0x1234;
    //call camera brandB sdk
    return id;
}

int CameraBrandB::setGain(uint32_t gain) {
    if (gain < 0 && gain > 16) {
        return -1;
    }
    return 0;
}
