#include "SQLiteException.hpp"

BadDrop::BadDrop(char *msg) : message(msg) {}

const char *BadDrop::what() const noexcept {
    return message;
}

BadPrepare::BadPrepare(char *msg) : message(msg) {}

const char *BadPrepare::what() const noexcept {
    return message;
}

BadEdit::BadEdit(char *msg) : message(msg) {}

const char *BadEdit::what() const noexcept {
    return message;
}