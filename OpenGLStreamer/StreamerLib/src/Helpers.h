/**************************************************************************
**   Author: Oleksiy Kasilov, bbv Software Services AG
**   Date:   10/23/2015
**   Year:   2015
**************************************************************************/

#ifndef HELPERS
#define HELPERS

#include <QtGlobal>

#include <cassert>

#define STRINGIFY(STR) #STR

namespace helper
{
    template<typename T>
    struct MethodTraits;

    template<class Class, typename Return, typename ... Args>
    struct MethodTraits<Return (Class::*)(Args...)>
    {
       using ClassType = Class;
       using ReturnType = Return;
       using MethodPtrType = Return (Class::*)(Args ...);
       using ParameterType = std::tuple<Args ...>;
       using Arity = std::tuple_size<ParameterType>;
    };

    template<std::size_t...S> struct seq
    {};

    template<std::size_t N, std::size_t ...S> struct gens : gens <N-1, N-1, S...>
    {};

    template<std::size_t ...S> struct gens<0, S...>
    {
       typedef seq<S...> type;
    };

    quint16 encodeCOB(const quint8 *srcBuf, quint16 srcLen, quint8 *destBuf);
    quint16 decodeCOB(const quint8 *srcBuf, quint16 srcLen, quint8 *destBuf);
}

#endif // HELPERS

