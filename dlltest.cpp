#include "DllExport.h"
#include <iostream>
using namespace std;
int main(int argc, char **argv)
{
    cout << SSIM_Percent("./3.png", "./3.png") << endl;

    return 0;
}