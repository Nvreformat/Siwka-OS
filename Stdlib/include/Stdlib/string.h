#ifndef STRING_H
#define STRING_H

typedef char* String;

size_t StringGetLength(String String);
int StringEqual(String String1, String String2);
String StringConcat(String String1, String String2);
void StringCopy(String SourceString, void* Destination);
String StringFormat(String Destination, String Pattern, ...);
String StringConvertUnsignedLong(String Buffer, uint64_t Value);
String StringConvertLong(String Buffer, int64_t Value);
String StringConvertHex(String Buffer, int64_t Value);
String StringLower(String Buffer);
String StringUpper(String Buffer);

#endif
