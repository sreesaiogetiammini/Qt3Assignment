#ifndef AGEVALIDATOR_H
#define AGEVALIDATOR_H

#include <QValidator>
#include <QObject>
#include <QDate>

class AgeValidator : public QValidator
{
public:
    AgeValidator(int minAge, QObject *parent = nullptr) : QValidator(parent), m_minAge(minAge) {}

    QValidator::State validate(QString &input, int &pos) const override
    {
        Q_UNUSED(pos);

        // Parse the input date
        QDate inputDate = QDate::fromString(input, "dd/MM/yyyy");

        // Check if the input date is valid
        if (!inputDate.isValid()) {
            return QValidator::Invalid;
        }

        // Calculate the age in years
        int age = inputDate.daysTo(QDate::currentDate()) / 365;

        // Check if the age is greater than or equal to the minimum age
        if (age >= m_minAge) {
            return QValidator::Acceptable;
        } else {
            return QValidator::Intermediate;
        }
    }

private:
    int m_minAge;
};

#endif // AGEVALIDATOR_H
