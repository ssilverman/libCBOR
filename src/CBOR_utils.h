// CBOR_utils.h contains definitions for some CBOR utility functions.
// This is part of libCBOR.
// (c) 2017 Shawn Silverman

#ifndef CBOR_UTILS_H_
#define CBOR_UTILS_H_

// C++ includes
#include <cstddef>

namespace qindesign {
namespace cbor {

// Checks if the data in the EEPROM at the given input stream is valid CBOR.
// It is assumed that EEPROM has been initialized and that the EEPROM size
// and address are valid.
//
// This returns false if the address is negative or the EEPROM size is zero.
bool isEEPROMWellFormed(size_t eepromSize, int address);

}  // namespace cbor
}  // namespace qindesign

#endif  // CBOR_UTILS_H_
