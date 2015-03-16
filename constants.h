#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QMap>
#include <QString>

class Constants
{
public:
    static QMap<int, QString> getWeekDays()
    {
        QMap<int, QString> weekDays;
        weekDays.insert(0, "Monday");
        weekDays.insert(1, "Thusday");
        weekDays.insert(2, "Wednesday");
        weekDays.insert(3, "Thursday");
        weekDays.insert(4, "Friday");
        weekDays.insert(5, "Saturday");
        weekDays.insert(6, "Sunday");

        return weekDays;
    }
};


#endif // CONSTANTS_H
