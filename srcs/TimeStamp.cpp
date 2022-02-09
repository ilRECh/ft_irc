//
// Created by Rasul on 17.01.2022.
//

#include "TimeStamp.hpp"

TimeStamp::TimeStamp()
	: _base_time(time(0)){}
TimeStamp::TimeStamp(TimeStamp const & oth)
	: _base_time(oth._base_time){}
time_t TimeStamp::getBaseTime() const {
	return _base_time;
}

time_t TimeStamp::getCurrTime() {
	return time(0);
}

bool TimeStamp::hasTimePassed(time_t secunds) const {
	if (difftime(time(0), _base_time) >= secunds)
		return true;
	return false;
}

bool TimeStamp::hasTimePassed(time_t base, time_t secunds){
	if (difftime(time(0), base) >= secunds)
		return true;
	return false;
}

double TimeStamp::diffTimeCmp() const {
	return difftime(time(0), _base_time);
}

double TimeStamp::diffTimeCmp(const time_t& baseTime, const time_t& newTime) {
	return difftime(newTime, baseTime);
}

std::string TimeStamp::getTimeStrCurrent() {
	time_t 	_curr_time;
	_curr_time = time(0);
	return setBrackets(ctime(&_curr_time));
}

std::string TimeStamp::getTimeStrStarted() const {
	return setBrackets(ctime(&_base_time));
}

std::string TimeStamp::getTimeStrOfTimeT(time_t of_this) {
	return setBrackets(ctime(&of_this));
}

void TimeStamp::updateBaseTime() {
	_base_time = time(0);
}

TimeStamp &TimeStamp::operator=(const TimeStamp &oth) {
	_base_time = oth._base_time;
	return *this;
}

bool TimeStamp::operator==(const TimeStamp &oth) const {
	return _base_time == oth._base_time;
}
bool TimeStamp::operatornot_eq(const TimeStamp &oth) const {
	return _base_time not_eq oth._base_time;
}
bool TimeStamp::operator>(const TimeStamp &oth) const {
	return _base_time > oth._base_time;
}
bool TimeStamp::operator>=(const TimeStamp &oth) const {
	return _base_time >= oth._base_time;
}
bool TimeStamp::operator<(const TimeStamp &oth) const {
	return _base_time < oth._base_time;
}
bool TimeStamp::operator<=(const TimeStamp &oth) const {
	return _base_time <= oth._base_time;
}

std::string TimeStamp::setBrackets(std::string stamp){
	stamp.insert(0, "[");
	*(stamp.end() - 1) = ']';
	return stamp;
}

