//
// Created by ivan on 01.07.23.
//

#ifndef DATASERVICE_SQLITEEXCEPTION_HPP
#define DATASERVICE_SQLITEEXCEPTION_HPP

#include <exception>

class BadDrop : public std::exception {
private:
    char *message;
public:
    BadDrop() = default;

    BadDrop(char *msg);

    virtual const char *what() const noexcept override;
};

class BadPrepare : public std::exception {
private:
    char *message;
public:
    BadPrepare() = default;

    BadPrepare(char *msg);

    virtual const char *what() const noexcept override;
};

class BadEdit : public std::exception {
private:
    char *message;
public:
    BadEdit() = default;

    BadEdit(char *msg);

    virtual const char *what() const noexcept override;
};

#endif //DATASERVICE_SQLITEEXCEPTION_HPP
