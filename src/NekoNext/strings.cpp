#include "strings.h"

NekoNext::Strings::AsciiString::AsciiString(TriglavPlugInStringService* stringService, const char* str)
{
    this->_stringService = stringService;

    TriglavPlugInStringObject value;
    this->_stringService->createWithAsciiStringProc(&value, str, static_cast<TriglavPlugInInt>(strlen(str)));

    this->_value = value;
}

NekoNext::Strings::AsciiString::AsciiString(TriglavPlugInStringService* stringService, const std::string& str) : AsciiString(stringService, str.c_str())
{
}

NekoNext::Strings::AsciiString::~AsciiString()
{
    this->_stringService->releaseProc(this->_value);
}

NekoNext::Strings::AsciiString::AsciiString(const AsciiString& other)
{
    this->_stringService = other._stringService;

    TriglavPlugInInt length;
    this->_stringService->getLocalCodeLengthProc(&length, other);

    const char* str = new char[length];
    this->_stringService->getLocalCodeCharsProc(&str, other);

    TriglavPlugInStringObject value;
    this->_stringService->createWithAsciiStringProc(&value, str, static_cast<TriglavPlugInInt>(strlen(str)));
    this->_value = value;
}

NekoNext::Strings::AsciiString& NekoNext::Strings::AsciiString::operator=(const AsciiString& other)
{
    if (this == &other)
        return *this;

    TriglavPlugInInt length;
    this->_stringService->getLocalCodeLengthProc(&length, other);

    const char* str = new char[length];
    this->_stringService->getLocalCodeCharsProc(&str, other);

    TriglavPlugInStringObject newString; // allocate
    other._stringService->createWithAsciiStringProc(&newString, str, static_cast<TriglavPlugInInt>(strlen(str))); // populate

    this->_stringService->releaseProc(this->_value); // deallocate

    this->_value = newString;
    return *this;
}

NekoNext::Strings::AsciiString& NekoNext::Strings::AsciiString::operator=(AsciiString&& other) noexcept
{
    std::swap(this->_value, other._value);

    return *this;
}

NekoNext::Strings::AsciiString::operator TriglavPlugInStringObject() const
{
    return this->_value;
}

NekoNext::Strings::AsciiString::AsciiString(AsciiString&& other) noexcept : _stringService(std::exchange(other._stringService, nullptr)),
                                                                            _value(std::exchange(other._value, nullptr))
{
}

NekoNext::Strings::UnicodeString::UnicodeString(TriglavPlugInStringService* stringService, const unsigned short* str)
{
    this->_stringService = stringService;

    TriglavPlugInStringObject value;
    this->_stringService->createWithUnicodeStringProc(&value, str, static_cast<TriglavPlugInInt>(std::char_traits<unsigned short>::length(str)));

    this->_value = value;
}

NekoNext::Strings::UnicodeString::UnicodeString(TriglavPlugInStringService* stringService, const std::wstring& str)
{
    this->_stringService = stringService;

    TriglavPlugInStringObject value;
    const auto length = str.length();
    const wchar_t* wcs = str.c_str();
    const auto uniStrings = new unsigned short[length];

    // MAYBE buffer-overrun???
    for (auto i = 0; i < length - 1; i++)
        uniStrings[i] = static_cast<unsigned short>(wcs[i]);

    this->_stringService->createWithUnicodeStringProc(&value, uniStrings, static_cast<TriglavPlugInInt>(str.length()));

    this->_value = value;
}

NekoNext::Strings::UnicodeString::~UnicodeString()
{
    this->_stringService->releaseProc(this->_value);
}

NekoNext::Strings::UnicodeString::UnicodeString(const UnicodeString& other)
{
    this->_stringService = other._stringService;

    TriglavPlugInInt length;
    this->_stringService->getUnicodeLengthProc(&length, other);

    const unsigned short* str = new unsigned short[length];
    this->_stringService->getUnicodeCharsProc(&str, other);

    TriglavPlugInStringObject value;
    this->_stringService->createWithUnicodeStringProc(&value, str, static_cast<TriglavPlugInInt>(std::char_traits<unsigned short>::length(str)));
    this->_value = value;
}

NekoNext::Strings::UnicodeString& NekoNext::Strings::UnicodeString::operator=(const UnicodeString& other)
{
    if (this == &other)
        return *this;

    TriglavPlugInInt length;
    this->_stringService->getUnicodeLengthProc(&length, other);

    const unsigned short* str = new unsigned short[length];
    this->_stringService->getUnicodeCharsProc(&str, other);

    TriglavPlugInStringObject newString; // allocate
    other._stringService->createWithUnicodeStringProc(&newString, str, static_cast<TriglavPlugInInt>(std::char_traits<unsigned short>::length(str))); // populate

    this->_stringService->releaseProc(this->_value); // deallocate

    this->_value = newString;
    return *this;
}

NekoNext::Strings::UnicodeString& NekoNext::Strings::UnicodeString::operator=(UnicodeString&& other) noexcept
{
    std::swap(this->_value, other._value);

    return *this;
}

NekoNext::Strings::UnicodeString::operator TriglavPlugInStringObject() const
{
    return this->_value;
}

NekoNext::Strings::UnicodeString::UnicodeString(UnicodeString&& other) noexcept : _stringService(std::exchange(other._stringService, nullptr)),
                                                                                  _value(std::exchange(other._value, nullptr))
{
}

NekoNext::Strings::LocalCodeString::LocalCodeString(TriglavPlugInStringService* stringService, const char* str)
{
    this->_stringService = stringService;

    TriglavPlugInStringObject value;
    this->_stringService->createWithLocalCodeStringProc(&value, str, static_cast<TriglavPlugInInt>(strlen(str)));

    this->_value = value;
}

NekoNext::Strings::LocalCodeString::LocalCodeString(TriglavPlugInStringService* stringService, const std::string& str) : LocalCodeString(stringService, str.c_str())
{
}

NekoNext::Strings::LocalCodeString::~LocalCodeString()
{
    this->_stringService->releaseProc(this->_value);
}

NekoNext::Strings::LocalCodeString::LocalCodeString(const LocalCodeString& other)
{
    this->_stringService = other._stringService;

    TriglavPlugInInt length;
    this->_stringService->getLocalCodeLengthProc(&length, other);

    const char* str = new char[length];
    this->_stringService->getLocalCodeCharsProc(&str, other);

    TriglavPlugInStringObject value;
    this->_stringService->createWithLocalCodeStringProc(&value, str, static_cast<TriglavPlugInInt>(strlen(str)));
    this->_value = value;
}

NekoNext::Strings::LocalCodeString& NekoNext::Strings::LocalCodeString::operator=(const LocalCodeString& other)
{
    if (this == &other)
        return *this;

    TriglavPlugInInt length;
    this->_stringService->getLocalCodeLengthProc(&length, other);

    const char* str = new char[length];
    this->_stringService->getLocalCodeCharsProc(&str, other);

    TriglavPlugInStringObject newString; // allocate
    other._stringService->createWithLocalCodeStringProc(&newString, str, static_cast<TriglavPlugInInt>(strlen(str))); // populate

    this->_stringService->releaseProc(this->_value); // deallocate

    this->_value = newString;
    return *this;
}

NekoNext::Strings::LocalCodeString& NekoNext::Strings::LocalCodeString::operator=(LocalCodeString&& other) noexcept
{
    std::swap(this->_value, other._value);

    return *this;
}

NekoNext::Strings::LocalCodeString::operator TriglavPlugInStringObject() const
{
    return this->_value;
}

NekoNext::Strings::LocalCodeString::LocalCodeString(LocalCodeString&& other) noexcept : _stringService(std::exchange(other._stringService, nullptr)),
                                                                                        _value(std::exchange(other._value, nullptr))
{
}
