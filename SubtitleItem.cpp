#include <iostream>
#include <algorithm>
#include <regex>
#include "SubtitleItem.h"

/*
#if (defined (WIN32) || defined (_WIN32_WCE)) && (defined(__MINGW32__) || !defined(__GNUC__))
#define LLD_M "I64d"
#define LLU_M "I64u"
#define LLD "%I64d"
#define LLU "%I64u"
#elif defined (__SYMBIAN32__)
#define LLD_M "d"
#define LLU_M "u"
#define LLD "%d"
#define LLU "%u"
#elif defined(__DARWIN__) || defined(__APPLE__)
#define LLD_M "lld"
#define LLU_M "llu"
#define LLD "%lld"
#define LLU "%llu"
#elif defined(_LP64) // Unix 64 bits
#define LLD_M "ld"
#define LLU_M "lu"
#define LLD "%ld"
#define LLU "%lu"
#else // Unix 32 bits
#define LLD_M "lld"
#define LLU_M "llu"
#define LLD "%lld"
#define LLU "%llu"
#endif

char* timestamp_to_srttime(unsigned long long milliseconds) {
    unsigned long long millis = milliseconds % 1000;
    milliseconds /= 1000;
    unsigned long long seconds = milliseconds % 60;
    milliseconds /= 60;
    unsigned long long minutes = milliseconds % 60;
    milliseconds /= 60;
    unsigned long long hours = milliseconds;

    char* buf = new char[(sizeof(char) * 15)];
    sprintf(buf, "%02" LLD_M ":%02" LLD_M ":%02" LLD_M ",%03" LLD_M, hours, minutes, seconds, millis);
    return buf;
}
*/

SubtitleItem::SubtitleItem(void)
{
}

SubtitleItem::SubtitleItem(std::string startTime,std::string endTime, std::string text)
{
	_startTime = timeMSec(startTime);
	_endTime = timeMSec(endTime);
	_text = text;

    _startTimeString = startTime;
    _endTimeString = endTime;

//    char *time = new char[1024];
//    time = timestamp_to_srttime(_startTime);
//
//    std::cout<<startTime<<" ---> "<<time<<std::endl;
}

SubtitleItem::SubtitleItem(std::string startTime,std::string endTime, std::string text, bool ignore = false,
						   std::string justDialogue = NULL , int speakerCount = 0, int nonDialogueCount = 0,
						   std::vector<std::string> speaker = std::vector<std::string>(),
						   std::vector<std::string> nonDialogue = std::vector<std::string>())
{
	_startTime = timeMSec(startTime);
	_endTime = timeMSec(endTime);
	_text = text;

    _startTimeString = startTime;
    _endTimeString = endTime;
    _ignore = ignore;
	_justDialogue = justDialogue;
	_speakerCount = speakerCount;
	_nonDialogueCount = nonDialogueCount;
	_speaker = speaker;
	_nonDialogue = nonDialogue;
}

long int SubtitleItem::timeMSec(std::string value)
{
	std::string szRegex = "([0-9]+):([0-9]{2}):([0-9]{2}),([0-9]{3})";
	std::regex subRegex (szRegex);
	int submatches[] = {1,2,3,4};
	std::regex_token_iterator<std::string::iterator> c ( value.begin(), value.end(), subRegex, submatches );
	std::regex_token_iterator<std::string::iterator> rend;
	std::vector<std::string> parts;
	while (c!=rend)
	{
		parts.push_back(*c++);
	}
	return atoi(parts[0].c_str()) * 3600000 + atoi(parts[1].c_str()) * 60000 + atoi(parts[2].c_str()) * 1000 + atoi(parts[3].c_str());
}

long int SubtitleItem::getStartTime() const
{
	return _startTime;
}
long int SubtitleItem::getEndTime() const
{
	return _endTime;
}

std::string SubtitleItem::getText() const
{
	return _text;
}

void SubtitleItem::setStartTime(long int startTime)
{
	_startTime = startTime;
}
void SubtitleItem::setEndTime(long int endTime)
{
	_endTime = endTime;
}
void SubtitleItem::setText(std::string text)
{
	_text = text;
}

SubtitleItem::~SubtitleItem(void)
{

}

std::string SubtitleItem::getStartTimeString() const
{
    return _startTimeString;
}

std::string SubtitleItem::getEndTimeString() const
{
    return _endTimeString;
}

bool SubtitleItem::getIgnoreStatus() const
{
	if(_ignore)
		return true;

	else
		return false;

}

void SubtitleItem::extractInfo(bool keepHTML = 0, bool doNotIgnoreNonDialogues = 0, bool doNotRemoveSpeakerNames = 0)
{
    std::string output;

    //stripping HTML tags
    if(!keepHTML)
    {
        /* REGEX Based approach; <! C++ 11
        std::regex tags("<[^<]*>");
        std::regex_replace(std::back_inserter(output), _text.begin(), _text.end(), tags, "");
        */

        int countP = 0;
        for(char& c : output)
        {
            if(c=='<')
            {
                countP++;
                c = '~';
            }

            else
            {
                if(countP!=0)
                {
                    if(c != '>')
                        c = '~';

                    else if(c == '>')
                    {
                        c = '~';
                        countP--;
                    }
                }
            }
        }
    }

    //stripping non dialogue data e.g. (applause)
    //EXPERIMENTAL
    if(!doNotIgnoreNonDialogues)
    {
        int countP = 0;
        for(char& c : output)
        {
            if(c=='(')
            {
                countP++;
                c = '~';
            }

            else
            {
                if(countP!=0)
                {
                    if(c != ')')
                        c = '~';

                    else if(c == ')')
                    {
                        c = '~';
                        countP--;
                    }
                }
            }
        }
    }

    //Extracting speaker names
    if(!doNotRemoveSpeakerNames)
    {
        for(int i=0; output[i]!='\0';i++)
        {
            int colonIndex = 0, prevSpaceIndex = 0;
            if(output[i]==':')  //speaker found; travel back
            {
                _speakerCount++;
                colonIndex = i;

                for(int j=i; j>0;j--)
                {
                    if(output[j]== ' ' || output[j]== '\n' )
                    {
                        prevSpaceIndex = j;
                        //i = prevSpaceIndex;
                        break;
                    }
                }

                _speaker.push_back(output.substr(prevSpaceIndex+1, colonIndex-prevSpaceIndex-1));
                output.erase(prevSpaceIndex+1, colonIndex-prevSpaceIndex);
            }

        }

    }

    output.erase(std::remove(output.begin(), output.end(), '~'), output.end());

    _justDialogue = output;


}

std::string SubtitleItem::getDialogue(bool keepHTML = 0, bool doNotIgnoreNonDialogues = 0,  bool doNotRemoveSpeakerNames = 0)
{
	if(_justDialogue.empty())
		extractInfo(keepHTML, doNotIgnoreNonDialogues, doNotRemoveSpeakerNames);

	return _justDialogue;
}
int SubtitleItem::getSpeakerCount() const
{
	return _speakerCount;
}
int SubtitleItem::getNonDialogueCount() const
{
	return _nonDialogueCount;
}
std::vector<std::string> SubtitleItem::getSpeakerNames()
{
	return _speaker;
}
std::vector<std::string> SubtitleItem::getNonDialogueWords()
{
	return _nonDialogue;
}

