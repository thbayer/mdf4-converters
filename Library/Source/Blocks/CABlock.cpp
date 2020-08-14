#include "CABlock.h"

#include <boost/endian/buffers.hpp>

namespace mdf {

#pragma pack(push, 1)
  struct CABlockData {
    boost::endian::little_uint8_buf_t ca_type;
    boost::endian::little_uint8_buf_t ca_storage;
    boost::endian::little_uint16_buf_t ca_ndim;
    boost::endian::little_uint32_buf_t ca_flags;
    boost::endian::little_int32_buf_t ca_byte_offset_base;
    boost::endian::little_uint32_buf_t ca_inval_bit_pos_base;
  };
#pragma pack(pop)

  std::shared_ptr<MdfBlock> CABlock::getCompositionBlock() const {
    return links[0];
  }

  bool CABlock::load(uint8_t const *dataPtr) {
    bool result = false;
    dimSize.clear();

    // Load data into a struct for easier access.
    auto ptr = reinterpret_cast<CABlockData const *>(dataPtr);

    type = ptr->ca_type.value();
    storage = ptr->ca_storage.value();
    ndim = ptr->ca_ndim.value();
    flags = ptr->ca_flags.value();
    byteOffsetBase = ptr->ca_byte_offset_base.value();
    invalBitPosBase = ptr->ca_inval_bit_pos_base.value();

    dataPtr += sizeof(CABlockData);

    // Load dimension values
    for (uint16_t i = 0; i < ndim; ++i) {
        auto value = reinterpret_cast<boost::endian::little_uint64_buf_t const*>(dataPtr);
        dimSize.emplace_back(value->value());
        dataPtr += sizeof(boost::endian::little_uint64_buf_t);
    }

    result = true;

    return result;
  }

  bool CABlock::saveBlockData(uint8_t *dataPtr) {
    auto ptr = reinterpret_cast<CABlockData *>(dataPtr);

    ptr->ca_type = type;
    ptr->ca_storage = storage;
    ptr->ca_ndim = ndim;
    ptr->ca_flags = flags;
    ptr->ca_byte_offset_base = byteOffsetBase;
    ptr->ca_inval_bit_pos_base = invalBitPosBase;

    dataPtr += sizeof(CABlockData);

    // Write dimension values.
    for(auto const& value: dimSize) {
        auto v = reinterpret_cast<boost::endian::little_uint64_buf_t*>(dataPtr);
        *v = value;
        dataPtr += sizeof(boost::endian::little_uint64_buf_t);
    }

    return true;
  }

}
