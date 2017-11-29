// stream.inc is part of libCBOR.
// (c) 2017 Shawn Silverman

// ***************************************************************************
//  Basic stream tests
// ***************************************************************************

test(empty_stream) {
  uint8_t b[] = { };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader r{bs};
  assertFalse(r.isWellFormed());
  assertEqual(r.getReadSize(), size_t{0});
  bs.reset();
  assertEqual(static_cast<int>(r.readDataType()), static_cast<int>(cbor::DataType::kEOS));
  assertEqual(r.getReadSize(), size_t{0});
}

test(partial_1_byte) {
  uint8_t b[] = { (0 << 5) + 24 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader r{bs};
  assertFalse(r.isWellFormed());
  assertEqual(r.getReadSize(), size_t{1});
  bs.reset();
  assertEqual(static_cast<int>(r.readDataType()), static_cast<int>(cbor::DataType::kEOS));
  assertEqual(r.getReadSize(), size_t{2});
}

test(partial_2_bytes) {
  uint8_t b[] = { (0 << 5) + 25, 0x12 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader r{bs};
  assertFalse(r.isWellFormed());
  assertEqual(r.getReadSize(), size_t{1});
  bs.reset();
  assertEqual(static_cast<int>(r.readDataType()), static_cast<int>(cbor::DataType::kEOS));
  assertEqual(r.getReadSize(), size_t{2});
}

test(partial_4_bytes) {
  uint8_t b[] = { (0 << 5) + 26, 0x12, 0x34, 0x56 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader r{bs};
  assertFalse(r.isWellFormed());
  assertEqual(r.getReadSize(), size_t{1});
  bs.reset();
  assertEqual(static_cast<int>(r.readDataType()), static_cast<int>(cbor::DataType::kEOS));
  assertEqual(r.getReadSize(), size_t{2});
}

test(partial_8_bytes) {
  uint8_t b[] = { (0 << 5) + 27, 0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader r{bs};
  assertFalse(r.isWellFormed());
  assertEqual(r.getReadSize(), size_t{1});
  bs.reset();
  assertEqual(static_cast<int>(r.readDataType()), static_cast<int>(cbor::DataType::kEOS));
  assertEqual(r.getReadSize(), size_t{2});
}

test(unsigned_1_byte_with_wait) {
  uint8_t b[] = { (0 << 5) + 24, 0x21 };
  cbor::BytesStream bs{b, sizeof(b), 1};
  cbor::Reader r{bs};
  assertFalse(r.isWellFormed());
  assertEqual(r.getReadSize(), size_t{0});
  bs.reset();
  assertEqual(static_cast<int>(r.readDataType()), static_cast<int>(cbor::DataType::kEOS));
  assertEqual(static_cast<int>(r.readDataType()), static_cast<int>(cbor::DataType::kEOS));
  assertEqual(static_cast<int>(r.readDataType()), static_cast<int>(cbor::DataType::kUnsignedInt));
  assertTrue(r.getUnsignedInt() == 0x21);
  assertEqual(r.getReadSize(), size_t{2});
}