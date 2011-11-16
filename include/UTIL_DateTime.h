//
// Writen by Ant-ON, 2010
//
// email: prozanton@gmail.com
//

#ifndef UTIL_DATATIME_H 
#define UTIL_DATATIME_H

#include <qstring.h>
#include <qdatetime.h>

class UTIL_DateTime : public QObject
{
    Q_OBJECT
public:
	UTIL_DateTime(QObject* parent=0, const char* name=0);
	~UTIL_DateTime();
	
	enum DateFormat
    {
        MM_DD_YYYY,
        YYYY_MM_DD,
        DD_MM_YYYY
	};
	
	enum TimeFormat
    {
		TIME_12,
		TIME_24	
	};
	
	enum DateAccuracy
    {
	};
	
	enum TimeAccuracy
    {
	};	
	
	static QString dateToString(QDate const&, DateAccuracy);
	static QString dateToString(QDate const&, DateFormat, DateAccuracy);
	QDateTime getCurrentUTC();
	static DateFormat getDateFormat();
	void getDateTimeFormat();
	bool getLocalTimeZone(int&, int&, int&, double&, QString&, QString&);
	static QString getMonthName(int);
	static QString getMonthShortName(int);
	static TimeFormat getTimeFormat();
	QString getTZRuleFromDstRule(QString const&);
	static QString getWeekdayName(int);
	bool isDateTimeChangeAllowed();
	static bool setDateFormat(DateFormat);
	static bool setTimeFormat(TimeFormat);
	void setTimeZoneEnv();
	static QString timeToString(QTime const&, TimeAccuracy);
	static QString timeToString(QTime const&, TimeFormat, TimeAccuracy);
	QString toString(QDate const&);
	QString toString(QTime const&);
	void updateTimeZoneEnv();
	
private slots:
	void slotFormatChanged(QCString const&, QArray<char> const&);

private:
	uint fix[10];
};

#endif
