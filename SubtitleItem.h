#pragma once
#include <vector>
#include "SubtitleWord.h"

class SubtitleItem
{
private:
	long int _startTime; //in milliseconds
	long int _endTime;
	std::string _text;
	long int timeMSec(std::string value);

	bool _ignore;
	std::string _justDialogue;
	int _speakerCount;
	std::vector<std::string> _speaker;
	int _nonDialogueCount;
	std::vector<std::string> _nonDialogue;
	void extractInfo();
public:
	long int getStartTime() const;
	long int getEndTime() const;
	std::string getText() const;

	bool getIgnoreStatus() const;
	std::string getDialogue();
	int getSpeakerCount() const;
	int getNonDialogueCount() const;
	std::vector<std::string> getSpeakerNames();
	std::vector<std::string> getNonDialogueWords();




	void setStartTime(long int startTime);
	void setEndTime(long int endTime);
	void setText(std::string text);

	SubtitleItem(void);
	SubtitleItem(int startTime,int endTime,std::string text);
	SubtitleItem(std::string startTime,std::string endTime, std::string text);
	SubtitleItem(std::string startTime,std::string endTime, std::string text, bool ignore,
			std::string justDialogue, int speakerCount, int nonDialogueCount,
			std::vector<std::string> speaker, std::vector<std::string> nonDialogue);
	~SubtitleItem(void);
};

