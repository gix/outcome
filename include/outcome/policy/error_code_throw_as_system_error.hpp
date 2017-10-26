/* Policies for result and outcome
(C) 2017 Niall Douglas <http://www.nedproductions.biz/> (59 commits)
File Created: Oct 2017


Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License in the accompanying file
Licence.txt or at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.


Distributed under the Boost Software License, Version 1.0.
(See accompanying file Licence.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef OUTCOME_POLICY_ERROR_CODE_THROW_AS_SYSTEM_ERROR_HPP
#define OUTCOME_POLICY_ERROR_CODE_THROW_AS_SYSTEM_ERROR_HPP

#include "../bad_access.hpp"
#include "detail/common.hpp"

#include <system_error>

OUTCOME_V2_NAMESPACE_EXPORT_BEGIN

namespace policy
{
  //! Override to define what the policies which throw a system error with payload ought to do for some particular `result`.
  template <class T> constexpr inline void throw_as_system_error_with_payload(const T * /*unused*/) { static_assert(!std::is_same<T, T>::value, "To use the *_throw_as_system_error_with_payload policy, you must define a throw_as_system_error_with_payload() free function to say how to handle the payload"); }
  namespace detail
  {
    template <bool has_error_payload, class T, class EC> struct throw_result_as_system_error
    {
      template <class Impl> throw_result_as_system_error(const Impl *self)
      {
        auto *_self = static_cast<const result<T, EC> *>(self);
        OUTCOME_THROW_EXCEPTION(std::system_error(policy::error_code(_self->error())));
      }
      template <class Impl> throw_result_as_system_error(Impl *self)
      {
        auto *_self = static_cast<result<T, EC> *>(self);
        OUTCOME_THROW_EXCEPTION(std::system_error(policy::error_code(_self->error())));
      }
    };
    template <class T, class EC> struct throw_result_as_system_error<true, T, EC>
    {
      template <class Impl> throw_result_as_system_error(Impl *self)
      {
        auto *_self = static_cast<result<T, EC> *>(self);
        throw_as_system_error_with_payload(_self);
      }
      template <class Impl> throw_result_as_system_error(const Impl *self)
      {
        auto *_self = static_cast<const result<T, EC> *>(self);
        throw_as_system_error_with_payload(_self);
      }
    };
  }

  /*! Policy interpreting `EC` as a type for which `trait::has_error_code_v<EC>` is true.
  Any wide attempt to access the successful state where there is none causes:

  1. If `trait::has_error_payload_v<EC>` is true, it calls an
  ADL discovered free function `throw_as_system_error_with_payload(&result|&outcome)`.
  2. If `trait::has_error_payload_v<EC>` is false, it calls `OUTCOME_THROW_EXCEPTION(std::system_error(policy::error_code(.error())))`
  */
  template <class T, class EC, class E> struct error_code_throw_as_system_error;
  template <class T, class EC> struct error_code_throw_as_system_error<T, EC, void> : detail::base
  {
    /*! Performs a wide check of state, used in the value() functions.
    \effects If result does not have a value, if it has an error it throws a `std::system_error(error())`, else it throws `bad_result_access`.
    */
    template <class Impl> static constexpr void wide_value_check(Impl *self)
    {
      if((self->_state._status & OUTCOME_V2_NAMESPACE::detail::status_have_value) == 0)
      {
        if((self->_state._status & OUTCOME_V2_NAMESPACE::detail::status_have_error) != 0)
        {
          detail::throw_result_as_system_error<trait::has_error_payload_v<EC>, T, EC>{self};
        }
        OUTCOME_THROW_EXCEPTION(bad_result_access("no value"));
      }
    }
    /*! Performs a wide check of state, used in the error() functions
    \effects If result does not have an error, it throws `bad_result_access`.
    */
    template <class Impl> static constexpr void wide_error_check(Impl *self)
    {
      if((self->_state._status & OUTCOME_V2_NAMESPACE::detail::status_have_error) == 0)
      {
        OUTCOME_THROW_EXCEPTION(bad_result_access("no error"));
      }
    }
  };
}  // namespace policy

OUTCOME_V2_NAMESPACE_END

#endif
