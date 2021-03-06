#ifndef TOOLS_SHARED_TIMECONVERTER_H
#define TOOLS_SHARED_TIMECONVERTER_H

#include <cstdint>

#include "CommonOptions.h"
#include "FileInfo.h"

namespace mdf::tools::shared {

    [[nodiscard]] time_t convertTimeStamp(DisplayTimeFormat const& displayTimeFormat, time_t timeStamp, FileInfo const& loggerInfo);

}

#endif //TOOLS_SHARED_TIMECONVERTER_H
