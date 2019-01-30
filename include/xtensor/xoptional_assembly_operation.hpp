/***************************************************************************
* Copyright (c) 2016, Johan Mabille, Sylvain Corlay, Wolf Vollprecht and   *
* Martin Renou                                                             *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XOPTIONAL_ASSEMBLY_OPERATION_HPP
#define XOPTIONAL_ASSEMBLY_OPERATION_HPP

#include "xoperation.hpp"
#include "xoptional_assembly.hpp"
#include "xoptional_assembly.hpp"

namespace xt
{
    namespace detail
    {
        template <class T>
        struct is_optional_assembly : std::false_type
        {
        };

        template <class VE, class FE>
        struct is_optional_assembly<xoptional_assembly<VE, FE>> : std::true_type
        {
        };

        template <class VEC, class FEC>
        struct is_optional_assembly<xoptional_assembly_adaptor<VEC, FEC>> : std::true_type
        {
        };

        struct fillna_functor
        {
            template <class A, class T>
            inline A operator()(const A& a, const T& value) const
            {
                using value_type = typename std::decay_t<A>::value_type;
                if (!a.has_value())
                {
                    // std::cout << "a " << a << " value " << value << std::endl;
                    // std::cout << "return " << A(value_type(value), true) << std::endl;
                    return A(value, true);
                }
                // std::cout << "TEST" << std::endl;
                return a;
            }
        };
    }

    template <class E, class T, XTL_REQUIRES(detail::is_optional_assembly<std::decay_t<E>>)>
    inline auto fillna(E&& e, T&& value)
    {
        return detail::make_xfunction<detail::fillna_functor>(std::forward<E>(e), std::forward<T>(value));
    }
}

#endif
