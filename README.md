# NDK with OpenCV

This application is a sample Android Studio project with native OpenCV.

## Usage

- Make sure you have Android SDK up to date, with NDK installed and CMake
- Download latest [OpenCV SDK](https://opencv.org/releases/)(_blank) for Android from OpenCV.org and decompress the zip file.
- Clone this project
- Copy the OpenCV SDK to opencv_sdk folder
- In app/CMakeLists.txt change line 9 to points to YOUR_OPENCV_SDK/sdk/native/jni/include
- Sync gradle
- Run the application

## Licence
MIT