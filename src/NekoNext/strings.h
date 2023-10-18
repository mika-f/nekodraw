#pragma once

#include "pch.h"
#include "defines.h"

namespace NekoNext::Strings
{
    /**
     * \brief create Triglav compatible strings for ASCII characters
     */
    class AsciiString
    {
    private:
        TriglavPlugInStringService* _stringService;
        TriglavPlugInStringObject _value;

    public:
        AsciiString(TriglavPlugInStringService* stringService, const char* str);
        AsciiString(TriglavPlugInStringService* stringService, const std::string& str);

        ~AsciiString();

        // copy constructor & assignment
        AsciiString(const AsciiString& other);
        AsciiString& operator=(const AsciiString& other);

        // move constructor & assignment
        AsciiString(AsciiString&& other) noexcept;
        AsciiString& operator=(AsciiString&& other) noexcept;

        // operators
        implicit operator TriglavPlugInStringObject() const;
    };

    /**
     * \brief create Triglav compatible strings for Unicode characters
     */
    class UnicodeString
    {
    private:
        TriglavPlugInStringService* _stringService;
        TriglavPlugInStringObject _value;

    public:
        UnicodeString(TriglavPlugInStringService* stringService, const unsigned short* str);
        UnicodeString(TriglavPlugInStringService* stringService, const std::wstring& str);

        ~UnicodeString();

        // copy constructor & assignment
        UnicodeString(const UnicodeString& other);
        UnicodeString& operator=(const UnicodeString& other);

        // move constructor & assignment
        UnicodeString(UnicodeString&& other) noexcept;
        UnicodeString& operator=(UnicodeString&& other) noexcept;

        // operators
        implicit operator TriglavPlugInStringObject() const;
    };

    /**
     * \brief create Triglav compatible strings for local code characters
     */
    class LocalCodeString
    {
    private:
        TriglavPlugInStringService* _stringService;
        TriglavPlugInStringObject _value;

    public:
        LocalCodeString(TriglavPlugInStringService* stringService, const char* str);
        LocalCodeString(TriglavPlugInStringService* stringService, const std::string& str);

        ~LocalCodeString();

        // copy constructor & assignment
        LocalCodeString(const LocalCodeString& other);
        LocalCodeString& operator=(const LocalCodeString& other);

        // move constructor & assignment
        LocalCodeString(LocalCodeString&& other) noexcept;
        LocalCodeString& operator=(LocalCodeString&& other) noexcept;

        // operators
        implicit operator TriglavPlugInStringObject() const;
    };
};
