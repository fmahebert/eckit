/*
 * (C) Copyright 1996-2013 ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#include <sstream>

#include "eckit/maths/Exp.h"
#include "eckit/maths/Value.h"

namespace eckit {
namespace maths {

//--------------------------------------------------------------------------------------------

Expr::Expr()
{}

Expr::Expr(const args_t &args) :
    args_(args)
{}

Expr::~Expr()
{}

ValPtr Expr::eval()
{
    context_t ctx;
    return optimise()->evaluate(ctx);
}

ValPtr Expr::eval( ExpPtr e )
{
    context_t ctx;
    ctx.push_back(e);
    ValPtr res = optimise()->evaluate(ctx);
    ASSERT( ctx.empty() );
    return res;
}

ValPtr Expr::eval(  ExpPtr a, ExpPtr b )
{
    context_t ctx;
    ctx.push_back(a);
    ctx.push_back(b);
    ValPtr res = optimise()->evaluate(ctx);
    ASSERT( ctx.empty() );
    return res;
}

ValPtr Expr::eval( const args_t& args) {
    context_t ctx;
    std::copy(args.begin(), args.end(), std::back_inserter(ctx));
    ValPtr res = optimise()->evaluate(ctx);
    ASSERT( ctx.empty() );
    return res;
}


ExpPtr Expr::param( const size_t& i, context_t* ctx ) const
{
    ASSERT( i < args_.size() );
    ASSERT( args_[i] );

    if( ctx && Undef::is(args_[i]) )
    {
        ASSERT( !ctx->empty() );
        ExpPtr e = ctx->front();
        ctx->pop_front();
        return e;
    }

    return args_[i];
}

void Expr::param(const size_t &i, ExpPtr p)
{
    ASSERT( i < args_.size() );
    ASSERT( p );
    if( p != args_[i] )
        args_[i] = p;
}

string Expr::str() const
{
    std::ostringstream os;
    print(os);
    return os.str();
}

//--------------------------------------------------------------------------------------------

Undef::Undef() : Expr()
{
}

Undef::~Undef()
{
}

ValPtr Undef::evaluate( context_t& ctx )
{
    return boost::static_pointer_cast<Value>( shared_from_this() );
}

ExpPtr Undef::clone()
{
    return undef();
}

ExpPtr undef()
{
    return ExpPtr( new Undef() );
}

//--------------------------------------------------------------------------------------------

} // namespace maths
} // namespace eckit
