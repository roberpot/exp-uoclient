//
// Created by rot on 10/10/16.
//

#include <cstring>
#include "errors.h"

FileError::FileError(const char *msg) noexcept {
    _msg = new char[strlen(msg) + 1];
    strcpy(_msg, msg);
}

FileError::FileError(const FileError& e) noexcept {
    _msg = new char[strlen(e._msg) + 1];
    strcpy(_msg, e._msg);
}

FileError& FileError::operator=(const FileError& e) noexcept {
    if (_msg) {
        delete _msg;
    }
    _msg = new char[strlen(e._msg) + 1];
    strcpy(_msg, e._msg);
    return *this;
}

FileError::~FileError() noexcept {
    if (_msg) {
        delete _msg;
    }
}

const char* FileError::what() const noexcept {
    return _msg;
}