#include "CBOR_utils.h"

// Project includes
#include "CBOR.h"
#include "Streams.h"

namespace qindesign {
namespace cbor {

bool isEEPROMWellFormed(size_t eepromSize, int address) {
  if (address < 0 || eepromSize == 0) {
    return false;
  }
  EEPROMStream es{eepromSize, address};
  CBORReader cbor{es};
  return cbor.isWellFormed();
}

}  // namespace cbor
}  // namespace qindesign
