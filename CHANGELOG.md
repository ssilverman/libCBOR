# Changelog

This document details the changes between each release.

## [1.3.1]

### Changed
* Moved the tests to a folder named `src_tests` for now. This makes it easier
  to directly reference this project as an Arduino and PlatformIO library.

## [1.3.0]

### Added
* `expectBoolean` helper function, for consistency.
* `expectBytesOrBreak` and `expectTextOrBreak` helper functions for reading
  indefinite-length Bytes or Text chunks.
* `isFalse()`, `isTrue()`, `isNull()`, `isUndefined()`, and `isBreak()`
  functions in `Reader`.
* `isNegativeOverflow()` and `isUnsigned()` functions in `Reader` help
  disambiguate some special cases when reading and expecting integer values
  via `Reader::getInt()` and `expectInt`.
* `isIndefinite` output parameter in `expectBytes`, `expectText`,
  `expectArray`, and `expectMap` for discovering indefinite-length data
  items.

### Changed
* The `readFully` helper function now returns a `size_t` instead of an
  `unsigned int`.
* `Reader::getInt()` and the `expectInt` helper function can now read and
  expect both signed and unsigned integers. New `isNegativeOverflow()` and
  `isUnsigned()` functions in `Reader` help disambiguate some special cases.
* Documentation updates.

### Removed
* `expectIndefiniteBytes` and `expectIndefiniteText` functions because
  there's no need to separate the syntactic difference. There's a new
  `isIndefinite` output parameter in `expectBytes`, `expectText`,
  `expectArray`, and `expectMap` for discovering indefinite-length data
  items.

### Fixed
* `expectDoubleValue` was using a `float` internally.
* `Reader::isWellFormed()` allowed nested indefinite-length bytes or text.
* `Reader::getBoolean()` was allowing certain 1-byte simple values to
  function as booleans.

## libCBOR v1.2.0

This release updates the API to include a way to access the read size and
write size, and also makes the Reader and Writer classes implement Stream
and Print, respectively. As well, the byte array and EEPROM Stream and Print
implementations now provide a way to access the internal index (or address,
in the case of EEPROM), for ease of determining how far reading or writing
has progressed.

## First libCBOR release

Tag: v1.1.0

This is the first release of the libCBOR library. It includes functions for
reading and writing, and helper functions for parsing and for processing
EEPROM.
