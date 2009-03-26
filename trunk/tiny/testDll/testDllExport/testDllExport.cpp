/* Replace "dll.h" with the name of your header */
#include "testDllExport.h"
#include <windows.h>

#include <iostream>
using namespace std;

DllClass::DllClass()
{

}


DllClass::~DllClass ()
{

}

void DllClass::Print(void)
{
    cout << "Hello, this is output of testDllExport project" << endl;   
}

BOOL APIENTRY DllMain (HINSTANCE hInst     /* Library instance handle. */ ,
                       DWORD reason        /* Reason this function is being called. */ ,
                       LPVOID reserved     /* Not used. */ )
{
    switch (reason)
    {
      case DLL_PROCESS_ATTACH:
        break;

      case DLL_PROCESS_DETACH:
        break;

      case DLL_THREAD_ATTACH:
        break;

      case DLL_THREAD_DETACH:
        break;
    }

    /* Returns TRUE on success, FALSE on failure */
    return TRUE;
}
extern "C" DLLIMPORT void TestPrint(void)
{
    DllClass* object = new DllClass();
    
    object->Print(); 
    
    delete object;
}
