#include "cameras_controller.h"
#include <iostream>
#include <string>
#include <getopt.h>

#define FLAG_SET_EXP 1
#define FLAG_CAPTURE (1 << 1)
#define FLAG_SET_TRIG_MODE (1 << 2)
#define FLAG_SCAN_CAM (1 << 3)
#define FLAG_OPEN_ALL (1 << 4)
#define FLAG_CLOSE_ALL (1 << 5)

static CamerasController controller = CamerasController::getInstance();

static int scan_cameras()
{
    int ret = 0;
    int count = 0;
    ret = controller.init();
    if (ret != 0)
    {
        std::cerr << "init controller failed" << std::endl;
        return ret;
    }
    ret = controller.scanCameras();
    if (ret != 0)
    {
        std::cerr << "scan camera failed" << std::endl;
        return ret;
    }
    count = controller.camera_list.size();
    std::cout << count << " cameras found" << std::endl;
    for (Camera *cam : controller.camera_list)
    {
        std::cout << "ID = " << std::to_string(cam->getId()) << std::endl;
    }
    return 0;
}

static int capture_all_cameras_one_frame(std::string path)
{
    int ret = 0;
    ret = controller.openAllCameras();
    if (ret != 0)
    {
        std::cerr << "open all camera failed" << std::endl;
        return ret;
    }
    ret = controller.setAllExpTime(10);
    if (ret != 0)
    {
        std::cerr << "init controller failed" << std::endl;
        return ret;
    }
    ret = controller.captureAll(path);
    if (ret != 0)
    {
        std::cerr << "init controller failed" << std::endl;
        return ret;
    }
}

const char *help_text =
"control_usb_cams\n" 
"[-h]: print this help\n"
"[-s]: scan and list connected cameras\n"
"[-t trig_mode]: set trigger mode for all connected cameras\n"
"              trig_mode 0: hardware 1: software\n"
"[-c]: capture one picture \n"
"[-e exp_time]: set exposure time for all connected cameras unit:ms\n";

static void print_help(){
    std::cout << help_text << std::endl;
}

int main(int argc, char **argv)
{
    int ret = 0;
    const char *optstring = "st:c:e:h"; 
    int opt = 0;
    int flag = 0;
    int exp_time = 0;
    TrigMode trig_mode;
    char *path;
    while ((opt = getopt(argc, argv, optstring)) != -1)
    {
        switch (opt)
        {
        case 's':
            flag |= FLAG_SCAN_CAM;
            break;
        case 'e':
            flag |= FLAG_SET_EXP;
            exp_time = atoi(optarg);
            break;
        case 'c':
            flag |= FLAG_CAPTURE;
            path = optarg;
            break;
        case 'h':
            print_help();
            return 0;
        case 't':
            flag |= FLAG_SET_TRIG_MODE;
            if (atoi(optarg) >= TRIG_MODE_MAX) {
                print_help();
                return 0;
            }
            trig_mode = (TrigMode)atoi(optarg);
            break;
        default:
            break;
        }
    }

    if (0 == flag) {
        print_help();
        return 0;
    }

    ret = scan_cameras();
    if (ret != 0) {
        std::cerr << "scan camera failed, return = " << ret << std::endl;
        return ret;
    }

    if (flag & FLAG_SET_EXP) {
        ret = controller.setAllExpTime(exp_time);
        if (ret != 0){
            std::cerr << "set exposure time failed, return = " << ret << std::endl;
            return ret;
        }
    }

    if (flag & FLAG_SET_TRIG_MODE) {
        ret = controller.setAllTrigMode(trig_mode);
        if (ret != 0){
            std::cerr << "set trig mode failed, return = " << ret << std::endl;
            return ret;
        }
    }

    if (flag & FLAG_CAPTURE) {
        ret = controller.captureAll(std::string(path));
        if (ret != 0){
            std::cerr << "capture all failed, return = " << ret << std::endl;
            return ret;
        }
    }
    return ret;
}