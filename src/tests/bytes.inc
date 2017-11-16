// bytes.inc is part of libCBOR.
// (c) 2017 Shawn Silverman

// ***************************************************************************
//  Bytes tests
// ***************************************************************************

test(bytes_empty) {
  uint8_t b[] = { (2 << 5) + 0 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kBytes));
  assertTrue(cbor.getLength() == 0);
}

test(bytes_something) {
  uint8_t b[] = { (2 << 5) + 4, 0x01, 0x02, 0x03, 0x04, 0 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kBytes));
  assertTrue(cbor.getLength() == 4);
  uint8_t b2[5]{0};
  assertEqual(cbor.readBytes(b2, 4), size_t{4});
  assertEqual(reinterpret_cast<char*>(&b2[0]), reinterpret_cast<char*>(&b[1]));
}

test(bytes_indefinite) {
  uint8_t b[] = { (2 << 5) + 31, (2 << 5) + 2, 0x01, 0x02, (2 << 5) + 3, 0x03, 0x04, 0x05, (7 << 5) + 31 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kBytes));
  assertTrue(cbor.isIndefiniteLength());

  uint8_t b2[6]{0};
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kBytes));
  assertTrue(cbor.getLength() == 2);
  assertEqual(cbor.readBytes(&b2[0], 2), size_t{2});
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kBytes));
  assertTrue(cbor.getLength() == 3);
  assertEqual(cbor.readBytes(&b2[2], 3), size_t{3});
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kBreak));

  uint8_t b3[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0 };
  assertEqual(reinterpret_cast<char*>(b2), reinterpret_cast<char*>(b3));
}

test(text_empty) {
  uint8_t b[] = { (3 << 5) + 0 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kText));
  assertTrue(cbor.getLength() == 0);
}

test(text_something) {
  uint8_t b[] = { (3 << 5) + 4, 0x49, 0x45, 0x54, 0x46, 0 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kText));
  assertTrue(cbor.getLength() == 4);
  uint8_t b2[5]{0};
  assertEqual(cbor.readBytes(b2, 4), size_t{4});
  assertEqual(reinterpret_cast<char*>(&b2[0]), reinterpret_cast<char*>(&b[1]));
}

test(text_indefinite) {
  uint8_t b[] = { (3 << 5) + 31, (3 << 5) + 5, 0x73, 0x74, 0x72, 0x65, 0x61, (3 << 5) + 4, 0x6d, 0x69, 0x6e, 0x67, (7 << 5) + 31 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kText));
  assertTrue(cbor.isIndefiniteLength());

  uint8_t b2[10]{0};
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kText));
  assertTrue(cbor.getLength() == 5);
  assertEqual(cbor.readBytes(&b2[0], 5), size_t{5});
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kText));
  assertTrue(cbor.getLength() == 4);
  assertEqual(cbor.readBytes(&b2[5], 4), size_t{4});

  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kBreak));

  uint8_t b3[] = { 0x73, 0x74, 0x72, 0x65, 0x61, 0x6d, 0x69, 0x6e, 0x67, 0 };
  assertEqual(reinterpret_cast<char*>(b2), reinterpret_cast<char*>(b3));
}
