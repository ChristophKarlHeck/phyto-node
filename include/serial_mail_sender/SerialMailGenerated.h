// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_SERIALMAIL_SERIALMAIL_H_
#define FLATBUFFERS_GENERATED_SERIALMAIL_SERIALMAIL_H_

#include "flatbuffers/flatbuffers.h"

// Ensure the included flatbuffers.h is the same version as when this file was
// generated, otherwise it may not be compatible.
static_assert(FLATBUFFERS_VERSION_MAJOR == 24 &&
              FLATBUFFERS_VERSION_MINOR == 3 &&
              FLATBUFFERS_VERSION_REVISION == 25,
             "Non-compatible flatbuffers version included");

namespace SerialMail {

struct Value;

struct SerialMail;
struct SerialMailBuilder;

FLATBUFFERS_MANUALLY_ALIGNED_STRUCT(1) Value FLATBUFFERS_FINAL_CLASS {
 private:
  uint8_t data_0_;
  uint8_t data_1_;
  uint8_t data_2_;

 public:
  Value()
      : data_0_(0),
        data_1_(0),
        data_2_(0) {
  }
  Value(uint8_t _data_0, uint8_t _data_1, uint8_t _data_2)
      : data_0_(::flatbuffers::EndianScalar(_data_0)),
        data_1_(::flatbuffers::EndianScalar(_data_1)),
        data_2_(::flatbuffers::EndianScalar(_data_2)) {
  }
  uint8_t data_0() const {
    return ::flatbuffers::EndianScalar(data_0_);
  }
  uint8_t data_1() const {
    return ::flatbuffers::EndianScalar(data_1_);
  }
  uint8_t data_2() const {
    return ::flatbuffers::EndianScalar(data_2_);
  }
};
FLATBUFFERS_STRUCT_END(Value, 3);

struct SerialMail FLATBUFFERS_FINAL_CLASS : private ::flatbuffers::Table {
  typedef SerialMailBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_CH0 = 4,
    VT_CH1 = 6,
    VT_NODE = 8
  };
  const ::flatbuffers::Vector<const Value *> *ch0() const {
    return GetPointer<const ::flatbuffers::Vector<const Value *> *>(VT_CH0);
  }
  const ::flatbuffers::Vector<const Value *> *ch1() const {
    return GetPointer<const ::flatbuffers::Vector<const Value *> *>(VT_CH1);
  }
  int32_t node() const {
    return GetField<int32_t>(VT_NODE, 0);
  }
  bool Verify(::flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_CH0) &&
           verifier.VerifyVector(ch0()) &&
           VerifyOffset(verifier, VT_CH1) &&
           verifier.VerifyVector(ch1()) &&
           VerifyField<int32_t>(verifier, VT_NODE, 4) &&
           verifier.EndTable();
  }
};

struct SerialMailBuilder {
  typedef SerialMail Table;
  ::flatbuffers::FlatBufferBuilder &fbb_;
  ::flatbuffers::uoffset_t start_;
  void add_ch0(::flatbuffers::Offset<::flatbuffers::Vector<const Value *>> ch0) {
    fbb_.AddOffset(SerialMail::VT_CH0, ch0);
  }
  void add_ch1(::flatbuffers::Offset<::flatbuffers::Vector<const Value *>> ch1) {
    fbb_.AddOffset(SerialMail::VT_CH1, ch1);
  }
  void add_node(int32_t node) {
    fbb_.AddElement<int32_t>(SerialMail::VT_NODE, node, 0);
  }
  explicit SerialMailBuilder(::flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ::flatbuffers::Offset<SerialMail> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = ::flatbuffers::Offset<SerialMail>(end);
    return o;
  }
};

inline ::flatbuffers::Offset<SerialMail> CreateSerialMail(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    ::flatbuffers::Offset<::flatbuffers::Vector<const Value *>> ch0 = 0,
    ::flatbuffers::Offset<::flatbuffers::Vector<const Value *>> ch1 = 0,
    int32_t node = 0) {
  SerialMailBuilder builder_(_fbb);
  builder_.add_node(node);
  builder_.add_ch1(ch1);
  builder_.add_ch0(ch0);
  return builder_.Finish();
}

inline ::flatbuffers::Offset<SerialMail> CreateSerialMailDirect(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    const std::vector<Value> *ch0 = nullptr,
    const std::vector<Value> *ch1 = nullptr,
    int32_t node = 0) {
  auto ch0__ = ch0 ? _fbb.CreateVectorOfStructs<Value>(*ch0) : 0;
  auto ch1__ = ch1 ? _fbb.CreateVectorOfStructs<Value>(*ch1) : 0;
  return CreateSerialMail(
      _fbb,
      ch0__,
      ch1__,
      node);
}

inline const SerialMail *GetSerialMail(const void *buf) {
  return ::flatbuffers::GetRoot<SerialMail>(buf);
}

inline const SerialMail *GetSizePrefixedSerialMail(const void *buf) {
  return ::flatbuffers::GetSizePrefixedRoot<SerialMail>(buf);
}

inline bool VerifySerialMailBuffer(
    ::flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<SerialMail>(nullptr);
}

inline bool VerifySizePrefixedSerialMailBuffer(
    ::flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<SerialMail>(nullptr);
}

inline void FinishSerialMailBuffer(
    ::flatbuffers::FlatBufferBuilder &fbb,
    ::flatbuffers::Offset<SerialMail> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedSerialMailBuffer(
    ::flatbuffers::FlatBufferBuilder &fbb,
    ::flatbuffers::Offset<SerialMail> root) {
  fbb.FinishSizePrefixed(root);
}

}  // namespace SerialMail

#endif  // FLATBUFFERS_GENERATED_SERIALMAIL_SERIALMAIL_H_
