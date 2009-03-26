#include <windows.h>
#include <cstdlib>
#include <iostream>

using namespace std;

#define DLLIMPORT __declspec(dllimport)

typedef void (*lpTestPrint)(void);

int main(int argc, char *argv[])
{
    HINSTANCE hDll = 0;
    lpTestPrint print = NULL;
    
    hDll = ::LoadLibraryA("testDllExport.dll");
    
    cout << "hDll: " << (long)hDll << endl;
    
    print = (lpTestPrint)::GetProcAddress(hDll, "TestPrint");
    
    if (print)
    {
        print();
    }
    else
    {
        cout << "Load function fail!" << endl;   
    }
    
    system("PAUSE");
    
    FreeLibrary(hDll);
    return EXIT_SUCCESS;
}
