#pragma once
#include <vector>
#include "SubtitleWord.h"

class SubtitleItem
{
private:
	long int _startTime; //in milliseconds
	long int _endTime;
	std::string _text;  // actual line, as present in subtitle file
	long int timeMSec(std::string value);

	std::string _startTimeString;
    std::string _endTimeString;
    bool _ignore;
	std::string _justDialogue;
	int _speakerCount;
	std::vector<std::string> _speaker;
	int _nonDialogueCount;
	std::vector<std::string> _nonDialogue;
    int _styleTagCount;
    std::vector<std::string> _styleTag;
	void extractInfo(bool keepHTML, bool doNotIgnoreNonDialogues,  bool doNotRemoveSpeakerNames);
public:
	long int getStartTime() const;
	long int getEndTime() const;
	std::string getText() const;

	std::string getStartTimeString() const;
    std::string getEndTimeString() const;
    bool getIgnoreStatus() const;
    std::string getDialogue(bool keepHTML, bool doNotIgnoreNonDialogues, bool doNotRemoveSpeakerNames);
	int getSpeakerCount() const;
	int getNonDialogueCount() const;
    int getStyleTagCount() const;
	std::vector<std::string> getSpeakerNames();
	std::vector<std::string> getNonDialogueWords();
    std::vector<std::string> getStyleTags();





    void setStartTime(long int startTime);
	void setEndTime(long int endTime);
	void setText(std::string text);

	SubtitleItem(void);
	SubtitleItem(int startTime,int endTime,std::string text);
	SubtitleItem(std::string startTime,std::string endTime, std::string text);
	SubtitleItem(std::string startTime,std::string endTime, std::string text, bool ignore,
			std::string justDialogue, int speakerCount, int nonDialogueCount, int styleTagCount,
			std::vector<std::string> speaker, std::vector<std::string> nonDialogue, std::vector<std::string> styleTags);
	~SubtitleItem(void);
};

