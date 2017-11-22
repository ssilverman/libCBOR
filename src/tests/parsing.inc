// simple_value.inc is part of libCBOR.
// (c) 2017 Shawn Silverman

// Tests for the parsing helper functions.

test(expect_value_fails) {
  uint8_t b[9] = { (7 << 5) + 20 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader r{bs};
  assertFalse(expectValue(r, cbor::DataType::kBoolean, 20));
  bs.reset();
  b[0] = (7 << 5) + 21;
  assertFalse(expectValue(r, cbor::DataType::kBoolean, 21));
  bs.reset();
  b[0] = (7 << 5) + 22;
  assertFalse(expectValue(r, cbor::DataType::kNull, 22));
  bs.reset();
  b[0] = (7 << 5) + 23;
  assertFalse(expectValue(r, cbor::DataType::kUndefined, 23));
  bs.reset();
  b[0] = (7 << 5) + 31;
  assertFalse(expectValue(r, cbor::DataType::kBreak, 31));

  bs.reset();
  b[0] = (7 << 5) + 26;
  b[1] = 0;
  b[2] = 0;
  b[3] = 0;
  b[4] = 0;
  assertFalse(expectValue(r, cbor::DataType::kFloat, 0));

  bs.reset();
  b[0] = (7 << 5) + 27;
  b[1] = 0;
  b[2] = 0;
  b[3] = 0;
  b[4] = 0;
  b[5] = 0;
  b[6] = 0;
  b[7] = 0;
  b[8] = 0;
  assertFalse(expectValue(r, cbor::DataType::kDouble, 0));
  assertEqual(static_cast<int>(r.readDataType()), static_cast<int>(cbor::DataType::kEOS));
  assertFalse(expectValue(r, cbor::DataType::kEOS, 0));

  bs.reset();
  b[0] = (7 << 5) + 30;
  assertEqual(static_cast<int>(r.readDataType()), static_cast<int>(cbor::DataType::kSyntaxError));
  bs.reset();
  assertFalse(expectValue(r, cbor::DataType::kSyntaxError, 0));
}

test(expect_unsigned_value) {
  uint8_t b[] = { (0 << 5) + 20 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader r{bs};
  assertTrue(expectValue(r, cbor::DataType::kUnsignedInt, 20));
  bs.reset();
  b[0] = (0 << 5) + 21;
  assertFalse(expectValue(r, cbor::DataType::kUnsignedInt, 20));
}

test(expect_unsigned) {
  uint8_t b[] = { (0 << 5) + 20 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader r{bs};
  uint64_t u;
  assertTrue(expectUnsignedInt(r, &u));
  assertTrue(u == 20);
}

test(expect_negative_value) {
  uint8_t b[] = { (1 << 5) + 20 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader r{bs};
  assertTrue(expectValue(r, cbor::DataType::kNegativeInt, -21));
  bs.reset();
  b[0] = (1 << 5) + 21;
  assertFalse(expectValue(r, cbor::DataType::kNegativeInt, -21));
}

test(expect_negative) {
  uint8_t b[] = { (1 << 5) + 20 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader r{bs};
  int64_t i;
  assertTrue(expectInt(r, &i));
  assertTrue(i == -21);
}

test(expect_simple_value) {
  uint8_t b[] = { (7 << 5) + 19 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader r{bs};
  assertTrue(expectValue(r, cbor::DataType::kSimpleValue, 19));
  bs.reset();
  b[0] = (7 << 5) + 18;
  assertFalse(expectValue(r, cbor::DataType::kSimpleValue, 19));

  bs.reset();
  b[0] = (7 << 5) + 18;
  uint8_t v;
  assertTrue(expectSimpleValue(r, &v));
  assertEqual(v, uint8_t{18});
}

test(expect_tag_value) {
  uint8_t b[] = { (6 << 5) + 20 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader r{bs};
  assertTrue(expectValue(r, cbor::DataType::kTag, 20));
  bs.reset();
  b[0] = (6 << 5) + 21;
  assertFalse(expectValue(r, cbor::DataType::kTag, 20));
}

test(expect_tag) {
  uint8_t b[] = { (6 << 5) + 20 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader r{bs};
  uint64_t t;
  assertTrue(expectTag(r, &t));
  assertTrue(t == 20);
}

test(expect_bytes_value) {
  uint8_t b[3] = { (2 << 5) + 20 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader r{bs};
  assertTrue(expectValue(r, cbor::DataType::kBytes, 20));
  bs.reset();
  b[0] = (2 << 5) + 21;
  assertFalse(expectValue(r, cbor::DataType::kBytes, 20));
}

test(expect_bytes) {
  uint8_t b[3] = { (2 << 5) + 20 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader r{bs};
  uint64_t len;
  bool isIndefinite;
  assertTrue(expectBytes(r, &len, &isIndefinite));
  assertTrue(len == 20);
  assertFalse(isIndefinite);

  bs.reset();
  b[0] = (2 << 5) + 31;
  b[1] = (2 << 5) + 0;
  b[2] = (7 << 5) + 31;
  assertTrue(expectBytes(r, &len, &isIndefinite));
  assertTrue(isIndefinite);
  bool isBreak;
  assertTrue(expectBytesOrBreak(r, &len, &isBreak));
  assertTrue(len == 0);
  assertEqual(isBreak, false);
  assertTrue(expectBytesOrBreak(r, &len, &isBreak));
  assertEqual(isBreak, true);
}

test(expect_text_value) {
  uint8_t b[3] = { (3 << 5) + 20 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader r{bs};
  assertTrue(expectValue(r, cbor::DataType::kText, 20));
  bs.reset();
  b[0] = (3 << 5) + 21;
  assertFalse(expectValue(r, cbor::DataType::kText, 20));
}

test(expect_text) {
  uint8_t b[3] = { (3 << 5) + 20 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader r{bs};
  uint64_t len;
  bool isIndefinite;
  assertTrue(expectText(r, &len, &isIndefinite));
  assertTrue(len == 20);
  assertFalse(isIndefinite);

  bs.reset();
  b[0] = (3 << 5) + 31;
  b[1] = (3 << 5) + 0;
  b[2] = (7 << 5) + 31;
  assertTrue(expectText(r, &len, &isIndefinite));
  assertTrue(isIndefinite);
  bool isBreak;
  assertTrue(expectTextOrBreak(r, &len, &isBreak));
  assertTrue(len == 0);
  assertEqual(isBreak, false);
  assertTrue(expectTextOrBreak(r, &len, &isBreak));
  assertEqual(isBreak, true);
}

test(expect_array_value) {
  uint8_t b[] = { (4 << 5) + 20 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader r{bs};
  assertTrue(expectValue(r, cbor::DataType::kArray, 20));
  bs.reset();
  b[0] = (4 << 5) + 21;
  assertFalse(expectValue(r, cbor::DataType::kArray, 20));
}

test(expect_array) {
  uint8_t b[] = { (4 << 5) + 20 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader r{bs};
  uint64_t len;
  bool isIndefinite;
  assertTrue(expectArray(r, &len, &isIndefinite));
  assertTrue(len == 20);
  assertFalse(isIndefinite);

  bs.reset();
  b[0] = (4 << 5) + 31;
  assertTrue(expectArray(r, &len, &isIndefinite));
  assertTrue(isIndefinite);
}

test(expect_map_value) {
  uint8_t b[] = { (5 << 5) + 20 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader r{bs};
  assertTrue(expectValue(r, cbor::DataType::kMap, 20));
  bs.reset();
  b[0] = (5 << 5) + 21;
  assertFalse(expectValue(r, cbor::DataType::kMap, 20));
}

test(expect_map) {
  uint8_t b[] = { (5 << 5) + 20 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader r{bs};
  uint64_t len;
  bool isIndefinite;
  assertTrue(expectMap(r, &len, &isIndefinite));
  assertTrue(len == 20);
  assertFalse(isIndefinite);

  bs.reset();
  b[0] = (5 << 5) + 31;
  assertTrue(expectMap(r, &len, &isIndefinite));
  assertTrue(isIndefinite);
}

test(expect_half_value) {
  uint8_t b[] = { (7 << 5) + 25, 0x3c, 0x00 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader r{bs};
  assertTrue(expectFloatValue(r, 1.0f));
  bs.reset();
  b[1] = 0x3e;
  assertFalse(expectFloatValue(r, 1.0f));
}

test(expect_half) {
  uint8_t b[] = { (7 << 5) + 25, 0x3c, 0x00 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader r{bs};
  float f;
  assertTrue(expectFloat(r, &f));
  assertEqual(f, 1.0f);
}

test(expect_float_value) {
  uint8_t b[] = { (7 << 5) + 26, 0x47, 0xc3, 0x50, 0x00 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader r{bs};
  assertTrue(expectFloatValue(r, 100000.0f));
  bs.reset();
  b[2] = 0xc4;
  assertFalse(expectFloatValue(r, 100000.0f));
}

test(expect_float) {
  uint8_t b[] = { (7 << 5) + 26, 0x47, 0xc3, 0x50, 0x00 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader r{bs};
  float f;
  assertTrue(expectFloat(r, &f));
  assertEqual(f, 100000.0f);
}

test(expect_double_value) {
  uint8_t b[] = { (7 << 5) + 27, 0xc0, 0x10, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader r{bs};
  assertTrue(expectDoubleValue(r, -4.1));
  bs.reset();
  b[2] = 0x11;
  assertFalse(expectDoubleValue(r, -4.1));
}

test(expect_double) {
  uint8_t b[] = { (7 << 5) + 27, 0xc0, 0x10, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader r{bs};
  double d;
  assertTrue(expectDouble(r, &d));
  assertEqual(d, -4.1);
}

test(expect_boolean_value) {
  uint8_t b[] = { (7 << 5) + 21 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader r{bs};

  assertTrue(expectBooleanValue(r, true));
  bs.reset();
  b[0] = { (7 << 5) + 20 };
  assertFalse(expectBooleanValue(r, true));

  bs.reset();
  b[0] = { (7 << 5) + 20 };
  assertTrue(expectBooleanValue(r, false));
  bs.reset();
  b[0] = { (7 << 5) + 21 };
  assertFalse(expectBooleanValue(r, false));

  bs.reset();
  b[0] = { (7 << 5) + 21 };
  assertTrue(expectTrue(r));
  bs.reset();
  b[0] = (7 << 5) + 20;
  assertFalse(expectTrue(r));

  bs.reset();
  b[0] = (7 << 5) + 20;
  assertTrue(expectFalse(r));
  bs.reset();
  b[0] = (7 << 5) + 21;
  assertFalse(expectFalse(r));
}

test(expect_boolean) {
  uint8_t b[] = { (7 << 5) + 21 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader r{bs};

  b[0] = (7 << 5) + 21;
  bool flag;
  assertTrue(expectBoolean(r, &flag));
  assertEqual(flag, true);

  bs.reset();
  b[0] = (7 << 5) + 20;
  assertTrue(expectBoolean(r, &flag));
  assertEqual(flag, false);
}

test(expect_null) {
  uint8_t b[] = { (7 << 5) + 22 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader r{bs};
  assertTrue(expectNull(r));
}

test(expect_undefined) {
  uint8_t b[] = { (7 << 5) + 23 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader r{bs};
  assertTrue(expectUndefined(r));
}
