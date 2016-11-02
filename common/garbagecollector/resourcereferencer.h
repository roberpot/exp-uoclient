//
// Created by rot on 27/10/16.
//

#ifndef __UONEWCLIENT_RESOURCEREFERENCER_H
#define __UONEWCLIENT_RESOURCEREFERENCER_H

class ReferencedResource {
public:
    ReferencedResource();
    virtual ~ReferencedResource() {};
    void dereference();
    void reference();
    virtual void counter_ends();
    virtual void counter_starts();
private:
    unsigned int _refcounter;
};


class AutoRemovedResource : public ReferencedResource {
public:
    AutoRemovedResource() {};
    virtual ~AutoRemovedResource() {};
    void counter_ends();
};


template<class T>
class ResourceRef {
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
    inline T * get() { return _t; }
    inline T * operator()() { return _t; }
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
