//
// Created by rot on 27/10/16.
//

#ifndef __UONEWCLIENT_RESOURCEREFERENCER_H
#define __UONEWCLIENT_RESOURCEREFERENCER_H

class ReferencedResource {
public:
    friend class ResourceRef;
    ReferencedResource();
private:
    void dereference();
    void reference();
    unsigned int _refcounter;
};

template<class T>
class ResourceRef<T> {
public:
    ResourceRef() : _t(0) {};
    ResourceRef(T * t) {
        if (_t == t) {
            return;
        }
        _t = t;
        if (_t) {
            _t->reference();
        }
    }
    ResourceRef(const ResourceRef & r) {
        if (this == &r) {
            return;
        }
        _t = r._t;
        if (_t) {
            _t->reference();
        }
    }
    ResourceRef & operator=(ResourceRef r) {
        if ((this == &r) || (_t == r._t)) {
            return *this;
        }
        if (_t) {
            _t->dereference();
        }
        _t = r._t;
        if (_t) {
            _t->reference();
        }
        return *this;
    }
    void dereference() {
        if (_t) {
            _t->dereference();
        }
        _t = 0;
    }
    ~ResourceRef() {
        if (_t) {
            _t->dereference();
        }
    }
private:
    T * _t;
};

#endif //__UONEWCLIENT_RESOURCEREFERENCER_H
