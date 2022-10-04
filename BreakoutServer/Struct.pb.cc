// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Struct.proto

#include "Struct.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG
namespace Protocol {
constexpr Player::Player(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : code_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , name_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string){}
struct PlayerDefaultTypeInternal {
  constexpr PlayerDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~PlayerDefaultTypeInternal() {}
  union {
    Player _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PlayerDefaultTypeInternal _Player_default_instance_;
constexpr KeyInput::KeyInput(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : onoff_(false)
  , direction_(false){}
struct KeyInputDefaultTypeInternal {
  constexpr KeyInputDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~KeyInputDefaultTypeInternal() {}
  union {
    KeyInput _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT KeyInputDefaultTypeInternal _KeyInput_default_instance_;
constexpr KeyInputU::KeyInputU(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : input_(nullptr)
  , userid_(0){}
struct KeyInputUDefaultTypeInternal {
  constexpr KeyInputUDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~KeyInputUDefaultTypeInternal() {}
  union {
    KeyInputU _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT KeyInputUDefaultTypeInternal _KeyInputU_default_instance_;
}  // namespace Protocol
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_Struct_2eproto[3];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_Struct_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_Struct_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_Struct_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Protocol::Player, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::Protocol::Player, code_),
  PROTOBUF_FIELD_OFFSET(::Protocol::Player, name_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Protocol::KeyInput, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::Protocol::KeyInput, onoff_),
  PROTOBUF_FIELD_OFFSET(::Protocol::KeyInput, direction_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Protocol::KeyInputU, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::Protocol::KeyInputU, userid_),
  PROTOBUF_FIELD_OFFSET(::Protocol::KeyInputU, input_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::Protocol::Player)},
  { 7, -1, sizeof(::Protocol::KeyInput)},
  { 14, -1, sizeof(::Protocol::KeyInputU)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::Protocol::_Player_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::Protocol::_KeyInput_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::Protocol::_KeyInputU_default_instance_),
};

const char descriptor_table_protodef_Struct_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\014Struct.proto\022\010Protocol\"$\n\006Player\022\014\n\004co"
  "de\030\001 \001(\t\022\014\n\004name\030\002 \001(\t\",\n\010KeyInput\022\r\n\005on"
  "Off\030\001 \001(\010\022\021\n\tdirection\030\002 \001(\010\">\n\tKeyInput"
  "U\022\016\n\006userId\030\001 \001(\005\022!\n\005input\030\002 \001(\0132\022.Proto"
  "col.KeyInputb\006proto3"
  ;
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_Struct_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_Struct_2eproto = {
  false, false, 180, descriptor_table_protodef_Struct_2eproto, "Struct.proto", 
  &descriptor_table_Struct_2eproto_once, nullptr, 0, 3,
  schemas, file_default_instances, TableStruct_Struct_2eproto::offsets,
  file_level_metadata_Struct_2eproto, file_level_enum_descriptors_Struct_2eproto, file_level_service_descriptors_Struct_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_Struct_2eproto_getter() {
  return &descriptor_table_Struct_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_Struct_2eproto(&descriptor_table_Struct_2eproto);
namespace Protocol {

// ===================================================================

class Player::_Internal {
 public:
};

Player::Player(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:Protocol.Player)
}
Player::Player(const Player& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  code_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_code().empty()) {
    code_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_code(), 
      GetArenaForAllocation());
  }
  name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_name().empty()) {
    name_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_name(), 
      GetArenaForAllocation());
  }
  // @@protoc_insertion_point(copy_constructor:Protocol.Player)
}

void Player::SharedCtor() {
code_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

Player::~Player() {
  // @@protoc_insertion_point(destructor:Protocol.Player)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void Player::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  code_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  name_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void Player::ArenaDtor(void* object) {
  Player* _this = reinterpret_cast< Player* >(object);
  (void)_this;
}
void Player::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void Player::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void Player::Clear() {
// @@protoc_insertion_point(message_clear_start:Protocol.Player)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  code_.ClearToEmpty();
  name_.ClearToEmpty();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Player::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string code = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          auto str = _internal_mutable_code();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "Protocol.Player.code"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // string name = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          auto str = _internal_mutable_name();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "Protocol.Player.name"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag == 0) || ((tag & 7) == 4)) {
          CHK_(ptr);
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* Player::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Protocol.Player)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string code = 1;
  if (!this->code().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_code().data(), static_cast<int>(this->_internal_code().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "Protocol.Player.code");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_code(), target);
  }

  // string name = 2;
  if (!this->name().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_name().data(), static_cast<int>(this->_internal_name().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "Protocol.Player.name");
    target = stream->WriteStringMaybeAliased(
        2, this->_internal_name(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Protocol.Player)
  return target;
}

size_t Player::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Protocol.Player)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string code = 1;
  if (!this->code().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_code());
  }

  // string name = 2;
  if (!this->name().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_name());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void Player::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:Protocol.Player)
  GOOGLE_DCHECK_NE(&from, this);
  const Player* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<Player>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:Protocol.Player)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:Protocol.Player)
    MergeFrom(*source);
  }
}

void Player::MergeFrom(const Player& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Protocol.Player)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from.code().empty()) {
    _internal_set_code(from._internal_code());
  }
  if (!from.name().empty()) {
    _internal_set_name(from._internal_name());
  }
}

void Player::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:Protocol.Player)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Player::CopyFrom(const Player& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Protocol.Player)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Player::IsInitialized() const {
  return true;
}

void Player::InternalSwap(Player* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &code_, GetArenaForAllocation(),
      &other->code_, other->GetArenaForAllocation()
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &name_, GetArenaForAllocation(),
      &other->name_, other->GetArenaForAllocation()
  );
}

::PROTOBUF_NAMESPACE_ID::Metadata Player::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_Struct_2eproto_getter, &descriptor_table_Struct_2eproto_once,
      file_level_metadata_Struct_2eproto[0]);
}

// ===================================================================

class KeyInput::_Internal {
 public:
};

KeyInput::KeyInput(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:Protocol.KeyInput)
}
KeyInput::KeyInput(const KeyInput& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::memcpy(&onoff_, &from.onoff_,
    static_cast<size_t>(reinterpret_cast<char*>(&direction_) -
    reinterpret_cast<char*>(&onoff_)) + sizeof(direction_));
  // @@protoc_insertion_point(copy_constructor:Protocol.KeyInput)
}

void KeyInput::SharedCtor() {
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&onoff_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&direction_) -
    reinterpret_cast<char*>(&onoff_)) + sizeof(direction_));
}

KeyInput::~KeyInput() {
  // @@protoc_insertion_point(destructor:Protocol.KeyInput)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void KeyInput::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void KeyInput::ArenaDtor(void* object) {
  KeyInput* _this = reinterpret_cast< KeyInput* >(object);
  (void)_this;
}
void KeyInput::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void KeyInput::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void KeyInput::Clear() {
// @@protoc_insertion_point(message_clear_start:Protocol.KeyInput)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&onoff_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&direction_) -
      reinterpret_cast<char*>(&onoff_)) + sizeof(direction_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* KeyInput::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // bool onOff = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          onoff_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // bool direction = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          direction_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag == 0) || ((tag & 7) == 4)) {
          CHK_(ptr);
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* KeyInput::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Protocol.KeyInput)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // bool onOff = 1;
  if (this->onoff() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteBoolToArray(1, this->_internal_onoff(), target);
  }

  // bool direction = 2;
  if (this->direction() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteBoolToArray(2, this->_internal_direction(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Protocol.KeyInput)
  return target;
}

size_t KeyInput::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Protocol.KeyInput)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // bool onOff = 1;
  if (this->onoff() != 0) {
    total_size += 1 + 1;
  }

  // bool direction = 2;
  if (this->direction() != 0) {
    total_size += 1 + 1;
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void KeyInput::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:Protocol.KeyInput)
  GOOGLE_DCHECK_NE(&from, this);
  const KeyInput* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<KeyInput>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:Protocol.KeyInput)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:Protocol.KeyInput)
    MergeFrom(*source);
  }
}

void KeyInput::MergeFrom(const KeyInput& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Protocol.KeyInput)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.onoff() != 0) {
    _internal_set_onoff(from._internal_onoff());
  }
  if (from.direction() != 0) {
    _internal_set_direction(from._internal_direction());
  }
}

void KeyInput::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:Protocol.KeyInput)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void KeyInput::CopyFrom(const KeyInput& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Protocol.KeyInput)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool KeyInput::IsInitialized() const {
  return true;
}

void KeyInput::InternalSwap(KeyInput* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(KeyInput, direction_)
      + sizeof(KeyInput::direction_)
      - PROTOBUF_FIELD_OFFSET(KeyInput, onoff_)>(
          reinterpret_cast<char*>(&onoff_),
          reinterpret_cast<char*>(&other->onoff_));
}

::PROTOBUF_NAMESPACE_ID::Metadata KeyInput::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_Struct_2eproto_getter, &descriptor_table_Struct_2eproto_once,
      file_level_metadata_Struct_2eproto[1]);
}

// ===================================================================

class KeyInputU::_Internal {
 public:
  static const ::Protocol::KeyInput& input(const KeyInputU* msg);
};

const ::Protocol::KeyInput&
KeyInputU::_Internal::input(const KeyInputU* msg) {
  return *msg->input_;
}
KeyInputU::KeyInputU(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:Protocol.KeyInputU)
}
KeyInputU::KeyInputU(const KeyInputU& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  if (from._internal_has_input()) {
    input_ = new ::Protocol::KeyInput(*from.input_);
  } else {
    input_ = nullptr;
  }
  userid_ = from.userid_;
  // @@protoc_insertion_point(copy_constructor:Protocol.KeyInputU)
}

void KeyInputU::SharedCtor() {
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&input_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&userid_) -
    reinterpret_cast<char*>(&input_)) + sizeof(userid_));
}

KeyInputU::~KeyInputU() {
  // @@protoc_insertion_point(destructor:Protocol.KeyInputU)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void KeyInputU::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  if (this != internal_default_instance()) delete input_;
}

void KeyInputU::ArenaDtor(void* object) {
  KeyInputU* _this = reinterpret_cast< KeyInputU* >(object);
  (void)_this;
}
void KeyInputU::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void KeyInputU::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void KeyInputU::Clear() {
// @@protoc_insertion_point(message_clear_start:Protocol.KeyInputU)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  if (GetArenaForAllocation() == nullptr && input_ != nullptr) {
    delete input_;
  }
  input_ = nullptr;
  userid_ = 0;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* KeyInputU::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // int32 userId = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          userid_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // .Protocol.KeyInput input = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          ptr = ctx->ParseMessage(_internal_mutable_input(), ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag == 0) || ((tag & 7) == 4)) {
          CHK_(ptr);
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* KeyInputU::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Protocol.KeyInputU)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 userId = 1;
  if (this->userid() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(1, this->_internal_userid(), target);
  }

  // .Protocol.KeyInput input = 2;
  if (this->has_input()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(
        2, _Internal::input(this), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Protocol.KeyInputU)
  return target;
}

size_t KeyInputU::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Protocol.KeyInputU)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // .Protocol.KeyInput input = 2;
  if (this->has_input()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
        *input_);
  }

  // int32 userId = 1;
  if (this->userid() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
        this->_internal_userid());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void KeyInputU::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:Protocol.KeyInputU)
  GOOGLE_DCHECK_NE(&from, this);
  const KeyInputU* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<KeyInputU>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:Protocol.KeyInputU)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:Protocol.KeyInputU)
    MergeFrom(*source);
  }
}

void KeyInputU::MergeFrom(const KeyInputU& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Protocol.KeyInputU)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.has_input()) {
    _internal_mutable_input()->::Protocol::KeyInput::MergeFrom(from._internal_input());
  }
  if (from.userid() != 0) {
    _internal_set_userid(from._internal_userid());
  }
}

void KeyInputU::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:Protocol.KeyInputU)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void KeyInputU::CopyFrom(const KeyInputU& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Protocol.KeyInputU)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool KeyInputU::IsInitialized() const {
  return true;
}

void KeyInputU::InternalSwap(KeyInputU* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(KeyInputU, userid_)
      + sizeof(KeyInputU::userid_)
      - PROTOBUF_FIELD_OFFSET(KeyInputU, input_)>(
          reinterpret_cast<char*>(&input_),
          reinterpret_cast<char*>(&other->input_));
}

::PROTOBUF_NAMESPACE_ID::Metadata KeyInputU::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_Struct_2eproto_getter, &descriptor_table_Struct_2eproto_once,
      file_level_metadata_Struct_2eproto[2]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace Protocol
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::Protocol::Player* Arena::CreateMaybeMessage< ::Protocol::Player >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Protocol::Player >(arena);
}
template<> PROTOBUF_NOINLINE ::Protocol::KeyInput* Arena::CreateMaybeMessage< ::Protocol::KeyInput >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Protocol::KeyInput >(arena);
}
template<> PROTOBUF_NOINLINE ::Protocol::KeyInputU* Arena::CreateMaybeMessage< ::Protocol::KeyInputU >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Protocol::KeyInputU >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>