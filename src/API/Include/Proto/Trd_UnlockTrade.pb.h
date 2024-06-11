// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Trd_UnlockTrade.proto

#ifndef PROTOBUF_Trd_5fUnlockTrade_2eproto__INCLUDED
#define PROTOBUF_Trd_5fUnlockTrade_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3005001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
#include "Common.pb.h"
// @@protoc_insertion_point(includes)

namespace protobuf_Trd_5fUnlockTrade_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[4];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
void InitDefaultsC2SImpl();
void InitDefaultsC2S();
void InitDefaultsS2CImpl();
void InitDefaultsS2C();
void InitDefaultsRequestImpl();
void InitDefaultsRequest();
void InitDefaultsResponseImpl();
void InitDefaultsResponse();
inline void InitDefaults() {
  InitDefaultsC2S();
  InitDefaultsS2C();
  InitDefaultsRequest();
  InitDefaultsResponse();
}
}  // namespace protobuf_Trd_5fUnlockTrade_2eproto
namespace Trd_UnlockTrade {
class C2S;
class C2SDefaultTypeInternal;
extern C2SDefaultTypeInternal _C2S_default_instance_;
class Request;
class RequestDefaultTypeInternal;
extern RequestDefaultTypeInternal _Request_default_instance_;
class Response;
class ResponseDefaultTypeInternal;
extern ResponseDefaultTypeInternal _Response_default_instance_;
class S2C;
class S2CDefaultTypeInternal;
extern S2CDefaultTypeInternal _S2C_default_instance_;
}  // namespace Trd_UnlockTrade
namespace Trd_UnlockTrade {

// ===================================================================

class C2S : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:Trd_UnlockTrade.C2S) */ {
 public:
  C2S();
  virtual ~C2S();

  C2S(const C2S& from);

  inline C2S& operator=(const C2S& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  C2S(C2S&& from) noexcept
    : C2S() {
    *this = ::std::move(from);
  }

  inline C2S& operator=(C2S&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const C2S& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const C2S* internal_default_instance() {
    return reinterpret_cast<const C2S*>(
               &_C2S_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(C2S* other);
  friend void swap(C2S& a, C2S& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline C2S* New() const PROTOBUF_FINAL { return New(NULL); }

  C2S* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const C2S& from);
  void MergeFrom(const C2S& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(C2S* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional string pwdMD5 = 2;
  bool has_pwdmd5() const;
  void clear_pwdmd5();
  static const int kPwdMD5FieldNumber = 2;
  const ::std::string& pwdmd5() const;
  void set_pwdmd5(const ::std::string& value);
  #if LANG_CXX11
  void set_pwdmd5(::std::string&& value);
  #endif
  void set_pwdmd5(const char* value);
  void set_pwdmd5(const char* value, size_t size);
  ::std::string* mutable_pwdmd5();
  ::std::string* release_pwdmd5();
  void set_allocated_pwdmd5(::std::string* pwdmd5);

  // required bool unlock = 1;
  bool has_unlock() const;
  void clear_unlock();
  static const int kUnlockFieldNumber = 1;
  bool unlock() const;
  void set_unlock(bool value);

  // optional int32 securityFirm = 3;
  bool has_securityfirm() const;
  void clear_securityfirm();
  static const int kSecurityFirmFieldNumber = 3;
  ::google::protobuf::int32 securityfirm() const;
  void set_securityfirm(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:Trd_UnlockTrade.C2S)
 private:
  void set_has_unlock();
  void clear_has_unlock();
  void set_has_pwdmd5();
  void clear_has_pwdmd5();
  void set_has_securityfirm();
  void clear_has_securityfirm();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  ::google::protobuf::internal::ArenaStringPtr pwdmd5_;
  bool unlock_;
  ::google::protobuf::int32 securityfirm_;
  friend struct ::protobuf_Trd_5fUnlockTrade_2eproto::TableStruct;
  friend void ::protobuf_Trd_5fUnlockTrade_2eproto::InitDefaultsC2SImpl();
};
// -------------------------------------------------------------------

class S2C : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:Trd_UnlockTrade.S2C) */ {
 public:
  S2C();
  virtual ~S2C();

  S2C(const S2C& from);

  inline S2C& operator=(const S2C& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  S2C(S2C&& from) noexcept
    : S2C() {
    *this = ::std::move(from);
  }

  inline S2C& operator=(S2C&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const S2C& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const S2C* internal_default_instance() {
    return reinterpret_cast<const S2C*>(
               &_S2C_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    1;

  void Swap(S2C* other);
  friend void swap(S2C& a, S2C& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline S2C* New() const PROTOBUF_FINAL { return New(NULL); }

  S2C* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const S2C& from);
  void MergeFrom(const S2C& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(S2C* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // @@protoc_insertion_point(class_scope:Trd_UnlockTrade.S2C)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  friend struct ::protobuf_Trd_5fUnlockTrade_2eproto::TableStruct;
  friend void ::protobuf_Trd_5fUnlockTrade_2eproto::InitDefaultsS2CImpl();
};
// -------------------------------------------------------------------

class Request : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:Trd_UnlockTrade.Request) */ {
 public:
  Request();
  virtual ~Request();

  Request(const Request& from);

  inline Request& operator=(const Request& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Request(Request&& from) noexcept
    : Request() {
    *this = ::std::move(from);
  }

  inline Request& operator=(Request&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Request& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Request* internal_default_instance() {
    return reinterpret_cast<const Request*>(
               &_Request_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    2;

  void Swap(Request* other);
  friend void swap(Request& a, Request& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Request* New() const PROTOBUF_FINAL { return New(NULL); }

  Request* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const Request& from);
  void MergeFrom(const Request& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(Request* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required .Trd_UnlockTrade.C2S c2s = 1;
  bool has_c2s() const;
  void clear_c2s();
  static const int kC2SFieldNumber = 1;
  const ::Trd_UnlockTrade::C2S& c2s() const;
  ::Trd_UnlockTrade::C2S* release_c2s();
  ::Trd_UnlockTrade::C2S* mutable_c2s();
  void set_allocated_c2s(::Trd_UnlockTrade::C2S* c2s);

  // @@protoc_insertion_point(class_scope:Trd_UnlockTrade.Request)
 private:
  void set_has_c2s();
  void clear_has_c2s();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  ::Trd_UnlockTrade::C2S* c2s_;
  friend struct ::protobuf_Trd_5fUnlockTrade_2eproto::TableStruct;
  friend void ::protobuf_Trd_5fUnlockTrade_2eproto::InitDefaultsRequestImpl();
};
// -------------------------------------------------------------------

class Response : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:Trd_UnlockTrade.Response) */ {
 public:
  Response();
  virtual ~Response();

  Response(const Response& from);

  inline Response& operator=(const Response& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Response(Response&& from) noexcept
    : Response() {
    *this = ::std::move(from);
  }

  inline Response& operator=(Response&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Response& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Response* internal_default_instance() {
    return reinterpret_cast<const Response*>(
               &_Response_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    3;

  void Swap(Response* other);
  friend void swap(Response& a, Response& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Response* New() const PROTOBUF_FINAL { return New(NULL); }

  Response* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const Response& from);
  void MergeFrom(const Response& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(Response* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional string retMsg = 2;
  bool has_retmsg() const;
  void clear_retmsg();
  static const int kRetMsgFieldNumber = 2;
  const ::std::string& retmsg() const;
  void set_retmsg(const ::std::string& value);
  #if LANG_CXX11
  void set_retmsg(::std::string&& value);
  #endif
  void set_retmsg(const char* value);
  void set_retmsg(const char* value, size_t size);
  ::std::string* mutable_retmsg();
  ::std::string* release_retmsg();
  void set_allocated_retmsg(::std::string* retmsg);

  // optional .Trd_UnlockTrade.S2C s2c = 4;
  bool has_s2c() const;
  void clear_s2c();
  static const int kS2CFieldNumber = 4;
  const ::Trd_UnlockTrade::S2C& s2c() const;
  ::Trd_UnlockTrade::S2C* release_s2c();
  ::Trd_UnlockTrade::S2C* mutable_s2c();
  void set_allocated_s2c(::Trd_UnlockTrade::S2C* s2c);

  // optional int32 errCode = 3;
  bool has_errcode() const;
  void clear_errcode();
  static const int kErrCodeFieldNumber = 3;
  ::google::protobuf::int32 errcode() const;
  void set_errcode(::google::protobuf::int32 value);

  // required int32 retType = 1 [default = -400];
  bool has_rettype() const;
  void clear_rettype();
  static const int kRetTypeFieldNumber = 1;
  ::google::protobuf::int32 rettype() const;
  void set_rettype(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:Trd_UnlockTrade.Response)
 private:
  void set_has_rettype();
  void clear_has_rettype();
  void set_has_retmsg();
  void clear_has_retmsg();
  void set_has_errcode();
  void clear_has_errcode();
  void set_has_s2c();
  void clear_has_s2c();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  ::google::protobuf::internal::ArenaStringPtr retmsg_;
  ::Trd_UnlockTrade::S2C* s2c_;
  ::google::protobuf::int32 errcode_;
  ::google::protobuf::int32 rettype_;
  friend struct ::protobuf_Trd_5fUnlockTrade_2eproto::TableStruct;
  friend void ::protobuf_Trd_5fUnlockTrade_2eproto::InitDefaultsResponseImpl();
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// C2S

// required bool unlock = 1;
inline bool C2S::has_unlock() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void C2S::set_has_unlock() {
  _has_bits_[0] |= 0x00000002u;
}
inline void C2S::clear_has_unlock() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void C2S::clear_unlock() {
  unlock_ = false;
  clear_has_unlock();
}
inline bool C2S::unlock() const {
  // @@protoc_insertion_point(field_get:Trd_UnlockTrade.C2S.unlock)
  return unlock_;
}
inline void C2S::set_unlock(bool value) {
  set_has_unlock();
  unlock_ = value;
  // @@protoc_insertion_point(field_set:Trd_UnlockTrade.C2S.unlock)
}

// optional string pwdMD5 = 2;
inline bool C2S::has_pwdmd5() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void C2S::set_has_pwdmd5() {
  _has_bits_[0] |= 0x00000001u;
}
inline void C2S::clear_has_pwdmd5() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void C2S::clear_pwdmd5() {
  pwdmd5_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_pwdmd5();
}
inline const ::std::string& C2S::pwdmd5() const {
  // @@protoc_insertion_point(field_get:Trd_UnlockTrade.C2S.pwdMD5)
  return pwdmd5_.GetNoArena();
}
inline void C2S::set_pwdmd5(const ::std::string& value) {
  set_has_pwdmd5();
  pwdmd5_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:Trd_UnlockTrade.C2S.pwdMD5)
}
#if LANG_CXX11
inline void C2S::set_pwdmd5(::std::string&& value) {
  set_has_pwdmd5();
  pwdmd5_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:Trd_UnlockTrade.C2S.pwdMD5)
}
#endif
inline void C2S::set_pwdmd5(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  set_has_pwdmd5();
  pwdmd5_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Trd_UnlockTrade.C2S.pwdMD5)
}
inline void C2S::set_pwdmd5(const char* value, size_t size) {
  set_has_pwdmd5();
  pwdmd5_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Trd_UnlockTrade.C2S.pwdMD5)
}
inline ::std::string* C2S::mutable_pwdmd5() {
  set_has_pwdmd5();
  // @@protoc_insertion_point(field_mutable:Trd_UnlockTrade.C2S.pwdMD5)
  return pwdmd5_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* C2S::release_pwdmd5() {
  // @@protoc_insertion_point(field_release:Trd_UnlockTrade.C2S.pwdMD5)
  clear_has_pwdmd5();
  return pwdmd5_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void C2S::set_allocated_pwdmd5(::std::string* pwdmd5) {
  if (pwdmd5 != NULL) {
    set_has_pwdmd5();
  } else {
    clear_has_pwdmd5();
  }
  pwdmd5_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), pwdmd5);
  // @@protoc_insertion_point(field_set_allocated:Trd_UnlockTrade.C2S.pwdMD5)
}

// optional int32 securityFirm = 3;
inline bool C2S::has_securityfirm() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void C2S::set_has_securityfirm() {
  _has_bits_[0] |= 0x00000004u;
}
inline void C2S::clear_has_securityfirm() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void C2S::clear_securityfirm() {
  securityfirm_ = 0;
  clear_has_securityfirm();
}
inline ::google::protobuf::int32 C2S::securityfirm() const {
  // @@protoc_insertion_point(field_get:Trd_UnlockTrade.C2S.securityFirm)
  return securityfirm_;
}
inline void C2S::set_securityfirm(::google::protobuf::int32 value) {
  set_has_securityfirm();
  securityfirm_ = value;
  // @@protoc_insertion_point(field_set:Trd_UnlockTrade.C2S.securityFirm)
}

// -------------------------------------------------------------------

// S2C

// -------------------------------------------------------------------

// Request

// required .Trd_UnlockTrade.C2S c2s = 1;
inline bool Request::has_c2s() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Request::set_has_c2s() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Request::clear_has_c2s() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Request::clear_c2s() {
  if (c2s_ != NULL) c2s_->Clear();
  clear_has_c2s();
}
inline const ::Trd_UnlockTrade::C2S& Request::c2s() const {
  const ::Trd_UnlockTrade::C2S* p = c2s_;
  // @@protoc_insertion_point(field_get:Trd_UnlockTrade.Request.c2s)
  return p != NULL ? *p : *reinterpret_cast<const ::Trd_UnlockTrade::C2S*>(
      &::Trd_UnlockTrade::_C2S_default_instance_);
}
inline ::Trd_UnlockTrade::C2S* Request::release_c2s() {
  // @@protoc_insertion_point(field_release:Trd_UnlockTrade.Request.c2s)
  clear_has_c2s();
  ::Trd_UnlockTrade::C2S* temp = c2s_;
  c2s_ = NULL;
  return temp;
}
inline ::Trd_UnlockTrade::C2S* Request::mutable_c2s() {
  set_has_c2s();
  if (c2s_ == NULL) {
    c2s_ = new ::Trd_UnlockTrade::C2S;
  }
  // @@protoc_insertion_point(field_mutable:Trd_UnlockTrade.Request.c2s)
  return c2s_;
}
inline void Request::set_allocated_c2s(::Trd_UnlockTrade::C2S* c2s) {
  ::google::protobuf::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == NULL) {
    delete c2s_;
  }
  if (c2s) {
    ::google::protobuf::Arena* submessage_arena = NULL;
    if (message_arena != submessage_arena) {
      c2s = ::google::protobuf::internal::GetOwnedMessage(
          message_arena, c2s, submessage_arena);
    }
    set_has_c2s();
  } else {
    clear_has_c2s();
  }
  c2s_ = c2s;
  // @@protoc_insertion_point(field_set_allocated:Trd_UnlockTrade.Request.c2s)
}

// -------------------------------------------------------------------

// Response

// required int32 retType = 1 [default = -400];
inline bool Response::has_rettype() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void Response::set_has_rettype() {
  _has_bits_[0] |= 0x00000008u;
}
inline void Response::clear_has_rettype() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void Response::clear_rettype() {
  rettype_ = -400;
  clear_has_rettype();
}
inline ::google::protobuf::int32 Response::rettype() const {
  // @@protoc_insertion_point(field_get:Trd_UnlockTrade.Response.retType)
  return rettype_;
}
inline void Response::set_rettype(::google::protobuf::int32 value) {
  set_has_rettype();
  rettype_ = value;
  // @@protoc_insertion_point(field_set:Trd_UnlockTrade.Response.retType)
}

// optional string retMsg = 2;
inline bool Response::has_retmsg() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Response::set_has_retmsg() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Response::clear_has_retmsg() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Response::clear_retmsg() {
  retmsg_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_retmsg();
}
inline const ::std::string& Response::retmsg() const {
  // @@protoc_insertion_point(field_get:Trd_UnlockTrade.Response.retMsg)
  return retmsg_.GetNoArena();
}
inline void Response::set_retmsg(const ::std::string& value) {
  set_has_retmsg();
  retmsg_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:Trd_UnlockTrade.Response.retMsg)
}
#if LANG_CXX11
inline void Response::set_retmsg(::std::string&& value) {
  set_has_retmsg();
  retmsg_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:Trd_UnlockTrade.Response.retMsg)
}
#endif
inline void Response::set_retmsg(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  set_has_retmsg();
  retmsg_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Trd_UnlockTrade.Response.retMsg)
}
inline void Response::set_retmsg(const char* value, size_t size) {
  set_has_retmsg();
  retmsg_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Trd_UnlockTrade.Response.retMsg)
}
inline ::std::string* Response::mutable_retmsg() {
  set_has_retmsg();
  // @@protoc_insertion_point(field_mutable:Trd_UnlockTrade.Response.retMsg)
  return retmsg_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Response::release_retmsg() {
  // @@protoc_insertion_point(field_release:Trd_UnlockTrade.Response.retMsg)
  clear_has_retmsg();
  return retmsg_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Response::set_allocated_retmsg(::std::string* retmsg) {
  if (retmsg != NULL) {
    set_has_retmsg();
  } else {
    clear_has_retmsg();
  }
  retmsg_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), retmsg);
  // @@protoc_insertion_point(field_set_allocated:Trd_UnlockTrade.Response.retMsg)
}

// optional int32 errCode = 3;
inline bool Response::has_errcode() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Response::set_has_errcode() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Response::clear_has_errcode() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Response::clear_errcode() {
  errcode_ = 0;
  clear_has_errcode();
}
inline ::google::protobuf::int32 Response::errcode() const {
  // @@protoc_insertion_point(field_get:Trd_UnlockTrade.Response.errCode)
  return errcode_;
}
inline void Response::set_errcode(::google::protobuf::int32 value) {
  set_has_errcode();
  errcode_ = value;
  // @@protoc_insertion_point(field_set:Trd_UnlockTrade.Response.errCode)
}

// optional .Trd_UnlockTrade.S2C s2c = 4;
inline bool Response::has_s2c() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Response::set_has_s2c() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Response::clear_has_s2c() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Response::clear_s2c() {
  if (s2c_ != NULL) s2c_->Clear();
  clear_has_s2c();
}
inline const ::Trd_UnlockTrade::S2C& Response::s2c() const {
  const ::Trd_UnlockTrade::S2C* p = s2c_;
  // @@protoc_insertion_point(field_get:Trd_UnlockTrade.Response.s2c)
  return p != NULL ? *p : *reinterpret_cast<const ::Trd_UnlockTrade::S2C*>(
      &::Trd_UnlockTrade::_S2C_default_instance_);
}
inline ::Trd_UnlockTrade::S2C* Response::release_s2c() {
  // @@protoc_insertion_point(field_release:Trd_UnlockTrade.Response.s2c)
  clear_has_s2c();
  ::Trd_UnlockTrade::S2C* temp = s2c_;
  s2c_ = NULL;
  return temp;
}
inline ::Trd_UnlockTrade::S2C* Response::mutable_s2c() {
  set_has_s2c();
  if (s2c_ == NULL) {
    s2c_ = new ::Trd_UnlockTrade::S2C;
  }
  // @@protoc_insertion_point(field_mutable:Trd_UnlockTrade.Response.s2c)
  return s2c_;
}
inline void Response::set_allocated_s2c(::Trd_UnlockTrade::S2C* s2c) {
  ::google::protobuf::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == NULL) {
    delete s2c_;
  }
  if (s2c) {
    ::google::protobuf::Arena* submessage_arena = NULL;
    if (message_arena != submessage_arena) {
      s2c = ::google::protobuf::internal::GetOwnedMessage(
          message_arena, s2c, submessage_arena);
    }
    set_has_s2c();
  } else {
    clear_has_s2c();
  }
  s2c_ = s2c;
  // @@protoc_insertion_point(field_set_allocated:Trd_UnlockTrade.Response.s2c)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace Trd_UnlockTrade

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_Trd_5fUnlockTrade_2eproto__INCLUDED