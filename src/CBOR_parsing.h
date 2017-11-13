// CBOR_parsing.h contains functions that help with parsing CBOR data.
// This is part of libCBOR.
// (c) 2017 Shawn Silverman

#ifndef CBOR_PARSING_H_
#define CBOR_PARSING_H_

// C++ includes
#include <cstdint>

// Project includes
#include "CBOR.h"

namespace qindesign {
namespace cbor {

// ***************************************************************************
//  Expectation functions. All of these functions treat end-of-stream as
//  an unexpected value.
// ***************************************************************************

// Expects a certain type and value. This will always return false for
// some data types having no value or a non-integral value: boolean, null,
// undefined, break, floating-point.
bool expectValue(Reader r, DataType dt, uint64_t val);

// Expects a half- or single-precision floating-point value. Zero and
// negative zero are considered different values.
bool expectFloatValue(Reader r, float f);

// Expects a double-precision floating-point value. Zero and negative zero
// are considered different values.
bool expectDoubleValue(Reader r, double d);

// Expects that the next data item is a boolean and has the value 'true'.
bool expectTrue(Reader r);

// Expects that the next data item is a boolean and has the value 'false'.
bool expectFalse(Reader r);

// Expects and fills in an unsigned value. This returns true if the data item
// is an unsigned value and false otherwise.
bool expectUnsignedInt(Reader r, uint64_t *u);

// Expects and fills in a negative value. This returns true if the data item
// is a negative value and false otherwise.
bool expectInt(Reader r, int64_t *i);

// Expects bytes and fills in the length. This returns true if the data
// item is non-indefinite length bytes and false otherwise.
bool expectBytes(Reader r, uint64_t *length);

// Expects bytes having indefinite length. This returns true if the data
// item is one of these and false otherwise.
bool expectIndefiniteBytes(Reader r);

// Expects text and fills in the length. This returns true if the data
// item is non-indefinite length text and false otherwise.
bool expectText(Reader r, uint64_t *length);

// Expects text having indefinite length. This returns true if the data
// item is one of these and false otherwise.
bool expectIndefiniteText(Reader r);

// Expects an array and fills in the length. This returns true if the data
// item is a non-indefinite length array and false otherwise.
bool expectArray(Reader r, uint64_t *length);

// Expects an indefinite length array. This returns true is the data item
// is one of these and false otherwise.
bool expectIndefiniteArray(Reader r);

// Expects a map and fills in the length. This returns true if the data
// item is a non-indefinite length map and false otherwise.
bool expectMap(Reader r, uint64_t *length);

// Expects an indefinite length map. This returns true is the data item
// is one of these and false otherwise.
bool expectIndefiniteMap(Reader r);

// Expects and fills in a boolean value. This returns true if the data item
// is a boolean and false otherwise.
bool expectBoolean(Reader r, bool *b);

// Expects and fills in a single-precision floating-point value. This returns
// true if the data item is one of these and false otherwise.
bool expectFloat(Reader r, float *f);

// Expects and fills in a double-precision floating-point value. This returns
// true if the data item is one of these and false otherwise.
bool expectDouble(Reader r, double *d);

// Expects a null value. This returns true if the data item is a null value
// and false otherwise.
bool expectNull(Reader r);

// Expects an undefined value. This returns true if the data item is an
// undefined value and false otherwise.
bool expectUndefined(Reader r);

// Expects and fills in a simple 1-byte value. This returns true if the data
// item is one of these and false otherwise.
bool expectSimpleValue(Reader r, uint8_t *v);

// // Expects a non-numerical and non-boolean simple value. The set of allowed
// // values includes null, undefined, and break.
// // This returns true if the data item is the expected type and false otherwise.
// bool expectSimpleValue(Reader r, DataType dt);

// Expects and fills in a tag. This returns true if the data item is one
// of these and false otherwise.
bool expectTag(Reader r, uint64_t *v);

// ***************************************************************************
//  Read functions.
// ***************************************************************************

// Attempts to read exactly len bytes into b. This will return the actual
// number of bytes read, a smaller number than len only if the stream
// encountered end-of-stream.
unsigned int readFully(Reader r, uint8_t *b, size_t len);

// Reads from the reader until there's some data available. If end-of-stream
// is encountered then this yields and keeps looking. Forever.
DataType readUntilData(Reader r);

}  // namespace cbor
}  // namespace qindesign

#endif  // CBOR_PARSING_H_
