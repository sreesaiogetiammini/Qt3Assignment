#ifndef PASSWORDVALIDATOR_H
#define PASSWORDVALIDATOR_H

#include <QValidator>
#include <QObject>


class PasswordValidator : public QValidator
{
public:
    PasswordValidator(QObject* parent = nullptr) : QValidator(parent) {}

    State validate(QString& input, int& pos) const override
    {
        // Check if input contains at least one uppercase, one lowercase, and one digit
        bool hasUpper = false;
        bool hasLower = false;
        bool hasDigit = false;
        for (int i = 0; i < input.length(); i++)
        {
            if (input.at(i).isUpper())
                hasUpper = true;
            if (input.at(i).isLower())
                hasLower = true;
            if (input.at(i).isDigit())
                hasDigit = true;
        }

        if (!hasUpper || !hasLower || !hasDigit)
            return Intermediate;

        // Check if input has a minimum length of 8 characters
        if (input.length() < 8)
            return Intermediate;

        return Acceptable;
    }
};
#endif // PASSWORDVALIDATOR_H
