// tag.inc is part of libCBOR.
// (c) 2017 Shawn Silverman

// ***************************************************************************
//  Tag tests
// ***************************************************************************

test(tag_2) {
  uint8_t b[] = { (6 << 5) + 2 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertFalse(cbor.isWellFormed());  // Missing something after the tag
  assertEqual(cbor.getReadSize(), size_t{1});
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kTag));
  assertTrue(cbor.getTag() == 2);
  assertEqual(cbor.getReadSize(), size_t{2});
}

test(tag_55799) {
  uint8_t b[] = { (6 << 5) + 25, 0xd9, 0xf7 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertFalse(cbor.isWellFormed());  // Missing something after the tag
  assertEqual(cbor.getReadSize(), size_t{3});
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kTag));
  assertTrue(cbor.getTag() == cbor::kSelfDescribeTag);
  assertEqual(cbor.getReadSize(), size_t{6});
}
