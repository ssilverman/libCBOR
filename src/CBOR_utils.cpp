#include "CBOR_utils.h"

// Project includes
#include "CBOR.h"
#include "CBOR_streams.h"

namespace qindesign {
namespace cbor {

bool isEEPROMWellFormed(size_t eepromSize, int address) {
  if (address < 0 || eepromSize == 0) {
    return false;
  }
  EEPROMStream es{eepromSize, address};
  Reader cbor{es};
  return cbor.isWellFormed();
}

}  // namespace cbor
}  // namespace qindesign
