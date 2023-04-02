#ifdef I2V_WINDOWS

#include <Windows.h>

#include "Img2Video.hpp"

using namespace std;

namespace Img2Video { //TODO: Implement Windows IPC

    bool checkInstall(ConversionInfo& info) {
        return false;
    }

    int runConversion(const ConversionInfo& info) {
        return 0;
    }
}

#endif //I2V_WINDOWS