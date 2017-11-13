// CBOR.h defines CBOR functions.
// See [Concise Binary Object Representation (CBOR)](https://tools.ietf.org/html/rfc7049)

#ifndef QINDESIGN_CBOR_H_
#define QINDESIGN_CBOR_H_

#include <Print.h>
#include <Stream.h>

namespace qindesign {
namespace cbor {

// Tag that can be used to self-describe a CBOR item.
constexpr uint16_t kSelfDescribeTag = 55799;

enum class DataType {
  kUnsignedInt,
  kNegativeInt,
  kBytes,
  kText,
  kArray,
  kMap,
  kTag,
  kFloat,
  kDouble,
  kBoolean,
  kNull,
  kUndefined,
  kBreak,
  kSimpleValue,
  kEOS,
  kSyntaxError,
};

enum class SyntaxError {
  kNoError,
  kUnknownAdditionalInfo,
  kNotAnIndefiniteType,
  kBadSimpleValue,
};

// Reader provides a way to parse bytes in a CBOR-encoded stream. This
// class only provides rudimentary parsing for data items; callers will
// have to manage nested depths themselves.
//
// The readXXX() functions advance the stream, while the getXXX() functions
// do not.
//
// If any of the getXXX() functions are called and the type does not match,
// then a default value of zero or false is returned.
class Reader {
 public:
  Reader(Stream &in)
      : state_(State::kStart),
        in_(in),
        initialByte_(0),
        majorType_(0),
        addlInfo_(0),
        waitAvailable_(0),
        value_(0),
        syntaxError_(SyntaxError::kNoError) {}
  ~Reader() = default;

  // Reads the start byte of a data item. This returns -1 if the end of
  // stream has been reached. If this returns a non-negative number, then
  // this guarantees that all the bytes necessary for any attached value
  // are available from the stream.
  //
  // Once the type is known, one of the getXXX() functions can be called
  // to retrieve any immediate values. If this is called and returns
  // DataType::kEOS, then the data from any of the getXXX() functions will
  // be invalid.
  //
  // The allowBreak parameter indicates that the break character is allowed
  // because we are inside an indefinite length data item. If this parameter
  // is false, break characters will cause this to return a syntax error.
  DataType readDataType(bool allowBreak = false);

  // Reads data for bytes or text. It is up to the caller to read the correct
  // number of bytes, and also to concatenate any definite-length portions
  // of an idefinite-length byte or text stream.
  //
  // This follows the same contract as Serial.readBytes.
  int readBytes(uint8_t *buffer, size_t length);

  // Returns the syntax error value if readDataType() returned
  // DataType::kSyntaxError.
  SyntaxError getSyntaxError();

  // Determines if the current bytes, text, array, or map has an indefinite
  // length. The end will be determined by a data item of type
  // DataType::kBreak.
  //
  // If this returns true, then the caller should keep track of nesting, and
  // true should be passed as the value for the allowBreak parameter in
  // readDataType the next time it is called.
  bool isIndefiniteLength();

  // Returns the length of bytes, text, arrays, or maps. For indefinite length
  // data items, this will return 0. For these types, please use the
  // isIndefiniteLength() function.
  uint64_t getLength();

  bool getBoolean();
  float getFloat();
  double getDouble();
  uint64_t getUnsignedInt();
  int64_t getInt();
  uint8_t getSimpleValue();
  uint64_t getTag();

  // Checks if the next data item is well-formed. This includes any nested
  // items and advances the stream. A data item is considered not well-formed
  // if there are syntax errors or end-of-stream has been reached before
  // processing all the data. This works best with a stream that can be reset.
  bool isWellFormed();

 private:
  enum class State {
    kStart,
    kAdditionalInfo,
    kWaitAvailable,
    kReadValue,
    kDetermineType,
  };

  // Checks if a data item is well-formed. This returns the major type
  // on success, -1 on error, and -2 on encountering a break value. The
  // breakable parameter indicates whether we should allow the break value.
  // If it's disallowed then this will return -1 if a break value is
  // encountered. When first called breakable should be set to false.
  int isWellFormed(bool breakable);

  // Checks if an indefinite-length item is well-formed. This returns the
  // major type on success, -1 on error, and -2 on encountering a break
  // value. The breakable parameter indicates whether we should allow the
  // break value.
  int isIndefiniteWellFormed(uint8_t majorType, bool breakable);

  State state_;
  Stream &in_;

  int initialByte_;
  uint8_t majorType_;
  uint8_t addlInfo_;
  int waitAvailable_;
  uint64_t value_;  // The simple or non-simple value after the major type
  SyntaxError syntaxError_;
};

// Writer provides a way to encode data to a CBOR-encoded stream. Callers
// need to manage proper structure themselves.
class Writer {
 public:
  Writer(Print &out) : out_(out) {}
  ~Writer() = default;

  // Returns any write error in the underlying Print object. This will
  // return zero if there is no error.
  int getWriteError() {
    return out_.getWriteError();
  }

  void writeBoolean(bool b);
  void writeFloat(float f);
  void writeDouble(double d);
  void writeUnsignedInt(uint64_t u);
  void writeInt(int64_t i);
  void writeNull();
  void writeUndefined();
  void writeSimpleValue(uint8_t v);
  void writeTag(uint64_t v);

  // Writes bytes to the output. This must be preceded by a call to
  // beginBytes, beginIndefiniteBytes, beginText, or beginIndefiniteText.
  // endIndefinite must be called when finished writing bytes preceded by
  // a beginIndefiniteBytes or beginIndefiniteText call. Finally, if
  // beginBytes or beginText was called, then it is up to the caller to
  // write enough bytes so that the total size matches the length given
  // in beginBytes or beginText.
  void writeBytes(uint8_t *buffer, size_t length);

  // Starts a byte string having a specific length. It is up to the caller
  // to write the correct total number of bytes.
  void beginBytes(unsigned int length);

  // Starts a text (UTF-8) string having a specific length. It is up to the
  // caller to write the correct total number of bytes.
  void beginText(unsigned int length);

  // Starts a byte string having no specific length. It is up to the caller
  // to write the correct total number of bytes by calling beginBytes followed
  // by an appropriate number of writeBytes calls.
  void beginIndefiniteBytes();

  // Starts a text string having no specific length. It is up to the caller
  // to write the correct total number of bytes by calling beginText followed
  // by an appropriate number of writeBytes calls.
  void beginIndefiniteText();

  // Starts an array having a specific length. It is up to the caller
  // to write the correct number of data items.
  void beginArray(unsigned int length);

  // Starts a map having a specific length. It is up to the caller
  // to write the correct number of key/value pairs.
  void beginMap(unsigned int length);

  // Starts an array having no specific length. It is up to the caller to
  // call endIndefinite after the correct number of elements has been written.
  void beginIndefiniteArray();

  // Starts a map having no specific length. It is up to the caller to
  // call endIndefinite after the correct number of key/value pairs has
  // been written.
  void beginIndefiniteMap();

  // Ends an indefinite stream of bytes, text, array elements, or map pairs.
  void endIndefinite();

 private:
  // Writes an int having the given major type, either 0x20 (signed)
  // or 0x00 (unsigned).
  void writeTypedInt(uint8_t mt, uint64_t u);

  Print &out_;
};

}  // namespace cbor
}  // namespace qindesign

#endif  // QINDESIGN_CBOR_H_
