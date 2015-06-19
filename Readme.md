<center>
master branch unit test status:

Linux: [![Build Status](https://ci.nedprod.com/job/Boost.Spinlock%20Test%20Linux%20GCC%204.8/badge/icon)](https://ci.nedprod.com/job/Boost.Spinlock%20Test%20Linux%20GCC%204.8/) Windows: [![Build Status](https://ci.nedprod.com/job/Boost.Spinlock%20Test%20Win8%20VS2014/badge/icon)](https://ci.nedprod.com/job/Boost.Spinlock%20Test%20Win8%20VS2014/) Coverage: [![Coverage Status](https://coveralls.io/repos/ned14/boost.spinlock/badge.svg?branch=master)](https://coveralls.io/r/ned14/boost.spinlock?branch=master)

Documentation: https://ci.nedprod.com/job/Boost.Spinlock%20Test%20Linux%20GCC%204.8/doxygen/annotated.html

Before monad<T> review:
 - [x] Add max opcodes constexpr unit testing
 - [x] Implement then(), bind(), map(), unwrap()
 - [x] Get then(), bind(), map() and unwrap() being constexpr unit tested
 - [x] Add CI build step for publishing single drop in header files. Script needs to include only local includes, not system includes.
 - [x] Add wandbox single click tryout http://melpon.org/wandbox/permlink/cnZM5KRNpjErXrPH
 
</center>
