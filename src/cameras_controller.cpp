#include "cameras_controller.h"
#include "camera_brandA.h"
#include "camera_brandB.h"
#include "string"
#include "camera_config.h"
#include "libusb.h"

CamerasController::CamerasController() {
    
}

CamerasController::~CamerasController() {
    this->deInit();
    for (Camera *c : this->camera_list){
        delete c;
    }
}

CamerasController CamerasController::getInstance() {
    static CamerasController instance;
    return instance;
}

int CamerasController::init() {
    return libusb_init(&this->usb_ctx);
}

void CamerasController::deInit() {
    libusb_free_device_list(this->udev_list, 1);
}

int CamerasController::scanCameras() {
    int ret = 0;
    int count = 0;
    
    this->camera_list.clear();

    count = libusb_get_device_list(this->usb_ctx, &this->udev_list);
    if (count < 0) {
        return count;
    }

    struct libusb_device_descriptor desc;
    for (int i = 0; i < count; i++) {
        ret = libusb_get_device_descriptor(this->udev_list[i], &desc);
        if (ret != 0) {
            continue;
        }
#if CAMERA_CONFIG == CAMERA_BRANDA
        CameraBrandA *cam;
        if (desc.idVendor == BRANDA_USB_VENDOR_ID && desc.idProduct == BRANDA_USB_PRODUCT_ID){
            cam = new CameraBrandA();
        }else{
            continue;
        }
#elif CAMERA_CONFIG == CAMERA_BRANDB
        CameraBrandB *cam;
        if (desc.idVendor == BRANDB_USB_VENDOR_ID && desc.idProduct == BRANDB_USB_PRODUCT_ID){
            cam = new CameraBrandB();
        }else{
            continue;
        }
#endif
        ret = cam->init(this->udev_list[i]);
        if (ret != 0) {
            delete cam;
            continue;
        }
        this->camera_list.push_back((Camera*)cam);
    }
    return 0;
}

int CamerasController::captureAll(std::string path) {
    for (Camera *cam : this->camera_list){
        cam->capture(path.append(std::to_string(cam->getId())).c_str());
    }
    return 0;
}

int CamerasController::setAllExpTime(uint32_t exp_time_ms) {
    int ret = 0;
    for(Camera *cam : this->camera_list){
        ret = cam->setExp(exp_time_ms);
        return ret;
    }
    return 0;
}

int CamerasController::setAllTrigMode(TrigMode mode){
    int ret = 0;
    for(Camera *cam : this->camera_list){
        ret = cam->setTrigMode(mode);
        return ret;
    }
    return 0;
}

int CamerasController::openAllCameras() {
    int ret = 0;
    for(Camera *cam : this->camera_list){
        ret = cam->open();
        if (ret != 0) {
            return ret;
        }
    }
    return 0;
}

int CamerasController::closeAllCameras() {
    int ret = 0;
    for(Camera *cam : this->camera_list){
        ret = cam->close();
        if (ret != 0) {
            return ret;
        }
    }
    return 0;
}

Camera* CamerasController::openCameraWithID(int id){
    for(Camera *cam : this->camera_list){
        if(cam->getId() == id && cam->open() == 0){
            return cam;
        }
    }
    return nullptr;
}

