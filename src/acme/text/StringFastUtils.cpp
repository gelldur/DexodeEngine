#include "StringFastUtils.h"

#include <string.h>
#include <stdio.h>
#include <regex>
#include "Utf8.h"

char buffer[2048];

void extractWord(std::vector<std::string>& processedTags, const char* text, long length)
{
	strncpy(buffer, text, length);
	buffer[length] = '\0';

	processedTags.push_back(buffer);
}

const std::vector<std::string> process(
		const char* text
		, long minimumTagLength
		, const std::vector<long>& skipPosition)
{
	const char* cText = text;

	std::vector<std::string> processedTags;
	processedTags.reserve(64);

	long previousStringStart = 0;
	long i = -1;

	long skipIndex = 0;

	while (text[++i] != '\0')
	{
		if (i < skipPosition[skipIndex])
		{
			if (text[i] == '&'
				&& text[i + 1] == 'n'
				&& text[i + 2] == 'b'
				&& text[i + 3] == 's'
				&& text[i + 4] == 'p'
				&& text[i + 5] == ';')
			{
				long tagLength = i - previousStringStart;
				if (tagLength >= minimumTagLength)
				{
					extractWord(processedTags, cText + previousStringStart, tagLength);
				}

				previousStringStart = i + 6;
			}
			if (text[i] == ','
				|| text[i] == ' '
				|| text[i] == '"'
				|| text[i] == '('
				|| text[i] == ')'
				|| text[i] == '*'
				|| text[i] == '/'
				|| text[i] == ':'
				|| text[i] == '.'
				|| text[i] == '\n'
				|| text[i] == '\t')
			{
				if (i - previousStringStart >= minimumTagLength)
				{
					extractWord(processedTags, cText + previousStringStart, i - previousStringStart);
				}

				previousStringStart = i + 1;
			}
		}
		else
		{
			if (i - previousStringStart >= minimumTagLength)
			{
				extractWord(processedTags, cText + previousStringStart, i - previousStringStart);
			}
			i = skipPosition[skipIndex + 1];
			skipIndex += 2;
			previousStringStart = i;
			--i;
			continue;
		}
	}

	if (i - previousStringStart >= minimumTagLength)
	{
		extractWord(processedTags, cText + previousStringStart, i - previousStringStart);
	}

	return processedTags;
}

/**
 * Returns vector of tags.
 */
const std::vector<std::string> processTags(
		const char* nativeString
		, long minimumTagLength
		, const std::vector<long>& skipPosition)
{
	std::string normalizedString(nativeString);
	Utf8::normalizeString(normalizedString);
	return process(normalizedString.c_str(), minimumTagLength, skipPosition);
}

std::regex htmlCodes("<[^>]*>");

const std::vector<std::string> processTagsStripHtml(const char* nativeString, long minimumTagLength)
{
	std::string normalizedString(nativeString);
	Utf8::normalizeString(normalizedString);

	const char* text = normalizedString.c_str();

	//Find all html codes
	std::cmatch matches;

	std::vector<long> skipChars;
	long offset = 0;
	while (std::regex_search(text + offset, matches, htmlCodes))
	{
		if (matches.size() < 1)
		{
			break;
		}

		for (unsigned long i = 0; i < matches.size(); ++i)
		{
			const long position = matches.position(i) + offset;
			const long length = matches.length(i);

			skipChars.push_back(position);
			skipChars.push_back(position + length);
			offset = position + length;
		}
	}

	skipChars.push_back(1000000);
	skipChars.push_back(10);

	return process(text, minimumTagLength, skipChars);
}
