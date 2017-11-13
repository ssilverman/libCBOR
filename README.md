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

## Code style

Code style for this project follows the
[Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html).

## References

1. Concise Binary Object Representation (CBOR):
   [RFC7049](https://tools.ietf.org/html/rfc7049)

---

Copyright (c) 2017 Shawn Silverman
