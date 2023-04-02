#ifndef IMG2VIDEO_HPP
#define IMG2VIDEO_HPP

#include <vector>
#include <string>

namespace Img2Video {

    static const uint32_t majorVersion = 0;
    static const uint32_t minorVersion = 0;
    static const uint32_t patchVersion = 1;

    /**
     * This struct contains the user inputs
     * (or default values) for conversion
    */
    struct ConversionInfo {
        float fps;
        std::string input;
        std::string output;
        std::string exeLocation;
    };
    
    /**
     * Checks whether FFMpeg is installed on the system
     * @param exeLocation The deduced location of FFMpeg
    */
    bool checkInstall(ConversionInfo& info);

    /**
     * Run the conversion
     * @param info The conversion infos
     * @return The return code
    */
    int runConversion(const ConversionInfo& info);
}

#endif //IMG2VIDEO_HPP