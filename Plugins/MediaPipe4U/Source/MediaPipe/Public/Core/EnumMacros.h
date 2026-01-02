// // Copyright (c) 2025 Anders Xiao. All rights reserved.
// // https://github.com/endink
// // Create: 2025-04-07

#pragma once



#define DEFINE_FLAG_ENUM(EnumClass, Export) \
inline Export EnumClass operator|(EnumClass A, EnumClass B) \
{ \
	return static_cast<EnumClass>(static_cast<uint8>(A) | static_cast<uint8>(B)); \
} \
\
inline Export EnumClass operator&(EnumClass A, EnumClass B) \
{ \
	return static_cast<EnumClass>(static_cast<uint8>(A) & static_cast<uint8>(B)); \
} \
\
inline Export EnumClass operator~(EnumClass A) \
{ \
	return static_cast<EnumClass>(~static_cast<uint8>(A)); \
} \
\
inline Export bool Has##EnumClass##Flag(const EnumClass& Value, const EnumClass& Flag) \
{ \
	return (Value & Flag) == Flag; \
} 

