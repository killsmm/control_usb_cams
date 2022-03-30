# Assumptions
1. Each of the camera provider provides different SDKs
2. Don't need to consider cameras unplugged unexpectedly during operating.
3. Each camera would give out their vender_id and product_id correctly
    (different manufactorer with different vender_id)

# Directories description
* camera_sdks: sdk provided by venders without modification
* header files created for this project
* source files created for this project


# Porting new camera steps
1. Put the new sdk into a seperated directory in "camera_sdks" folder
2. Create a new class inheriting Camera class which is defined in camera.h
3. Edit camera_config.h. Define a new macro like "#define CAMERA_BRANDC 1" and define macro CAMERA_CONFIG to the new macro.
4. Edit CamerasController::scanCameras() function to adapt the new camera macro

# Future improvment
1. In order to support multiply camera types , auto recognize camera type by USB Vendor Id and create correponding camera devices.
2. Porting generic uvc camera to support all the cameras with uvc standard protocol.

