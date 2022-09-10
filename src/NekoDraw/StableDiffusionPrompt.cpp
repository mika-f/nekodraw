#include "pch.h"

#include "StableDiffusionPrompt.h"
#include "Strings.h"

std::string StableDiffusionPrompt::toString() const
{
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
    const auto vector = std::vector{
        convert.to_bytes(this->format),
        convert.to_bytes(this->subject),
        convert.to_bytes(this->subjectCaption),
        convert.to_bytes(this->servant),
        convert.to_bytes(this->formatCaption),
        convert.to_bytes(this->flavor)
    };

    const auto delimiter = " ";
    std::ostringstream os;
    std::ranges::copy(vector, std::ostream_iterator<std::string>(os, delimiter));

    return trim_c(os.str());
}
