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
        delete this;
    }
}

void ReferencedResource::reference() {
    _refcounter++;
}
