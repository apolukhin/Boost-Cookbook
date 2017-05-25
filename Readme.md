Boost C++ Application Development Cookbook
===================================
This repository contains all the code examples from the **[Boost C++ Application Development Cookbook](http://www.packtpub.com/boost-cplusplus-application-development-cookbook/book)** `(ISBN: 9781849514880)`, [Packt Publishing](http://www.packtpub.com), by Antony Polukhin.

[Compile and Run Examples Online](http://apolukhin.github.io/Boost-Cookbook-4880OS/).

### Testing
Second edition: [![Build Status](https://travis-ci.org/apolukhin/Boost-Cookbook-4880OS.svg?branch=second_edition)](https://travis-ci.org/apolukhin/Boost-Cookbook-4880OS) [![Build status](https://ci.appveyor.com/api/projects/status/github/apolukhin/boost-cookbook-4880os?branch=second_edition&svg=true)](https://ci.appveyor.com/project/apolukhin/boost-cookbook-4880os/branch/second_edition) [![Coverage Status](https://coveralls.io/repos/github/apolukhin/Boost-Cookbook-4880OS/badge.svg?branch=second_edition)](https://coveralls.io/github/apolukhin/Boost-Cookbook-4880OS?branch=second_edition) [![codecov.io](https://codecov.io/github/apolukhin/Boost-Cookbook-4880OS/coverage.svg?branch=second_edition)](https://codecov.io/github/apolukhin/Boost-Cookbook-4880OS?branch=second_edition)

First edition: [![Build Status](https://travis-ci.org/apolukhin/Boost-Cookbook-4880OS.svg?branch=first_edition)](https://travis-ci.org/apolukhin/Boost-Cookbook-4880OS) [![Coverage Status](https://coveralls.io/repos/github/apolukhin/Boost-Cookbook-4880OS/badge.svg?branch=first_edition)](https://coveralls.io/github/apolukhin/Boost-Cookbook-4880OS?branch=first_edition)

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
* Chapter 10 "Detecting RTTI support" - add Boost.TypeIndex example AND Sync code
* Chapter07 Note about boost::string_ref(string&&) and boost::string_view
* How about describing boost::future?
* Coroutine interface changed in Boost 1.56
* Filesystem is accepted into the Standard
* RCU example using atomics?
* sync code and book
* Fix introduction in "Chapter09. Getting the benefits of single-linked list and memory pool"
* Boost.DLL examples
* flat containers were proposed for C++17
* Update this README.md with a link to second edition of the book

Done:
* Optional and Variant now understand rvalue references
* add a note to the book about source code availability at github
* Variant is proposed for C++17. Highlight the differences.
* Boost will have an unique_ptr in 1.58
* LexicalCast now has a try_lexical_convert method
* add *_pointer_cast examples?
* describe in depth changes from 135a24926a1d084e76f8f527deeee6236274e496

