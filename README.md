# libCBOR

This is a library for processing CBOR data.

## Features

Notable features of this library:

1. Handles and identifies well-formed and not-well-formed CBOR data.
2. Provides utility functions to make it easier to parse data.
3. Provides some Stream and Print implementations to make it easy to
   interface with byte arrays and the EEPROM.

## How to use

The classes you'll need are in the `qindesign::cbor` namespace:
`Reader` and `Writer`. A complete example of how to use them are in
`StructInBytes`.

The main class documentation can be found in `src/CBOR.h`. Other documentation
can be found as follows:

* Utility functions: `src/CBOR_utils.h`
* `Stream` and `Print` implementations: `src/CBOR_streams.h`
* Parsing helpers: `src/CBOR_parsing.h`

## Installing as an Arduino library

Not all the files in this project are necessary in an installed library.
Only the following files and directories need to be there:

* `examples/`
* `library.properties`
* `LICENSE`
* `README.md`
* `src/CBOR*`

## Running the tests

There are tests included in this project that rely on a project called
[ArduinoUnit](https://github.com/mmurdoch/arduinounit). This should work
out of the box on a Teensy, but some modifications may need to be made for
ESP8266-based devices.

Note that the code for ArduinoUnit is not included in this library and needs
to be downloaded separately.

### Running the tests on an ESP8266-based device

In ArduinoUnit's source, change `ArduinoUnitUtility/Compare.h` so that the
`#if defined(F)` block at the top is changed to:

```c++
#if defined(F)
#ifdef ESP8266
#define typeof(x) __typeof__(x)
#undef PROGMEM
#define PROGMEM
#undef PGM_P
#define PGM_P  		 const char *
#undef PGM_VOID_P
#define PGM_VOID_P const void *
#undef PSTR
#define PSTR(s) (s)
#undef pgm_read_byte
#define pgm_read_byte(addr) (*reinterpret_cast<const uint8_t*>(addr))
#undef pgm_read_word
#define pgm_read_word(addr) (*reinterpret_cast<const uint16_t*>(addr))
#else
#include <avr/pgmspace.h>
#endif  // ESP8266
#endif
```

## Code style

Code style for this project follows the
[Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html).

## References

1. Concise Binary Object Representation (CBOR):
   [RFC 7049](https://tools.ietf.org/html/rfc7049)

---

Copyright (c) 2017 Shawn Silverman
