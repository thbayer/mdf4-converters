#ifndef MDFSIMPLECONVERTERS_CABLOCK_H
#define MDFSIMPLECONVERTERS_CABLOCK_H

#include "MdfBlock.h"

namespace mdf {

  struct CABlock : MdfBlock {
    [[nodiscard]] std::shared_ptr<MdfBlock> getCompositionBlock() const;

  protected:
    bool load(uint8_t const *dataPtr) override;

    bool saveBlockData(uint8_t *dataPtr) override;

    uint8_t type;
    uint8_t storage;
    uint16_t ndim;
    uint32_t flags;
    int32_t byteOffsetBase;
    uint32_t invalBitPosBase;

    std::vector<uint64_t> dimSize;
  };

}

#endif //MDFSIMPLECONVERTERS_CABLOCK_H
