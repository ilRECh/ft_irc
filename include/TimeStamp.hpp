//
// Created by Rasul on 17.01.2022.
//

#ifndef FT_IRC_TIMESTAMP_H
#define FT_IRC_TIMESTAMP_H
#include <time.h>
#include <string>
#include <sstream>

//using std::string;

class TimeStamp {
private:
	time_t 	_base_time;
public:
	TimeStamp();
	TimeStamp(TimeStamp const & oth);
// Вернет время когда был создан этот объект
	time_t
	getBaseTime() const;
// Вернет текущее время в
	static time_t
	getCurrTime();
// прошло ли время для текущего объекта ?
	bool
	hasTimePassed(time_t secunds) const;
// прошло ли время ?
	static bool
	hasTimePassed(time_t base, time_t secunds);
// Получаем текущее время в string
	static std::string
	getTimeStrCurrent();
// Получаем время когда создался этот объект в string
	std::string
	getTimeStrStarted() const;
// Получаем время когда этого (time_t of_this) в string
	static std::string
	getTimeStrOfTimeT(time_t of_this);
// Обновляем базовое время
	void
	updateBaseTime();
	
private:
// Вернет разницу в секундах c момента запуска создания этого объекта
	double
	diffTimeCmp() const;
// Вернет разницу в секундах между двумя (time_T или int)
	static double
	diffTimeCmp(const time_t&, const time_t&);

	static std::string
	setBrackets(std::string stamp);

public:
	TimeStamp		&operator=(TimeStamp const & oth);
	bool			operator==(TimeStamp const & oth) const;
	bool			operator!=(TimeStamp const & oth) const;
	bool			operator>(TimeStamp const & oth) const;
	bool			operator>=(TimeStamp const & oth) const;
	bool			operator<(TimeStamp const & oth) const;
	bool			operator<=(TimeStamp const & oth) const;
};

#endif //FT_IRC_TIMESTAMP_H
