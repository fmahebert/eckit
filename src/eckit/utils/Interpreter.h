/*
 * (C) Copyright 1996-2013 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */
/// @author Piotr Kuchta, May 2015

#ifndef Interpreter_H
#define Interpreter_H

#include "eckit/parser/Request.h"
#include <list>

namespace eckit {

class ExecutionContext;

class Interpreter {
public:
    static Values eval(const Request, ExecutionContext&);

private:
    static Values evalList(const Request, ExecutionContext&);
    static Values evalRequests(const Request, ExecutionContext&);
    static Values evalLet(const Request, ExecutionContext&);
    static Values defineFunction(const Request, ExecutionContext&);
    static Values evalFunction(const Request, const Request, ExecutionContext&);
    static Values evalNative(const Request object, const Request request, ExecutionContext&);
    static Request evalAttributes(const Request, ExecutionContext&);
};

} // namespace eckit

#endif
