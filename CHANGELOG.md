This document details the changes between each release.

# libCBOR v1.3.0

Tag: v1.3.0

Changes in this release:
* Bug fixes:
  * `expectDoubleValue` was using a `float` internally.
  * `Reader::isWellFormed()` allowed nested indefinite-length bytes or text.
  * `Reader::getBoolean()` was allowing certain 1-byte simple values to
    function as booleans.
* Adding an `expectBoolean` helper function, for consistency.
* Removing `expectIndefiniteBytes` and `expectIndefiniteText` functions
  because there's no need to separate the syntactic difference. There's
  a new `isIndefinite` output parameter in `expectBytes`, `expectText`,
  `expectArray`, and `expectMap` for discovering indefinite-length data
  items.
* New `expectBytesOrBreak` and `expectTextOrBreak` helper functions for
  reading indefinite-length Bytes or Text chunks.
* The `readFully` helper function now returns a `size_t` instead of an
  `unsigned int`.
* Adding new `isFalse()`, `isTrue()`, `isNull()`, `isUndefined()`,
  and `isBreak()` functions to `Reader`.
* `Reader::getInt()` and the `expectInt` helper function can now read and
  expect both signed and unsigned integers. New `isNegativeOverflow()` and
  `isUnsigned()` functions in `Reader` help disambiguate some special cases.
* Documentation updates.

# libCBOR v1.2.0

Tag: v1.2.0

This release updates the API to include a way to access the read size and
write size, and also makes the Reader and Writer classes implement Stream
and Print, respectively. As well, the byte array and EEPROM Stream and Print
implementations now provide a way to access the internal index (or address,
in the case of EEPROM), for ease of determining how far reading or writing
has progressed.

# First libCBOR release

Tag: v1.1.0

This is the first release of the libCBOR library. It includes functions for
reading and writing, and helper functions for parsing and for processing
EEPROM.
