#include "main.h"

#include "../Leap/LeapSDK/include/Leap.h"
#include "../Leap/LeapSDK/include/Leapmath.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>

Leap::Controller control;

struct fdata
{
    float fingers[40];
    float grab_confidence[2];
};

//float* tenfingers;

fdata get_finger_positions()
{
    Leap::Frame frame = control.frame();
    Leap::FingerList fingers = frame.fingers();
    Leap::ToolList tools = frame.tools();
    Leap::HandList hands = frame.hands();

    //std::vector<std::pair<cl_float4, int>> positions;

    fdata hand_data;


    int p = 0;

    for(int i=0; i<40; i++)
    {
        hand_data.fingers[i] = 0.0f;
    }

    ///will explode if more than 2
    for(int i=0; i<hands.count(); i++)
    {
        const Leap::Hand hand = hands[i];
        Leap::FingerList h_fingers = hand.fingers();

        float grab_strength = hand.grabStrength();

        hand_data.grab_confidence[i] = grab_strength;

        for(int j=0; j<h_fingers.count(); j++)
        {
            const Leap::Finger finger = h_fingers[j];

            float mfingerposx = finger.tipPosition().x;
            float mfingerposy = finger.tipPosition().y;
            float mfingerposz = finger.tipPosition().z;

            //cl_float4 ps = {mfingerposx, mfingerposy, mfingerposz, 0.0f};
            //cl_float4 ps = {mfingerposx, mfingerposy, mfingerposz, 0.0f};

            int id = finger.id();

            hand_data.fingers[p++] = mfingerposx;
            hand_data.fingers[p++] = mfingerposy;
            hand_data.fingers[p++] = mfingerposz;
            hand_data.fingers[p++] = 0.0f;

            //positions.push_back(std::pair<cl_float4, int>(ps, id));

        }
    }

    return hand_data;
}


/*extern "C" DLL_EXPORT BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
            //printf("lolo\n");
            LoadLibrary("Leap.dll");
            control = new Leap::Controller;
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // succesful
}*/

#define PNAME "\\\\.\\pipe\\LogPipe"
//#define PNAME "Local\\test"

/*int main()
{
    control.setPolicyFlags(Leap::Controller::POLICY_BACKGROUND_FRAMES);

    tenfingers = (float*)malloc(sizeof(float)*10*4);

    //HANDLE pipe = CreateFile(PNAME, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
    HANDLE hMapFile;
    volatile char* buf;

    int len = sizeof(float)*10*4;

    hMapFile = CreateFileMapping(
                 INVALID_HANDLE_VALUE,    // use paging file
                 NULL,                    // default security
                 PAGE_READWRITE,          // read/write access
                 0,                       // maximum object size (high-order DWORD)
                 len,                // maximum object size (low-order DWORD)
                 PNAME);

    //hMapFile = CreateFile("test", GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hMapFile == NULL)
    {
      printf(TEXT("Could not create file mapping object (%d).\n"),
             GetLastError());
      return 1;
    }


    //string message = "Hi";
    //WriteFile(pipe, message.c_str(), message.length() + 1, NULL, NULL);

    buf = (char*) MapViewOfFile(hMapFile,   // handle to map object
                        FILE_MAP_ALL_ACCESS, // read/write permission
                        0,
                        0,
                        len);

    if(buf == NULL)
    {
        std::cout << "uh oh " << GetLastError() << std::endl;
        CloseHandle(hMapFile);
        return 1;
    }

    while(1)
    {
        float* ret = get_finger_positions();

        //WriteFile(pipe, (char*)ret, sizeof(float)*10*4, &word, NULL);

        //memcpy(buf, ret, len);

        CopyMemory((PVOID)buf, (char*)ret, (sizeof(float)*40));

        //std::cout << ((float*)buf)[0] << std::endl;

        //Sleep((1.0f/115.0)*1000.0f);
    }

    CloseHandle(hMapFile);
}*/

HANDLE pipe;

void fin()
{
    CloseHandle(pipe);
}

int main()
{
    control.setPolicyFlags(Leap::Controller::POLICY_BACKGROUND_FRAMES);

    pipe = CreateFile(PNAME, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

    atexit(fin);

    //tenfingers = (float*)malloc(sizeof(float)*10*4);

    printf("connected\n");

    //get fist positions as well

    DWORD word = 0;

    while(1)
    {
        fdata ret = get_finger_positions();

        WriteFile(pipe, (char*)&ret, sizeof(fdata), &word, NULL);

        Sleep(1);
    }

    //CloseHandle(pipe);
}
