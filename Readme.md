Boost C++ Application Development Cookbook,
Second Edition
===================================
This repository contains all the code examples from the **[Boost C++ Application Development Cookbook, Second Edition](https://www.packtpub.com/application-development/boost-c-application-development-cookbook-second-edition)** `(ISBN: 9781787282247)`, [Packt Publishing](http://www.packtpub.com), by Antony Polukhin.

[Compile and Run Examples Online](http://apolukhin.github.io/Boost-Cookbook/).

[![Build Status](https://travis-ci.org/apolukhin/Boost-Cookbook.svg?branch=second_edition)](https://travis-ci.org/apolukhin/Boost-Cookbook) [![Build status](https://ci.appveyor.com/api/projects/status/github/apolukhin/boost-cookbook?branch=second_edition&svg=true)](https://ci.appveyor.com/project/apolukhin/boost-cookbook/branch/second_edition) [![Coverage Status](https://coveralls.io/repos/github/apolukhin/Boost-Cookbook/badge.svg?branch=second_edition)](https://coveralls.io/github/apolukhin/Boost-Cookbook?branch=second_edition) [![codecov.io](https://codecov.io/github/apolukhin/Boost-Cookbook/coverage.svg?branch=second_edition)](https://codecov.io/github/apolukhin/Boost-Cookbook?branch=second_edition)

### Content
This repository contatins project files for QtCreator IDE. `BoostBook.pro` - is the main project file.
See config.txt file for setupping platform specific flags.

QtCreator's project files are very simple and it's easy to understand what is required for example
compilation by just opening the '.pro' file with any text editor.

All source code is distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


### Coding style
Some of the C++ coding styles are broken to fit better cookbook educational format:

* Headers are not always included in the beginning of source and header files.

This is done in attempt to show in which header which classes and functions
are defined. Another goal of doing so, is to avoid errors while copying parts
of code to book (it is simpler and safer to copy required peace of code at
once, instead of gathering together headers and code parts all across the project).

* Our own classes are declared in global namespace (instead of separate namespace).

This is done to reduce amount of unrequired text in book.

* Usually no aliases for namespaces used and usually no `using namespace` used.

This is done for your simplicity. You may open any recipe, start it from the
middle of 'How to do it' part and see a working part of code that does not
require searching all around the chapter for an answer 'In what namespace is
this class defined?'.



### Thanks
Thanks to Heather Gopsill from Packt Publishing for giving a permission to make sources publicly available.
Thanks to Nitin Dasan from Packt Publishing for getting all the necessary approvals for making sources publicly available for the second edition of the book.

### Notes for book update
For year 2022+ :
* Separate chapters on Graphs/Testing/Image processinggit
* Remove description of all the Boost libraries that were added into C++11 (including Boost.Move)
* More recipes for unordered containers
* Move string_view into the first chapter
* Pimpl example using ...?
* Boost.Range recipes
* boost::allocate_shared ?
* Dig into the boost::function and statefull allocator support?
* Boost.Convert ecamples
* Add a very simple example on regexes.
* MPL11 example (Something like "Finding the sequential layout ordering of N different types that would minimize padding due to
alignment between them").
* Add an example on stateful allocators in Boost.
* Add an example on Boost.PolyCollection.




