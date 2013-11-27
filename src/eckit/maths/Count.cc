/*
 * (C) Copyright 1996-2013 ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#include "eckit/maths/Count.h"
#include "eckit/maths/Scalar.h"

namespace eckit {
namespace maths {

//--------------------------------------------------------------------------------------------

Count::Count(ExpPtr e) : Function()
{
    args_.push_back(e);
}

string Count::returnSignature() const
{
    return Scalar::sig();
}

ExpPtr Count::evaluate( Scope &ctx ) const
{
    return maths::scalar( param(0, ctx)->arity() )->as<Value>();
}

ExpPtr Count::cloneWith(args_t &a) const {
    NOTIMP;
}

void Count::asCode(std::ostream&o) const
{
    o << "maths::count("; printArgs(o); o << ")";
}

//--------------------------------------------------------------------------------------------

ExpPtr count( ExpPtr e )
{
    return ExpPtr( new Count(e) );
}

//--------------------------------------------------------------------------------------------

} // namespace maths
} // namespace eckit
