// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Struct.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_Struct_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_Struct_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3017000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3017001 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_Struct_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_Struct_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[3]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_Struct_2eproto;
namespace Protocol {
class KeyInput;
struct KeyInputDefaultTypeInternal;
extern KeyInputDefaultTypeInternal _KeyInput_default_instance_;
class KeyInputU;
struct KeyInputUDefaultTypeInternal;
extern KeyInputUDefaultTypeInternal _KeyInputU_default_instance_;
class Player;
struct PlayerDefaultTypeInternal;
extern PlayerDefaultTypeInternal _Player_default_instance_;
}  // namespace Protocol
PROTOBUF_NAMESPACE_OPEN
template<> ::Protocol::KeyInput* Arena::CreateMaybeMessage<::Protocol::KeyInput>(Arena*);
template<> ::Protocol::KeyInputU* Arena::CreateMaybeMessage<::Protocol::KeyInputU>(Arena*);
template<> ::Protocol::Player* Arena::CreateMaybeMessage<::Protocol::Player>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace Protocol {

// ===================================================================

class Player final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Protocol.Player) */ {
 public:
  inline Player() : Player(nullptr) {}
  ~Player() override;
  explicit constexpr Player(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  Player(const Player& from);
  Player(Player&& from) noexcept
    : Player() {
    *this = ::std::move(from);
  }

  inline Player& operator=(const Player& from) {
    CopyFrom(from);
    return *this;
  }
  inline Player& operator=(Player&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const Player& default_instance() {
    return *internal_default_instance();
  }
  static inline const Player* internal_default_instance() {
    return reinterpret_cast<const Player*>(
               &_Player_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(Player& a, Player& b) {
    a.Swap(&b);
  }
  inline void Swap(Player* other) {
    if (other == this) return;
    if (GetOwningArena() == other->GetOwningArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Player* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline Player* New() const final {
    return new Player();
  }

  Player* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<Player>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const Player& from);
  void MergeFrom(const Player& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Player* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Protocol.Player";
  }
  protected:
  explicit Player(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kCodeFieldNumber = 1,
    kNameFieldNumber = 2,
  };
  // string code = 1;
  void clear_code();
  const std::string& code() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_code(ArgT0&& arg0, ArgT... args);
  std::string* mutable_code();
  PROTOBUF_FUTURE_MUST_USE_RESULT std::string* release_code();
  void set_allocated_code(std::string* code);
  private:
  const std::string& _internal_code() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_code(const std::string& value);
  std::string* _internal_mutable_code();
  public:

  // string name = 2;
  void clear_name();
  const std::string& name() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_name(ArgT0&& arg0, ArgT... args);
  std::string* mutable_name();
  PROTOBUF_FUTURE_MUST_USE_RESULT std::string* release_name();
  void set_allocated_name(std::string* name);
  private:
  const std::string& _internal_name() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_name(const std::string& value);
  std::string* _internal_mutable_name();
  public:

  // @@protoc_insertion_point(class_scope:Protocol.Player)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr code_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr name_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_Struct_2eproto;
};
// -------------------------------------------------------------------

class KeyInput final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Protocol.KeyInput) */ {
 public:
  inline KeyInput() : KeyInput(nullptr) {}
  ~KeyInput() override;
  explicit constexpr KeyInput(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  KeyInput(const KeyInput& from);
  KeyInput(KeyInput&& from) noexcept
    : KeyInput() {
    *this = ::std::move(from);
  }

  inline KeyInput& operator=(const KeyInput& from) {
    CopyFrom(from);
    return *this;
  }
  inline KeyInput& operator=(KeyInput&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const KeyInput& default_instance() {
    return *internal_default_instance();
  }
  static inline const KeyInput* internal_default_instance() {
    return reinterpret_cast<const KeyInput*>(
               &_KeyInput_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(KeyInput& a, KeyInput& b) {
    a.Swap(&b);
  }
  inline void Swap(KeyInput* other) {
    if (other == this) return;
    if (GetOwningArena() == other->GetOwningArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(KeyInput* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline KeyInput* New() const final {
    return new KeyInput();
  }

  KeyInput* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<KeyInput>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const KeyInput& from);
  void MergeFrom(const KeyInput& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(KeyInput* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Protocol.KeyInput";
  }
  protected:
  explicit KeyInput(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kOnOffFieldNumber = 1,
    kDirectionFieldNumber = 2,
  };
  // bool onOff = 1;
  void clear_onoff();
  bool onoff() const;
  void set_onoff(bool value);
  private:
  bool _internal_onoff() const;
  void _internal_set_onoff(bool value);
  public:

  // bool direction = 2;
  void clear_direction();
  bool direction() const;
  void set_direction(bool value);
  private:
  bool _internal_direction() const;
  void _internal_set_direction(bool value);
  public:

  // @@protoc_insertion_point(class_scope:Protocol.KeyInput)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  bool onoff_;
  bool direction_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_Struct_2eproto;
};
// -------------------------------------------------------------------

class KeyInputU final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Protocol.KeyInputU) */ {
 public:
  inline KeyInputU() : KeyInputU(nullptr) {}
  ~KeyInputU() override;
  explicit constexpr KeyInputU(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  KeyInputU(const KeyInputU& from);
  KeyInputU(KeyInputU&& from) noexcept
    : KeyInputU() {
    *this = ::std::move(from);
  }

  inline KeyInputU& operator=(const KeyInputU& from) {
    CopyFrom(from);
    return *this;
  }
  inline KeyInputU& operator=(KeyInputU&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const KeyInputU& default_instance() {
    return *internal_default_instance();
  }
  static inline const KeyInputU* internal_default_instance() {
    return reinterpret_cast<const KeyInputU*>(
               &_KeyInputU_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  friend void swap(KeyInputU& a, KeyInputU& b) {
    a.Swap(&b);
  }
  inline void Swap(KeyInputU* other) {
    if (other == this) return;
    if (GetOwningArena() == other->GetOwningArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(KeyInputU* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline KeyInputU* New() const final {
    return new KeyInputU();
  }

  KeyInputU* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<KeyInputU>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const KeyInputU& from);
  void MergeFrom(const KeyInputU& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(KeyInputU* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Protocol.KeyInputU";
  }
  protected:
  explicit KeyInputU(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kInputFieldNumber = 2,
    kUserIdFieldNumber = 1,
  };
  // .Protocol.KeyInput input = 2;
  bool has_input() const;
  private:
  bool _internal_has_input() const;
  public:
  void clear_input();
  const ::Protocol::KeyInput& input() const;
  PROTOBUF_FUTURE_MUST_USE_RESULT ::Protocol::KeyInput* release_input();
  ::Protocol::KeyInput* mutable_input();
  void set_allocated_input(::Protocol::KeyInput* input);
  private:
  const ::Protocol::KeyInput& _internal_input() const;
  ::Protocol::KeyInput* _internal_mutable_input();
  public:
  void unsafe_arena_set_allocated_input(
      ::Protocol::KeyInput* input);
  ::Protocol::KeyInput* unsafe_arena_release_input();

  // int32 userId = 1;
  void clear_userid();
  ::PROTOBUF_NAMESPACE_ID::int32 userid() const;
  void set_userid(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_userid() const;
  void _internal_set_userid(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // @@protoc_insertion_point(class_scope:Protocol.KeyInputU)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::Protocol::KeyInput* input_;
  ::PROTOBUF_NAMESPACE_ID::int32 userid_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_Struct_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Player

// string code = 1;
inline void Player::clear_code() {
  code_.ClearToEmpty();
}
inline const std::string& Player::code() const {
  // @@protoc_insertion_point(field_get:Protocol.Player.code)
  return _internal_code();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void Player::set_code(ArgT0&& arg0, ArgT... args) {
 
 code_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:Protocol.Player.code)
}
inline std::string* Player::mutable_code() {
  // @@protoc_insertion_point(field_mutable:Protocol.Player.code)
  return _internal_mutable_code();
}
inline const std::string& Player::_internal_code() const {
  return code_.Get();
}
inline void Player::_internal_set_code(const std::string& value) {
  
  code_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArenaForAllocation());
}
inline std::string* Player::_internal_mutable_code() {
  
  return code_.Mutable(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArenaForAllocation());
}
inline std::string* Player::release_code() {
  // @@protoc_insertion_point(field_release:Protocol.Player.code)
  return code_.Release(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArenaForAllocation());
}
inline void Player::set_allocated_code(std::string* code) {
  if (code != nullptr) {
    
  } else {
    
  }
  code_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), code,
      GetArenaForAllocation());
  // @@protoc_insertion_point(field_set_allocated:Protocol.Player.code)
}

// string name = 2;
inline void Player::clear_name() {
  name_.ClearToEmpty();
}
inline const std::string& Player::name() const {
  // @@protoc_insertion_point(field_get:Protocol.Player.name)
  return _internal_name();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void Player::set_name(ArgT0&& arg0, ArgT... args) {
 
 name_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:Protocol.Player.name)
}
inline std::string* Player::mutable_name() {
  // @@protoc_insertion_point(field_mutable:Protocol.Player.name)
  return _internal_mutable_name();
}
inline const std::string& Player::_internal_name() const {
  return name_.Get();
}
inline void Player::_internal_set_name(const std::string& value) {
  
  name_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArenaForAllocation());
}
inline std::string* Player::_internal_mutable_name() {
  
  return name_.Mutable(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArenaForAllocation());
}
inline std::string* Player::release_name() {
  // @@protoc_insertion_point(field_release:Protocol.Player.name)
  return name_.Release(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArenaForAllocation());
}
inline void Player::set_allocated_name(std::string* name) {
  if (name != nullptr) {
    
  } else {
    
  }
  name_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), name,
      GetArenaForAllocation());
  // @@protoc_insertion_point(field_set_allocated:Protocol.Player.name)
}

// -------------------------------------------------------------------

// KeyInput

// bool onOff = 1;
inline void KeyInput::clear_onoff() {
  onoff_ = false;
}
inline bool KeyInput::_internal_onoff() const {
  return onoff_;
}
inline bool KeyInput::onoff() const {
  // @@protoc_insertion_point(field_get:Protocol.KeyInput.onOff)
  return _internal_onoff();
}
inline void KeyInput::_internal_set_onoff(bool value) {
  
  onoff_ = value;
}
inline void KeyInput::set_onoff(bool value) {
  _internal_set_onoff(value);
  // @@protoc_insertion_point(field_set:Protocol.KeyInput.onOff)
}

// bool direction = 2;
inline void KeyInput::clear_direction() {
  direction_ = false;
}
inline bool KeyInput::_internal_direction() const {
  return direction_;
}
inline bool KeyInput::direction() const {
  // @@protoc_insertion_point(field_get:Protocol.KeyInput.direction)
  return _internal_direction();
}
inline void KeyInput::_internal_set_direction(bool value) {
  
  direction_ = value;
}
inline void KeyInput::set_direction(bool value) {
  _internal_set_direction(value);
  // @@protoc_insertion_point(field_set:Protocol.KeyInput.direction)
}

// -------------------------------------------------------------------

// KeyInputU

// int32 userId = 1;
inline void KeyInputU::clear_userid() {
  userid_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 KeyInputU::_internal_userid() const {
  return userid_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 KeyInputU::userid() const {
  // @@protoc_insertion_point(field_get:Protocol.KeyInputU.userId)
  return _internal_userid();
}
inline void KeyInputU::_internal_set_userid(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  userid_ = value;
}
inline void KeyInputU::set_userid(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_userid(value);
  // @@protoc_insertion_point(field_set:Protocol.KeyInputU.userId)
}

// .Protocol.KeyInput input = 2;
inline bool KeyInputU::_internal_has_input() const {
  return this != internal_default_instance() && input_ != nullptr;
}
inline bool KeyInputU::has_input() const {
  return _internal_has_input();
}
inline void KeyInputU::clear_input() {
  if (GetArenaForAllocation() == nullptr && input_ != nullptr) {
    delete input_;
  }
  input_ = nullptr;
}
inline const ::Protocol::KeyInput& KeyInputU::_internal_input() const {
  const ::Protocol::KeyInput* p = input_;
  return p != nullptr ? *p : reinterpret_cast<const ::Protocol::KeyInput&>(
      ::Protocol::_KeyInput_default_instance_);
}
inline const ::Protocol::KeyInput& KeyInputU::input() const {
  // @@protoc_insertion_point(field_get:Protocol.KeyInputU.input)
  return _internal_input();
}
inline void KeyInputU::unsafe_arena_set_allocated_input(
    ::Protocol::KeyInput* input) {
  if (GetArenaForAllocation() == nullptr) {
    delete reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(input_);
  }
  input_ = input;
  if (input) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:Protocol.KeyInputU.input)
}
inline ::Protocol::KeyInput* KeyInputU::release_input() {
  
  ::Protocol::KeyInput* temp = input_;
  input_ = nullptr;
  if (GetArenaForAllocation() != nullptr) {
    temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  }
  return temp;
}
inline ::Protocol::KeyInput* KeyInputU::unsafe_arena_release_input() {
  // @@protoc_insertion_point(field_release:Protocol.KeyInputU.input)
  
  ::Protocol::KeyInput* temp = input_;
  input_ = nullptr;
  return temp;
}
inline ::Protocol::KeyInput* KeyInputU::_internal_mutable_input() {
  
  if (input_ == nullptr) {
    auto* p = CreateMaybeMessage<::Protocol::KeyInput>(GetArenaForAllocation());
    input_ = p;
  }
  return input_;
}
inline ::Protocol::KeyInput* KeyInputU::mutable_input() {
  // @@protoc_insertion_point(field_mutable:Protocol.KeyInputU.input)
  return _internal_mutable_input();
}
inline void KeyInputU::set_allocated_input(::Protocol::KeyInput* input) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaForAllocation();
  if (message_arena == nullptr) {
    delete input_;
  }
  if (input) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
        ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper<::Protocol::KeyInput>::GetOwningArena(input);
    if (message_arena != submessage_arena) {
      input = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, input, submessage_arena);
    }
    
  } else {
    
  }
  input_ = input;
  // @@protoc_insertion_point(field_set_allocated:Protocol.KeyInputU.input)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace Protocol

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_Struct_2eproto
