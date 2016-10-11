//
// Created by rot on 10/10/16.
//

#ifndef __UONEWCLIENT_ERRORS_H
#define __UONEWCLIENT_ERRORS_H

#include <exception>

class FileError : public std::exception {
public:
    FileError(const char *msg) noexcept;
    FileError(const FileError& e) noexcept;
    FileError& operator=(const FileError& e) noexcept;
    virtual ~FileError() noexcept;
    const char* what() const noexcept;
private:
    char * _msg;
};

#endif //__UONEWCLIENT_ERRORS_H
