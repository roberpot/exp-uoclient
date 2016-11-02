//
// Created by rot on 27/10/16.
//

#include "resourcereferencer.h"

ReferencedResource::ReferencedResource() {
    _refcounter = 0;
}

void ReferencedResource::dereference() {
    _refcounter--;
    if (!_refcounter) {
        counter_ends();
    }
}

void ReferencedResource::reference() {
    _refcounter++;
    if (_refcounter == 1) {
        counter_starts();
    }
}

void ReferencedResource::counter_ends() {

}

void ReferencedResource::counter_starts() {

}

void AutoRemovedResource::counter_ends() {
    delete this;
}